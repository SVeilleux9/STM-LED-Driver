#include <run.h>
#include <LIS3DH.h>

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

	while (1){
		LEDS[19].setHigh();
		uint8_t data = accellerometer.read();
		LEDS[19].setLow();

		for(size_t i=0; i<8; i++){
			if(data & (1 << i)){
				LEDS[7-i].setHigh();
			}else{
				LEDS[7-i].setLow();
			}
		}
		LEDS[18].toggle();
		HAL_Delay(1000);
//		cnt = (cnt+1)%20;
	}

}
