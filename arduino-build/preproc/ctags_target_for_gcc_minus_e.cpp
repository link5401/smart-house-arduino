# 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino"
# 2 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 3 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 4 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 5 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 6 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 7 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 8 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 9 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2
# 10 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2

//
//#define BLYNK_PRINT DebugSerial
//#include <SoftwareSerial.h>
//SoftwareSerial DebugSerial(2, 3); // RX, TX
//

# 18 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\logic_des.ino" 2


//#define BLYNK_TEMPLATE_ID   "TMPLyoutuC_H"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 char auth[] = "NEGIHQRiIs4o_LT2XCFuiAjMJ3vE6bp7";

void setup()
{

   Serial.begin(9600);
   Blynk.begin(Serial, auth);
  pinMode(13, 0x1);
  pinMode(12, 0x1);
  pinMode(11, 0x1);
  setTimer1(1000);
  // initialize timer1 : interupt each 10ms
  timer_init();
  display_init();

  pinMode(12, 0x2);
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
# 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino"
# 2 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino" 2
# 3 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino" 2
# 4 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\display.ino" 2
const int DHTPIN = 8;
const int DHTTYPE = 11 /**< DHT TYPE 11 */;
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
