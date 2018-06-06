#ifndef __BATTERY_INCLUDED__
#define __BATTERY_INCLUDED__

#include "stm32f4xx_hal.h"

#include <vector>
#include <string>

using namespace std;

#define LTC2941_ADDRESS     0xC8
#define LTC2941_REG_A       0x00 // Status                    - R   - See Below
#define LTC2941_REG_B       0x01 // Control                   - R/W - 0x3C
#define LTC2941_REG_C       0x02 // Accumulated Charge MSB    - R/W - 0x7F
#define LTC2941_REG_D       0x03 // Accumulated Charge LSB    - R/W - 0xFF
#define LTC2941_REG_E       0x04 // Charge Threshold High MSB - R/W - 0xFF
#define LTC2941_REG_F       0x05 // Charge Threshold High LSB - R/W - 0xFF
#define LTC2941_REG_G       0x06 // Charge Threshold Low MSB  - R/W - 0x00
#define LTC2941_REG_H       0x07 // Charge Threshold Low LSB  - R   - 0x00

#define BATTERY_BUFFER_SIZE 8


class Battery
{
private:
    TIM_HandleTypeDef *htim;
    I2C_HandleTypeDef *hi2c;
    uint16_t charge_raw;
    uint8_t buffer[BATTERY_BUFFER_SIZE];

public:
    Battery(I2C_HandleTypeDef *hi2c, TIM_HandleTypeDef *htim);

    inline TIM_HandleTypeDef * get_htim(void)
    {
        return htim;
    }

    inline I2C_HandleTypeDef * get_i2c(void)
    {
        return hi2c;
    }

    inline void start_tim(void)
    {
        HAL_TIM_Base_Start_IT(htim);
    }

    inline void stop_tim(void)
    {
        HAL_TIM_Base_Stop_IT(htim);
    }

    inline bool read_charge(void)
    {
        if (HAL_I2C_Mem_Read(hi2c, LTC2941_ADDRESS, LTC2941_REG_B, BATTERY_BUFFER_SIZE, buffer, 2, 100) != HAL_OK)
        {
            return false;
        }
        calculate_charge();
        return true;
    }

    inline bool read_charge_it(void)
    {
        return HAL_I2C_Mem_Read_IT(hi2c, LTC2941_ADDRESS, LTC2941_REG_B, BATTERY_BUFFER_SIZE, buffer, 2);
    }

    inline void calculate_charge(void)
    {
        charge_raw = (buffer[0] << 1) + buffer[1];
    }

    inline uint16_t get_charge_raw(void)
    {
        return charge_raw;
    }
};

#endif // ifndef __BATTERY_INCLUDED__
