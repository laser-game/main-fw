#include "globals.hpp"

Global *global = Global::instance();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == global->hmtrp->get_huart()->Instance)
    {
        global->radio_buffer_rx->insert(global->hmtrp->buffer_rx[0]);

        global->hmtrp->rx_it();
    }
}
