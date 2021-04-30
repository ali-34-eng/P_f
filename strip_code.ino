// Glucose Measurement System
#define test_strip_d4 D4
#define insert_strip_d0 D0
#define write_d7 D7
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <LCD_I2C.h>
LCD_I2C lcd(0x27); 
WiFiClient client;
#include "CTBot.h"
CTBot myBot;

String apiKey = "V9JFKXZV1YIKAKH2";   
  long  average = 0;
long ID=818222669;
String ssid =  "Tree";     
String pass =  "ZXCV12345";//can use const char*
const char* server = "api.thingspeak.com";
String token = "1775492194:AAEtCKNab3vpbzrLpL9_oEr22V1U-gzfRUg";
const int analogInPin_A0 = A0;

      
int buttonState = 0;
void setup() {
  
Serial.begin(9600);
    pinMode(analogInPin_A0,INPUT);
 pinMode(insert_strip_d0, INPUT);
pinMode(test_strip_d4,OUTPUT);

 delay(10);
        WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

} 
void loop() {
   lcd.begin();
    lcd.backlight();
     lcd.print("   Insert");
    lcd.setCursor(4, 1);
    lcd.print("Strip");
    delay(700);
     for (int i = 0; i < 6; ++i)
    {
        lcd.backlight();
        delay(60);
        lcd.noBacklight();
        delay(60);
    }

    
    delay(1000);
    lcd.backlight();
    lcd.clear();
    delay(500);

  digitalWrite(test_strip_d4,HIGH);
 if( digitalRead(insert_strip_d0)==LOW){
    lcd.clear();
  lcd.print("NO_Strip");
 
  delay(4000);
 }
 else if( digitalRead(insert_strip_d0)==HIGH){
  delay(1600);
 // digitalWrite(test_strip_d4,LOW);
  digitalWrite(write_d7,HIGH);
   lcd.clear();
  lcd.print("Drop_Blood");
   delay(8000);
 
 average =analogRead(analogInPin_A0);
 }
 if(average>=5&&average<700){
   lcd.clear();
     lcd.print("sensor_V= ");
     lcd.setCursor(1,1);
   lcd.print(average);
   delay(500);
  TBMessage msg;
 // myBot.sendMessage(ID,"Glocuse Mesuerment...");
// myBot.sendMessage(ID,"PN:Zaid Ali");
   String lo=String(average);
   
//myBot.sendMessage(ID,lo);
   
 }
    
      long randNumber =analogRead(A0);
long x=randNumber;
              if (isnan(x)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(x);
                            // postStr +="&field2=";
                           //  postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             
                        }
          client.stop();
 
    
 delay(1999);
 
 }
 
