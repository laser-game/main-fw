#include "gun.hpp"

Gun::Gun(UART_HandleTypeDef *huart) : UART(huart)
{
    rx_it();
}

void Gun::set_address(uint8_t address)
{
    uint8_t addr[2];
    addr[0] = GUN_CMD_ADDRESS_H | (address >> 4);
    addr[1] = GUN_CMD_ADDRESS_L | (address & GUN_MASK_DAT);
    tx(addr, sizeof(addr));
}

void Gun::rgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t color[6];

    color[0] = GUN_CMD_RED_H | (r >> 4);
    color[1] = GUN_CMD_RED_L | (r & GUN_MASK_DAT);
    color[2] = GUN_CMD_GREEN_H | (g >> 4);
    color[3] = GUN_CMD_GREEN_L | (g & GUN_MASK_DAT);
    color[4] = GUN_CMD_BLUE_H | (b >> 4);
    color[5] = GUN_CMD_BLUE_L | (b & GUN_MASK_DAT);

    tx(color, sizeof(color));
}
