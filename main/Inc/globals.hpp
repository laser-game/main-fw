#ifndef __GLOBALS_INLUDED__
#define __GLOBALS_INLUDED__

#include "stm32f4xx_hal.h"

#include "cm-circular-buffer.hpp"
#include "cm-crc.hpp"
#include "cm-packet.hpp"
#include "cm-uart.hpp"
#include "cm-hm-trp.hpp"

#include "color.hpp"
#include "sound-player.hpp"
#include "vest.hpp"
#include "battery.hpp"
#include "command-queue.hpp"
#include "ir-rx.hpp"
#include "gun.hpp"

#include <vector>
using namespace std;

class Global
{
private:
    Global(){ };
public:
    inline static Global * instance()
    {
        static Global object;
        return &object;
    }

    CommandQueue *cmd_queue;
    HMTRP *hmtrp;
    Gun *gun;
    CircularBuffer *radio_buffer_rx;
    ColorDriver *color_driver;
    SoundPlayer *sound_player;
    Vest *vest;
    UART *debug;
    Battery *battery;
    Packet *packet;

    inline void init(void)
    {
        CRC32::init();
    }

    void i2c_scan(void);
};

extern Global *global;

#endif // ifndef __GLOBALS_INLUDED__
