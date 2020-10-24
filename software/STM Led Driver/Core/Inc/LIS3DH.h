#pragma once

#include "stm32f0xx_hal.h"
#include "pin.h"
#include "common.h"

#include <array>

class LIS3DH{
public:
	LIS3DH() : m_CS_PIN(pin(GPIOA, GPIO_PIN_4)) {
		m_CS_PIN.setHigh();
		write({0x20, 0x77}); // write some stuff, cant remember. Need to look at datasheet.
		write({0x23, 0x08});
	};

	std::array<int8_t, 1> read(std::array<uint8_t, 1> txBuff){

		std::array<int8_t, 1> rxBuff;

		txBuff[0] = txBuff[0] | 0x80;

		m_CS_PIN.setLow();
		HAL_Delay(1);
		HAL_SPI_Transmit(&hspi1, txBuff.data(), txBuff.size(), 1000);
		HAL_SPI_Receive(&hspi1, (uint8_t*)rxBuff.data(), rxBuff.size(), 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		m_CS_PIN.setHigh();

		return rxBuff;
	}

	void write(std::array<uint8_t, 2> txBuff){

		m_CS_PIN.setLow();
		HAL_Delay(1);
		HAL_SPI_Transmit(&hspi1, txBuff.data(), txBuff.size(), 1000);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		m_CS_PIN.setHigh();

	}

private:
	pin m_CS_PIN;
};
