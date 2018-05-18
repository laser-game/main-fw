#include "sound_player.hpp"

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

void SoundPlayer::play(uint32_t *p_data, uint32_t size, uint32_t alignment)
{
    HAL_DAC_Start_DMA(dac, channel, p_data, size, alignment);
}

void SoundPlayer::play_and_wait(uint32_t *p_data, uint32_t size, uint32_t alignment)
{
    on();
    play(p_data, size, alignment);
    wait_to_end_sound();
    off();
}
