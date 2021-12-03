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
