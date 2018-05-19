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

    inline bool is_sound_playing(void)
    {
        return (HAL_DMA_GetState(dma_dac) == HAL_DMA_STATE_BUSY) ? true : false;
    }

    inline void wait_to_end_sound(void)
    {
        while (is_sound_playing())
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

    void play(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
    void play_and_wait(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
};

#endif // ifndef __SOUND_PLAYER_INCLUDED__
