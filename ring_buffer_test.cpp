#include "CppUTest/TestHarness.h"

#include "ring_buffer.h"

#define RING_BUFFER_SIZE 200

ringBuffer_t buffer;
uint8_t workBuffer[RING_BUFFER_SIZE];

TEST_GROUP(RingBufferInitTestGroup)
{
    void setup()
    {
    }
};

TEST(RingBufferInitTestGroup, CheckInitOneByteElementTest)
{
    RingBuffer_Init(&buffer, sizeof(uint8_t), 10, workBuffer);

    CHECK_EQUAL(workBuffer, buffer.ptrBuffer);
    CHECK_EQUAL(0, buffer.wr);
    CHECK_EQUAL(0, buffer.rd);
    CHECK_EQUAL(0, buffer.numOfElements);
    CHECK_EQUAL(10, buffer.maxNumOfElements);
    CHECK_EQUAL(1, buffer.elementSize);
}

TEST(RingBufferInitTestGroup, CheckInitTwoBytesElementTest)
{
    RingBuffer_Init(&buffer, sizeof(uint16_t), 10, workBuffer);

    CHECK_EQUAL(workBuffer, buffer.ptrBuffer);
    CHECK_EQUAL(0, buffer.wr);
    CHECK_EQUAL(0, buffer.rd);
    CHECK_EQUAL(0, buffer.numOfElements);
    CHECK_EQUAL(10, buffer.maxNumOfElements);
    CHECK_EQUAL(2, buffer.elementSize);
}

TEST_GROUP(RingBufferCommonTestGroup)
{
    void setup()
    {
        RingBuffer_Init(&buffer, sizeof(uint8_t), 10, workBuffer);
    }
};

TEST(RingBufferCommonTestGroup, CheckNumOfElementsTest)
{
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
    uint8_t element = 100;
    CHECK(RingBuffer_Push(&buffer, &element));
    CHECK_EQUAL(1, RingBuffer_NumOfElements(&buffer));

    CHECK(RingBuffer_Push(&buffer, &element));
    CHECK_EQUAL(2, RingBuffer_NumOfElements(&buffer));

    CHECK(RingBuffer_Push(&buffer, &element));
    CHECK_EQUAL(3, RingBuffer_NumOfElements(&buffer));

    CHECK(RingBuffer_Pop(&buffer, &element));
    CHECK_EQUAL(2, RingBuffer_NumOfElements(&buffer));

    CHECK(RingBuffer_Pop(&buffer, &element));
    CHECK_EQUAL(1, RingBuffer_NumOfElements(&buffer));

    CHECK(RingBuffer_Pop(&buffer, &element));
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckNumOfElementsFullBufferTest)
{
    // Заполняем буфер
    uint8_t element = 100;
    for (int i = 0; i < 10; ++i)
    {
        CHECK(RingBuffer_Push(&buffer, &element));
        CHECK_EQUAL(i + 1, RingBuffer_NumOfElements(&buffer));
    }
    
    // Если буфер полный, то количество элементов не увеличется
    CHECK_FALSE(RingBuffer_Push(&buffer, &element));
    CHECK_EQUAL(10, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckNumOfElementsEmptyBufferTest)
{
    uint8_t element = 100;
    // Если извлечь из пустого буфера, то количество элементов по прежнему ноль
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
    CHECK_FALSE(RingBuffer_Pop(&buffer, &element));
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckClearTest)
{
    uint8_t element = 100;
    RingBuffer_Push(&buffer, &element);
    CHECK_EQUAL(1, RingBuffer_NumOfElements(&buffer));
    RingBuffer_Clear(&buffer);
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckClearFullBufferTest)
{
    // Заполняем буфер
    uint8_t element = 100;
    for (int i = 0; i < 10; ++i)
    {
        RingBuffer_Push(&buffer, &element);
    }

    CHECK_EQUAL(10, RingBuffer_NumOfElements(&buffer));
    RingBuffer_Clear(&buffer);
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckClearEmptyBufferTest)
{
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
    RingBuffer_Clear(&buffer);
    CHECK_EQUAL(0, RingBuffer_NumOfElements(&buffer));
}

TEST(RingBufferCommonTestGroup, CheckPushAndPopTest)
{
    uint8_t elements[10] = {0x20, 0x31, 0x45, 0x1, 0x0, 0xEE, 0x77, 0xA0, 0xB, 0xC};

    for (int i = 0; i < 10; ++i)
    {
        CHECK(RingBuffer_Push(&buffer, &elements[i]));
    }

    for (int i = 0; i < 10; ++i)
    {
        uint8_t readElement = 0;
        CHECK(RingBuffer_Pop(&buffer, &readElement));
        CHECK_EQUAL(elements[i], readElement);
    }
}

TEST(RingBufferCommonTestGroup, CheckPushToFullBufferTest)
{
    // Заполняем буфер
    uint8_t element = 100;
    for (int i = 0; i < 10; ++i)
    {
        RingBuffer_Push(&buffer, &element);
    }

    CHECK_FALSE(RingBuffer_Push(&buffer, &element));
}

TEST(RingBufferCommonTestGroup, CheckPopFromEmptyBufferTest)
{
    uint8_t element = 0;
    CHECK_FALSE(RingBuffer_Pop(&buffer, &element));
}
