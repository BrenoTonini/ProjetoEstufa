#include <SoftwareSerial.h> // rs485
#include <Adafruit_BMP085.h> //barometro
#include <Wire.h> //barometro
#include <OneWire.h> //sensor temperatura solo
#include <DallasTemperature.h> //sensor temperatura solo

#define ONE_WIRE_BUS 7
#define RX_PIN 10
#define TX_PIN 11

Adafruit_BMP085 barometro;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial rs485(RX_PIN, TX_PIN);

const int deviceAddress = 1;
int sensorUmidade = 14;

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(sensorUmidade, INPUT);
  
  if (!barometro.begin()) {
    Serial.println("Barômetro não detectado!");
    while (1);
  }

  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  
  int bmpTemperatura = int(barometro.readTemperature() * 100);
  int bmpAltitude = int(barometro.readAltitude());
  int bmpPressao = int(barometro.readPressure());
  int umidade = analogRead(sensorUmidade);
  int temperaturaSolo = int(sensors.getTempCByIndex(0) * 100);

  rs485.write(deviceAddress);
  rs485.print(",");
  rs485.print(bmpTemperatura);
  rs485.print(",");
  rs485.print(bmpAltitude);
  rs485.print(",");
  rs485.print(bmpPressao);
  rs485.print(",");
  rs485.print(umidade);
  rs485.print(",");
  rs485.println(temperaturaSolo);

  delay(1000);
}
