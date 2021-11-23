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

void setup()
{

  // Serial.begin(9600);
  // Blynk.begin(Serial, auth);
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
BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
}
bool LED = false;
void loop(){
   //Blynk.run();
    if(isTimer1() == 1) {
      read_info();
      display_info();
      setTimer1(1000);      
    }
    if(isTimer2() == 1) toggle_LED_every_2s();  
    fsm_for_button();
}
