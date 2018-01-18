#ifndef EVENT_H
#define EVENT_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ET_COLLIDE,
    ET_INPUT
} EventType;

typedef union {
    char *s;
    uint64_t i;
    double d;
    void *data;
} EventData;

typedef struct {
    int t;
    EventData d;
} Event;

typedef struct {
    Event queue[256];
    int head;
} EventQueue;

bool eq_enqueue(EventQueue *q, Event e);
// returns NULL if the queue is empty
Event *eq_dequeue(EventQueue *q);

#endif
