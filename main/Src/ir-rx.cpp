#include "ir-rx.hpp"
#include "globals.hpp"

#define check_pulse_hight(puls) \
    ( \
      cnt >= ((puls) - IR_TIM_TOLERANCE) &&  \
      cnt <= ((puls) + IR_TIM_TOLERANCE) &&  \
      HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin) \
    )

#define check_pulse_low(puls) \
    ( \
      cnt >= ((puls) - IR_TIM_TOLERANCE) &&  \
      cnt <= ((puls) + IR_TIM_TOLERANCE) &&  \
      !HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin) \
    )

IR::IR(TIM_HandleTypeDef *htim) : Timer(htim)
{
    this->decoder_state = IR_DEC_STATE_START_PULS;
    start_tim();
}

uint32_t IR::crc16b(void)
{
    uint16_t gp   = 0x4599;
    uint32_t mask = 0x00FF0000;
    uint32_t data;
    uint32_t gp_shift;
    uint8_t i, i_max;

    data = this->data;

    for (i_max = 0, gp_shift = gp; !(gp_shift & 0x80000000); i_max++)
    {
        gp_shift = gp << i_max;
    }
    i_max--;

    for (i = 0; data &mask; i++)
    {
        if ((data << i) & 0x80000000)
        {
            gp_shift = gp << (i_max - i);
            data    ^= gp_shift;
        }
    }

    return data;
}

void IR::ext_it(void)
{
    static uint8_t index = 0;
    uint16_t cnt         = get_tim_cnt();
    set_tim_cnt(0);

    switch (this->decoder_state)
    {
        case IR_DEC_STATE_START_PULS:
            if (check_pulse_hight(IR_TIM_START_PULS))
            {
                this->decoder_state = IR_DEC_STATE_START_SPACE;
                index      = 0;
                this->data = 0;
            }
            break;
        case IR_DEC_STATE_START_SPACE:
            if (check_pulse_low(IR_TIM_START_SPACE))
            {
                this->decoder_state = IR_DEC_STATE_DATA_PULS;
            }
            else
            {
                this->decoder_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_DATA_PULS:
            if (check_pulse_hight(IR_TIM_DATA_PULS))
            {
                this->decoder_state = IR_DEC_STATE_DATA_SPACE;
            }
            else
            {
                this->decoder_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_DATA_SPACE:
            if (check_pulse_low(IR_TIM_DATA0_SPACE))
            {
                this->decoder_state = (index < 23) ? IR_DEC_STATE_DATA_PULS : IR_DEC_STATE_END_PULS;
                index++;
                this->data <<= 1;
            }
            else if (check_pulse_low(IR_TIM_DATA1_SPACE))
            {
                this->decoder_state = (index < 23) ? IR_DEC_STATE_DATA_PULS : IR_DEC_STATE_END_PULS;
                index++;
                this->data <<= 1;
                this->data  |= 1;
            }
            else
            {
                this->decoder_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_END_PULS:
            if (check_pulse_hight(IR_TIM_END_PULS))
            {
                if (not crc16b())
                {
                    this->address = uint8_t(this->data >> 16);
                    this->crc     = uint16_t(this->data & 0xFFFF);
                    global->sound_player->play_dont_give_up();
                }
            }
            this->decoder_state = IR_DEC_STATE_START_PULS;
            break;
    }
} /* ir_ext_it */
