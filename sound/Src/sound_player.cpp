#include "sound_player.hpp"

SoundPlayer::SoundPlayer(DAC_HandleTypeDef *dac, DMA_HandleTypeDef *dma_dac, TIM_HandleTypeDef *tim, UART_HandleTypeDef *uart, uint8_t channel)
{
    this->dac       = dac;
    this->dma_dac   = dma_dac;
    this->tim       = tim;
    this->uart      = uart;
    this->channel   = channel;
    this->sound_set = SOUND_SET_EN;
}

void SoundPlayer::init(void)
{
    off();
    HAL_TIM_Base_Start(tim);
    HAL_DAC_Start(dac, channel);
    HAL_DAC_SetValue(dac, channel, DAC_ALIGN_12B_R, 0);
    rx();
}

void SoundPlayer::play(uint32_t *p_data, uint32_t size, uint32_t alignment)
{
    // off();
    on();
    set_pin_is_playing(true);
    HAL_DAC_Start_DMA(dac, channel, p_data, size, alignment);
}

void SoundPlayer::play_and_wait(uint32_t *p_data, uint32_t size, uint32_t alignment)
{
    play(p_data, size, alignment);
    wait_to_end_sound();
    off();
}

void SoundPlayer::cmd(uint8_t cmd)
{
    switch (cmd)
    {
        case SOUND_CMD_STOP:
            off();
            break;
        case SOUND_CMD_SET_SOUND_SET_EN:
            sound_set = SOUND_SET_EN;
            break;
        case SOUND_CMD_SET_SOUND_SET_CZ:
            sound_set = SOUND_SET_CZ;
            break;
        case SOUND_CMD_PLAY_ACTIVATED:
            play((uint32_t *) sound_cm_activated, SOUND_CM_ACTIVATED_SIZE);
            break;
        case SOUND_CMD_PLAY_GUN:
            play((uint32_t *) sound_cm_gun, SOUND_CM_GUN_SIZE);
            break;
        case SOUND_CMD_PLAY_DONT_GIVE_UP:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_dont_give_up, SOUND_EN_DONT_GIVE_UP_SIZE);
            else
                play((uint32_t *) sound_cz_nevzdavejse, SOUND_CZ_NEVZDAVEJSE_SIZE);
            break;
        case SOUND_CMD_PLAY_GAME_OVER:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_game_over, SOUND_EN_GAME_OVER_SIZE);
            else
                play((uint32_t *) sound_cz_konec_hry, SOUND_CZ_KONEC_HRY_SIZE);
            break;
        case SOUND_CMD_PLAY_GO:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_go, SOUND_EN_GO_SIZE);
            else
                play((uint32_t *) sound_cz_bez, SOUND_CZ_BEZ_SIZE);
            break;
        case SOUND_CMD_PLAY_KEEP_GOING:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_keep_going, SOUND_EN_KEEP_GOING_SIZE);
            else
                play((uint32_t *) sound_cz_pokracuj, SOUND_CZ_POKRACUJ_SIZE);
            break;
        case SOUND_CMD_PLAY_NUMBER_1:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_number_1, SOUND_EN_NUMBER_1_SIZE);
            else
                play((uint32_t *) sound_cz_cislo_1, SOUND_CZ_CISLO_1_SIZE);
            break;
        case SOUND_CMD_PLAY_NUMBER_2:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_number_2, SOUND_EN_NUMBER_2_SIZE);
            else
                play((uint32_t *) sound_cz_cislo_2, SOUND_CZ_CISLO_2_SIZE);
            break;

        case SOUND_CMD_PLAY_NUMBER_3:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_number_3, SOUND_EN_NUMBER_3_SIZE);
            else
                play((uint32_t *) sound_cz_cislo_3, SOUND_CZ_CISLO_3_SIZE);
            break;
        case SOUND_CMD_PLAY_NUMBER_4:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_number_4, SOUND_EN_NUMBER_4_SIZE);
            else
                play((uint32_t *) sound_cz_cislo_4, SOUND_CZ_CISLO_4_SIZE);
            break;
        case SOUND_CMD_PLAY_NUMBER_5:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_number_5, SOUND_EN_NUMBER_5_SIZE);
            else
                play((uint32_t *) sound_cz_cislo_5, SOUND_CZ_CISLO_5_SIZE);
            break;
        case SOUND_CMD_PLAY_PLAY:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_play, SOUND_EN_PLAY_SIZE);
            else
                play((uint32_t *) sound_cz_hrej, SOUND_CZ_HREJ_SIZE);
            break;
        case SOUND_CMD_PLAY_WELL_DONE:
            if (sound_set == SOUND_SET_EN)
                play((uint32_t *) sound_en_well_done, SOUND_EN_WELL_DONE_SIZE);
            else
                play((uint32_t *) sound_cz_dobry_zasah, SOUND_CZ_DOBRY_ZASAH_SIZE);
            break;
        default:
            break;
    }
} // cmd

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    extern SoundPlayer sound_player;
    sound_player.cmd(sound_player.get_uart_rx_buffer());
    sound_player.rx();
}
