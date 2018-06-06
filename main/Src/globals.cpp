#include "globals.hpp"

Global *global = Global::instance();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == global->hmtrp->get_huart()->Instance)
    {
        global->radio_buffer_rx->insert(global->hmtrp->buffer_rx[0]);
        global->hmtrp->rx_it();
    }
    else if (huart->Instance == global->debug->get_huart()->Instance)
    { }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BTN_Pin)
    {
        global->color->rgb(255, 0, 0);
    }
}
