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
/** @file  WS2812.c
 *  @brief This is the source file for WS2812 module
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "WS2812.h"
#include "include/winc_legacy.h"
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

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : WS2812_Init
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
* @param    num_of_led(IN):  number of LED we are going to use
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_Init(10);
* @endcode
*
* @see WS2812_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_Init(uint16_t num_of_led)
{
    //Get a copy of number of LED
    num_led = num_of_led;
    
    // Calculate total number of bytes
    // size = byte holding reset time + number of led * 3 colors * 8 bit per color
    led_buff_size = RESET_TIME + num_led * 3 * 8;
    
    // Allocate memory for the data
    ptr_led_buff = (uint16_t *)malloc(led_buff_size * sizeof(uint16_t));
    if(NULL == ptr_led_buff){
        return WS2812_NOT_MEMORY;
    }
    
    //initialize underlying hardware
#ifdef USING_AVR4808
    //InitHardware();
    ATMEGA4808_PWM_Init();
    ATMEGA4808_PWM_GetRGBDataInfo(&ptr_led_buff, led_buff_size);
#endif
    
    //Set value to 0;
    memset(ptr_led_buff, 0, led_buff_size);

    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_DeInit()
*//** 
* \b Description:
*
* This function de-initialize the WS2812 module. It frees the memory and also
* de-initializes the underlying hardware
*
* PRE-CONDITION: None
*
* POST-CONDITION: free all resources required for WS2812 module
* 
* @param    None
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_DeInit();
* @endcode
*
* @see WS2812_DeInit
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_DeInit(void)
{
    //free the memory
    if(NULL != ptr_led_buff){
        free(ptr_led_buff);
    }
    led_buff_size = 0;
    
    //de-initialize underlying hardware
#ifdef USING_AVR4808
    ATMEGA4808_PWM_DeInit();
    //InitHardware();
#endif
    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_SetColor()
*//** 
* \b Description:
*
* This function "sets" the color of a individual LED. It receives the RGB data
* and prepares the RGB data buffer  
*
* PRE-CONDITION: WS2812_Init must be executed
*
* POST-CONDITION: WS2812_Update must be executed to actually see the color change
* 
* @param    position(IN): position of the LED we want to update the color
* @param    r(IN): red color value
* @param    g(IN): green color value
* @param    b(IN): blue color value
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_SetColor(3, 255, 233, 132);
* @endcode
*
* @see WS2812_Update
* @see WS2812_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_SetColor(uint16_t position, uint8_t r, uint8_t g, uint8_t b)
{
    /*
     * 3 colors RGB, Each color is 8-bit value
     * we have a loop with 8 iteration, n = 0 -> 7
     * each iteration we update value of bit n of each color 
     */
    for(uint8_t i = 0; i < 8; i++)
    {
        ptr_led_buff[RESET_TIME + position * 24 + i] =      (g >> i) & 1 ?  BIT_1 : BIT_0;
        ptr_led_buff[RESET_TIME + position * 24 + i + 8] =  (r >> i) & 1 ?  BIT_1 : BIT_0;
        ptr_led_buff[RESET_TIME + position * 24 + i + 16] = (b >> i) & 1 ?  BIT_1 : BIT_0;
    }
    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_SetColorAll()
*//** 
* \b Description:
*
* This function "sets" the color of a complete LED strip. It receives the 
* RGB data and prepares the RGB data buffer  
*
* PRE-CONDITION: WS2812_Init must be executed
*
* POST-CONDITION: WS2812_Update must be executed to actually see the color change
* 
* @param    r(IN): red color value
* @param    g(IN): green color value
* @param    b(IN): blue color value
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_SetColorAll(255, 233, 132);
* @endcode
*
* @see WS2812_Init
* @see WS2812_Update
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_SetColorAll(uint8_t r, uint8_t g, uint8_t b)
{
    //set color to all LEDs, don't touch the reset value (always 0)
    for(uint16_t i = 0; i < num_led; i++){
        WS2812_SetColor(i, r, g, b);
    }
    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_SetColorAll()
*//** 
* \b Description:
*
* This function updates the new color of the LED strip. It calls the underlying 
* hardware, which sends the RGB data stream to the WS2812 strip
*
* PRE-CONDITION: WS2812_Init must be executed
*
* POST-CONDITION: None
* 
* @param    None
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_Update();
* @endcode
*
* @see WS2812_Init
* @see WS2812_SetColor
* @see WS2812_SetColorAll 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_Update(void)
{
    //run underlying hardware
#ifdef USING_AVR4808
    //Hardware_SendDataToLED();
    ATMEGA4808_PWM_Start();
#endif

    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_SetColorAll()
*//** 
* \b Description:
*
* This function turns off the color of the LED strip. It set the RGB data to "0"
*
* PRE-CONDITION: WS2812_Init must be executed
*
* POST-CONDITION: WS2812_Update must be executed to actually see the color change
* 
* @param    None
* @return   Status code
*
* \b Example Example:
* @code
* 	WS2812_Update();
* @endcode
*
* @see WS2812_Init
* @see WS2812_Update
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_LedOff(void)
{
    //set color to all LEDs, don't touch the reset value (always 0)
    for(uint16_t i = 0; i < num_led; i++){
        WS2812_SetColor(i, 0, 0, 0);
    }
    return WS2812_OK;
}

/******************************************************************************
* Function : WS2812_GetPointerToRGBData()
*//** 
* \b Description:
*
* This function returns the pointer to the RGB data buffer
*
* PRE-CONDITION: WS2812_Init must be executed
*
* POST-CONDITION: None
* 
* @param    ptr(OUT): pointer to RGB data buffer
* @return   Status code
*
* \b Example Example:
* @code
*   uint16_t *ptr_to_buffer = NULL;
*
* 	WS2812_GetPointerToRGBData(&ptr_to_buffer);
* @endcode
*
* @see WS2812_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 13.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
WS2812_Status WS2812_GetPointerToRGBData(uint16_t **ptr)
{
    if(NULL == ptr_led_buff){
        return WS2812_NOT_INIT;
    }
    *ptr = ptr_led_buff;
    return WS2812_OK;
}

/*** End of File **************************************************************/