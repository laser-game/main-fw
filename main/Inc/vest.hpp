#ifndef __VEST_INLUDED__
#define __VEST_INLUDED__

#include "stm32f4xx_hal.h"

#include "cm-vest.hpp"
#include "cm-macro.hpp"

#include <vector>
#include <string>

using namespace std;

class Vest : public BasicVest
{
private:

public:
    Vest(void);
    void read_address(void);
};

#endif // ifndef __VEST_INLUDED__
