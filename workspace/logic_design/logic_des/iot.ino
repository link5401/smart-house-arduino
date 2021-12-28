#include "iot.h"
#include <BlynkSimpleStream.h>
#include <Arduino.h>

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
