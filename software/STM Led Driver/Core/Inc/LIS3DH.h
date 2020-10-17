#pragma once

#include "stm32f0xx_hal.h"
#include "pin.h"
#include "common.h"

#include <array>

class LIS3DH{
public:
	LIS3DH() : m_CS_PIN(pin(GPIOA, GPIO_PIN_4)) {
		m_CS_PIN.setHigh();
//		With these disabled then the board will show 00110011 from LEDS[7:0]
//		Shit breaks when writing to any register, even if you dont change anything.

		write({0x20, 0x77});
		write({0x23, 0x08});
	};

	void read(uint8_t* txBuff, uint8_t* rxBuff, size_t len){

		txBuff[0] = txBuff[0] | 0x80;

		m_CS_PIN.setLow();
		HAL_Delay(1);
		HAL_SPI_Transmit(&hspi1, txBuff, len, 1000);
		HAL_SPI_Receive(&hspi1, rxBuff, len, 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		m_CS_PIN.setHigh();
		HAL_Delay(1);

	}

	void write(std::array<uint8_t, 2> txBuff){

		m_CS_PIN.setLow();
		HAL_Delay(1);
		HAL_SPI_Transmit(&hspi1, txBuff.data(), txBuff.size(), 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		m_CS_PIN.setHigh();

		HAL_Delay(100);

	}

private:
	pin m_CS_PIN;
};
