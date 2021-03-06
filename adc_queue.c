/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "queue.h"

void init_adc_queue(adc_queue* q)
{
    q->front = 0;
    q->rear  = 0;
    q->count = 0;
}

// important to remember, where the rear is, there should be no value
// this means an array of 256 can only fit 255 elements
void adc_enqueue(adc_queue* q, uint16 val)
{
    if (q->count >= QUEUE_SIZE - 1) // rear - front >= 255
    {
        UART_UartPutString("Queue FULL\r\n");
    }
    else
    {
        q->container[q->rear] = val;
        q->count += 1;
        // increment q->rear
        if (q->rear < QUEUE_SIZE - 1) q->rear += 1;
        else q->rear = 0;
    }
}

uint16* adc_dequeue(adc_queue* q)
{
    uint16* to_return = NULL;
    if (q->count == 0)
    {
        UART_UartPutString("Queue Empty\r\n");
    }
    else
    {
        to_return = &(q->container[q->front]);
        q->count -= 1;
        // increment q->front
        if (q->front < QUEUE_SIZE) q->front += 1;
        else q->front = 0;
    }
    return to_return;
}

uint16* adc_peek(adc_queue* q)
{
    uint16* to_return = NULL;
    if (q->count == 0)
    {
        UART_UartPutString("Queue Empty\r\n");
    }
    else
    {
        to_return = &(q->container[q->front]);
    }
    return to_return;
}

bool adc_is_empty(adc_queue* q)
{
    return (q->count <= 0);
}

/* [] END OF FILE */
