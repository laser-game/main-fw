#ifndef __SOUND_INCLUDED__
#define __SOUND_INCLUDED__

#include "stm32f4xx_hal.h"


#define SOUND_CM_ACTIVATED_SIZE    19368
#define SOUND_CM_GUN_SIZE          9679
#define SOUND_CZ_BEZ_SIZE          10031
#define SOUND_CZ_CISLO_1_SIZE      10725
#define SOUND_CZ_CISLO_2_SIZE      8679
#define SOUND_CZ_CISLO_3_SIZE      8216
#define SOUND_CZ_CISLO_4_SIZE      11119
#define SOUND_CZ_CISLO_5_SIZE      7554
#define SOUND_CZ_DOBRY_ZASAH_SIZE  18831
#define SOUND_CZ_HREJ_SIZE         11076
#define SOUND_CZ_KONEC_HRY_SIZE    12685
#define SOUND_CZ_NEVZDAVEJSE_SIZE  20542
#define SOUND_CZ_POKRACUJ_SIZE     12536
#define SOUND_EN_DONT_GIVE_UP_SIZE 14548
#define SOUND_EN_GAME_OVER_SIZE    15620
#define SOUND_EN_GO_SIZE           10028
#define SOUND_EN_KEEP_GOING_SIZE   17034
#define SOUND_EN_NUMBER_1_SIZE     9308
#define SOUND_EN_NUMBER_2_SIZE     9668
#define SOUND_EN_NUMBER_3_SIZE     9042
#define SOUND_EN_NUMBER_4_SIZE     9591
#define SOUND_EN_NUMBER_5_SIZE     11127
#define SOUND_EN_PLAY_SIZE         11233
#define SOUND_EN_WELL_DONE_SIZE    12992


extern const uint16_t sound_cm_activated[SOUND_CM_ACTIVATED_SIZE];
extern const uint16_t sound_cm_gun[SOUND_CM_GUN_SIZE];
extern const uint16_t sound_cz_bez[SOUND_CZ_BEZ_SIZE];
extern const uint16_t sound_cz_cislo_1[SOUND_CZ_CISLO_1_SIZE];
extern const uint16_t sound_cz_cislo_2[SOUND_CZ_CISLO_2_SIZE];
extern const uint16_t sound_cz_cislo_3[SOUND_CZ_CISLO_3_SIZE];
extern const uint16_t sound_cz_cislo_4[SOUND_CZ_CISLO_4_SIZE];
extern const uint16_t sound_cz_cislo_5[SOUND_CZ_CISLO_5_SIZE];
extern const uint16_t sound_cz_dobry_zasah[SOUND_CZ_DOBRY_ZASAH_SIZE];
extern const uint16_t sound_cz_hrej[SOUND_CZ_HREJ_SIZE];
extern const uint16_t sound_cz_konec_hry[SOUND_CZ_KONEC_HRY_SIZE];
extern const uint16_t sound_cz_nevzdavejse[SOUND_CZ_NEVZDAVEJSE_SIZE];
extern const uint16_t sound_cz_pokracuj[SOUND_CZ_POKRACUJ_SIZE];
extern const uint16_t sound_en_dont_give_up[SOUND_EN_DONT_GIVE_UP_SIZE];
extern const uint16_t sound_en_game_over[SOUND_EN_GAME_OVER_SIZE];
extern const uint16_t sound_en_go[SOUND_EN_GO_SIZE];
extern const uint16_t sound_en_keep_going[SOUND_EN_KEEP_GOING_SIZE];
extern const uint16_t sound_en_number_1[SOUND_EN_NUMBER_1_SIZE];
extern const uint16_t sound_en_number_2[SOUND_EN_NUMBER_2_SIZE];
extern const uint16_t sound_en_number_3[SOUND_EN_NUMBER_3_SIZE];
extern const uint16_t sound_en_number_4[SOUND_EN_NUMBER_4_SIZE];
extern const uint16_t sound_en_number_5[SOUND_EN_NUMBER_5_SIZE];
extern const uint16_t sound_en_play[SOUND_EN_PLAY_SIZE];
extern const uint16_t sound_en_well_done[SOUND_EN_WELL_DONE_SIZE];


#endif // ifndef __SOUND_INCLUDED__
