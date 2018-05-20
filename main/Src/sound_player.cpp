#include "sound_player.hpp"

SoundPlayer::SoundPlayer(UART_HandleTypeDef *uart)
{
    this->uart = uart;
}
