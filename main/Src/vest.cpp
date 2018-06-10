#include "vest.hpp"
#include "globals.hpp"

Vest::Vest(void)
{
    read_address();
    global->gun->set_address(get_address());
}

void Vest::read_address(void)
{
    uint8_t tmp = gpio_pin_state_to_int(HAL_GPIO_ReadPin(A0_GPIO_Port, A0_Pin));
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A1_GPIO_Port, A1_Pin)) << 1;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A2_GPIO_Port, A2_Pin)) << 2;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A3_GPIO_Port, A3_Pin)) << 3;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A4_GPIO_Port, A4_Pin)) << 4;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A5_GPIO_Port, A5_Pin)) << 5;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A6_GPIO_Port, A6_Pin)) << 6;
    tmp += gpio_pin_state_to_int(HAL_GPIO_ReadPin(A7_GPIO_Port, A7_Pin)) << 7;

    set_address(tmp);
}
