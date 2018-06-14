/*
 *  @author     Couet David
 *  @version    v1.0
 *  @date       14/06/2018
 *  @brief      The code implement the control loop for the motors. 
 *              Inputs : 
 *                    Hall sensors
 *                    Commands from controller
 *              Outputs :
 *                    PWM for each H bridge
 */
#define DEBUG

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Debug started");
  #endif
}

void loop() {
  

}
