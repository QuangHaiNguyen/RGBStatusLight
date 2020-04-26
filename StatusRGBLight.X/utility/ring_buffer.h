/* 
 * File:   ring_buffer.h
 * Author: haing
 *
 * Created on April 24, 2020, 11:34 PM
 */

#ifndef RING_BUFFER_H
#define	RING_BUFFER_H

/* Include section ---------------------------------------------------*/
#include "../common.h"


/* Define section ---------------------------------------------------*/



/* Global variable section -------------------------------------------*/



/* Global function prototype section ---------------------------------*/
typedef struct
{
    uint8_t *buff;
    uint8_t capacity;
    uint8_t head;
    uint8_t tail;
    uint8_t count;
}RingBuffer;

typedef enum CirBuff_Status
{
    BUFF_OK = 0,
    BUFF_NO_MEMORY,
	BUFF_ERROR,
	BUFF_FULL,
	BUFF_EMPTY
}RingBuff_Status;

RingBuff_Status RingBuffer_IsEmpty(RingBuffer * _this);
RingBuff_Status RingBuffer_IsFull(RingBuffer * _this);
RingBuff_Status RingBuffer_Push(RingBuffer * _this, char * data, uint8_t size);
RingBuff_Status RingBuffer_Pop(RingBuffer * _this, char * data, uint8_t size);
RingBuff_Status RingBuffer_Deinit(RingBuffer * _this);
RingBuff_Status RingBuffer_Reset(RingBuffer * _this);
RingBuff_Status RingBuffer_Init( RingBuffer * _this, uint8_t size);
RingBuff_Status RingBuffer_GetAvailableMemory( RingBuffer * _this, uint8_t * avail_mem);

#endif	/* RING_BUFFER_H */

