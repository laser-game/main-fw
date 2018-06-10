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
                this->address = uint8_t(this->data >> 16);
                this->crc     = uint16_t(this->data & 0xFFFF);
                if (this->crc == CRC16::calculate(this->address))
                {
                    global->sound_player->play_dont_give_up();
                }
            }
            this->decoder_state = IR_DEC_STATE_START_PULS;
            break;
    }
} /* ir_ext_it */
