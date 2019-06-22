#include <doxygen.h>
#include "ESP8266.h"

#include <SerialESP8266wifi.h>

#include <ESP8266_Lib.h>

#include <SimpleTimer.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#define sw_serial_rx_pin 3 //  Connect this pin to TX on the esp8266
#define sw_serial_tx_pin 2 //  Connect this pin to RX on the esp8266

#include <BlynkSimpleShieldEsp8266.h>
#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
//Include ESP and Blynk libraries

#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;
// Set ESP8266 Serial object
#include "SoftwareSerial.h"
#define EspSerial Serial
//SoftwareSerial EspSerial(3,2); // RX, TX
ESP8266 wifi(EspSerial); 

const int trigPin = 8;
const int echoPin = 9;
char auth[] = "6944a20c9a5a4a32972cf712d99e06f5";
void setup() 
{
Serial.begin(9600);
// Set console baud rate
Serial.begin(9600);
delay(10);
// Set ESP8266 baud rate
// 9600 is recommended for Software Serial
EspSerial.begin(9600);
delay(10);
Blynk.begin(auth, wifi, "AndroidAP_2894", "panzer28");
timer.setInterval(3000, CheckDistance);
}
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
void CheckDistance()
{
long duration;
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
long inches = microsecondsToInches(duration);
long cm = microsecondsToCentimeters(duration);
Serial.print(inches);
Serial.print("in ");
Serial.println();
Blynk.virtualWrite(V5, inches);
//Check whether Bin is full or not
if(inches < 2)
{
Blynk.virtualWrite(V3, 255);
Blynk.notify(" Yaaay....Overflow!!");
}
delay(1000);
}
