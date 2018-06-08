#ifndef __COMMAND_QUEUE_INCLUDED__
#define __COMMAND_QUEUE_INCLUDED__

#include "stm32f4xx_hal.h"

#include <queue>
#include <string>
using namespace std;

class CommandQueue
{
private:
    queue<uint8_t> fifo;
public:
    inline CommandQueue(){ }

    inline void push(uint8_t data)
    {
        fifo.push(data);
    }

    inline uint8_t pop(void)
    {
        uint8_t tmp = fifo.front();
        fifo.pop();
        return tmp;
    }
};

#endif // ifndef __COMMAND_QUEUE_INCLUDED__
