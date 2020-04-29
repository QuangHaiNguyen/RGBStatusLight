/* 
 * File:   led.h
 * Author: haing
 *
 * Created on April 7, 2020, 11:57 PM
 */

#ifndef LED_H
#define	LED_H

#include "../common.h"

typedef enum LED{
    RED_LED =0,
    BLUE_LED,
    YELLOW_LED,
    GREEN_LED,
    NUM_OF_LED
}Led;

typedef struct LEC_COMP{
    uint8_t (* NumOfLed) (void);
    void (* LED_SetHigh)(Led led);
    void (* LED_SetLow)(Led led);
    void (* LED_GetVerion) (uint8_t * ver, uint8_t * s_version, uint8_t * ss_version);
}Led_Comp;

void LED_Init(Led_Comp * led_comp);
void LED_Deinit(Led_Comp * led_comp);

#endif	/* LED_H */

