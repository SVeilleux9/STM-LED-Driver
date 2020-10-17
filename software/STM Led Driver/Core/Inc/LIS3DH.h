#pragma once

#include "stm32f0xx_hal.h"
#include "pin.h"
#include "common.h"

#include <array>

class LIS3DH{
public:
	LIS3DH() {
//		With these disabled then the board will show 00110011 from LEDS[7:0]
//		Shit breaks when writing to any register, even if you dont change anything.

		write({0x20, 0x77});
		write({0x23, 0x00});
	};

	void read(uint8_t* txBuff, uint8_t* rxBuff, size_t len){

		txBuff[0] = txBuff[0] | 0x80;

		HAL_SPI_TransmitReceive(&hspi1, txBuff, rxBuff, len, 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );

	}

	void write(std::array<uint8_t, 2> txBuff){

		HAL_SPI_Transmit(&hspi1, txBuff.data(), txBuff.size(), 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		HAL_Delay(100);

	}

private:
//	pin m_CS_PIN;
};
