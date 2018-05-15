#include "sound_player.hpp"

extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_dac1;
extern TIM_HandleTypeDef htim6;

SoundPlayer::SoundPlayer(DAC_HandleTypeDef *dac, DMA_HandleTypeDef *dma_dac, TIM_HandleTypeDef *tim, uint8_t channel)
{
    off();
    this->dac     = dac;
    this->dma_dac = dma_dac;
    this->tim     = tim;
    this->channel = channel;
    HAL_TIM_Base_Start(tim);
    HAL_DAC_Start(dac, channel);
    HAL_DAC_SetValue(dac, channel, DAC_ALIGN_12B_R, 0);
}
