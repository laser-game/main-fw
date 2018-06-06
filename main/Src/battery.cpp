#include "battery.hpp"

Battery::Battery(I2C_HandleTypeDef *hi2c, TIM_HandleTypeDef *htim)
{
    this->hi2c = hi2c;
    this->htim = htim;
    start_tim();
}
