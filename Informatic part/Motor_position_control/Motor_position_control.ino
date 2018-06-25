/*
 *  @author     Couet David
 *  @version    v1.0
 *  @date       14/06/2018
 *  @brief      
 */

/* Includes ----------------------------------------------------------*/

#include "PID.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/

#define kp1 1
#define kp2 1
#define ki1 1
#define ki2 1

/* Variables ---------------------------------------------------------*/

volatile uint16_t cptA1 = 0, cptB1 = 0;
volatile uint16_t cptA2 = 0, cptB2 = 0;
volatile byte stateA1 = 0, stateB1 = 0;
volatile byte stateA2 = 0, stateB2 = 0;
volatile byte stateA1prec = 0, stateB1prec = 0;
volatile byte stateA2prec = 0, stateB2prec = 0;

struct pid_controller pid1;
struct pid_controller pid2;

float in1 = 0, in2 = 0;
float out1 = 0, out2 = 0;
float set1 = 0, set2 = 0;

/* Function prototypes -----------------------------------------------*/

void interruptInit();

/* Setup  ------------------------------------------------------------*/

void setup() {
  //Start uart transmission
  Serial.begin(9600);

  //Set interrupts
  interruptInit();

  //Create pid controller
  pid_create(&pid1, &in1, &out1, &set1, kp1, ki1, 0);
  pid_create(&pid2, &in2, &out2, &set2, kp2, ki2, 0);
}

/* Loop --------------------------------------------------------------*/

void loop() {
  delay(1000);
  Serial.println(cptA1);
}

/* Function ----------------------------------------------------------*/

void interruptInit(){
  //pin 2 3 4 5 as input
  DDRD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5));
  
  PCICR |= (1<<PCIE2);  //enable interrupt on PCINT[23:16]
  PCMSK2 |= ((1<<PCINT18)|(1<<PCINT19)|(1<<PCINT20)|(1<<PCINT21));

  //enable interrupt
  SREG |= (1<<7);  
}

ISR(PCINT2_vect){
  //This is the way it works
  
  stateA1 = PIND & (1<<PIND2);
  stateB1 = PIND & (1<<PIND3);
  stateA2 = PIND & (1<<PIND4);
  stateB2 = PIND & (1<<PIND5);
  
  if(stateA1 != stateA1prec){
    stateA1prec = stateA1;
    cptA1++;
  }
  
  if(stateB1 != stateB1prec){
    stateB1prec = stateB1;
    cptB1++;
  }
  
  if(stateA2 != stateA2prec){
    stateA2prec = stateA2;
    cptA2++;
  }
  
  if(stateB2 != stateB2prec){
    stateB2prec = stateB2;
    cptB2++;
  }
}
