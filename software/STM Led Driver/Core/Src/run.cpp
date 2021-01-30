#include "cmsis_os.h"

#include <run.h>
#include <LIS3DH.h>
#include <math.h>

#define PI 3.14159265

// Return value from [0,360]
constexpr float calculateAngle(int8_t x, int8_t y){
	float fy = -1*(float)y;
	float fx = (float)x;
	return std::atan2(fy,fx)*180/PI+180;
}

// This could be better, it does not have an equal window for LED 0 or 20  compared to the others
constexpr uint8_t angleToLed(float angle){
	uint8_t pin = floor(angle/18);
	if(pin > 19) pin = 19;
	if(pin < 0) pin = 0;
	return pin;
}

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

	//Have to set what Pin the CS is connected to.
	LIS3DH accellerometer(pin(GPIOA, GPIO_PIN_4));

	uint8_t lastLed=0;

	for(;;){

		auto x = accellerometer.getX();
		auto y = accellerometer.getY();
//		auto z = accellerometer.getZ(); //I dont use z-axis so I dont need it

		auto angle = calculateAngle(x,y);
		auto currLed = angleToLed(angle);

		// Set the LED pointing down on and turn last one off.
		LEDS[lastLed].setLow();
		LEDS[currLed].setHigh();
		lastLed = currLed;

		osDelay(100);
	}

}
