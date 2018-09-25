/***************************************************************************//*!
*
* @file      queue_circular.h
* @author    C0138
* @version   V0.0.0
* @date      20180324
* @brief     
*
******************************************************************************/

#ifndef __QUEUE_CIRCULAR_H__
#define __QUEUE_CIRCULAR_H__


/*******************************************************************************
* Includes
********************************************************************************/
#include "stdbool.h"
#include "stdint.h"
#include "string.h"

/*******************************************************************************
* Constants
********************************************************************************/    

/*******************************************************************************
* Macros
********************************************************************************/


/*******************************************************************************
* Types
********************************************************************************/
typedef struct
{
	uint32_t ID;
	uint8_t DLC;
	uint8_t Msg[8];
} st_can_message_t, *st_can_message_ptr;

typedef struct
{
	uint8_t QHead;
	uint8_t QTail;
	uint8_t QTag;
	uint8_t QDeep;
	uint8_t QMaxLength;
	st_can_message_ptr pstCanMsg;
} st_can_queue_t, *st_can_queue_ptr;

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/

/***************************************************************************//*!
* @brief	 initialize queue
* @param[in] pstQueue, implement of queue.
* @param[in] pstCanMsgQBuf, element buffer.
* @param[in] u8MaxLength, length of queue.
* @return    bool, true - indicate success, false - indicate fail.
********************************************************************************/
bool Queue_Init(st_can_queue_ptr pstQueue,
				st_can_message_ptr pstCanMsgQBuf,
				uint8_t u8MaxLength);

/***************************************************************************//*!
* @brief	 Enqueue element.
* @param[in] pstQueue, implement of queue.
* @param[in] pstCanMsg, element.
* @return	 bool, true - indicate success, false - indicate fail.
********************************************************************************/
bool Queue_EnqueueCanMessage(st_can_queue_ptr pstQueue,
							 st_can_message_ptr pstCanMsg);

/***************************************************************************//*!
* @brief	 Dequeue element.
* @param[in] pstQueue, implement of queue.
* @param[in] pstCanMsg, element.
* @return	 bool, true - indicate success, false - indicate fail.
********************************************************************************/
bool Queue_DequeueCanMessage(st_can_queue_ptr pstQueue,
							 st_can_message_ptr pstCanMsg);

/***************************************************************************//*!
* @brief	 check if queue full.
* @param[in] pstQueue, implement of queue.
* @return	 bool, true - indicate full, false - indicate not full.
********************************************************************************/
bool Queue_IsFull(st_can_queue_ptr pstQueue);

/***************************************************************************//*!
* @brief	 check if queue empty.
* @param[in] pstQueue, implement of queue.
* @return	 bool, true - indicate empty, false - indicate not empty.
********************************************************************************/
bool Queue_IsEmpty(st_can_queue_ptr pstQueue);


#endif  /* __QUEUE_CIRCULAR_H__ */

/******************************* EOF *******************************************/
