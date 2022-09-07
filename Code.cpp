/*        Your Name & E-mail: Angelica Simityan   asimi003@ucr.edu

 *         Discussion Section: 021

 *         Assignment: Lab # 5 Exercise # 2

 *         Exercise Description: [optional - include for your own benefit]

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link:

 https://youtube.com/shorts/rT9q55Mpyg4?feature=share

 */

enum States{INIT, S0, S1} SM1_state;
unsigned long lastRan;
const unsigned long period = 100;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
int b_buf = 0;

const int button = 2;
int count = 0;





const int xAxis_median = 100; // Adjust this if needed

// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
          if (digitalRead(button) == 0){
            state = S1;
          }
          else{
            state = S0;
          }
         //State Transition
        break;
      case S1:
            if (digitalRead(button) == 1){
                state = S0;
               
            }
            else{
                state = S1;
            }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            //State Action
            resetBuffer();

            if(analogRead(A0) > 850)
            {
               b_buf = b_buf | 1;
            }
            if (analogRead(A0) < 250)
            {
              b_buf = b_buf | 2;
            }
            if (analogRead(A1) < 200)
            {
              b_buf = b_buf | 4;
            }
            if (analogRead(A1) > 600)
            {
              b_buf = b_buf | 8;
            }
         
           writeBuffer(b_buf);

         //State Action
        break;
      case S1:
            //State Action
          resetBuffer();
          b_buf=0;
            
         
         //State Action
        break;
    }

    return state;
}


void setup() {
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
           
        }
        pinMode(button, INPUT_PULLUP);
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}
