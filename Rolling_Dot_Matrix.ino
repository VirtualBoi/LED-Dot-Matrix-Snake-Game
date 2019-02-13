#include "LedControl.h"
#include "binary.h"

int xVar = 0;
int yVar = 0;
// set the three pins used on the arduino as 16, 5, 4 (NodeMCU Board)
LedControl lc = LedControl(16, 4, 5, 1);

unsigned long delaytime = 600;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  //initiallize the dot matrix 
}


void loop() {
  lc.clearDisplay(0);
  if (xVar <= 7) {
    xVar++;
  }
  else if (xVar >= 8) {
    xVar = 0;
    if (yVar <= 7) {
      yVar++;
    }
    else if (yVar >= 8) {
      yVar = 0;
    }
  }
    //move the LED position by one in x then one in y as x gets to its max
  lc.setLed(0, xVar, yVar, true);
  delay(80);
}
