/*---------------------
Client Section
-----------------------*/
//0 to 50 °C, 20% to 90%maximum relative humidity

#include "DHT.h"        //dht11 sensor library
#define DHTPIN 5        //digital pin to which the sensor is connected
#define DHTTYPE DHT11   // DHT_11 object for LORA
#include <SPI.h>        //DHT_11 object for LORA
#include <RH_RF95.h> 

RH_RF95 rf95; 
DHT dht(DHTPIN, DHTTYPE); //functions to use from the sensor library

void setup() {
  Serial.begin(9600);   //Serial port
  dht.begin();          //Sensor Object Start
  if (!rf95.init())     //If you don't start the LORA
    Serial.println("Fallo de inicio en LORA"); // Error message
  rf95.setFrequency(433.0); //LORA frequency
}

void loop() {
  float h = dht.readHumidity();       //Humidity Variable 
  float t = dht.readTemperature();    //Temperature Variable
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t)) {
    Serial.println("¡Error al leer del sensor DHT!");
    return;
  }
  
  //Print format on sensor data monitor
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");
  //Forms the output chain-humidity and sensor temperature
  String data = String(h) + "-" + String(t);

  //Save the length of the string in a variable
  int dataLength = data.length(); 
  dataLength++;                 //Increase length by 1
  uint8_t total[dataLength];    //total variable to send data
  //Change the string unit8_t to array to send data
  data.toCharArray(total, dataLength); 
  Serial.println(data);
  rf95.send(total, dataLength); //Sending data to LORA
  rf95.waitPacketSent();
  delay(500);
}
