#define e D2
#define r D7
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
char ssid[] = "neelimaj";
char pass[] = "12345678";
WiFiClient client;
unsigned long counterChannelNumber = 670394;
const char * myCounterReadAPIKey = "94JAW5TR9Q7YP06Z";
unsigned int counterFieldNumber = 1;
unsigned int counterFieldNumber1 = 2;

void setup() {
Serial.begin(115200); // Initialize serial
pinMode(e,OUTPUT);
pinMode(r,OUTPUT);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
int statusCode = 0;
if(WiFi.status() != WL_CONNECTED){
  Serial.print("Attempting to connect to SSID: ");
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnected");
}
long count = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber,
myCounterReadAPIKey);
long count1 = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber1,
myCounterReadAPIKey);
statusCode = ThingSpeak.getLastReadStatus();
Serial.println("Counter1: " + String(count1));
if(statusCode == 200){
  Serial.println("Counter: " + String(count));
}
else{
  Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
}
if(count==2)
{
  Serial.println("2");
  digitalWrite(e,HIGH);//BULB ON
}
else if(count==3)
{
  Serial.println("3");
  digitalWrite(e,LOW);//bulb off
}
else if(count==4)
{
  Serial.println("4");
digitalWrite(r,HIGH);//bulb off
}
else if(count==5)
{
  Serial.println("5");
  digitalWrite(r,LOW);//bulb off
}
}

}
