#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "position.h"

// Queue struct declarations
typedef struct QueueNodeTag 
{
    Position pos; 
    struct QueueNodeTag* next; 
} QueueNode;                   

typedef struct QueueTag
{
    QueueNode* head;           
    QueueNode* tail;           
    int size;
} Queue;

// Function Prototypes
Queue* createQueue();
void enqueue(Queue* queue, Position p);
Position dequeue(Queue* queue);
Position Head(Queue* queue);
Position Tail(Queue* queue);
bool isEmptyQueue(Queue* queue);
bool isFullQueue(Queue* queue);
void deleteQueue(Queue** queue);

#endif // QUEUE_H