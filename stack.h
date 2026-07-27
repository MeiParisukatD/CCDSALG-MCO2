#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "position.h"

typedef struct StackNodeTag 
{
    Position pos; 
    struct StackNodeTag* next; 
} StackNode;                   

typedef struct StackTag
{
    StackNode* top;            
    int size;
} Stack;

Stack* createStack();
void push(Stack* stack, Position p);
Position pop(Stack* stack);
Position top(Stack* stack);
bool isEmptyStack(Stack* stack);
bool isFullStack(Stack* stack);
void deleteStack(Stack** stack);

#endif // STACK_H