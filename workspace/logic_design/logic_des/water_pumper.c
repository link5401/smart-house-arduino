#include "water_pumper.h"
#include "arduino.h"
#include "timer.h"
#include "display.h"

#define PUMP  10

////////////////////////////////////////////////PUMPER///////////
void open_pump(){
  digitalWrite(PUMP , HIGH);
}
void close_pump(){
  digitalWrite(PUMP , LOW);
}

void pump_run(){
    if(read_moist() <= 30) open_pump();
    else close_pump();
}
