#ifndef __GLOBALS_INLUDED__
#define __GLOBALS_INLUDED__

#include "stm32f4xx_hal.h"

#include "cm-circular-buffer.hpp"
#include "cm-crc.hpp"
#include "cm-packet.hpp"

#include "hm-trp.hpp"
#include "color.hpp"
#include "sound-player.hpp"

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

    HMTRP *hmtrp;
    CircularBuffer *radio_buffer_rx;
    Color *color;
    SoundPlayer *sound_player;

    inline void init(void)
    {
        CRC32::init();
    }
};

extern Global *global;

#endif // ifndef __GLOBALS_INLUDED__