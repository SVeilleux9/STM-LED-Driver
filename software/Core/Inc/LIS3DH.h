#pragma once

#include "stm32f0xx_hal.h"
#include "pin.h"
#include "common.h"

class LIS3DH{
public:
	LIS3DH(pin cs_pin, pin disp) : m_CS_PIN(cs_pin), m_disp(disp){};

	uint8_t read(){

		uint8_t txBuff[1] = {0xE8};
		uint8_t rxBuff[1] = {0xAA};

		m_CS_PIN.setLow();
		m_disp.setHigh();
		HAL_SPI_TransmitReceive_IT(&hspi1,(uint8_t *)txBuff,(uint8_t *)rxBuff,1);
		while( (&hspi1)->State == HAL_SPI_STATE_BUSY );
		m_CS_PIN.setHigh();
		m_disp.setLow();

		return rxBuff[0];
	};

	void write(){

	}

private:
	pin m_CS_PIN;
	pin m_disp;
};
