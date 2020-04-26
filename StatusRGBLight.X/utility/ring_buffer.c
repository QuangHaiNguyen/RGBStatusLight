
/* Include section ---------------------------------------------------*/
#include "ring_buffer.h"
#include <string.h>

/* Define section ---------------------------------------------------*/


/* Global variable section -------------------------------------------*/

/* Local variable section --------------------------------------------*/

/* Global function section ---------------------------------*/

/**
 * @brief Initilize a circular buffer
 * 
 * @param cir_buff a circular buffer struct 
 *    
 * @return void
 */
RingBuff_Status RingBuffer_Init( RingBuffer * _this, uint8_t size)
{
    _this->head = 0;
    _this->tail = 0;
    _this->count = 0;
    _this->capacity = size;
    _this->buff = (uint8_t *)malloc(size * sizeof(uint8_t));
    if(NULL == _this->buff){
        return BUFF_NO_MEMORY;
    }
    memset(_this->buff, 0, _this->capacity);
    return BUFF_OK;
}

/**
 * @brief Check if the buffer is empty
 * 
 * @param cir_buff a circular buffer struct 
 *    
 * @return Status of the buffer
 *          + OK (not empty)
 *          + EMPTY
 */
RingBuff_Status RingBuffer_IsEmpty(RingBuffer * _this)
{
    return (0 == _this->count) ? BUFF_EMPTY : BUFF_OK;
}

/**
 * @brief Check if the buffer is full
 * 
 * @param cir_buff a circular buffer struct 
 *    
 * @return Status of the buffer
 *          + OK (not full)
 *          + FULL
 */
RingBuff_Status RingBuffer_IsFull(RingBuffer * _this)
{
    return (_this->count == _this->capacity) ? BUFF_FULL : BUFF_OK;
}

/**
 * @brief Push data into buffer
 * 
 * @param cir_buff  a circular buffer struct
 *        data      data pushed into buffer 
 *    
 * @return Status of the buffer
 *          + OK
 *          + FULL (buffer is full, data will be discarded)
 */
RingBuff_Status RingBuffer_Push(RingBuffer * _this, char * data, uint8_t size)
{
    if(_this->capacity - _this->count < size){
        return BUFF_NO_MEMORY;
    }
    else{
        memcpy(&_this->buff[_this->head], data, size);
        _this->head = (_this->head + size <  _this->capacity) ? (_this->head + size) : 0;
        _this->count = (_this->count + size <  _this->capacity) ? (_this->count + size) :  _this->capacity;
        return BUFF_OK;
    }
}

/**
 * @brief Pop data out of buffer
 * 
 * @param cir_buff  a circular buffer struct
 *        data      a variable to store data popped out of buffer
 *    
 * @return Status of the buffer
 *          + OK
 *          + EMPTY (buffer is empty)
 */
RingBuff_Status RingBuffer_Pop(RingBuffer * _this, char * data, uint8_t size)
{
    if(_this->count < size)
    {
        return BUFF_NO_MEMORY;
    }
    else
    {
         memcpy(data, &_this->buff[_this->tail], size);
        _this->tail = (_this->tail + size < _this->capacity) ? (_this->tail + size) : 0;
        _this->count = (_this->count - size > 0) ? (_this->count - size) : 0;
        return BUFF_OK;
        
    }
}

/**
 * @brief Clear the buffer
 * 
 * @param cir_buff a circular buffer struct 
 *    
 * @return void
 */
RingBuff_Status RingBuffer_Deinit(RingBuffer * _this)
{
    if(_this->buff != NULL)
        free(_this->buff);
    return BUFF_OK;
}

RingBuff_Status RingBuffer_Reset(RingBuffer * _this)
{
    _this->head = 0;
    _this->tail = 0;
    _this->count = 0;
    memset(_this->buff, 0, _this->capacity);
    return BUFF_OK;
}

RingBuff_Status RingBuffer_GetAvailableMemory( RingBuffer * _this, uint8_t * avail_mem)
{
    *avail_mem = _this->capacity - _this->count;
    return BUFF_OK;
}