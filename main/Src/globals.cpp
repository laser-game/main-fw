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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // if (htim->Instance == global->battery->get_htim()->Instance)
    if (htim->Instance == TIM8)
    {
        global->hmtrp->tx("START MEASURE CHARGE\n");
        global->battery->read_charge_it();
    }
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    global->battery->calculate_charge();
    global->hmtrp->tx("Accumulated Charge: " + to_string(global->battery->get_charge_raw()) + '\n');
}

void Global::i2c_scan(void)
{
    global->hmtrp->tx("I2C SCAN\n");
    for (uint8_t addr = 0; addr < 128; addr++)
    {
        if (HAL_I2C_IsDeviceReady(global->battery->get_i2c(), addr << 1, 2, 100) == HAL_OK)
        {
            global->hmtrp->tx("\tSLAVE ADDR: " + to_string(addr << 1) + '\n');
        }
    }
}
