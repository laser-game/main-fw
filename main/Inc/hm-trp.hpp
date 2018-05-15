#ifndef __HMTRP_INCLUDED__
#define __HMTRP_INCLUDED__

#include "stm32f4xx_hal.h"
#include <vector>
#include <string>

using namespace std;

class HMTRP
{
private:
    void enable(bool ena = true);
    void config(bool cnf = true);
public:
    HMTRP();
    void send(string str);
};

#endif // ifndef __HMTRP_INCLUDED__
