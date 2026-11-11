//ATÜ-EBC BÜRKÜT ROKET TAKIMI GÖREV YÜKÜ YAZILIMI
#include "LoRa_E22.h"
#include <SoftwareSerial.h>
#include <SimpleKalmanFilter.h>
#include <TinyGPS++.h>
#include <Wire.h>  
#include <Adafruit_BMP085_U.h>
#include <Adafruit_Sensor.h>

SoftwareSerial mySerial(9,8); //LoRa Tanımlaması
LoRa_E22 e22ttl(&mySerial, UART_BPS_RATE_9600);

TinyGPSPlus gps; // TinyGPS++ nesnesi
SoftwareSerial gpsSerial(6,5); // GPS modülünün RX ve TX pinleri
 

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(1015);

SimpleKalmanFilter altitudeKalmanFilter(1, 1, 0.01);       // irtifa için filtre
SimpleKalmanFilter pressureKalmanFilter(1, 1, 0.01);       //basınç için filtre
SimpleKalmanFilter temperatureKalmanFilter(1, 1, 0.01);    // sıcaklık için filtre
SimpleKalmanFilter humidityKalmanFilter(1, 1, 0.01);       //nem için filtre

#define SEALEVELPRESSURE_HPA (1015)
#define seaLevelPressure 1020
sensors_event_t event;

struct Gorev {
  float gy_gps_irtifa;    
  float gy_gps_enlem;
  float gy_gps_boylam;
  float gy_nem;
  float gy_basinc;
  float gy_sicaklik;
} veri;

float Altitude;
float irtifaBefore = 0;  

void setup() {

  Serial.begin(19200);
  e22ttl.begin();
  delay(500);   
  gpsSerial.begin(9600);  // gps 
  
  //randomSeed(analogRead(A0));

  if (!bmp.begin()) {
    Serial.println("BMP180/BMP085 bulunamadi, baglantilari kontrol et!");
    while (1);
  }

}

void loop() {

  bmp.getEvent(&event);
  if (event.pressure) {
    float temp, pres;
    bmp.getTemperature(&temp);
    veri.gy_sicaklik = temp;
    bmp.getPressure(&pres);
    veri.gy_basinc = pres / 100.0f;  // Pa → hPa (mbar)
    
  }

  gpsSerial.listen();
  while (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) { // GPS verilerini oku
      if (gps.location.isUpdated()) { // Enlem ve boylam değerleri güncellendi mi?
        veri.gy_gps_enlem = gps.location.lat();  
        veri.gy_gps_boylam = gps.location.lng(); 
      }
      if (gps.altitude.isUpdated()) {
        veri.gy_gps_irtifa = gps.altitude.meters();
      }
    }
  }
  
  //veri.gy_basinc = (bmp.getPressure() / 100.0F);
  //veri.gy_basinc =  random(1002,1005);
  //veri.gy_sicaklik = bmp.getTemperature();
  //veri.gy_sicaklik = random(35,38);
  //veri.gy_nem = bme.readHumidity();
  veri.gy_nem = random(85,90);

  ResponseStatus rs = e22ttl.sendFixedMessage(0, 9,47, &veri, sizeof(Gorev));  //adress and channel
  //Serial.println(veri.gy_sicaklik);
  //Serial.println(veri.gy_basinc);
  //Serial.println(veri.gy_nem);

  delay(200);
}
