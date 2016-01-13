
#include "ring.h"
#include <stdio.h>

static void buf_reset(RingBuffer *buf);
static int buf_len(RingBuffer *buf);
static int buf_isfull(RingBuffer *buf);
static int buf_isempty(RingBuffer *buf);



static void buf_reset(RingBuffer *buf)
{
    buf->head = buf->tail = 0;
}

static int buf_len(RingBuffer *buf)
{
    int len = buf->tail - buf->head;
    if (len < 0)
        len += RINGBUF_SIZE;
    
    return len;
}

static int buf_isfull(RingBuffer *buf)
{
    return buf_len(buf) == (RINGBUF_SIZE-1);
}

static int buf_isempty(RingBuffer *buf)
{
    return buf->head == buf->tail;
}

uint8_t buf_get_byte(RingBuffer *buf)
{
    uint8_t item;
    
    item = buf->data[buf->head++];
    printf("head = %d\n", buf->head);
    if (buf->head == RINGBUF_SIZE)         // Wrap
    {
        printf("resetting head\n");
        buf->head = 0;
    }   
    printf("get_byte: %d\n", item);
    return item;
}

void buf_put_byte(RingBuffer *buf, uint8_t val)
{
    
    buf->data[buf->tail++] = val;
    Printqueue(buf);
    printf("tail = %d\n", buf->tail);
    if (buf->tail == RINGBUF_SIZE) {
        printf("resetting tail\n");
        buf->tail = 0;
    }
}

int Enqueue(RingBuffer* buf, uint8_t data)
{
    if(buf_isfull(buf)) {
        printf("buf is full: %d\n", data);
        return 0;
    }
    else {
        buf_put_byte(buf, data);
    }
    return 1;
}

int Dequeue(RingBuffer* buf, uint8_t *data)
{
    if(buf_isempty(buf)) {
        printf("buf is empty\n");
    }
    else {
        *data = buf_get_byte(buf);
    }
    return 1;
}

void Printqueue(RingBuffer *buf) 
{
    int tmp = buf->head;
    while(tmp != buf->tail) {
        printf("%d ", tmp++);
    }
    printf("\n");
}
