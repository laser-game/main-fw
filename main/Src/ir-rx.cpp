#include "ir-rx.hpp"
#include "globals.hpp"

#define HAL_TIM_IR htim7
#define TIM_IR     TIM7

#define ir_tim_start() HAL_TIM_Base_Start(&(HAL_TIM_IR))
#define ir_tim_stop()  HAL_TIM_Base_Stop(&(HAL_TIM_IR))

extern TIM_HandleTypeDef HAL_TIM_IR;
extern UART_HandleTypeDef huart1;

ir_data_t ir_data;
ir_dec_state_t ir_dec_state;

void ir_rx_init(void)
{
    // run timer, one tick is 10 us
    ir_tim_start();
    ir_dec_state = IR_DEC_STATE_START_PULS;
}

// calculate 16b crc
uint32_t ir_crc16b(void)
{
    static uint16_t gp   = 0x4599;
    static uint32_t mask = 0x00FF0000;
    uint32_t data;
    uint32_t gp_shift;
    uint8_t i, i_max;

    data = ir_data.data;

    // find max shift;
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

void ir_ext_it(void)
{
    static uint8_t index;
    uint16_t ir_cnt;

    ir_cnt      = TIM_IR->CNT;
    TIM_IR->CNT = 0;

    switch (ir_dec_state)
    {
        case IR_DEC_STATE_START_PULS:
            if (ir_cnt >= (IR_TIM_START_PULS - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_START_PULS + IR_TIM_TOLERANCE) &&  \
          HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                ir_dec_state = IR_DEC_STATE_START_SPACE;
                index        = 0;
                ir_data.data = 0;
            }
            break;
        case IR_DEC_STATE_START_SPACE:
            if (ir_cnt >= (IR_TIM_START_SPACE - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_START_SPACE + IR_TIM_TOLERANCE) &&  \
          !HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                ir_dec_state = IR_DEC_STATE_DATA_PULS;
            }
            else
            {
                ir_dec_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_DATA_PULS:
            if (ir_cnt >= (IR_TIM_DATA_PULS - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_DATA_PULS + IR_TIM_TOLERANCE) &&  \
          HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                ir_dec_state = IR_DEC_STATE_DATA_SPACE;
            }
            else
            {
                ir_dec_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_DATA_SPACE:
            if (ir_cnt >= (IR_TIM_DATA0_SPACE - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_DATA0_SPACE + IR_TIM_TOLERANCE) &&  \
          !HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                ir_dec_state = (index < 23) ? IR_DEC_STATE_DATA_PULS : IR_DEC_STATE_END_PULS;
                index++;
                ir_data.data <<= 1;
            }
            else if (ir_cnt >= (IR_TIM_DATA1_SPACE - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_DATA1_SPACE + IR_TIM_TOLERANCE) &&  \
          !HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                ir_dec_state = (index < 23) ? IR_DEC_STATE_DATA_PULS : IR_DEC_STATE_END_PULS;
                index++;
                ir_data.data <<= 1;
                ir_data.data  |= 1;
            }
            else
            {
                ir_dec_state = IR_DEC_STATE_START_PULS;
            }
            break;
        case IR_DEC_STATE_END_PULS:
            if (ir_cnt >= (IR_TIM_END_PULS - IR_TIM_TOLERANCE) &&  \
          ir_cnt <= (IR_TIM_END_PULS + IR_TIM_TOLERANCE) &&  \
          HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
            {
                if (!ir_crc16b())
                {
                    /*if (players[player_address].available)
                     * {
                     *  players[player_address].available = 0;
                     *  rgb(0, 0, 0);
                     *  sec_timer = 1;
                     *  play_au();
                     *
                     *  // start_sec_timer(death_time);
                     *
                     *  ir_data.address = ir_data.data >> 16;
                     *  ir_data.crc     = ir_data.data & 0x0000FFFF;
                     *
                     *  RF_TxData.To   = RF_ADDRESS_MASTER;
                     *  RF_TxData.From = player_address;
                     *  RF_TxData.Data = ir_data.address;
                     *
                     *  RF_PacketInit(&RF_TxPacket, &RF_TxData);
                     *  RF_PacketSend(&RF_TxPacket);
                     * }*/
                    global->sound_player->play_dont_give_up();
                    global->debug->tx("Kill me player " + to_string (ir_data.data >> 16) + '\n');
                }
            }
            ir_dec_state = IR_DEC_STATE_START_PULS;
            break;
    }
} /* ir_ext_it */
