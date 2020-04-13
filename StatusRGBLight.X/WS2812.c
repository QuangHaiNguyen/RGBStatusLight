/*******************************************************************************
* Title                 :   WS2812 Module   
* Filename              :   WS2812.c
* Author                :   Quang Hai Nguyen
* Origin Date           :   13.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** SOURCE REVISION LOG *****************************************
*
*  Date         Version     Author              Description 
*  13.04.2020   1.0.0       Quang Hai Nguyen    Initial Release.
*
*******************************************************************************/
/** @file TODO: WS2812.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "WS2812.h"
#include <string.h>
#include <stdio.h>

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
uint16_t led_buff_size;
uint16_t *ptr_led_buff;
uint16_t num_led;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
//None

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : WS2812_Init()
*//** 
* \b Description:
*
* This function initialize the WS2812 module. It reserves the memory for the RGB
* data and initializes the underlying hardware. 
*
* PRE-CONDITION: None
*
* POST-CONDITION: Memory is reserved for RGB data, return pointer to reserve
* data
* @param    num_of_led: IN number of LED we are going to use
* @param    ptr: OUT pointer to the reserved memory for the RGB data 
* @return   Status code
*
* \b Example Example:
* @code
* 	uint16_t *ptr_RGB_buffer
*
* 	WS2812_Init(10, &ptr_RGB_buffer);
* @endcode
*
* @see WS2812_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> HN       </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_Init(uint16_t num_of_led, uint16_t **ptr)
{
    //Get a copy of number of LED
    num_led = num_of_led;
    
    // Calculate total number of bytes
    led_buff_size = RESET_TIME + num_led * 24;
    
    // Allocate memory for the data
    ptr_led_buff = (uint16_t *)malloc(led_buff_size * sizeof(uint16_t));
    if(NULL == ptr_led_buff){
        return WS2812_NOT_MEMORY;
    }
    
    //initialize underlying hardware
#ifdef USING_AVR4808
    //InitHardware();
#endif
    
    //Set value to 0;
    memset(ptr_led_buff, 0, led_buff_size);
    
    
    *ptr = ptr_led_buff; 
    return WS2812_OK;
}

WS2812_Status WS2812_DeInit(void)
{
    //free the memory
    if(NULL != ptr_led_buff){
        free(ptr_led_buff);
    }
    led_buff_size = 0;
    
    //de-initialize underlying hardware
#ifdef USING_AVR4808
    //InitHardware();
#endif
    return WS2812_OK;
}


WS2812_Status WS2812_SetColor(uint16_t position, uint8_t r, uint8_t g, uint8_t b)
{
    /*
     * 3 colors RGB, Each color is 8-bit value
     * we have a loop with 8 iteration, n = 0 -> 7
     * each iteration we update value of bit n of each color 
     */
    for(uint8_t i = 0; i < 8; i++)
    {
        ptr_led_buff[RESET_TIME + position * 24 + i] =      (r >> i) & 1 ?  BIT_1 : BIT_0;
        ptr_led_buff[RESET_TIME + position * 24 + i + 8] =  (g >> i) & 1 ?  BIT_1 : BIT_0;
        ptr_led_buff[RESET_TIME + position * 24 + i + 16] = (b >> i) & 1 ?  BIT_1 : BIT_0;
    }
    return WS2812_OK;
}

WS2812_Status WS2812_SetColorAll(uint8_t r, uint8_t g, uint8_t b)
{
    //set color to all LEDs, don't touch the reset value (always 0)
    for(uint16_t i = 0; i < num_led; i++){
        WS2812_SetColor(i, r, g, b);
    }
    return WS2812_OK;
}

WS2812_Status WS2812_Update(void)
{
    //run underlying hardware
#ifdef USING_AVR4808
    //Hardware_SendDataToLED();
#endif
    return WS2812_OK;
}

WS2812_Status WS2812_LedOff(void)
{
    //set color to all LEDs, don't touch the reset value (always 0)
    for(uint16_t i = 0; i < led_buff_size - RESET_TIME; i++){
        WS2812_SetColor(i, 0, 0, 0);
    }
    return WS2812_OK;
}
