# smart-house-arduino
smart house implementation, simulated with Proteus and C
##  Proteus
We use a DHT11 and an LED to simulate the sensor and the display-ing of the values in Proteus

<img src="https://imgur.com/JGb94Hq.png">
## Arduino code
We use a timer structure to operate the functions of each component. 
In this case, we use an ISR of 10ms:
```cpp
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
}
```
Our timer are as follows:
```cpp
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
```
##IOT connections:
We use Blynk app and virutalize COM ports to set-up a connection between Proteus and our phones:
```cpp
void setup()
{
   Serial.begin(9600);
   Blynk.begin(Serial, auth);
 }
```
```cpp
BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  if(pinData==1){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
}
```
```cpp
void loop(){
   Blynk.run();
```
##Demo:
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/qkD3KExjTyg/0.jpg)](https://www.youtube.com/watch?v=qkD3KExjTyg)
