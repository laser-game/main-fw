#ifndef __COLOR_INCLUDED__
#define __COLOR_INCLUDED__

#include "stm32f4xx_hal.h"

#include <vector>
#include <string>
using namespace std;

class ColorDriver
{
private:
    TIM_HandleTypeDef *htim;
    uint32_t tim_channel_r;
    uint32_t tim_channel_g;
    uint32_t tim_channel_b;
public:
    ColorDriver(TIM_HandleTypeDef *htim, uint32_t tim_channel_r, uint32_t tim_channel_g, uint32_t tim_channel_b);
    void enable(void);
    void disable(void);
    void rgb(uint8_t r, uint8_t g, uint8_t b);
};

#endif // ifndef __COLOR_INCLUDED__
