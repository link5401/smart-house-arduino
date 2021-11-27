#include "pir.h"
#include "Arduino.h"
#define RELAY_OPEN  7
#define RELAY_CLOSE 6
#define PIR         9
bool door_state = false;
void open_door(){
  door_state = true;
  digitalWrite(RELAY_OPEN, 1);
  digitalWrite(RELAY_CLOSE, 0);  
}
void close_door(){
  door_state = false;
  digitalWrite(RELAY_OPEN, 0);
  digitalWrite(RELAY_CLOSE,1);  
}
void pir_setup(){
  pinMode(RELAY_OPEN, OUTPUT);
  pinMode(RELAY_CLOSE, OUTPUT);
  pinMode(PIR,   INPUT);  
}

void pir_run(){
if(digitalRead(PIR) == HIGH) open_door();
else close_door();
}
