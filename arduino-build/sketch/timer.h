#line 1 "E:\\arduino-software\\workspace\\logic_design\\logic_des\\timer.h"
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
#ifdef __cplusplus
}
#endif
