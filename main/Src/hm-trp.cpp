#include "hm-trp.hpp"

extern UART_HandleTypeDef huart2;

HMTRP::HMTRP()
{
    config(false);
    enable(true);
}

void HMTRP::enable(bool ena)
{
    HAL_GPIO_WritePin(RF_ENABLE_GPIO_Port, RF_ENABLE_Pin, (ena) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HMTRP::config(bool cnf)
{
    HAL_GPIO_WritePin(RF_CONFIG_GPIO_Port, RF_CONFIG_Pin, (cnf) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HMTRP::send(string str)
{
    HAL_UART_Transmit(&huart2, (uint8_t *) str.c_str(), str.size(), 0xFFFFFF);
}
