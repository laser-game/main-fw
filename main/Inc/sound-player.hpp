#ifndef __SOUND_PLAYER_INCLUDED__
#define __SOUND_PLAYER_INCLUDED__

#include "stm32f4xx_hal.h"

#include "cm-uart.hpp"
#include "cm-sound.hpp"


class SoundPlayer : public UART
{
public:
    inline SoundPlayer(UART_HandleTypeDef *huart) : UART(huart)
    { }

    inline bool is_sound_playing(void)
    {
        return (HAL_GPIO_ReadPin(SOUND_IS_PLAYING_GPIO_Port, SOUND_IS_PLAYING_Pin) == GPIO_PIN_SET) ? true : false; // TODO removed true and false
    }

    inline void set_sound_set_cz(void)
    {
        tx(SOUND_CMD_SET_SOUND_SET_CZ);
    }

    inline void set_sound_set_en(void)
    {
        tx(SOUND_CMD_SET_SOUND_SET_EN);
    }

    inline void stop(void)
    {
        tx(SOUND_CMD_STOP);
    }

    inline void play_activated(void)
    {
        tx(SOUND_CMD_PLAY_ACTIVATED);
    }

    inline void play_gun(void)
    {
        tx(SOUND_CMD_PLAY_GUN);
    }

    inline void play_dont_give_up(void)
    {
        tx(SOUND_CMD_PLAY_DONT_GIVE_UP);
    }

    inline void play_game_over(void)
    {
        tx(SOUND_CMD_PLAY_GAME_OVER);
    }

    inline void play_go(void)
    {
        tx(SOUND_CMD_PLAY_GO);
    }

    inline void play_keep_going(void)
    {
        tx(SOUND_CMD_PLAY_KEEP_GOING);
    }

    inline void play_number_1(void)
    {
        tx(SOUND_CMD_PLAY_NUMBER_1);
    }

    inline void play_number_2(void)
    {
        tx(SOUND_CMD_PLAY_NUMBER_2);
    }

    inline void play_number_3(void)
    {
        tx(SOUND_CMD_PLAY_NUMBER_3);
    }

    inline void play_number_4(void)
    {
        tx(SOUND_CMD_PLAY_NUMBER_4);
    }

    inline void play_number_5(void)
    {
        tx(SOUND_CMD_PLAY_NUMBER_5);
    }

    inline void play_play(void)
    {
        tx(SOUND_CMD_PLAY_PLAY);
    }

    inline void play_well_done(void)
    {
        tx(SOUND_CMD_PLAY_WELL_DONE);
    }
};

#endif // ifndef __SOUND_PLAYER_INCLUDED__
