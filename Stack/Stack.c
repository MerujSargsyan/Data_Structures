#include <stdio.h>
#include <stdlib.h>

#define BASE_SIZE 1 //Base size of a Stack
#define EMPTY -999 //Empty value

struct Stack {
    int top;
    int length;
    int numValues;
    int *values;

    void (*push)(struct Stack *stack, int value);
    int (*pop)(struct Stack *stack);
    int (*peek)(struct Stack *stack);
    int (*empty)(struct Stack *stack);
    int (*search)(struct Stack *stack, int value);
};
typedef struct Stack stack; 


void shiftArrayRight(stack *stack) {
    int *array = malloc((stack->length + 1) * sizeof(int));
    if(array == NULL) {
        printf("Error in shiftArrayLeft");
        return;
    }

    for(int i = 0; i < stack->length; i++) {
        array[i+1] = stack->values[i]; 
    }

    free(stack->values);
    stack->values = array; 
    stack->length++;
}

int shiftArrayLeft(stack *stack) {
    int *array = malloc((stack->length - 1) * sizeof(int));
    if(array == NULL) {
        printf("Error in shiftArrayLeft");
        return -1;
    }
    int output = stack->top;

    for(int i = 1; i < stack->length; i++) {
       array[i-1] = stack->values[i];
    }

    stack->top = array[0];
    free(stack->values);
    stack->values = array;
    return output;
}

int pop(stack *stack) {
    stack->numValues--;
    return shiftArrayLeft(stack);
}

void push(stack *stack, int value) {
    shiftArrayRight(stack);
    stack->values[0] = value;
    stack->top = value;
    stack->numValues++;
}

int peek(stack *stack) {
    return stack->top;
}

int empty(stack *stack) {
    return stack->numValues == 0;
}

int search(stack *stack, int value) {
    for(int i = 0; i < stack->length; i++) {
        if(stack->values[i] == value) {
            return i;
        }
    }
    return -1;
}

stack *initStack() {
    stack *newStack = malloc(sizeof(stack));
    if(newStack == NULL) {
        printf("Error");
        return NULL;
    }
    newStack->values = malloc(BASE_SIZE * sizeof(int));
    newStack->top = EMPTY;
    newStack->length = 1;
    newStack->numValues = 0;
    newStack->push = push;
    newStack->pop = pop;
    newStack->peek = peek;
    newStack->empty = empty;
    newStack->search = search;
    return newStack;
}

void freeStack(stack *stack) {
    free(stack->values);
    free(stack);
}

//TO-DO: Write test cases