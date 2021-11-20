#line 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino"
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <dht_nonblocking.h>
#include "timer.h"
#include "button_reading.h"
#include "fsm.h"
#include "display.h"

//
//#define BLYNK_PRINT DebugSerial
//#include <SoftwareSerial.h>
//SoftwareSerial DebugSerial(2, 3); // RX, TX
//

#include <BlynkSimpleStream.h>
#define ledPin 13
#define SDCARD_CS 4
//#define BLYNK_TEMPLATE_ID   "TMPLyoutuC_H"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 char auth[] = "NEGIHQRiIs4o_LT2XCFuiAjMJ3vE6bp7";

#line 24 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino"
void setup();
#line 42 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino"
void loop();
#line 12 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino"
void read_info();
#line 17 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino"
void display_info();
#line 26 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino"
void display_init();
#line 24 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino"
void setup()
{

   Serial.begin(9600);
   Blynk.begin(Serial, auth);
  pinMode(ledPin, OUTPUT);  
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  setTimer1(1000);
  // initialize timer1 : interupt each 10ms
  timer_init();
  display_init();
  
  pinMode(12, INPUT_PULLUP);
  //button_init();
}

bool LED = false;
void loop(){
   Blynk.run();
    if(isTimer1() == 1) {
      read_info();
      display_info();
      setTimer1(1000);      
    }
    if(isTimer2() == 1) toggle_LED_every_2s();  
    fsm_for_button();
}

#line 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
const int DHTPIN = 8;      
const int DHTTYPE = DHT11; 
DHT dht(DHTPIN, DHTTYPE);
//DHT_nonblocking ndht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
 float humid = 0;
 float temp = 0;
 
void read_info(){
   humid = dht.readHumidity();
   temp = dht.readTemperature();
}

void display_info(){
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(humid);
}

void display_init(){
     lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    dht.begin();
}

