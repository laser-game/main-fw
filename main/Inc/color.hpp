#ifndef __COLOR_INCLUDED__
#define __COLOR_INCLUDED__

#include "stm32f4xx_hal.h"
#include <vector>
#include <string>

using namespace std;

class Color
{
public:
    Color();
    void pwm_r_enable(bool ena = true);
    void pwm_g_enable(bool ena = true);
    void pwm_b_enable(bool ena = true);
    void rgb(uint8_t r, uint8_t g, uint8_t b);
};

#endif // ifndef __COLOR_INCLUDED__
