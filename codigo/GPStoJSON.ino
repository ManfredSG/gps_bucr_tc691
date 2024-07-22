#include <TinyGPS++.h> // Libreria para extraer datos del GPS
#include <SoftwareSerial.h> 
#include <ArduinoJson.h> // Libreria para crear y manejar archivos JSON

TinyGPSPlus gpsModule;
SoftwareSerial GPS(4, 3); // RX, TX para GPS

void setup()
{
  Serial.begin(9600);
  GPS.begin(9600);
}

void loop()
{
  while (GPS.available() > 0)
    if (gpsModule.encode(GPS.read())) // Actualiza 'gpsModule' con la información del GPS
      gpsData();

  // Revisar si el GPS no responde
  if (millis() > 5000 && gpsModule.charsProcessed() < 10)
  {
    Serial.println("Error: GPS no responde");
    while (true);
  }
}

void gpsData()
{
  StaticJsonDocument<256> JSON; // JSON de 256 bytes
////////////LOCALIZACIÓN////////////
  if (gpsModule.location.isValid())
  {
    JSON["latitud"] = gpsModule.location.lat();
    JSON["longitud"] = gpsModule.location.lng();
    JSON["altitud"] = gpsModule.altitude.meters();
  }
  else
  {
    JSON["localizacion"] = "No disponible";
  }
////////////FECHA////////////
  if (gpsModule.date.isValid())
  {
    char fecha[11];
    sprintf(fecha, "%02d/%02d/%04d", gpsModule.date.day(), gpsModule.date.month(), gpsModule.date.year());
    JSON["fecha"] = fecha;
  }
  else
  {
    JSON["fecha"] = "No disponible";
  }
////////////HORA////////////
  if (gpsModule.time.isValid())
  {
    char hora[13];
    sprintf(hora, "%02d:%02d:%02d.%02d", gpsModule.time.hour() - 6, gpsModule.time.minute(), gpsModule.time.second(), gpsModule.time.centisecond());
    JSON["hora"] = hora;
  }
  else
  {
    JSON["hora"] = "No disponible";
  }
/////////////////////////////////////////
  serializeJson(JSON, Serial); // Lo envia a Serial Monitor
  Serial.println();
  delay(1000);
}
