#include <OneWire.h>
#include <DallasTemperature.h>
  
#define ONE_WIRE_BUS  2 // DATA
#define SENSER_BIT    1 // 精度

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.setResolution(SENSER_BIT);
}

void loop() {
  sensors.requestTemperatures();
  float f = sensors.getTempCByIndex(0);
  Serial.println(String(f));
  delay(1000);
}