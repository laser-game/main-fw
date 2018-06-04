#ifndef __HMTRP_INLUDED__
#define __HMTRP_INLUDED__

#include "stm32f4xx_hal.h"
#include "cm-uart.hpp"
#include "cm-macro.hpp"
#include <vector>
#include <string>

using namespace std;

class HMTRP : public UART
{
private:
    void enable(bool ena = true);
    void config(bool cnf = true);
    void cmd(vector<uint8_t> vector_bytes);
    void reset_to_default(void);
    bool check_data_rate(uint32_t data_rate);
    void set_wireless_data_rate(uint32_t baudrate);
    void set_uart_transfer_speed(uint32_t baudrate);
public:
    HMTRP(UART_HandleTypeDef *huart, uint32_t baudrate = 9600);
};

#endif // ifndef __HMTRP_INLUDED__
