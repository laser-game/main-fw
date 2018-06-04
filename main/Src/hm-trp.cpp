#include "hm-trp.hpp"

HMTRP::HMTRP(UART_HandleTypeDef *huart, uint32_t baudrate) : UART(huart)
{
    config(false);
    enable(true);

    /*for (uint32_t bd : {1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200})
     * {
     *  set_baudrate(bd);
     *  reset_to_default();
     *  HAL_Delay(10);
     * }*/

    /*set_baudrate(9600);
     * set_wireless_data_rate(baudrate);
     * set_uart_transfer_speed(baudrate);*/
    rx_it();
}

void HMTRP::enable(bool ena)
{
    HAL_GPIO_WritePin(RF_ENABLE_GPIO_Port, RF_ENABLE_Pin, (ena) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HMTRP::config(bool cnf)
{
    HAL_GPIO_WritePin(RF_CONFIG_GPIO_Port, RF_CONFIG_Pin, (cnf) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HMTRP::cmd(vector<uint8_t> vector_bytes)
{
    config(true);
    tx(vector_uint8_t_array(0xAA, 0xFA));
    tx(vector_bytes);
    config(false);
    HAL_Delay(10);
}

void HMTRP::reset_to_default(void)
{
    vector<uint8_t> conf;
    conf.push_back(0xF0);
    cmd(conf);
}

bool HMTRP::check_data_rate(uint32_t data_rate)
{
    for (uint32_t dr : { 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200 })
        if (data_rate == dr)
            return true;

    return false;
}

void HMTRP::set_wireless_data_rate(uint32_t baudrate)
{
    if (check_data_rate(baudrate))
    {
        vector<uint8_t> conf;
        conf.push_back(0xC3);
        conf.push_back(uint8_t((baudrate >> 24) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 16) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 8) & 0xFF));
        conf.push_back(uint8_t(baudrate & 0xFF));
        cmd(conf);
    }
}

void HMTRP::set_uart_transfer_speed(uint32_t baudrate)
{
    if (check_data_rate(baudrate))
    {
        vector<uint8_t> conf;
        conf.push_back(0xE1);
        conf.push_back(uint8_t((baudrate >> 24) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 16) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 8) & 0xFF));
        conf.push_back(uint8_t(baudrate & 0xFF));
        cmd(conf);
        set_baudrate(baudrate);
    }
}
