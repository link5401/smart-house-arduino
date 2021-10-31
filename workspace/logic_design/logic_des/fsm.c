#include "Arduino.h"
#include "fsm.h"
#include "button_reading.h"
#define NUMBER_OF_BUTTON 1
#define BUTTON1          0
#define TARGET_LED_PIN   13
enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_2_SECOND};

enum ButtonState buttonStates[NUMBER_OF_BUTTON] = {BUTTON_RELEASED};

void button_init(){
    digitalWrite(12, true);
}
bool state = false;
void toggle_LED_every_2s(){
            state = !state;
            digitalWrite(TARGET_LED_PIN, state);
            setTimer2(2000);
}
void fsm_for_button(){
    switch(buttonStates[BUTTON1]){
      case BUTTON_RELEASED:
          if(is_button_pressed(BUTTON1)) {
            state = !state;
            digitalWrite(TARGET_LED_PIN, state); 
            buttonStates[BUTTON1] = BUTTON_PRESSED;
          }
          break;
       case BUTTON_PRESSED:
          if(!is_button_pressed(BUTTON1)) buttonStates[BUTTON1] = BUTTON_RELEASED;
          else {
            if(is_button_press_2s(BUTTON1)){
              toggle_LED_every_2s();
              buttonStates[BUTTON1] = BUTTON_PRESSED_MORE_THAN_2_SECOND;
            }
          }
          break;
       case BUTTON_PRESSED_MORE_THAN_2_SECOND:
            if(!is_button_pressed(BUTTON1)){
              setTimer2(0);
              buttonStates[BUTTON1] = BUTTON_RELEASED;
           }
          break;        
    }
}
