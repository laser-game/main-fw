#ifndef __SOUND_PLAYER_INCLUDED__
#define __SOUND_PLAYER_INCLUDED__

#include "stm32f4xx_hal.h"
#include "cm-sound.hpp"
#include "cm-uart.hpp"
#include "sound.hpp"

using namespace std;

class SoundPlayer : public UART
{
private:
    DAC_HandleTypeDef *dac;
    DMA_HandleTypeDef *dma_dac;
    TIM_HandleTypeDef *tim;
    UART_HandleTypeDef *uart;
    uint8_t channel;
    uint8_t uart_rx_buffer;
    sound_set_t sound_set;
public:
    SoundPlayer(
      UART_HandleTypeDef *uart,
      DAC_HandleTypeDef * dac,
      DMA_HandleTypeDef * dma_dac,
      TIM_HandleTypeDef * tim,
      uint8_t             channel
    );

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
        HAL_DAC_Stop_DMA(dac, channel);
    }

    inline void set_pin_is_playing(bool level)
    {
        HAL_GPIO_WritePin(SOUND_IS_PLAYING_GPIO_Port, SOUND_IS_PLAYING_Pin, (level) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void play(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
    void play_and_wait(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
    void cmd(uint8_t cmd);
};


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

extern SoundPlayer *sound_player;

#endif // ifndef __SOUND_PLAYER_INCLUDED__
