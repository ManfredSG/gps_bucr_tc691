código de arduino  para generar el serial en python

#include <SoftwareSerial.h>

SoftwareSerial Dta(4, 3);

void setup() {
  Serial.begin(9600);
  Dta.begin(9600);
}

void loop() {
  // Simula datos de GPS
  float latitude = 37.7749;
  float longitude = -122.4194;

  // Formatea los datos como texto plano
  String data_line = String(latitude, 6) + "," + String(longitude, 6) + "\n";

  // Envía los datos por el puerto serie
  Dta.print(data_line);

  // Espera un minuto antes de enviar el siguiente dato (ajusta según tus necesidades)
  delay(60000);
}

