#include <TinyGPS++.h> // Librería para extraer datos del GPS
#include <SoftwareSerial.h> // Librería para crear una conexión serial por software
#include <ArduinoJson.h> // Librería para crear y manejar archivos JSON
#include <WiFiEspAT.h> // Librería para manejar comandos AT

// Instancia del módulo GPS
TinyGPSPlus gpsModule;
// Configuración de los pines RX y TX para el GPS
SoftwareSerial GPS(4, 3); // RX, TX para GPS
// Configuración de los pines RX y TX para el ESP8266
SoftwareSerial espSerial(8, 9); // RX, TX para ESP8266

// Constantes para la conexión WiFi y las URLs de las APIs
const char* ssid = "ARCOSWIFI-INII-2G";
const char* password = "Lnrqv6ozs4FEc";
const char* login_url = "https://realtime.bucr.digital/api/operator";
const char* position_url = "https://realtime.bucr.digital/api/position";

// Cliente WiFi para realizar las solicitudes HTTP
WiFiClient client;

// Variables para almacenar las credenciales del operador
String operator_username;
String operator_password;

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios
  GPS.begin(9600); // Inicia la comunicación serial con el módulo GPS
  espSerial.begin(9600); // Inicia la comunicación serial con el módulo ESP8266

  // Inicializa el módulo WiFi
  WiFi.init(espSerial);

  // Verifica si la comunicación con el módulo WiFi falló
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // Detiene el programa si falla la comunicación con el WiFi
  }

  connectToWiFi(); // Llama a la función para conectar a la red WiFi
}

void loop() {
  // Si las credenciales del operador están vacías, solicita las credenciales
  if (operator_username.length() == 0 && operator_password.length() == 0) {
    getLoginCredentials();
  } else {
    // Realiza el login del operador y limpia las variables de credenciales
    loginOperator();
    operator_username = "";
    operator_password = "";
  }

  // Lee los datos del GPS cuando están disponibles
  while (GPS.available() > 0)
    if (gpsModule.encode(GPS.read())) // Actualiza 'gpsModule' con la información del GPS
      gpsData();

  // Verifica si el GPS no responde
  if (millis() > 5000 && gpsModule.charsProcessed() < 10) {
    Serial.println("Error: GPS no responde");
    while (true); // Detiene el programa si el GPS no responde
  }
}

// Función para conectar a la red WiFi
void connectToWiFi() {
  // Intentar conectar a la red WiFi hasta que se logre
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password); // Inicia la conexión WiFi

    unsigned long start = millis();
    // Espera hasta 10 segundos para la conexión WiFi
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
  }

  Serial.println("Connected to WiFi");
}

// Función para solicitar las credenciales del operador
void getLoginCredentials() {
  Serial.println("Waiting for login credentials from Raspberry Pi...");
  while (Serial.available() == 0) {} // Espera a que se reciban las credenciales
  String credentials = Serial.readStringUntil('\n'); // Lee las credenciales
  int commaIndex = credentials.indexOf(',');
  operator_username = credentials.substring(0, commaIndex);
  operator_password = credentials.substring(commaIndex + 1);
  Serial.println("Credentials received: " + operator_username + ", " + operator_password); // Mensaje de depuración
}

// Función para realizar el login del operador
void loginOperator() {
  // Conectar al servidor de la API de login
  if (client.connect(getHost(login_url).c_str(), getPort(login_url))) {
    // Construir el JSON para la solicitud de login
    String json = "{\"username\":\"" + operator_username + "\",\"password\":\"" + operator_password + "\"}";
    // Construir la solicitud HTTP POST
    String request = "POST " + getPath(login_url) + " HTTP/1.1\r\n";
    request += "Host: " + getHost(login_url) + "\r\n";
    request += "Content-Type: application/json\r\n";
    request += "Content-Length: " + String(json.length()) + "\r\n";
    request += "\r\n";
    request += json;

    client.print(request); // Enviar la solicitud al servidor

    // Leer y procesar la respuesta del servidor
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break; // Fin de los encabezados de la respuesta
      }
    }
    String response = client.readString(); // Leer el cuerpo de la respuesta
    Serial.println("Login Response: " + response); // Imprimir la respuesta del servidor

    client.stop(); // Cerrar la conexión
  } else {
    Serial.println("Connection to login API failed"); // Mensaje de error si falla la conexión
  }
}

// Función para extraer y enviar datos del GPS
void gpsData() {
  StaticJsonDocument<256> JSON; // JSON de 256 bytes para almacenar los datos

  // Extraer datos de localización
  if (gpsModule.location.isValid()) {
    JSON["latitud"] = gpsModule.location.lat();
    JSON["longitud"] = gpsModule.location.lng();
    JSON["altitud"] = gpsModule.altitude.meters();
  } else {
    JSON["localizacion"] = "No disponible";
  }

  // Extraer datos de fecha
  if (gpsModule.date.isValid()) {
    char fecha[11];
    sprintf(fecha, "%02d/%02d/%04d", gpsModule.date.day(), gpsModule.date.month(), gpsModule.date.year());
    JSON["fecha"] = fecha;
  } else {
    JSON["fecha"] = "No disponible";
  }

  // Extraer datos de hora
  if (gpsModule.time.isValid()) {
    char hora[13];
    sprintf(hora, "%02d:%02d:%02d.%02d", gpsModule.time.hour() - 6, gpsModule.time.minute(), gpsModule.time.second(), gpsModule.time.centisecond());
    JSON["hora"] = hora;
  } else {
    JSON["hora"] = "No disponible";
  }

  // Serializar el objeto JSON en una cadena
  String json;
  serializeJson(JSON, json);
  Serial.println(json); // Imprimir el JSON en el monitor serial

  // Enviar los datos del GPS a la API
  sendToAPI(position_url, json);
  delay(1000); // Esperar un segundo antes de la siguiente lectura
}

// Función para enviar datos a una API
void sendToAPI(String url, String data) {
  // Conectar al servidor de la API
  if (client.connect(getHost(url).c_str(), getPort(url))) {
    // Construir la solicitud HTTP POST
    String request = "POST " + getPath(url) + " HTTP/1.1\r\n";
    request += "Host: " + getHost(url) + "\r\n";
    request += "Content-Type: application/json\r\n";
    request += "Content-Length: " + String(data.length()) + "\r\n";
    request += "\r\n";
    request += data;

    client.print(request); // Enviar la solicitud al servidor

    // Leer y procesar la respuesta del servidor
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break; // Fin de los encabezados de la respuesta
      }
    }
    String response = client.readString(); // Leer el cuerpo de la respuesta
    Serial.println("API Response: " + response); // Imprimir la respuesta del servidor

    client.stop(); // Cerrar la conexión
  } else {
    Serial.println("Connection to API failed"); // Mensaje de error si falla la conexión
  }
}

// Función para extraer el host de una URL
String getHost(String url) {
  int idx1 = url.indexOf("://") + 3;
  int idx2 = url.indexOf("/", idx1);
  return url.substring(idx1, idx2);
}

// Función para obtener el puerto de una URL
int getPort(String url) {
  if (url.startsWith("https://")) {
    return 443; // Puerto para HTTPS
  } else {
    return 80; // Puerto para HTTP
  }
}

// Función para extraer la ruta de una URL
String getPath(String url) {
  int idx1 = url.indexOf("://") + 3;
  int idx2 = url.indexOf("/", idx1);
  return url.substring(idx2);
}
