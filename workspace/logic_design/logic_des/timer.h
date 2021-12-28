#ifdef __cplusplus
 extern "C" {
#endif



#define TIMER_CYCLE 10
#include "Arduino.h"

void timer_init(void );
void setTimer1(uint16_t DURATION);
void timer1_run(void );
uint8_t isTimer1(void );
/////////////////////////////////////////////////////////////////////////////////////////////////
void timer_init(void );
void setTimer2(uint16_t DURATION);
void timer2_run(void );
uint8_t isTimer2(void );
///////////////////////////////////////////////////////////////////////////////////////////////
void setTimerDoor(uint16_t DURATION);
void timerDoor_run();
uint8_t isTimerDoor();
////////////////////////////////////////////////////////////////////////////////////////////////
void setTimerSeg(uint16_t DURATION);
void timerSeg_run();
uint8_t isTimerSeg();

#ifdef __cplusplus
}
#endif
