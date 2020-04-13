/* 
 * File:   WS2812_conf.h
 * Author: haing
 *
 * Created on April 13, 2020, 3:36 PM
 */

#ifndef WS2812_CONF_H
#define	WS2812_CONF_H

#ifdef	__cplusplus
extern "C" {
#endif


#define USING_AVR4808       1 

#if USING_AVR4808
    #include "atmega4808_pwm.h"
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* WS2812_CONF_H */

