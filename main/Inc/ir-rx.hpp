/*
 * Knihovna pro infračervenou kominukaci
 *
 * autor: wykys
 * verze: 1.0
 * datum: 4.8.2016
 */

#ifndef IR_H_INCLUDED
#define IR_H_INCLUDED

#include "stm32f4xx_hal.h"
// #include "rf_hw.h"
// #include "rf_protocol.h"
// #include "color.h"

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

typedef struct {
    uint8_t  address;
    uint16_t crc;
    uint32_t data;
} ir_data_t;


extern ir_data_t ir_data;
extern ir_dec_state_t ir_dec_state;

void ir_rx_init(void);
uint32_t ir_crc16b(void);
void ir_ext_it(void);

#endif // IR_H_INCLUDED
