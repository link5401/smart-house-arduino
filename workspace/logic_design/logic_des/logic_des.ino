#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "timer.h"
#include "button_reading.h"
#include "fsm.h"
#define ledPin 13
const int DHTPIN = 8;      
const int DHTTYPE = DHT11; 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
 float humid = 0;
 float temp = 0;
void read_info(void ){
   humid = dht.readHumidity();
   temp = dht.readTemperature();
}
void display_info(void ){
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
  //pinmode
  pinMode(ledPin, OUTPUT);  
  setTimer1(10000);
  // initialize timer1 : interupt each 10ms
  timer_init();
  display_init();
  
  pinMode(12, INPUT_PULLUP);
  //button_init();
}



bool LED = false;
void loop(){
    if(isTimer1() == 1) {
      read_info();
      display_info();
      setTimer1(10000);      
    }
    if(isTimer2() == 1) toggle_LED_every_2s();  
    fsm_for_button();
}
