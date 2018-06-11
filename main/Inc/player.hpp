#ifndef __PLAYER_INLUDED__
#define __PLAYER_INLUDED__

#include "stm32f4xx_hal.h"

#include "cm-player.hpp"

#include <vector>
#include <string>

using namespace std;

class Player : public BasicPlayer
{
public:
    Player(void);
    void live(void);
    void death(void);
};

#endif // ifndef __PLAYER_INLUDED__
