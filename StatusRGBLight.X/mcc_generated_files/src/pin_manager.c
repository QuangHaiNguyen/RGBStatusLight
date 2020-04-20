/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/


#include "../include/pin_manager.h"
static void (*PORTF_SW0_InterruptHandler)(void);
static void (*PORTA_RST_InterruptHandler)(void);
static void (*PORTA_PA4_InterruptHandler)(void);
static void (*PORTA_PA6_InterruptHandler)(void);
static void (*PORTA_PA5_InterruptHandler)(void);
static void (*PORTA_nCS_InterruptHandler)(void);
static void (*PORTF_PF1_InterruptHandler)(void);
static void (*PORTF_PF0_InterruptHandler)(void);
static void (*PORTD_YELLOW_LED_InterruptHandler)(void);
static void (*PORTF_CE_InterruptHandler)(void);
static void (*PORTC_PC0_InterruptHandler)(void);
static void (*PORTD_RED_LED_InterruptHandler)(void);
static void (*PORTF_INT_InterruptHandler)(void);
static void (*PORTF_SW1_InterruptHandler)(void);
static void (*PORTD_BLUE_LED_InterruptHandler)(void);
static void (*PORTC_PC2_InterruptHandler)(void);
static void (*PORTD_GREEN_LED_InterruptHandler)(void);
static void (*PORTF_WAKE_InterruptHandler)(void);
static void (*PORTC_PC1_InterruptHandler)(void);

void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0xD2;
    PORTB.DIR = 0x00;
    PORTC.DIR = 0x07;
    PORTD.DIR = 0x0A;
    PORTE.DIR = 0x00;
    PORTF.DIR = 0x19;

    /* OUT Registers Initialization */
    PORTA.OUT = 0x80;
    PORTB.OUT = 0x00;
    PORTC.OUT = 0x00;
    PORTD.OUT = 0x00;
    PORTE.OUT = 0x00;
    PORTF.OUT = 0x00;

    /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x00;
    PORTA.PIN1CTRL = 0x00;
    PORTA.PIN2CTRL = 0x00;
    PORTA.PIN3CTRL = 0x00;
    PORTA.PIN4CTRL = 0x00;
    PORTA.PIN5CTRL = 0x00;
    PORTA.PIN6CTRL = 0x00;
    PORTA.PIN7CTRL = 0x00;
    PORTB.PIN0CTRL = 0x00;
    PORTB.PIN1CTRL = 0x00;
    PORTB.PIN2CTRL = 0x00;
    PORTB.PIN3CTRL = 0x00;
    PORTB.PIN4CTRL = 0x00;
    PORTB.PIN5CTRL = 0x00;
    PORTB.PIN6CTRL = 0x00;
    PORTB.PIN7CTRL = 0x00;
    PORTC.PIN0CTRL = 0x00;
    PORTC.PIN1CTRL = 0x00;
    PORTC.PIN2CTRL = 0x00;
    PORTC.PIN3CTRL = 0x00;
    PORTC.PIN4CTRL = 0x00;
    PORTC.PIN5CTRL = 0x00;
    PORTC.PIN6CTRL = 0x00;
    PORTC.PIN7CTRL = 0x00;
    PORTD.PIN0CTRL = 0x00;
    PORTD.PIN1CTRL = 0x00;
    PORTD.PIN2CTRL = 0x00;
    PORTD.PIN3CTRL = 0x00;
    PORTD.PIN4CTRL = 0x00;
    PORTD.PIN5CTRL = 0x00;
    PORTD.PIN6CTRL = 0x00;
    PORTD.PIN7CTRL = 0x00;
    PORTE.PIN0CTRL = 0x00;
    PORTE.PIN1CTRL = 0x00;
    PORTE.PIN2CTRL = 0x00;
    PORTE.PIN3CTRL = 0x00;
    PORTE.PIN4CTRL = 0x00;
    PORTE.PIN5CTRL = 0x00;
    PORTE.PIN6CTRL = 0x00;
    PORTE.PIN7CTRL = 0x00;
    PORTF.PIN0CTRL = 0x00;
    PORTF.PIN1CTRL = 0x00;
    PORTF.PIN2CTRL = 0x0B;
    PORTF.PIN3CTRL = 0x00;
    PORTF.PIN4CTRL = 0x00;
    PORTF.PIN5CTRL = 0x03;
    PORTF.PIN6CTRL = 0x03;
    PORTF.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x00;
    PORTMUX.EVSYSROUTEA = 0x00;
    PORTMUX.TCAROUTEA = 0x02;
    PORTMUX.TCBROUTEA = 0x00;
    PORTMUX.TWISPIROUTEA = 0x00;
    PORTMUX.USARTROUTEA = 0x00;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTF_SW0_SetInterruptHandler(PORTF_SW0_DefaultInterruptHandler);
    PORTA_RST_SetInterruptHandler(PORTA_RST_DefaultInterruptHandler);
    PORTA_PA4_SetInterruptHandler(PORTA_PA4_DefaultInterruptHandler);
    PORTA_PA6_SetInterruptHandler(PORTA_PA6_DefaultInterruptHandler);
    PORTA_PA5_SetInterruptHandler(PORTA_PA5_DefaultInterruptHandler);
    PORTA_nCS_SetInterruptHandler(PORTA_nCS_DefaultInterruptHandler);
    PORTF_PF1_SetInterruptHandler(PORTF_PF1_DefaultInterruptHandler);
    PORTF_PF0_SetInterruptHandler(PORTF_PF0_DefaultInterruptHandler);
    PORTD_YELLOW_LED_SetInterruptHandler(PORTD_YELLOW_LED_DefaultInterruptHandler);
    PORTF_CE_SetInterruptHandler(PORTF_CE_DefaultInterruptHandler);
    PORTC_PC0_SetInterruptHandler(PORTC_PC0_DefaultInterruptHandler);
    PORTD_RED_LED_SetInterruptHandler(PORTD_RED_LED_DefaultInterruptHandler);
    PORTF_INT_SetInterruptHandler(PORTF_INT_DefaultInterruptHandler);
    PORTF_SW1_SetInterruptHandler(PORTF_SW1_DefaultInterruptHandler);
    PORTD_BLUE_LED_SetInterruptHandler(PORTD_BLUE_LED_DefaultInterruptHandler);
    PORTC_PC2_SetInterruptHandler(PORTC_PC2_DefaultInterruptHandler);
    PORTD_GREEN_LED_SetInterruptHandler(PORTD_GREEN_LED_DefaultInterruptHandler);
    PORTF_WAKE_SetInterruptHandler(PORTF_WAKE_DefaultInterruptHandler);
    PORTC_PC1_SetInterruptHandler(PORTC_PC1_DefaultInterruptHandler);
}

void PORT_Initialize(void)
{
    /* On AVR devices all peripherals are enable from power on reset, this
     * disables all peripherals to save power. Driver shall enable
     * peripheral if used */

    /* Set all pins to low power mode */
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTE + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTF + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTC + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTD + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
}

/**
  Allows selecting an interrupt handler for PORTF_SW0 at application runtime
*/
void PORTF_SW0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_SW0_InterruptHandler = interruptHandler;
}

void PORTF_SW0_DefaultInterruptHandler(void)
{
    // add your PORTF_SW0 interrupt custom code
    // or set custom function using PORTF_SW0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_RST at application runtime
*/
void PORTA_RST_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_RST_InterruptHandler = interruptHandler;
}

void PORTA_RST_DefaultInterruptHandler(void)
{
    // add your PORTA_RST interrupt custom code
    // or set custom function using PORTA_RST_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA4 at application runtime
*/
void PORTA_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA4_InterruptHandler = interruptHandler;
}

void PORTA_PA4_DefaultInterruptHandler(void)
{
    // add your PORTA_PA4 interrupt custom code
    // or set custom function using PORTA_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA6 at application runtime
*/
void PORTA_PA6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA6_InterruptHandler = interruptHandler;
}

void PORTA_PA6_DefaultInterruptHandler(void)
{
    // add your PORTA_PA6 interrupt custom code
    // or set custom function using PORTA_PA6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA5 at application runtime
*/
void PORTA_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA5_InterruptHandler = interruptHandler;
}

void PORTA_PA5_DefaultInterruptHandler(void)
{
    // add your PORTA_PA5 interrupt custom code
    // or set custom function using PORTA_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_nCS at application runtime
*/
void PORTA_nCS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_nCS_InterruptHandler = interruptHandler;
}

void PORTA_nCS_DefaultInterruptHandler(void)
{
    // add your PORTA_nCS interrupt custom code
    // or set custom function using PORTA_nCS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_PF1 at application runtime
*/
void PORTF_PF1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_PF1_InterruptHandler = interruptHandler;
}

void PORTF_PF1_DefaultInterruptHandler(void)
{
    // add your PORTF_PF1 interrupt custom code
    // or set custom function using PORTF_PF1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_PF0 at application runtime
*/
void PORTF_PF0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_PF0_InterruptHandler = interruptHandler;
}

void PORTF_PF0_DefaultInterruptHandler(void)
{
    // add your PORTF_PF0 interrupt custom code
    // or set custom function using PORTF_PF0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_YELLOW_LED at application runtime
*/
void PORTD_YELLOW_LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_YELLOW_LED_InterruptHandler = interruptHandler;
}

void PORTD_YELLOW_LED_DefaultInterruptHandler(void)
{
    // add your PORTD_YELLOW_LED interrupt custom code
    // or set custom function using PORTD_YELLOW_LED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_CE at application runtime
*/
void PORTF_CE_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_CE_InterruptHandler = interruptHandler;
}

void PORTF_CE_DefaultInterruptHandler(void)
{
    // add your PORTF_CE interrupt custom code
    // or set custom function using PORTF_CE_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_PC0 at application runtime
*/
void PORTC_PC0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC0_InterruptHandler = interruptHandler;
}

void PORTC_PC0_DefaultInterruptHandler(void)
{
    // add your PORTC_PC0 interrupt custom code
    // or set custom function using PORTC_PC0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_RED_LED at application runtime
*/
void PORTD_RED_LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_RED_LED_InterruptHandler = interruptHandler;
}

void PORTD_RED_LED_DefaultInterruptHandler(void)
{
    // add your PORTD_RED_LED interrupt custom code
    // or set custom function using PORTD_RED_LED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_INT at application runtime
*/
void PORTF_INT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_INT_InterruptHandler = interruptHandler;
}

void PORTF_INT_DefaultInterruptHandler(void)
{
    // add your PORTF_INT interrupt custom code
    // or set custom function using PORTF_INT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_SW1 at application runtime
*/
void PORTF_SW1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_SW1_InterruptHandler = interruptHandler;
}

void PORTF_SW1_DefaultInterruptHandler(void)
{
    // add your PORTF_SW1 interrupt custom code
    // or set custom function using PORTF_SW1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_BLUE_LED at application runtime
*/
void PORTD_BLUE_LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_BLUE_LED_InterruptHandler = interruptHandler;
}

void PORTD_BLUE_LED_DefaultInterruptHandler(void)
{
    // add your PORTD_BLUE_LED interrupt custom code
    // or set custom function using PORTD_BLUE_LED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_PC2 at application runtime
*/
void PORTC_PC2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC2_InterruptHandler = interruptHandler;
}

void PORTC_PC2_DefaultInterruptHandler(void)
{
    // add your PORTC_PC2 interrupt custom code
    // or set custom function using PORTC_PC2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTD_GREEN_LED at application runtime
*/
void PORTD_GREEN_LED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTD_GREEN_LED_InterruptHandler = interruptHandler;
}

void PORTD_GREEN_LED_DefaultInterruptHandler(void)
{
    // add your PORTD_GREEN_LED interrupt custom code
    // or set custom function using PORTD_GREEN_LED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTF_WAKE at application runtime
*/
void PORTF_WAKE_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTF_WAKE_InterruptHandler = interruptHandler;
}

void PORTF_WAKE_DefaultInterruptHandler(void)
{
    // add your PORTF_WAKE interrupt custom code
    // or set custom function using PORTF_WAKE_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTC_PC1 at application runtime
*/
void PORTC_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTC_PC1_InterruptHandler = interruptHandler;
}

void PORTC_PC1_DefaultInterruptHandler(void)
{
    // add your PORTC_PC1 interrupt custom code
    // or set custom function using PORTC_PC1_SetInterruptHandler()
}
ISR(PORTF_PORT_vect)
{  
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       PORTF_SW0_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       PORTF_PF1_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       PORTF_PF0_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       PORTF_CE_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       PORTF_INT_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       PORTF_SW1_InterruptHandler();
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       PORTF_WAKE_InterruptHandler();
    }

    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

