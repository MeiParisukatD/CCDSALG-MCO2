#include "stack.h"

/*
    Purpose: initializes a new, empty stack in memory
    Returns: a pointer to the newly created stack
*/
Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("\nFailed to create stack");
    }
    else
    {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

/*
    Purpose: inserts a new position at the top of the stack
    @param : stack is the pointer to the stack where the position will be pushed
    @param : p is the position to be inserted
*/
void push(Stack* stack, Position p) 
{
    if (stack == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        StackNode* node = (StackNode*)malloc(sizeof(StackNode)); 
        if (node == NULL)
        {
            printf("\nStack Overflow");
        }
        else
        {
            node->pos = p;
            node->next = stack->top;
            stack->top = node;
            stack->size++;
        }
    }
}

/*
    Purpose: removes and returns the position at the top of the stack
    Returns: the position that was removed, or a position containing {-1,-1} if the queue is empty
    @param : stack is the pointer to the stack to pop from
*/
Position pop(Stack* stack) 
{
    Position resultPosition = {-1,-1};

    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack Underflow");
    }
    else
    {
        StackNode* temp = stack->top; 
        resultPosition = temp->pos;

        stack->top = stack->top->next;
        stack->size--;
        
        free(temp);
    }
    return resultPosition;
}

/*
    Purpose: retrieves the position at the top of the stack without removing it
    Returns: the position at the top, or a position containing {-1,-1} if the queue is empty
    @param : stack is the pointer to the stack being checked
*/
Position top(Stack* stack) 
{
    Position resultPosition = {-1,-1};

    if (stack == NULL || stack->top == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        resultPosition = stack->top->pos;
    }
    return resultPosition;
}

/*
    Purpose: checks if the given stack contains no elements
    Returns: true if the stack is empty or NULL, false otherwise
    @param : stack is the pointer to the stack being checked
*/
bool isEmptyStack(Stack* stack)
{
    bool result = false;
    if (stack == NULL || stack->size == 0)
    {
        result = true;
    }
    return result;
}

/*
    Purpose: checks if the system has run out of memory to allocate a new stack node
    Returns: true if memory allocation fails, false if memory is available
    @param : stack is the pointer to the stack being checked
*/
bool isFullStack(Stack* stack)
{
    bool result = false;
    StackNode* testNode = (StackNode*)malloc(sizeof(StackNode)); 
    if (stack == NULL || testNode == NULL)
    {
        result = true;
    }
    else
    {
        free(testNode);
    }
    return result;
}

/*
    Purpose: frees all memory associated with the stack and its nodes
    @param : stack is a double pointer to the stack so it can be safely set to NULL after deletion
*/
void deleteStack(Stack** stack)
{
    if (stack == NULL || *stack == NULL)
    {
        printf("\nStack is NULL");
    }
    else
    {
        Stack* temp = *stack;
        StackNode* current = temp->top; 
        StackNode* next = NULL;         

        while(current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        free(temp);
        *stack = NULL;
    }
}
