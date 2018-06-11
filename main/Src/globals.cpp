#include "globals.hpp"

Global *global = Global::instance();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == global->hmtrp->get_huart()->Instance)
    {
        global->radio_buffer_rx->insert(global->hmtrp->buffer_rx[0]);
        global->hmtrp->rx_it();
        if (global->packet->find(global->radio_buffer_rx))
        {
            uint8_t r = global->packet->data[0];
            uint8_t g = global->packet->data[1];
            uint8_t b = global->packet->data[2];

            global->color_driver->rgb(r, g, b);
            global->packet->create();
            global->hmtrp->tx(global->packet->stream);
        }
    }
    else if (huart->Instance == global->gun->get_huart()->Instance)
    {
        if (global->gun->buffer_rx[0] == GUN_CMD_BANG)
        {
            global->sound_player->play_gun();
        }
        global->gun->rx_it();
    }
    else if (huart->Instance == global->debug->get_huart()->Instance)
    {
        global->debug->rx_it();
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == IR_RX_Pin)
    {
        global->ir->ext_it();
    }
    else if (GPIO_Pin == BTN_Pin)
    {
        global->color_driver->rgb(55, 0, 0);
        uint8_t hub[512];
        uint16_t i;
        for (i = 0; i < 512; i++)
            hub[i] = (i > 256) ? i % 256 : i;
        HAL_UART_Transmit(global->hmtrp->get_huart(), hub, 512, 100);
        global->color_driver->rgb(0, 55, 0);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == global->battery->get_htim()->Instance)
    {
        global->debug->tx("START MEASURE CHARGE\n");
        // global->battery->read_charge_it();
        global->battery->read_charge();
        global->debug->tx("Accumulated Charge: " + to_string(global->battery->get_charge_raw()) + '\n');
    }
    else if (htim->Instance == global->timer_spirit->get_htim()->Instance)
    {
        global->player->live();
    }
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    global->battery->calculate_charge();
    global->debug->tx("Accumulated Charge: " + to_string(global->battery->get_charge_raw()) + '\n');
}

void Global::i2c_scan(void)
{
    global->debug->tx("I2C SCAN\n");
    for (uint8_t addr = 0; addr < 128; addr++)
    {
        if (HAL_I2C_IsDeviceReady(global->battery->get_i2c(), addr << 1, 2, 100) == HAL_OK)
        {
            global->debug->tx("\tSLAVE ADDR: " + to_string(addr << 1) + '\n');
        }
    }
}
