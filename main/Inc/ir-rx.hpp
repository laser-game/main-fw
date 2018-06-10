#ifndef __IR_INCLUDED__
#define __IR_INCLUDED__

#include "stm32f4xx_hal.h"

#include "cm-timer.hpp"

typedef enum {
    IR_TIM_START_PULS   = 5000,
    IR_TIM_START_SPACE  = IR_TIM_START_PULS,
    IR_TIM_DATA_PULS    = 600,
    IR_TIM_DATA0_SPACE  = IR_TIM_DATA_PULS,
    IR_TIM_DATA1_SPACE  = 2 * IR_TIM_DATA0_SPACE,
    IR_TIM_END_PULS     = 3000,
    IR_TIM_PACKET_SPACE = 30000,
    IR_TIM_TOLERANCE    = 200
} ir_time_t;

typedef enum {
    IR_DEC_STATE_START_PULS,
    IR_DEC_STATE_START_SPACE,
    IR_DEC_STATE_DATA_PULS,
    IR_DEC_STATE_DATA_SPACE,
    IR_DEC_STATE_END_PULS
} ir_dec_state_t;


class IR : public Timer
{
private:
    uint16_t crc;
    uint32_t data;
    uint8_t address;
    ir_dec_state_t decoder_state;
public:
    IR(TIM_HandleTypeDef *htim);
    uint32_t crc16b(void);
    void ext_it(void);
};

#endif // __IR_INCLUDED__
