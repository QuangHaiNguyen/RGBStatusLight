/* 
 * File:   common.h
 * Author: haing
 *
 * Created on April 22, 2020, 3:26 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ATMEGA4808      1
    
#if ATMEGA4808
#include "mcc_generated_files/mcc.h" 
#else
#warning a hardware must be choose
#endif

#include "utility/debug.h"

uint8_t version;
uint8_t sub_version;
uint8_t ssub_version;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

