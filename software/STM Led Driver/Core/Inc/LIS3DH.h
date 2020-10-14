#pragma once

#include "stm32f0xx_hal.h"
#include "pin.h"
#include "common.h"

class LIS3DH{
public:
	LIS3DH(){};

	uint8_t read(){

		uint8_t txBuff[1] = {0x8F}; // address to read x-axis
		uint8_t rxBuff[1] = {0x00};


		HAL_SPI_TransmitReceive(&hspi1, txBuff, rxBuff, 1, 1000);
		  	while( (&hspi1)->State == HAL_SPI_STATE_BUSY );

		return rxBuff[0];
	}

	void write(){

	}

private:
};
