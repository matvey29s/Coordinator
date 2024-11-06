#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(12, 13);
#define IP_receiver "192.168.1.100" 
#define STASSID "netis_2.4G_98ED49"
#define STAPSK "password"
#define SIZE_OF_DATA 1203
unsigned int localPort = 8888;
uint8_t inputString[SIZE_OF_DATA];
//uint8_t data_buffer[SIZE_OF_DATA];
uint8_t incomingByte = 0;
bool firstByte;
WiFiUDP Udp;

void setup() {
  Serial.begin(230400);
  //mySerial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print('.');
    delay(100);
  }
  //Serial.print("Connected! IP address: ");
  //Serial.println(WiFi.localIP());
  Udp.begin(localPort);
}

void loop() {
    firstByte=true;
    int index = 0;
    while(index<SIZE_OF_DATA) {
      if (Serial.available()) {
        incomingByte = Serial.read();
      if (incomingByte==160) firstByte=false;
      if (!firstByte) {
          inputString[index] = incomingByte;
          index++;
      } 
      }
    }
    /*
    int index = 0;
    bool validData = false;
    bool startDetected = false;
    while (index < SIZE_OF_DATA) {
    if (mySerial.available()) {
        incomingByte = mySerial.read();
        
        if (index == 0 && incomingByte == 10) {
            validData = true;
        } else if (index == SIZE_OF_DATA - 1 && incomingByte == 254) {
            validData = true;
        }

        if (validData) {
            inputString[index] = incomingByte;
            Serial.write(incomingByte);
            index++;
        } else {
            // Сбросить индекс, если данные не соответствуют формату
            index = 0;
        }
    }
    }*/
    
      Udp.beginPacket(IP_receiver, localPort);
      Udp.write( inputString,SIZE_OF_DATA);
      Udp.endPacket();
  
    
}


