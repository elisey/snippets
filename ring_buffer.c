#include "ring_buffer.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

static uint16_t incrementRingBufferIndex(uint16_t index, uint16_t maxIndexValue);

void RingBuffer_Init(ringBuffer_t* obj, uint8_t elementSize, uint16_t numOfElements, uint8_t *workBuffer)
{
	assert(obj != NULL);
	assert(workBuffer != NULL);
	assert(elementSize != 0);

	obj->elementSize = elementSize;
	obj->maxNumOfElements = numOfElements;

	obj->ptrBuffer = workBuffer;
	RingBuffer_Clear(obj);
}

void RingBuffer_Clear(ringBuffer_t *obj)
{
	assert(obj != NULL);

	obj->numOfElements = 0;
	obj->rd = 0;
	obj->wr = 0;
}

bool RingBuffer_Push(ringBuffer_t *obj, void *ptrElement)
{
	assert(obj != NULL);
	assert(ptrElement != NULL);

	if (obj->numOfElements == obj->maxNumOfElements)	{
		return false;
	}

	uint8_t *ptrDst = &(obj->ptrBuffer[ obj->wr * obj->elementSize ]);
	memcpy( ptrDst, ptrElement, obj->elementSize );
	obj->wr = incrementRingBufferIndex(obj->wr, obj->maxNumOfElements);
	obj->numOfElements++;

	assert(obj->numOfElements <= obj->maxNumOfElements);
	return true;
}

bool RingBuffer_Pop(ringBuffer_t *obj, void *ptrElement)
{
	assert(obj != NULL);
	assert(ptrElement != NULL);

	if (obj->numOfElements == 0)	{
		return false;
	}

	uint8_t *ptrSrc = &(obj->ptrBuffer[ obj->rd * obj->elementSize ]);
	memcpy( ptrElement, ptrSrc, obj->elementSize );
	obj->rd = incrementRingBufferIndex(obj->rd, obj->maxNumOfElements);

	assert(obj->numOfElements > 0);
	obj->numOfElements--;
	return true;
}

uint16_t RingBuffer_NumOfElements(ringBuffer_t *obj)
{
	assert(obj != NULL);
	
	return obj->numOfElements;
}

static uint16_t incrementRingBufferIndex(uint16_t index, uint16_t maxIndexValue)
{
	index++;
	if (index >= maxIndexValue)	{
		index = 0;
	}
	return index;
}
