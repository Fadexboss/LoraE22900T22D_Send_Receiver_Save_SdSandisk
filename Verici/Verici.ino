
#include <LoRa_E22.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); 
LoRa_E22 e22ttl(&mySerial);

#define M0 7
#define M1 6


struct Message{
  float sicaklik[10];
  float hiz[10];
}message;

//data myData;

void setup()
{
  Serial.begin(9600);
  pinMode(M0,OUTPUT);
  pinMode(M1,OUTPUT);
  digitalWrite(M0,LOW);
  digitalWrite(M1,LOW);

  e22ttl.begin();
  
}

void loop()
{
  *(float*)(message.sicaklik)=6;
  *(float*)(message.hiz)=3;

  
  mySerial.listen();
  ResponseStatus rs = e22ttl.sendFixedMessage(0 , 56 , 22 , &message , sizeof(message));
}







