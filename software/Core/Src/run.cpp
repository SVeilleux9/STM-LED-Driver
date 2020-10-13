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

	LIS3DH Accellerometer(pin(GPIOA, GPIO_PIN_4), LEDS[19]);

//	size_t cnt=0;
	while (1){
		uint8_t data = Accellerometer.read();
		for(size_t i=0; i<8; i++){
			if(data & (1 << i)){
				LEDS[i].setHigh();
			}else{
				LEDS[i].setLow();
			}
		}
		LEDS[18].toggle();
		HAL_Delay(1000);
//		cnt = (cnt+1)%20;
	}

}
