#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <dht_nonblocking.h>
#include "timer.h"
#include "button_reading.h"
#include "fsm.h"
#include "display.h"
#include "pir.h"
#include "water_pumper.h"
#include "iot.h"
#define PUMPER 10 
#define BUTTON 12
#define MOIST_SENSOR A1
//
//#define BLYNK_PRINT DebugSerial
//#include <SoftwareSerial.h>
//SoftwareSerial DebugSerial(2, 3); // RX, TX


#include <BlynkSimpleStream.h>
#define ledPin 13
#define SDCARD_CS 4
//#define BLYNK_TEMPLATE_ID   "TMPLyoutuC_H"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
//

  pir_setup();
  iot_setup();
  
  pinMode(MOIST_SENSOR, INPUT);
  pinMode(PUMPER, OUTPUT);
  setTimer1(1000);
  // initialize timer1 : interupt each 10ms
  timer_init();
  display_init();
  
  pinMode(BUTTON, INPUT_PULLUP);

  //button_init();
}
bool LED = false;
void loop(){
   
    iot_run();
    pir_run();
    pump_run();
    if(isTimer1() == 1) {
      
      read_info();
      display_info();
      setTimer1(1000);      
    }
    if(isTimer2() == 1) toggle_LED_every_2s();  
    if(isTimerDoor() == 1){ reset_door();}

    fsm_for_button();
    

}
