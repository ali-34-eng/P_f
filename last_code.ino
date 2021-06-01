/*
----------------------------------------------------------------------------------------------------------------
 
******************************** Glucose Measurement System ****************************************************
 Editing By Ali Abdul Hussein Khalil
 2020/2021
 Al-Nahrain University
----------------------------------------------------------------------------------------------------------------
 */

 #include <LCD_I2C.h>
LCD_I2C lcd(0x27); 
#define test_strip_d4 D4
#define insert_strip_d0 D0
#define write_d7 D7
#define led_d8 D8
#define help_d3 D3
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>


#include "CTBot.h"
CTBot myBot;

const char * myWriteAPIKey = "V9JFKXZV1YIKAKH2"; //Your Write API Key
long ID = 818222669; //Your Channel Number (Without Brackets)
unsigned long myChannelNumber=1370397;
String ssid =  "Tree";     
String pass =  "ZXCV123456";//can use const char*
const char* server = "api.thingspeak.com";
String token = "1828120441:AAF5PsHpWyTILga5JAq7j_Hgazrlm4YiIY8";
long analogInPin_A0=A0;
WiFiClient client;
      
int buttonState = 0;
void setup() {

Serial.begin(9600);
    pinMode(analogInPin_A0,INPUT);
 pinMode(insert_strip_d0, INPUT);
pinMode(test_strip_d4,OUTPUT);
  pinMode(help_d3,INPUT);
pinMode(led_d8,OUTPUT);

digitalWrite(led_d8,LOW);

 delay(10);
        WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
     ThingSpeak.begin(client);
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
 
  delay(1000);
  return;
 }
 else if( digitalRead(insert_strip_d0)==HIGH){
 // digitalWrite(test_strip_d4,LOW);
  digitalWrite(write_d7,HIGH);
  // lcd.clear();
  //lcd.print("Drop_Blood");
  long average =3;
 
average =analogRead(analogInPin_A0);
 Serial.println(average);
 if(average>50&&average<200){
   lcd.clear();
        lcd.setCursor(1,1);

     lcd.print("used strip");
      Serial.println(">>>>>>");
delay(2200);
 }

  else if(average>=0&&average<=50){
   lcd.clear();
   lcd.print("Drop_Blood");
   long average =0;
   delay(10600);
    average =analogRead(analogInPin_A0);

    if(average>=200&&average<1024){
    
        average=average*0.16438;

      
   lcd.clear();

     lcd.print("sensor_V= ");
     lcd.setCursor(1,1);
   lcd.print(average);
   
  TBMessage msg;
  myBot.sendMessage(ID,"Glocuse Mesuerment...");
 myBot.sendMessage(ID,"PN:Zaid Ali");
   String lo=String(average);
   
myBot.sendMessage(ID,lo);
   
 ThingSpeak.writeField(myChannelNumber, 1,average, myWriteAPIKey); //Update in ThingSpeak

  
 Serial.println("telebot");
      long x=1;

  for(x=1;x<100000000;x++){
          Serial.println("wait");

  TBMessage msg;
  digitalWrite(help_d3,LOW);
  
  // if there is an incoming message...
  if(myBot.getNewMessage(msg)){
    // ...forward it to the sender
    myBot.sendMessage(msg.sender.id, msg.text);
             Serial.println(msg.text);
                String mm=String(msg.text);
                    lcd.clear();

             lcd.print(mm);
              if (msg.text.equalsIgnoreCase("LT ON")) {              // if the received message is "LIGHT ON"...
      digitalWrite(led_d8, HIGH);                               // turn on the LED (inverted logic!)
     myBot.sendMessage(ID, "Light is now ON");
        lcd.backlight();
     lcd.print("   HIGH");
    lcd.setCursor(4, 1);
    lcd.print("GLUCOSE");
    delay(700);
     for (int i = 0; i < 6; ++i)
    {
        lcd.backlight();
        delay(60);
        lcd.noBacklight();
        delay(60);
    }

    
    
     
              }

  }
 
   
   
   else if(digitalRead(help_d3) ==LOW){
        lcd.clear();
 
     myBot.sendMessage(ID,"help");
         lcd.print("help");


}

  delay(3000); }
}
}
 }
}
