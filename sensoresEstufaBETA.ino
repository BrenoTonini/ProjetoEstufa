//libs do barometro:
#include <Adafruit_BMP085.h>
#include <Wire.h>

//libs do sensor de temperatura:
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7

int sensorUmidade = 14;

Adafruit_BMP085 barometro;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(sensorUmidade, INPUT);
  if (!barometro.begin()){
    Serial.println("Barometro não identificado, verifique as conexões.");
    while(1){}
  }

  sensors.begin();
  
}

void loop() {
  sensors.requestTemperatures();
  
  String bmpTemperatura = String(barometro.readTemperature(), 2);
  String bmpAltitude = String(barometro.readAltitude()); 
  String bmpPressao = String(barometro.readPressure());
  String umidade = String(analogRead(sensorUmidade));
  String temperaturaSolo = String(sensors.getTempCByIndex(0), 2);
  
  Serial.println( bmpTemperatura + "°C, " + bmpAltitude + "M, " + bmpPressao + "Pa, " + umidade + ", " + temperaturaSolo + "°C");
  delay(1000);
}