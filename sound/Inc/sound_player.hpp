#ifndef __SOUND_PLAYER_INCLUDED__
#define __SOUND_PLAYER_INCLUDED__

#include "stm32f4xx_hal.h"
#include "cm_sound.hpp"
#include "sound.hpp"

using namespace std;

class SoundPlayer
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
    SoundPlayer(DAC_HandleTypeDef *dac, DMA_HandleTypeDef *dma_dac, TIM_HandleTypeDef *tim, UART_HandleTypeDef *uart, uint8_t channel);

    inline bool is_sound_playing(void)
    {
        return (HAL_DMA_GetState(dma_dac) == HAL_DMA_STATE_BUSY) ? true : false;
    }

    inline uint8_t get_uart_rx_buffer(void)
    {
        return uart_rx_buffer;
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

    inline void rx(void)
    {
        HAL_UART_Receive_IT(uart, &uart_rx_buffer, 1);
    }

    void play(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
    void play_and_wait(uint32_t *p_data, uint32_t size, uint32_t alignment = DAC_ALIGN_12B_R);
    void cmd(uint8_t cmd);
};


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif // ifndef __SOUND_PLAYER_INCLUDED__
