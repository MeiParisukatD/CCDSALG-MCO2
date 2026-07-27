#include "queue.h"

/*
    Purpose: initializes a new, empty queue in memory
    Returns: a pointer to the newly created queue
*/
Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("\nFailed to create queue");
    }
    else 
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

/*
    Purpose: inserts a new position at the tail of the queue
    @param : queue is the pointer to the queue where the position will be added
    @param : p is the position to be inserted
*/
void enqueue(Queue* queue, Position p) 
{
    if (queue == NULL)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode)); 
        if (node == NULL)
        {
            printf("\nQueue Overflow");
        }
        else
        {
            node->pos = p;
            node->next = NULL;

            if(queue->size == 0)
            {
                queue->head = node;
                queue->tail = node;
            }
            else
            {
                queue->tail->next = node;
                queue->tail = node;
            }
            queue->size++;
        }
    }
}

/*
    Purpose: removes and returns the position at the head of the queue
    Returns: the position that was removed, or a position containing {-1,-1} if the queue is empty
    @param : queue is the pointer to the queue to dequeue from
*/
Position dequeue(Queue* queue) 
{
    Position resultPosition = {-1,-1};

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue Underflow");
    }
    else
    {
        QueueNode* temp = queue->head; 
        resultPosition = temp->pos;

        queue->head = queue->head->next;
        queue->size--;

        if(queue->size == 0)
        {
            queue->tail = NULL;
        }
        
        free(temp);
    }
    return resultPosition;
}

/*
    Purpose: retrieves the position at the head of the queue without removing it
    Returns: the position at the head, or a position containing {-1,-1} if the queue is empty
    @param : queue is the pointer to the queue being checked
*/
Position Head(Queue* queue) 
{
    Position resultPosition = {-1,-1};

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultPosition = queue->head->pos;
    }
    return resultPosition;
}

/*
    Purpose: retrieves the position at the tail of the queue without removing it
    Returns: the position at the tail, or a position containing {-1,-1} if the queue is empty
    @param : queue is the pointer to the queue being checked
*/
Position Tail(Queue* queue) 
{
    Position resultPosition = {-1,-1};

    if (queue == NULL || queue->size == 0)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        resultPosition = queue->tail->pos; 
    }
    return resultPosition;
}

/*
    Purpose: checks if the given queue contains no elements
    Returns: true if the queue is empty or NULL, false otherwise
    @param : queue is the pointer to the queue being checked
*/
bool isEmptyQueue(Queue* queue)
{
    bool emptyStatus = false;
    if (queue == NULL || queue->size == 0)
    {
        emptyStatus = true;
    }
    return emptyStatus; 
}

/*
    Purpose: checks if the system has run out of memory to allocate a new queue node
    Returns: true if memory allocation fails, false if memory is available
    @param : queue is the pointer to the queue being checked
*/
bool isFullQueue(Queue* queue)
{
    bool fullStatus = false;
    QueueNode* testNode = (QueueNode*)malloc(sizeof(QueueNode)); 
    if (testNode == NULL) 
    {
        fullStatus = true;
    }
    else
    {
        free(testNode);
    }
    return fullStatus;
}

/*
    Purpose: frees all memory associated with the queue and its nodes
    @param : queue is a double pointer to the queue so it can be safely set to NULL after deletion
*/
void deleteQueue(Queue** queue)
{
    if (queue == NULL || *queue == NULL)
    {
        printf("\nQueue is NULL");
    }
    else
    {
        Queue* temp = *queue;
        QueueNode* current = temp->head; 
        QueueNode* next = NULL;          

        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        free(temp);
        *queue = NULL;
    }
}
