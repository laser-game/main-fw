#ifndef __SOUND_PLAYER_INCLUDED__
#define __SOUND_PLAYER_INCLUDED__

#include "stm32f4xx_hal.h"
#include <vector>
#include <string>

using namespace std;

class SoundPlayer
{
private:
    DAC_HandleTypeDef *dac;
    DMA_HandleTypeDef *dma_dac;
    TIM_HandleTypeDef *tim;
    uint8_t channel;
public:
    SoundPlayer(DAC_HandleTypeDef *dac, DMA_HandleTypeDef *dma_dac, TIM_HandleTypeDef *tim, uint8_t channel);

    inline void wait_to_end_sound(void)
    {
        while (HAL_DMA_GetState(dma_dac) == HAL_DMA_STATE_BUSY)
            ;
    }

    inline void on(void)
    {
        HAL_GPIO_WritePin(MUTE_GPIO_Port, MUTE_Pin, GPIO_PIN_RESET);
    }

    inline void off(void)
    {
        HAL_GPIO_WritePin(MUTE_GPIO_Port, MUTE_Pin, GPIO_PIN_SET);
    }
};

#endif // ifndef __SOUND_PLAYER_INCLUDED__
