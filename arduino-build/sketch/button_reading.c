#line 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\button_reading.c"
#include "button_reading.h"
#include "Arduino.h"
#define NUMBER_OF_BUTTON              1
#define DURATION_FOR_AUTO_INCREASING  200

#define BUTTON_IS_RELEASED             true
#define BUTTON_IS_PRESSED           false

static bool buttonBuffer[NUMBER_OF_BUTTON] = {BUTTON_IS_RELEASED};

static bool debounceButtonBuffer1[NUMBER_OF_BUTTON] = {BUTTON_IS_RELEASED};

static bool debounceButtonBuffer2[NUMBER_OF_BUTTON] = {BUTTON_IS_RELEASED};

static uint16_t counterForButtonPress2s[NUMBER_OF_BUTTON] = {0};

static uint8_t flagForButtonPress2s[NUMBER_OF_BUTTON] = {0};

static uint8_t buttonPin[NUMBER_OF_BUTTON] = {12};

unsigned char is_button_pressed(uint8_t index){
    if(index >= NUMBER_OF_BUTTON) return 0 ;
    return(buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_press_2s(uint8_t index){
   if(index >= NUMBER_OF_BUTTON) return 0;
   return (flagForButtonPress2s[index] == 1);
}

void button_reading(void){
  for(uint8_t i = 0; i < NUMBER_OF_BUTTON; i++){
    //read pin, check for bounce
    debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
    debounceButtonBuffer1[i] = digitalRead(buttonPin[i]);

    if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
      buttonBuffer[i] = debounceButtonBuffer1[i];
      if(buttonBuffer[i] == BUTTON_IS_PRESSED){
        if(counterForButtonPress2s[i] < DURATION_FOR_AUTO_INCREASING){
          counterForButtonPress2s[i]++;
        } else {
          flagForButtonPress2s[i] = 1;

        }

      } else {
        counterForButtonPress2s[i] = 0;
        flagForButtonPress2s[i] = 0;
      }
    }
  } 
}
