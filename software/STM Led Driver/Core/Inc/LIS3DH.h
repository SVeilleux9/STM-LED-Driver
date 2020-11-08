#pragma once

#include "ch.h"
#include "hal.h"
#include "pin.h"
#include "common.h"

#include <array>

class LIS3DH{
public:
	LIS3DH(pin CS_PIN) : m_CS_PIN(CS_PIN) {
		m_CS_PIN.setHigh();
		write({0x20, 0x77}); // write some stuff, cant remember. Need to look at datasheet.
		write({0x23, 0x08});
	};

	const int8_t getX(){
		return (int8_t)read(0x29);
	}

	const int8_t getY(){
		return (int8_t)read(0x2B);
	}

	const uint8_t getZ(){
		return (int8_t)read(0x2D);
	}

	const uint8_t read(uint8_t txBuff){

		uint8_t rxBuff;

		txBuff = txBuff | 0x80;

		m_CS_PIN.setLow();
		HAL_Delay(1);
		HAL_SPI_Transmit(&hspi1, &txBuff, 1, 1000);
		HAL_SPI_Receive(&hspi1, &rxBuff, 1, 1000);
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
