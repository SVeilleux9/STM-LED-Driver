#pragma once

#include "stm32f0xx_hal.h"

class pin
{
public:
	pin(GPIO_TypeDef* port, uint16_t pinNum) : m_port(port), m_pinNum(pinNum){
		//Initialize Everything of being off
		setLow();
	};
	const void toggle(){ HAL_GPIO_TogglePin(m_port, m_pinNum); }
	const void setLow(){ HAL_GPIO_WritePin(m_port, m_pinNum, GPIO_PIN_RESET); }
	const void setHigh(){ HAL_GPIO_WritePin(m_port, m_pinNum, GPIO_PIN_SET); }

private:
	GPIO_TypeDef* m_port;
	const uint16_t m_pinNum;
};
