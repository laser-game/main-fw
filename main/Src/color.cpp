#include "color.hpp"
#include "globals.hpp"

ColorDriver::ColorDriver(
  TIM_HandleTypeDef *htim,
  uint32_t           tim_channel_r,
  uint32_t           tim_channel_g,
  uint32_t           tim_channel_b
)
{
    this->htim = htim;
    this->tim_channel_r = tim_channel_r;
    this->tim_channel_g = tim_channel_g;
    this->tim_channel_b = tim_channel_b;
    enable();
}

void ColorDriver::enable(void)
{
    HAL_TIM_Base_Start(htim);
    HAL_TIM_PWM_Start(htim, tim_channel_r);
    HAL_TIM_PWM_Start(htim, tim_channel_g);
    HAL_TIM_PWM_Start(htim, tim_channel_b);
}

void ColorDriver::disable(void)
{
    HAL_TIM_Base_Stop(htim);
    HAL_TIM_PWM_Stop(htim, tim_channel_r);
    HAL_TIM_PWM_Stop(htim, tim_channel_g);
    HAL_TIM_PWM_Stop(htim, tim_channel_b);
}

void ColorDriver::rgb(uint8_t r, uint8_t g, uint8_t b)
{
    *((uint32_t *) ((uint8_t *) &htim->Instance->CCR1 + tim_channel_r)) = r;
    *((uint32_t *) ((uint8_t *) &htim->Instance->CCR1 + tim_channel_g)) = g;
    *((uint32_t *) ((uint8_t *) &htim->Instance->CCR1 + tim_channel_b)) = b;

    global->gun->rgb(r, g, b);
}
