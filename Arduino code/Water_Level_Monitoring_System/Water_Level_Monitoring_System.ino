#define BLYNK_TEMPLATE_ID "Your Template ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Your Blynk Auth Token"
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
const char* ssid     = "Wifi Name";
const char* pass = "Wifi Password";
const char* password = "Wifi Password";
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);
String motoron = "";
String prevmotoron = "q";
String hour_format;
int percent = 0;
int last_percent = -1;
int onhour, onmin, onsec, offhour, offmin, offsec, tothr, totmin, hours, minutes, seconds, virtualPinValue = -1, isvirtualPinValue;
unsigned long lastDebounceTime = 0,lastDebounceTime1 = 0,lastDebounceTime2 = 0,lastDebounceTime3 = 0,lastDebounceTime4 = 0,lastDebounceTime5 = 0,lastDebounceTime6 = 0,lastDebounceTime7 = 0;
const unsigned long debounceDelay = 6000;
const unsigned long debounceDelay2 = 10000;
unsigned long wifiprevmill = 0;
unsigned long previousMillis = 0;
const long interval = 200;
int switchState;
bool isnight, isvirtual, else_condition, relay,Dryrun,error_sens;
char auth[] = BLYNK_AUTH_TOKEN;

void setup() {
  Wire.begin(D3, D1); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  timeClient.begin();
  motoron= "OFF";
  onhour = 0;
  onmin = 0;
  onsec = 0;
  relay = true;
  isnight = true;
  isvirtual = true;
  else_condition = true;
  Dryrun = true;
  error_sens = false;
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  pinMode(D7, INPUT);
  pinMode(D0, INPUT);
  pinMode(D2, INPUT);
  pinMode(D5, INPUT);
  pinMode(D8, OUTPUT);
  pinMode(D6,OUTPUT);
  Blynk.syncVirtual(V1);
   Blynk.virtualWrite(V4, 0);  
}

BLYNK_WRITE(V1) {
  isvirtualPinValue = param.asInt();
} 
// For Switch
BLYNK_WRITE(V3)
{
  switchState = param.asInt();
  
  if(switchState == 1) {
    motoron= "ON";
  } else {
    motoron= "OFF";
  }
}

void loop() {
   if (WiFi.status() != WL_CONNECTED) {
    unsigned long wifimill = millis();
    if (wifimill - previousMillis >= 5000){
      WiFi.begin(ssid, pass);
      previousMillis = wifimill;
    }
  }
  Blynk.run();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  timeClient.update();
  int sensorValue = digitalRead(D7);
  int sensorValue1 = digitalRead(D0);
  int sensorValue2 = digitalRead(D2);
  int sensorValue3 = digitalRead(D5);
///////////////////////////////////////////////////
  if (!Dryrun){
    Blynk.virtualWrite(V3,0);
  }
///////////////////////////////////////////////////
  if ((!else_condition) || (error_sens)){
  delay (1000);
  lcd.setCursor(11, 1); 
  lcd.print("     "); 
  Blynk.virtualWrite(V4, 0); 
  else_condition = true;
  error_sens = false;
  }
  if (isvirtual) {
    Blynk.virtualWrite(V1,isvirtualPinValue);
    isvirtual = false;
  }
  if((timeClient.getHours()==0) && (timeClient.getMinutes()==0) && (timeClient.getSeconds()<30) && isnight){
    isvirtualPinValue = 0;
   isnight = false; 
  }
  if ((timeClient.getHours()==0) && (timeClient.getMinutes()==0) && (timeClient.getSeconds()>30) && !isnight){
    isnight = true;
  }

   
  if (sensorValue1 != 0){
  lastDebounceTime4 = millis();
  }

  if (sensorValue2 != 0){
  lastDebounceTime2 = millis();
  }

  if (sensorValue3 != 0){
  lastDebounceTime = millis();
  }

  if ((sensorValue != 0)){
  lastDebounceTime6 = millis();
 }

 if (!(sensorValue == 1 && sensorValue1 == 1 && sensorValue2 == 1 && sensorValue3 == 1)){
  lastDebounceTime7 = millis();
 }

  
 if (sensorValue3 == 0){
  if ((millis() - lastDebounceTime) >= debounceDelay2) {
    percent = 100;
    lcd.setCursor(13, 0);
    motoron = "OFF";
  if (sensorValue == 1 || sensorValue1 == 1 || sensorValue2 == 1 ){
    if ((millis() - lastDebounceTime1) >= debounceDelay){
    lcd.setCursor(11, 1); 
    lcd.print("     "); 
    lcd.setCursor(11, 1);
    lcd.print("Error");
    error_sens = true;
    Blynk.virtualWrite(V4, 255);       
    Blynk.setProperty(V4, "color", "#FF0000");
    }
  }else {
    lastDebounceTime1 = millis();
  }
 }
 }
 else if (sensorValue2 == 0){
  if ((millis() - lastDebounceTime2) >= debounceDelay) {
  percent = 75;
  if (sensorValue == 1 || sensorValue1 == 1){
    if ((millis() - lastDebounceTime3) >= debounceDelay){
    lcd.setCursor(11, 1); 
    lcd.print("     "); 
    lcd.setCursor(11, 1);
    lcd.print("Error");
    error_sens = true;
    Blynk.virtualWrite(V4, 255);       
    Blynk.setProperty(V4, "color", "#FF0000");
    }
  }else {
    lastDebounceTime3 = millis();
  }
 }
 }

 else if (sensorValue1 == 0){
  if ((millis() - lastDebounceTime4) >= debounceDelay){
  percent = 50;
  if (sensorValue == 1){
    if ((millis() - lastDebounceTime5) >= debounceDelay){
    lcd.setCursor(11, 1); 
    lcd.print("     "); 
    lcd.setCursor(11, 1);
    lcd.print("Error");
    error_sens = true;
    Blynk.virtualWrite(V4, 255);       
    Blynk.setProperty(V4, "color", "#FF0000");
    }
  }else {
    lastDebounceTime5 = millis();
  }
  }
 }

 else if (sensorValue == 0 && sensorValue1 == 1 && sensorValue2 == 1 && sensorValue3 == 1){
  if ((millis() - lastDebounceTime6) >= debounceDelay){
  percent = 25;
  }
 }
 
 else if (sensorValue == 1 && sensorValue1 == 1 && sensorValue2 == 1 && sensorValue3 == 1){
  if ((millis() - lastDebounceTime7) >= debounceDelay2){
    if (relay){
  motoron = "ON";
    }
    percent = 0;
  }
 }
  else {
    if (Dryrun){
  lcd.setCursor(11, 1); 
  lcd.print("     "); 
  lcd.setCursor(11, 1);
  lcd.print("Error");
  else_condition = false;
    }
  }

///////////////////////////////////////////////////
if (motoron == "ON"){
  if (relay){
  digitalWrite(D8,HIGH);
  digitalWrite(D6,HIGH);
  Blynk.logEvent("motorstate",String("Motor ") + motoron); 
  lcd.setCursor(0,1);
  lcd.print("     ");
  onhour = timeClient.getHours();
  onmin = timeClient.getMinutes();
  onsec = timeClient.getSeconds();
  hour_format = convertTo12HourFormat(onhour,onmin);
  lcd.setCursor(0,0);
  lcd.print("       ");
  lcd.setCursor(0,0);
  lcd.print(hour_format);
  Blynk.virtualWrite(V5, hour_format);  
  relay = false;
  Blynk.virtualWrite(V3,1);
  isvirtualPinValue = isvirtualPinValue + 1;
  }
}
else if (motoron == "OFF"){
  if (!relay && Dryrun ){
  digitalWrite(D8,LOW);
  digitalWrite(D6,LOW);
  Blynk.logEvent("motorstate",String("Motor ") + motoron); 
  offhour = timeClient.getHours();
  offmin = timeClient.getMinutes();
  offsec = timeClient.getSeconds();
  calculateMotorRuntime(onhour,onmin,onsec,offhour,offmin,offsec);
  if (minutes < 10){
  lcd.setCursor(0, 1);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print(String("0")+String(minutes)+String(":"));
  }
  else {
  lcd.setCursor(0, 1);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print(String(minutes)+String(":"));
  }
  if (seconds < 10){
  lcd.setCursor(3, 1);
  lcd.print("  ");
  lcd.setCursor(3, 1);
  lcd.print(String("0")+String(seconds));
  }
  else {
  lcd.setCursor(3, 1);
  lcd.print("  ");
  lcd.setCursor(3, 1);
  lcd.print(seconds);
  }
  Blynk.virtualWrite(V3,0);
  relay = true;
  }
}
//////////////////////////////////////////////////
if (motoron == "ON"){
  calculateMotorRuntime(onhour,onmin,onsec,timeClient.getHours(),timeClient.getMinutes(),timeClient.getSeconds());
  if ((minutes >=8) && Dryrun){
    digitalWrite(D8,LOW);
    digitalWrite(D6,LOW);
    motoron = "OFF";
    Blynk.logEvent("motorstate",String("Motor ") + motoron); 
    Blynk.virtualWrite(V3,0);
    Blynk.logEvent("error4", "Dry Run Detected,Reset Required");
    Blynk.virtualWrite(V4, 255);       
    Blynk.setProperty(V4, "color", "#FF0000"); 
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.setCursor(0, 1);
    lcd.print(String("0")+String(minutes)+String(":"));
    if (seconds < 10){
    lcd.setCursor(3, 1);
    lcd.print("  ");
    lcd.setCursor(3, 1);
    lcd.print(String("0")+String(seconds));
    }
    else {
    lcd.setCursor(3, 1);
    lcd.print("  ");
    lcd.setCursor(3, 1);
    lcd.print(seconds);
  }
  lcd.setCursor(9, 1); 
  lcd.print("     "); 
  lcd.setCursor(9, 1);
  lcd.print("Dry Run");
  relay = false;
  Dryrun = false;
  }
  }
/// ////////////////////////////////////////////////
//////////////////////////////////////////////////  
 if (percent != last_percent) {
  lcd.setCursor(9, 0); 
  lcd.print("    "); 
  lcd.setCursor(9, 0);
  lcd.print(percent);
  lcd.print("%");
  last_percent = percent;
  if (percent == 0){
  Blynk.setProperty(V2, "color", "#8B0000");
  Blynk.virtualWrite(V2, percent);
}
else if (percent == 25){
  Blynk.setProperty(V2, "color", "#FFA500");
  Blynk.virtualWrite(V2, percent);
}
else if (percent == 50){
  Blynk.setProperty(V2, "color", "#FFFF00");
  Blynk.virtualWrite(V2, percent);
}
else if (percent == 75){
  Blynk.setProperty(V2, "color", "#ADFF2F");
  Blynk.virtualWrite(V2, percent);
}
else if (percent == 100){
  Blynk.setProperty(V2, "color", "#008000");
  Blynk.virtualWrite(V2, percent);
}
}

if (isvirtualPinValue != virtualPinValue){
  Blynk.virtualWrite(V1, isvirtualPinValue);
  lcd.setCursor(6, 1);
  lcd.print("     ");
  lcd.setCursor(6, 1);
  lcd.print(isvirtualPinValue);
  virtualPinValue = isvirtualPinValue;
}
if (motoron != prevmotoron){
  lcd.setCursor(13, 0);
  lcd.print("   ");
  lcd.setCursor(13, 0);
  lcd.print(motoron);
  Blynk.virtualWrite(V3, String("Motor ") + motoron);
  prevmotoron = motoron;
}
previousMillis = currentMillis;
}
} 

// Function to convert hours, minutes, and seconds to total seconds
unsigned long timeInSeconds(int hours, int minutes, int seconds) {
  return (hours * 3600UL) + (minutes * 60UL) + seconds;
}

// Function to calculate motor runtime
void calculateMotorRuntime(int startH, int startM, int startS, int endH, int endM, int endS) {
  unsigned long startTime = timeInSeconds(startH, startM, startS);
  unsigned long endTime = timeInSeconds(endH, endM, endS);
  
  // Handle case when motor runs past midnight
  if (endTime < startTime) {
    endTime += 24 * 3600UL;  // Add 24 hours in seconds
  }

  // Calculate the total time the motor was on (in seconds)
  unsigned long totalTime = endTime - startTime;

  // Convert the total time back to hours, minutes, and seconds
  hours = totalTime / 3600;
  minutes = (totalTime % 3600) / 60;
  seconds = totalTime % 60;
}
String convertTo12HourFormat(int hour24, int minute24) {
  String period = "AM";
  int hour12 = hour24;

  // Check if PM
  if (hour24 >= 12) {
    period = "PM";
    if (hour24 > 12) {
      hour12 = hour24 - 12; // Convert to 12-hour format
    }
  } else if (hour24 == 0) {
    hour12 = 12; // Midnight edge case
  }

  // Pad hour and minute with zero if needed
  String hourStr = (hour12 < 10 ? "0" : "") + String(hour12);
  String minuteStr = (minute24 < 10 ? "0" : "") + String(minute24);

  // Combine the strings
  String time12h = hourStr + ":" + minuteStr + period;

  return time12h;
}
