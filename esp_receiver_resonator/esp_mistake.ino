
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <SoftwareSerial.h>
#define STASSID "netis_2.4G_98ED49" // Задаем название WiFI-сети
#define STAPSK "password" // Задаем Пароль WiFI-сети

//#define NUMBER_OF_TRANSMITTERS 5 // Задаем число клиентов
#define SIZE_OF_DATA 1203 // Размер данных принимаемого массива 
//uint8_t result_data[NUMBER_OF_TRANSMITTERS*SIZE_OF_DATA] = {}; // Массив для хранения общего пакета данных
 uint8_t packetBuffer[SIZE_OF_DATA]={}; //Буфер для хранения принимаемых данных с ESP
 uint8_t result_data[SIZE_OF_DATA*5]={};
 uint8_t null[SIZE_OF_DATA*5]={};
//bool isrepeat[5]={false,false,false,false,false};
 //bool trasmitted=false;
IPAddress ip(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);
//String http_string1=""; //Буферные строки данных для отправки на веб-страницу
//String http_string2="";
//String http_string3="";
//String http_string4="";
//String http_string5="";
//IPAddress clientIPs[NUMBER_OF_TRANSMITTERS]; //Массив IP-адресов клиентов
unsigned int localPort = 8888;  // Задаем локальный порт для обмена между ESP
unsigned int localPort1 = 8080;  // Задаем локальный порт для веб-страницы

long lastUART=0;
int i = 0;
uint8_t count=0;
//int clientCount = 0;
WiFiUDP Udp;

 uint8_t currenttransmitter;
//ESP8266WebServer server(8080); //Задаем порт Wi-Fi сервера

//SoftwareSerial mySerial = SoftwareSerial(13, 12);

void setup() {
  //mySerial.begin(230400); 
  Serial.begin(921600);

  WiFi.softAP(STASSID,STAPSK,1,true,5);
  WiFi.softAPConfig(ip, gateway, subnet);
  delay(100);
/*
  WiFi.begin(STASSID, STAPSK); //Подключаемся к локальной сети
  while (WiFi.status() != WL_CONNECTED) { //Проверяем соединение с сетью
    //Serial.print('.');
    delay(500);
  }*/
  //Serial.print("Connected! IP address: ");
  //Serial.println(WiFi.localIP());
  //Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort); //Инициализируем UDP 
  //server.on("/",http_server); //Инициализируем передачу на веб-страицу
  //server.begin();
  lastUART=millis();

}

//void http_server() {
  //server.send(200, "text/html", SendHTML());  //Отправляем HTML-код
//}
/*String SendHTML(){ 
  //Разбиваем общий пакет данных на строки для передачу на веб-страницу
   for (int i = 0; i < SIZE_OF_DATA; i++) {
    http_string1 += (int)result_data[i];
    http_string1 += " ";
    http_string1 +="\0";
    http_string2 += (int)result_data[i+SIZE_OF_DATA];
    http_string2 += " ";
    http_string2 +="\0";
    http_string3 += (int)result_data[i+2*SIZE_OF_DATA];
    http_string3 += " ";
    http_string3 +="\0";
    http_string4 += (int)result_data[i+3*SIZE_OF_DATA];
    http_string4 += " ";
    http_string4 +="\0";
    http_string5 += (int)result_data[i+4*SIZE_OF_DATA];
    http_string5 += " ";
    http_string5 +="\0";
  } 
  //HTML-код отправляем в строке ptr
  String ptr = "<!DOCTYPE html> <html>\n"; 
  ptr +="<meta http-equiv=\"Refresh\" content=\"0.5\" /><meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Координатор</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Координатор.Данные с 5 устройств:</h1>\n";
  ptr +="<h1>1 передатчик "+http_string1+"</h1>";
  ptr +="<h1>2 передатчик "+http_string2+"</h1>";
  ptr +="<h1>3 передатчик "+http_string3+"</h1>";
  ptr +="<h1>4 передатчик "+http_string4+"</h1>";
  ptr +="<h1>5 передатчик "+http_string5+"</h1>";
  ptr +="<h1>1 передатчик</h1>";
  ptr +="<h1>1 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[2]*256+result_data[3];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[4]*256+result_data[5];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[6]*256+result_data[7];
  ptr +="</h1>";
  ptr +="<h1>2 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[8]*256+result_data[9];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[10]*256+result_data[11];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[12]*256+result_data[13];
  ptr +="</h1>";
   ptr +="<h1>2 передатчик</h1>";
  ptr +="<h1>1 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[2+SIZE_OF_DATA]*256+result_data[3+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[4+SIZE_OF_DATA]*256+result_data[5+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[6+SIZE_OF_DATA]*256+result_data[7+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>2 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[8+SIZE_OF_DATA]*256+result_data[9+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[10+SIZE_OF_DATA]*256+result_data[11+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[12+SIZE_OF_DATA]*256+result_data[13+SIZE_OF_DATA];
  ptr +="</h1>";
  ptr +="<h1>3 передатчик</h1>";
  ptr +="<h1>1 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[2+SIZE_OF_DATA*2]*256+result_data[3+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[4+SIZE_OF_DATA*2]*256+result_data[5+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[6+SIZE_OF_DATA*2]*256+result_data[7+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>2 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[8+SIZE_OF_DATA*2]*256+result_data[9+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[10+SIZE_OF_DATA*2]*256+result_data[11+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[12+SIZE_OF_DATA*2]*256+result_data[13+SIZE_OF_DATA*2];
  ptr +="</h1>";
  ptr +="<h1>4 передатчик</h1>";
  ptr +="<h1>1 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[2+SIZE_OF_DATA*3]*256+result_data[3+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[4+SIZE_OF_DATA*3]*256+result_data[5+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[6+SIZE_OF_DATA*3]*256+result_data[7+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>2 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[8+SIZE_OF_DATA*3]*256+result_data[9+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[10+SIZE_OF_DATA*3]*256+result_data[11+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[12+SIZE_OF_DATA*3]*256+result_data[13+SIZE_OF_DATA*3];
  ptr +="</h1>";
  ptr +="<h1>5 передатчик</h1>";
  ptr +="<h1>1 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[2+SIZE_OF_DATA*4]*256+result_data[3+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[4+SIZE_OF_DATA*4]*256+result_data[5+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[6+SIZE_OF_DATA*4]*256+result_data[7+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="<h1>2 акселерометр</h1>";
  ptr +="<h1>Ось X - ";
  ptr +=result_data[8+SIZE_OF_DATA*4]*256+result_data[9+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="<h1>Ось Y - ";
  ptr +=result_data[10+SIZE_OF_DATA*4]*256+result_data[11+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="<h1>Ось Z - ";
  ptr +=result_data[12+SIZE_OF_DATA*4]*256+result_data[13+SIZE_OF_DATA*4];
  ptr +="</h1>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  //Обнуляем строки
    http_string1="";
    http_string2="";
    http_string3="";
    http_string4="";
    http_string5="";
  return ptr;
  
}*/
void loop() {
  //server.handleClient();
  int packetSize = Udp.parsePacket(); 
  if (packetSize) {
    int n = Udp.read(packetBuffer,SIZE_OF_DATA); //Считываем данные по UDP в массив
    if (packetBuffer[0]==160 && packetBuffer[1202]==254 && packetBuffer[1]==1) {
      memcpy(result_data,packetBuffer, SIZE_OF_DATA);
    }
    if (packetBuffer[0]==160 && packetBuffer[1202]==254 && packetBuffer[1]==2) {
      memcpy(result_data+SIZE_OF_DATA,packetBuffer, SIZE_OF_DATA);
    }
    if (packetBuffer[0]==160 && packetBuffer[1202]==254 && packetBuffer[1]==3) {
      memcpy(result_data+2*SIZE_OF_DATA,packetBuffer, SIZE_OF_DATA);
    }
    if (packetBuffer[0]==160 && packetBuffer[1202]==254 && packetBuffer[1]==4) {
      memcpy(result_data+3*SIZE_OF_DATA,packetBuffer, SIZE_OF_DATA);
    }
    if (packetBuffer[0]==160 && packetBuffer[1202]==254 && packetBuffer[1]==5) {
      memcpy(result_data+4*SIZE_OF_DATA,packetBuffer, SIZE_OF_DATA);
    }
    //Serial.write(packetBuffer,SIZE_OF_DATA);
    //packetBuffer[n] = 0; 
    //IPAddress current_remoteIP = Udp.remoteIP();
/*
    if (clientCount < 5 && !(clientIPs[clientCount]=current_remoteIP) ) {
      clientIPs[clientCount] =current_remoteIP;
      clientCount++;
    }*/

    //Собираем общий пакет данных,проверяем по 1-му индексу(1,2,3,4,5 соответственно номера передатчиков)
    /*currenttransmitter = packetBuffer[1];
    if (packetBuffer[1]==1) {
      for (int j=0;SIZE_OF_DATA>j; j++) {
        result_data[j]=packetBuffer[j];    
    }
    }
    if (packetBuffer[1]==2) {
      for (int j=0;SIZE_OF_DATA>j; j++) {
        result_data[j+SIZE_OF_DATA]=packetBuffer[j];
      }
    }
    if (packetBuffer[1]==3) {
      for (int j=0;SIZE_OF_DATA>j; j++) {
        result_data[j+SIZE_OF_DATA*2]=packetBuffer[j];
      }
    }
    if (packetBuffer[1]==4) {
      for (int j=0;SIZE_OF_DATA>j; j++) {
        result_data[j+SIZE_OF_DATA*3]=packetBuffer[j];
      }
    }
    if (packetBuffer[1]==5) {
      for (int j=0;SIZE_OF_DATA>j; j++) {
        result_data[j+SIZE_OF_DATA*4]=packetBuffer[j];
      }
    }*/
    //delay(1000);
    //for (int i = 0; i < NUMBER_OF_TRANSMITTERS*SIZE_OF_DATA; i++) {
      //Serial.print(result_data[i],HEX);
      //Serial.print(" ");
    //}
    
  }

  if (millis()-lastUART > 1000) 
    {
      Serial.write(result_data,SIZE_OF_DATA*5);
      count++;
      if(count>5) {
		    count=0;
		    memcpy(result_data,null,6015);
	    }
      lastUART = millis();
      
    }
    //for (int i=0;SIZE_OF_DATA>i;i++) {
      
    //}
    //mySerial.write(result_data,SIZE_OF_DATA*NUMBER_OF_TRANSMITTERS);
    

}

