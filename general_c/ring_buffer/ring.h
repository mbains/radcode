/* 
 * File:   ring.h
 * Author: mannyb
 *
 * Created on November 24, 2013, 12:12 PM
 */

#ifndef RING_H
#define	RING_H
#include<stdint.h>

#define RINGBUF_SIZE (4)

typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint8_t data[RINGBUF_SIZE];
} RingBuffer;

int Enqueue(RingBuffer *buf, uint8_t data);
int Dequeue(RingBuffer *buf, uint8_t *data);
void Printqueue(RingBuffer *buf);


void buf_put_byte(RingBuffer *buf, uint8_t val);
uint8_t buf_get_byte(RingBuffer *buf);
#endif	/* RING_H */


