/*******************************************************************************
* Title                 :   atmega4808_pwm Component   
* Filename              :   atmega4808_pwm.c
* Author                :   Quang Hai Nguyen
* Origin Date           :   20.04.2020
* Version               :   0.0.99
*
*******************************************************************************/

/*************** SOURCE REVISION LOG *****************************************
*
*  Date         Version     Author              Description 
*  20.04.2020   1.0.0       Quang Hai Nguyen    Initial Release.
*
*******************************************************************************/
/** @file  atmega4808_pwm.c
 *  @brief This is the source file for atmega4808_pwm component
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "atmega4808_pwm.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
//None

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/** \brief pointer to the buffer holding RGB data */
static uint16_t *pointer_to_RGB_buff = NULL;

/** \brief size of the buffer holding RGB data  */
static uint16_t RGB_buff_size = 0;

/** \brief index of buffer holding RGB data */
static uint16_t RGB_buff_index;

/******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function : ATMEGA4808_PWM_Init
*//** 
* \b Description:
*
* This function initializes the TCA of the Atmega4808 and uses it as single
* slope PWM generator. The initialization is actually carried out by Microchip 
* Code Configurator (MCC), we only modify minor detail.
*
* PRE-CONDITION: TCA must be generated by MCC or manually implemented  
*
* POST-CONDITION: None
* data
* @param    None
* @return   None
*
* \b Example Example:
* @code
* 	ATMEGA4808_PWM_Init();
* @endcode
*
* @see ATMEGA4808_PWM_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void ATMEGA4808_PWM_Init(void)
{
    //The actual PWM initialization is done by Microchip Code Configurator
    //We only modify some minor detail
    ATMEGA4808_PWM_Stop();
   
    //writing my own interrupt code
    TCA0.SINGLE.INTCTRL = 0 << TCA_SINGLE_CMP0_bp   /* Compare 0 Interrupt: disabled */
                        | 0 << TCA_SINGLE_CMP1_bp /* Compare 1 Interrupt: disabled */
                        | 0 << TCA_SINGLE_CMP2_bp /* Compare 2 Interrupt: disabled */
                        | 1 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt Enable: enabled */
    
    TCA0.SINGLE.PERBUF = PERIOD;
    
    return;
}

/******************************************************************************
* Function : ATMEGA4808_PWM_GetRGBDataInfo
*//** 
* \b Description:
*
* This function gets the address of the RGB buffer and the size of the buffer.
*
* PRE-CONDITION: None 
*
* POST-CONDITION: None
* data
* @param    ptr_to_buff(IN): address of the RGB buffer 
* @return   buff_size(IN): size of the buffer
*
* \b Example Example:
* @code
* 	ATMEGA4808_PWM_GetRGBDataInfo(&ptr_to_buff, 10);
* @endcode
*
* @see ATMEGA4808_PWM_GetRGBDataInfo
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void ATMEGA4808_PWM_GetRGBDataInfo(uint16_t **ptr_to_buff, uint16_t buff_size)
{
    //Store data to the internal variable
    pointer_to_RGB_buff = *ptr_to_buff;
    RGB_buff_size = buff_size;
}


/******************************************************************************
* Function : ATMEGA4808_PWM_Start
*//** 
* \b Description:
*
* This function resets the counter of the timer, the index of the buffer and 
* starts PWM
*
* PRE-CONDITION: ATMEGA4808_PWM_Init and ATMEGA4808_PWM_GetRGBDataInfo must 
* be executed before hand 
*
* POST-CONDITION: None
* 
* @param    None
* @return   None
*
* \b Example Example:
* @code
* 	ATMEGA4808_PWM_Start();
* @endcode
*
* @see ATMEGA4808_PWM_Init
* @see ATMEGA4808_PWM_GetRGBDataInfo 
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void ATMEGA4808_PWM_Start(void)
{
    //Reset led buffer index
    RGB_buff_index = 0;
    
    //Assign first value to capture compare
    TCA0.SINGLE.CMP0BUF = pointer_to_RGB_buff[RGB_buff_index];
    
    //Reset timer counter
    TCA0.SINGLE.CNT = 0;
    
    //Start PWM
    TCA0.SINGLE.CTRLA |= (1 << TCA_SINGLE_ENABLE_bp);
}

/******************************************************************************
* Function : ATMEGA4808_PWM_Stop
*//** 
* \b Description:
*
* This function stops the PWM 
*
* PRE-CONDITION: ATMEGA4808_PWM_Init must be executed before hand
*
* POST-CONDITION: None
* data
* @param    None
* @return   None
*
* \b Example Example:
* @code
* 	ATMEGA4808_PWM_Stop();
* @endcode
*
* @see ATMEGA4808_PWM_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void ATMEGA4808_PWM_Stop(void)
{
    //Stop PWM
    TCA0.SINGLE.CTRLA &= ~(1 << TCA_SINGLE_ENABLE_bp);
}

/******************************************************************************
* Function : ATMEGA4808_PWM_DeInit
*//** 
* \b Description:
*
* This function de-reference the pointer, reset index, cleanup stuffs
*
* PRE-CONDITION: ATMEGA4808_PWM_Init must be executed before hand  
*
* POST-CONDITION: None
* data
* @param    None
* @return   None
*
* \b Example Example:
* @code
* 	ATMEGA4808_PWM_Stop();
* @endcode
*
* @see ATMEGA4808_PWM_Init
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
void ATMEGA4808_PWM_DeInit(void)
{
    ATMEGA4808_PWM_Stop();
    
    //Dereference pointer
    pointer_to_RGB_buff = NULL;
    
    //Reset index
    RGB_buff_size = 0;
}

/******************************************************************************
* Function : TCA0_OVF_vect
*//** 
* \b Description:
*
* Interrupt service routine to handle capture and compare interrupt. After each 
* match, we load the new value from the buffer to the Capture and compare 
* register
*
* PRE-CONDITION: ATMEGA4808_PWM_Init and ATMEGA4808_PWM_GetRGBDataInfo
* must be executed before hand  
*
* POST-CONDITION: None
* data
* @param    None
* @return   None
*
* <br><b> - HISTORY OF CHANGES - </b>
*  
* <table align="left" style="width:800px">
* <tr><td> Date       </td><td> Software Version </td><td> Initials         </td><td> Description </td></tr>
* <tr><td> 20.04.2020 </td><td> 0.0.99           </td><td> Quang Hai Nguyen </td><td> Interface Created </td></tr>
* </table><br><br>
* <hr>
*
*******************************************************************************/
ISR(TCA0_OVF_vect)
{
    //If we have done with the bufferm stop the PWM
    if(++RGB_buff_index > RGB_buff_size)
    {
        ATMEGA4808_PWM_Stop();
    } 
    TCA0.SINGLE.CMP0BUF = pointer_to_RGB_buff[RGB_buff_index];   
    
    //"Clear" interrupt flag
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

/*** End of File **************************************************************/