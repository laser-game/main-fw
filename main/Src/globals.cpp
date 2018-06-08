#include "globals.hpp"

Global *global = Global::instance();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint32_t cnt=0;
    if (huart->Instance == global->hmtrp->get_huart()->Instance)
    {
        global->radio_buffer_rx->insert(global->hmtrp->buffer_rx[0]);
        if (global->packet->find(global->radio_buffer_rx))
        {
            //global->debug->tx("OK PACKET :D\n");
            //global->debug->tx("size :" + to_string(global->packet->get_size()) + "\n");
            uint8_t r, g, b, i = global->packet->get_index_start();
            r = global->radio_buffer_rx->read(i);
            g = global->radio_buffer_rx->read(i + 1);
            b = global->radio_buffer_rx->read(i + 2);
            global->color_driver->rgb(r, g, b);
            //global->debug->tx("rgb: " + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + "\n");
            //global->debug->tx("cnt :" + to_string(++cnt) + "\n");
        }
        else
        {
            //global->debug->tx("PACKET neni celi\n");
        }
        global->hmtrp->rx_it();
    }
    else if (huart->Instance == global->debug->get_huart()->Instance)
    { }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BTN_Pin)
    {
        global->color_driver->rgb(255, 0, 0);
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
