/***************************************************************************//*!
*
* @file      queue_circular.c
* @author    yanghanhai
* @version   V0.0.0
* @date      20180324
* @brief     
*
******************************************************************************/

#include "queue_circular.h"

/******************************************************************************
* External variables
******************************************************************************/

/******************************************************************************
* Global variables
******************************************************************************/


/******************************************************************************
* Constants and macros
******************************************************************************/


/******************************************************************************
* Local types
******************************************************************************/


/******************************************************************************
* Local function prototypes
******************************************************************************/


/******************************************************************************
* Local variables
******************************************************************************/


/******************************************************************************
* Local functions
******************************************************************************/


/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* Function Name	:	Queue_Init
******************************************************************************/
bool Queue_Init(st_can_queue_ptr pstQueue,
				st_can_message_ptr pstCanMsgQBuf,
				uint8_t u8MaxLength)
{
	bool bRtn;

	if(pstQueue != 0)
	{
		pstQueue->QHead = 0U;
		pstQueue->QTail = 0U;
		pstQueue->QTag = 0U;
		pstQueue->QDeep = 0U;
		pstQueue->QMaxLength = u8MaxLength;
		pstQueue->pstCanMsg = pstCanMsgQBuf;

		bRtn = true;
	}
	else
	{
		bRtn = false;
	}

	return bRtn;
}

/******************************************************************************
* Function Name	:	Queue_EnqueueCanMessage
******************************************************************************/
bool Queue_EnqueueCanMessage(st_can_queue_ptr pstQueue,
							 st_can_message_ptr pstCanMsg)
{
	bool bRtn;

	/* if queue full return false */
	if ((pstQueue->QTail == pstQueue->QHead) && (pstQueue->QTag == 1))
	{
		bRtn = false;
	}
	else	/* can enqueue */
	{
		/* { copy element */
		pstQueue->pstCanMsg[pstQueue->QTail].DLC = pstCanMsg->DLC;
		pstQueue->pstCanMsg[pstQueue->QTail].ID = pstCanMsg->ID;

		(void)memcpy(pstQueue->pstCanMsg[pstQueue->QTail].Msg, pstCanMsg->Msg, 8);
		/* { copy element */

		/* update tail */
		pstQueue->QTail = (pstQueue->QTail + 1) % pstQueue->QMaxLength;

		pstQueue->QDeep++;

		/* set queue full flag */
	    if(pstQueue->QTail == pstQueue->QHead)
	    	pstQueue->QTag = 1;

		bRtn = true;
	}

	return bRtn;
}

/******************************************************************************
* Function Name	:	Queue_DequeueCanMessage
******************************************************************************/
bool Queue_DequeueCanMessage(st_can_queue_ptr pstQueue,
							 st_can_message_ptr pstCanMsg)
{
	bool bRtn;

	/* if queue empty, retuen false */
	if ((pstQueue->QHead == pstQueue->QTail) && (pstQueue->QTag == 0))
	{
		bRtn = false;
	}
	else
	{
		/* { copy element */
		pstCanMsg->DLC = pstQueue->pstCanMsg[pstQueue->QHead].DLC;
		pstCanMsg->ID = pstQueue->pstCanMsg[pstQueue->QHead].ID;

		(void)memcpy(pstCanMsg->Msg, pstQueue->pstCanMsg[pstQueue->QHead].Msg, 8);
		/* } copy element */

		/* update head */
		pstQueue->QHead = (pstQueue->QHead + 1) % pstQueue->QMaxLength;

		pstQueue->QDeep--;

		if(pstQueue->QTail == pstQueue->QHead)
			pstQueue->QTag = 0;

		bRtn = true;
	}

	return bRtn;
}

/******************************************************************************
* Function Name	:	Queue_IsFull
******************************************************************************/
bool Queue_IsFull(st_can_queue_ptr pstQueue)
{
	return ((pstQueue->QTail == pstQueue->QHead) && (pstQueue->QTag == 1))? true : false;
}

/******************************************************************************
* Function Name	:	Queue_IsEmpty
******************************************************************************/
bool Queue_IsEmpty(st_can_queue_ptr pstQueue)
{
	return ((pstQueue->QHead == pstQueue->QTail) && (pstQueue->QTag == 0))? true : false;
}

/***************************** EOF *******************************************/


