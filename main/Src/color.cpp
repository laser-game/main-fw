#include "color.hpp"

extern TIM_HandleTypeDef htim3;

Color::Color()
{
    HAL_TIM_Base_Start(&htim3);
    pwm_r_enable();
    pwm_g_enable();
    pwm_b_enable();
}

void Color::pwm_r_enable(bool ena)
{
    if (ena)
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    else
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void Color::pwm_g_enable(bool ena)
{
    if (ena)
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    else
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
}

void Color::pwm_b_enable(bool ena)
{
    if (ena)
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    else
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

void Color::rgb(uint8_t r, uint8_t g, uint8_t b)
{
    TIM3->CCR1 = b;
    TIM3->CCR2 = g;
    TIM3->CCR3 = r;
}
