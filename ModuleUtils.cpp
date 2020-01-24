#include "ModuleUtils.h"

#include "NTPClient.h"
#include "WiFiUdp.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

Adafruit_BME280 bme;

int const bmeSda = 17;
int const bmeScl = 16;

void ModuleUtils::initialization (int timeOffset) {
  timeClient.begin();
  timeClient.setTimeOffset(timeOffset);
}

long ModuleUtils::currentTime() {
  timeClient.update();
  
  return timeClient.getEpochTime();
}

void ModuleUtils::initializationBme() {
  Wire.begin(bmeSda, bmeScl);

  bool statusBme = bme.begin(0x76, &Wire);
  if (!statusBme) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
}

void ModuleUtils::recordingData() {
  //  Serial.print("Temperature from BME2 = ");
  //  Serial.print(bme.readTemperature());
  //  Serial.println(" *C");
  //
  //  Serial.print("Humidity from BME2 = ");
  //  Serial.print(bme.readHumidity());
  //  Serial.println(" %");
  //
  //  Serial.print("Pressure from BME2 = ");
  //  Serial.print(bme.readPressure() / 100.0F);
  //  Serial.println(" hPa");
}
