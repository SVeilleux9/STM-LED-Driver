#include <run.h>
#include <LIS3DH.h>
#include <math.h>

#define PI 3.14159265
#define PI2 1.57079632

void run(){
	pin LEDS[] {pin(GPIOA, GPIO_PIN_11),
				pin(GPIOB, GPIO_PIN_15),
				pin(GPIOB, GPIO_PIN_14),
				pin(GPIOB, GPIO_PIN_13),
				pin(GPIOB, GPIO_PIN_12),
				pin(GPIOB, GPIO_PIN_11),
				pin(GPIOB, GPIO_PIN_10),
				pin(GPIOB, GPIO_PIN_2),
				pin(GPIOB, GPIO_PIN_1),
				pin(GPIOB, GPIO_PIN_0),
				pin(GPIOC, GPIO_PIN_15),
				pin(GPIOC, GPIO_PIN_14),
				pin(GPIOC, GPIO_PIN_13),
				pin(GPIOB, GPIO_PIN_9),
				pin(GPIOB, GPIO_PIN_8),
				pin(GPIOB, GPIO_PIN_5),
				pin(GPIOB, GPIO_PIN_4),
				pin(GPIOB, GPIO_PIN_3),
				pin(GPIOA, GPIO_PIN_15),
				pin(GPIOA, GPIO_PIN_12)};

	for(size_t i = 0; i<19; i++){
		LEDS[i].setLow();
	}

	LIS3DH accellerometer;
	uint8_t lastLed=0;
	while (1){
		//I dont know if the read should return a vector so you can read multiple things at once?
		//Or if this is fine just calling read multiple times.
		auto x = accellerometer.read({0x29});
		auto y = accellerometer.read({0x2B});

		// Add PI because I want the angle in [0, 360]
		float angle = (std::atan2(-1*(float)y[0],(float)x[0])+PI)*180/PI;

		// This could be better, it does not have an equal window for LED 0 or 20  compared to the others
		uint8_t currLed = floor((angle+9)/18);

		// Set the LED pointing down on and turn last one off. This doesnt need this if statement technically
		LEDS[currLed].setHigh();
		if(currLed != lastLed){
			LEDS[lastLed].setLow();
			lastLed = currLed;
		}

		HAL_Delay(10);
	}

}
