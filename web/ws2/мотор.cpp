мотор

#include <AmperkaStepper.h>

#define SPEED_1      5 
#define DIR_1        4
 
#define SPEED_2      6
#define DIR_2        7
 
void setup() {
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
} 
 
void loop() {
 digitalWrite(DIR_1, HIGH);
  analogWrite(SPEED_1, 255);
}