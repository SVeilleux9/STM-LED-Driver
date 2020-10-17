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

	HAL_Delay(3000);

	uint8_t rxBuff[1] = {0};
	uint8_t txBuff[1] = {0};

	LIS3DH accellerometer;
//	accellerometer.write();

	while (1){
		LEDS[19].setHigh();
		txBuff[0] = 0x29;
		rxBuff[0] = 0x00;
		accellerometer.read(txBuff, rxBuff, 1);
		LEDS[19].setLow();

		for(size_t i=0; i<8; i++){
			if(rxBuff[0] & (1 << i)){
				LEDS[i].setHigh();
			}else{
				LEDS[i].setLow();
			}
		}
		LEDS[18].toggle();
		HAL_Delay(10);
//		cnt = (cnt+1)%20;
	}

}
