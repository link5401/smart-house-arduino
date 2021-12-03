#include "pir.h"
#include "Arduino.h"
#include "timer.h"
#define RELAY_OPEN  7
#define RELAY_CLOSE 6
#define PIR         9
#define DOOR_DELAY  2000
enum DoorState{OPENNING, CLOSING , CLOSED, OPENNED};
enum DoorState door_state = CLOSED;
bool secure = true;
void open_door(){
  setTimerDoor(DOOR_DELAY);
  digitalWrite(RELAY_OPEN, 1);
  digitalWrite(RELAY_CLOSE, 0);  
  digitalWrite(PIR, 0);
}
void close_door(){
  setTimerDoor(DOOR_DELAY);
  digitalWrite(RELAY_OPEN, 0);
  digitalWrite(RELAY_CLOSE,1);  

}
void pir_setup(){
  pinMode(RELAY_OPEN, OUTPUT);
  pinMode(RELAY_CLOSE, OUTPUT);
  pinMode(PIR,   INPUT);  
}
void reset_door(){
    digitalWrite(RELAY_OPEN, 0);
    digitalWrite(RELAY_CLOSE,0);  
}

void pir_run(){
    switch(door_state){
    case CLOSED:
        if(digitalRead(PIR) == 1) door_state = OPENNING;
        break;
    case OPENNED:
        if(digitalRead(PIR) == 0) door_state = CLOSING;
        break;
    case OPENNING:
        open_door();
        door_state = OPENNED;
        break;
    case CLOSING:
        close_door();
        door_state = CLOSED;
        break;      
    }
}
