#include "timer.h"
#include "Arduino.h"



void timer_init(){
  cli();                      // disable all interrupts
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A
  OCR1A = 625 ;               //Finally we set compare register A to this value 
  sei();                      //Enable back the interrupts
}
//timer interrupt service call
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0; 
  timer1_run();
  button_reading();
  timer2_run();
  timerDoor_run();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static uint16_t timer1_counter = 0;
static uint8_t timer1_flag = 0;
void setTimer1(uint16_t DURATION){
     timer1_counter = DURATION/TIMER_CYCLE;
     timer1_flag = 0;
}

void timer1_run(){
    if(timer1_counter > 0){
      timer1_counter--;
      if(timer1_counter == 0) timer1_flag = 1;  
    }  
}

uint8_t isTimer1(){
    return (timer1_flag == 1) ? 1 : 0;  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint16_t timer2_counter = 0;
static uint8_t timer2_flag = 0;
void setTimer2(uint16_t DURATION){
     timer2_counter = DURATION/TIMER_CYCLE;
     timer2_flag = 0;
}

void timer2_run(){
    if(timer2_counter > 0){
      timer2_counter--;
      if(timer2_counter == 0) timer2_flag = 1;  
    }  
}

uint8_t isTimer2(){
    return (timer2_flag == 1) ? 1 : 0;  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint16_t timerDoor_counter = 0;
static uint8_t timerDoor_flag = 0;
void setTimerDoor(uint16_t DURATION){
    timerDoor_counter = DURATION/TIMER_CYCLE;
    timerDoor_flag = 0;  
}
void timerDoor_run(){
    if(timerDoor_counter > 0){
      timerDoor_counter--;
      if(timerDoor_counter == 0) timerDoor_flag = 1;  
    }  
}
uint8_t isTimerDoor(){
    return (timerDoor_flag == 1) ? 1 : 0;  
}
////////////////////////////////////////////////////////////////////////////////////////
