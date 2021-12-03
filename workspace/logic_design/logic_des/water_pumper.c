#include "water_pumper.h"
#include "arduino.h"
#include "timer.h"
#include "display.h"
#define PUMP  10
void open_pump(){
  digitalWrite(PUMP , HIGH);
}
void close_pump(){
  digitalWrite(PUMP , LOW);
}

void pump_run(){
    if(get_humid_value() <= 30) open_pump();
    else close_pump();
}
