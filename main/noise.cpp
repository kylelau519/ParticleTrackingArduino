#include "noise.h"
#include <Arduino.h>  // Required for Arduino functions
#include <Adafruit_NeoPixel.h>


void runNoise(LEDSystem* ledControl) {
	for(int i=0; i<5; i++){
    for(int j=0; j<7; j++){
      int nLights = random(10,30);
		  for(int k=0; k<nLights; k++){
			  int pixel = random(0,100);
			  int r = random(50,255);
			  int g = random(50,255);
			  int b = random(50,255);
        ledControl->setPixel(j,pixel, r,g,b);
		  }
    }
		ledControl->show();
		delay(100);

		// Turn off all the lights
		ledControl->clear();
	}
}
