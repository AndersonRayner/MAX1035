
#include "max1035/max1035.h"
#include <SPI.h>


#define CS_A2D        10

MAX1035 max1035(CS_A2D);


void setup() {  
  // Initialise serial
  SerialUSB.begin(115200);
  while (!SerialUSB) {}

  // Initialise the A2D converter
  SPI.begin();
  max1035.init();

}

void loop() {
    // Update A2D converter
    max1035.update(1);         // take an average of 1 samples

    // Display values on screen
    SerialUSB.print(max1035.get_value(0)); SerialUSB.print("  \t  ");
    SerialUSB.print(max1035.get_value(1)); SerialUSB.print("  \t  ");
    SerialUSB.print(max1035.get_value(2)); SerialUSB.print("  \t  ");
    SerialUSB.print(max1035.get_value(3)); SerialUSB.print("\n");

    delay(100);
}

