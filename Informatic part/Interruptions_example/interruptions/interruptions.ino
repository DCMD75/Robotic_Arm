

volatile uint16_t cptA1 = 0, cptB1 = 0;
volatile uint16_t cptA2 = 0, cptB2 = 0;
volatile byte stateA1 = 0, stateB1 = 0;
volatile byte stateA2 = 0, stateB2 = 0;
volatile byte stateA1prec = 0, stateB1prec = 0;
volatile byte stateA2prec = 0, stateB2prec = 0;

void setup() {
  
  Serial.begin(9600);
  
  //pin 2 3 as input
  DDRD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5));
  
  PCICR |= (1<<PCIE2);  //enable interrupt on PCINT[23:16]
  PCMSK2 |= ((1<<PCINT18)|(1<<PCINT19)|(1<<PCINT20)|(1<<PCINT21)); //only on PCINT18 and 19 pin2 and pin3

  //enable interrupt
  SREG |= (1<<7);  
}

void loop() {
  delay(1000);
  Serial.print(cptA1);
  Serial.print(" ");
  Serial.println(cptA2);
}

ISR(PCINT2_vect){
    
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

