#ifndef __GLOBALS_INLUDED__
#define __GLOBALS_INLUDED__

#include "stm32f4xx_hal.h"
#include "hm-trp.hpp"
#include "cm-circular-buffer.hpp"
#include "cm-crc.hpp"
#include "cm-packet.hpp"

using namespace std;

class Global
{
private:
    Global(){ };
public:
    static Global * instance();
    HMTRP *hmtrp;
    CircularBuffer *radio_buffer_rx;
};

extern Global *global;

#endif // ifndef __GLOBALS_INLUDED__
