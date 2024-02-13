#include "LoRa_E22.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

// Sd Karta erisme anahtarı belirleyelim dataFile kelimesini yazarak ulasabiliriz 
File dataFile;
//sd kartin chipSelect için pin sayısı belirleyelim
int chipSelect = 4;
//gene loranin rx tx pinleri
SoftwareSerial mySerial(9, 8);
LoRa_E22 e22ttl(&mySerial);


#define M0 7
#define M1 6


struct Message{
  byte sicaklik[10];
  byte hiz[10];

};


void setup() {
  Serial.begin(9600);
  pinMode(M0,OUTPUT);
  pinMode(M1,OUTPUT);
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);
  e22ttl.begin();
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD kart başlatılamadı!");
    return;
  
  }

  // csv dosyasını aç
  dataFile = SD.open("veriler.csv", FILE_WRITE);

  // Başlık satırını yazdır
  dataFile.println("Sicaklik,Hiz");
  
  // Dosya kapat
  dataFile.close();
  

}
void loop() {
  
  while (e22ttl.available()>0) {
  ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(Message));
  struct Message message =* (Message*) rsc.data;
  Serial.print(*(byte*)message.sicaklik);
  Serial.println();
  Serial.println(*(float*)(message.sicaklik));
  Serial.println(*(float*)(message.hiz));  
  Serial.println("Sd yazıyor");

  Serial.print(*(byte*)message.hiz);  
    pinMode(chipSelect,OUTPUT);
    if (!SD.begin(chipSelect)) {
      Serial.println("SD kart başlatılamadı!");
      return;
    }
      dataFile = SD.open("veriler.csv", FILE_WRITE);
    
      //Verileri Byte olarak yazdir
      dataFile.print(*(byte*)message.sicaklik);
      dataFile.print(",");
      dataFile.println(*(byte*)message.hiz);
      dataFile.close();
      Serial.println(*(float*)(message.sicaklik));
      Serial.println(*(float*)(message.hiz));
  }
  mySerial.listen();
}
