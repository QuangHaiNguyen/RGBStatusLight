#include "led.h" 

#define VERSION         0
#define SUB_VERSION     99
#define S_SUB_VERSION   0

static void LED_SetHigh(Led led);
static void LED_SetLow(Led led);
static uint8_t LED_GetNumOfLed(void);
static void LED_GetVersion(uint8_t * ver, uint8_t * s_version, uint8_t * ss_version);

void LED_Init(Led_Comp * led_comp)
{
    led_comp->LED_SetHigh = LED_SetHigh;
    led_comp->LED_SetLow = LED_SetLow;
    led_comp->NumOfLed = LED_GetNumOfLed;
    led_comp->LED_GetVerion = LED_GetVersion;
}

void LED_Deinit(Led_Comp * led_comp)
{
    led_comp->LED_SetHigh = NULL;
    led_comp->LED_SetLow = NULL;
}

static void LED_GetVersion(uint8_t * ver, uint8_t * s_version, uint8_t * ss_version)
{
    * ver = VERSION;
    * s_version = SUB_VERSION;
    * ss_version = S_SUB_VERSION;
}

uint8_t LED_GetNumOfLed(void)
{
    return NUM_OF_LED;
}

static void LED_SetHigh(Led led)
{
    switch(led){
        case RED_LED:
            RED_LED_SetHigh();
            break;
        case BLUE_LED:
            BLUE_LED_SetHigh();
            break;
        case GREEN_LED:
            GREEN_LED_SetHigh();
            break;
        case YELLOW_LED:
            YELLOW_LED_SetHigh();
            break;
        default:
            break;  
    }
}

static void LED_SetLow(Led led)
{
    switch(led){
        case RED_LED:
            RED_LED_SetLow();
            break;
        case BLUE_LED:
            BLUE_LED_SetLow();
            break;
        case GREEN_LED:
            GREEN_LED_SetLow();
            break;
        case YELLOW_LED:
            YELLOW_LED_SetLow();
            break;
        default:
            break;  
    }
}