#include "display.h"
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "iot.h"
#include <BlynkSimpleStream.h>
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
float get_humid_value(){
    return humid;
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
///////////////////////////////////////////////////////////////

 char auth[] = "NEGIHQRiIs4o_LT2XCFuiAjMJ3vE6bp7";
void iot_setup(){
   Serial.begin(9600);
   Blynk.begin(Serial, auth);  
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
void iot_run(){
    Blynk.run();  
}
