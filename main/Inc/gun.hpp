#ifndef __GUN_INLUDED__
#define __GUN_INLUDED__

#include "stm32f4xx_hal.h"

#include "cm-uart.hpp"
#include "cm-macro.hpp"

#include <vector>
#include <string>

using namespace std;


typedef enum {
    GUN_CMD_RESET           = 0x00,
    GUN_CMD_ADDRESS_L       = 0x10,
    GUN_CMD_ADDRESS_H       = 0x20,
    GUN_CMD_RED_L           = 0x30,
    GUN_CMD_RED_H           = 0x40,
    GUN_CMD_GREEN_L         = 0x50,
    GUN_CMD_GREEN_H         = 0x60,
    GUN_CMD_BLUE_L          = 0x70,
    GUN_CMD_BLUE_H          = 0x80,
    GUN_CMD_FUSE_BANG       = 0x90,
    GUN_CMD_FUSE_LED_WH     = 0xA0,
    GUN_CMD_FUSE_LED_UV     = 0xB0,
    GUN_CMD_FUSE_DEACTIVATE = 0xC0,
    GUN_CMD_DEATH           = 0xD0,
    GUN_CMD_LIVE            = 0xE0,
    GUN_CMD_BANG            = 0xF0, // information on shots in bang
    GUN_MASK_CMD            = 0xF0,
    GUN_MASK_DAT            = 0x0F
} gun_cmd_t;


class Gun : public UART
{
public:
    Gun(UART_HandleTypeDef *huart);
    void set_address(uint8_t address);
    void rgb(uint8_t r, uint8_t g, uint8_t b);
};

#endif // ifndef __GUN_INLUDED__
