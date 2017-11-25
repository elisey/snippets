/**
 * @file
 * \brief API библиотеки для работы с монохромным дисплеем
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct
{
	uint8_t *ptrBuffer;
	uint16_t wr;
	uint16_t rd;
	uint16_t numOfElements;
	uint16_t maxNumOfElements;
	uint8_t elementSize;
} ringBuffer_t;

void RingBuffer_Init(ringBuffer_t* obj, uint8_t elementSize, uint16_t numOfElements, uint8_t *workBuffer);
void RingBuffer_Clear(ringBuffer_t *obj);
bool RingBuffer_Push(ringBuffer_t *obj, void *ptrElement);
bool RingBuffer_Pop(ringBuffer_t *obj, void *ptrElement);
uint16_t RingBuffer_NumOfElements(ringBuffer_t *obj);

#ifdef __cplusplus
}
#endif