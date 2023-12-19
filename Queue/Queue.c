#include <stdlib.h>
#include <stdio.h>

#define BASE_SIZE 1 //Defines an initial length for a queue
#define EMPTY -999 //Defines an empty value in queue

struct Queue{
    int length;
    int top;
    int *values;

    void (*add)(struct Queue *q, int value);
    void (*addAll)(struct Queue *q, int *array, int length);
    int (*poll)(struct Queue *q);
    int (*peek)(struct Queue *q);
    void (*printQueue)(struct Queue *q);
};
typedef struct Queue queue;


void add(queue *q, int value) {
    if(q->top == EMPTY) {
        q->values[0] = value;
        q->top = value;
        return;
    }
    int *newArr = malloc((q->length+1) * sizeof(int));
    for(int i = 0; i < q->length; i++) {
        newArr[i] = q->values[i];
    }

    newArr[q->length] = value;
    free(q->values);
    q->values = newArr;
    q->length++;
}

//remove and return the first element in the queue
int poll(queue *q) {
    if(q->length == 0) {
        printf("no values in queue\n");
        return EMPTY;
    }

    int returnValue = q->values[0];
    int *newArr = malloc((q->length - 1) * sizeof(int));

    for(int i = 1; i < q->length; i++) {
        newArr[i-1] = q->values[i];
    }

    free(q->values);
    q->values = newArr;
    q->top = q->values[0];
    q->length--;
    return returnValue;
}

int peek(queue *q) {
    return q->top;
}


void addAll(queue *q, int *array, int length) {
    for(int i = 0; i < length; i++) {
        q->add(q, array[i]);
    }
}

void printQueue(queue *q) {
    printf("[ ");
    for(int i = 0; i < q->length; i++) {
        printf("%i ", q->values[i]);
    }
    printf("] \n");
}

queue *initQueue() {
    queue *newQueue = malloc(sizeof(queue));
    newQueue->values = malloc(BASE_SIZE * sizeof(int));
    newQueue->top = EMPTY;
    newQueue->length = BASE_SIZE;

    //TO-DO: Add functions also
    newQueue->add = add;
    newQueue->addAll = addAll;
    newQueue->poll = poll;
    newQueue->peek = peek;
    newQueue->printQueue = printQueue;
    return newQueue;
}

void freeQueue(queue *q) {
    free(q->values);
    free(q);
}

//Tests addAll() and peek() method
int test1(queue *q, int *testArr, int length) {
    q->addAll(q, testArr, length);
    int expectedO = testArr[0];
    int actualO = q->peek(q);
    printf("expected 1: %i, actual 1: %i ", expectedO, actualO);
    return expectedO == actualO;
}

//Tests addAll() and poll() method
int test2(queue *q, int *testArr, int length) {
    q->addAll(q, testArr, length);
    q->poll(q);
    int expectedO = testArr[1];
    int actualO = q->peek(q);
    printf("expected 2: %i, actual 2: %i ", expectedO, actualO);
    return expectedO == actualO;
}

//Tests add() method and multiple poll() calls
int test3(queue *q, int *testArr, int length) {
    for(int i = 0; i < length; i++) {
        q->add(q, testArr[i]);
    }
    q->poll(q);
    q->poll(q);
    int expectedO = testArr[2];
    int actualO = q->poll(q);
    printf("expected 3: %i, actual 3: %i ", expectedO, actualO);
    return expectedO == actualO;
}

//Tests empty queue edge case
int test4(queue *q) {
    int startingLength = q->length;
    for(int i = 0; i < startingLength; i++) {
        q->poll(q);
    }
    int errorNum = q->poll(q);
    printf("%i \n", errorNum);
    return errorNum == EMPTY;
}

int main() {
    int array1[] = {1,2,3,4,5};
    int length1 = sizeof(array1) / sizeof(int);
    queue *q1 = initQueue();
    printf("test 1: %i \n", test1(q1, array1, length1));

    int array2[] = {5,4,3,2,1};
    int length2 = sizeof(array2) / sizeof(int);
    queue *q2 = initQueue();
    printf("test 2: %i \n", test2(q2, array2, length2));

    int array3[] = {3,1,3};
    int length3 = sizeof(array3) / sizeof(int);
    queue *q3 = initQueue();
    printf("test 3: %i \n", test3(q3, array3, length3));

    int array4[] = {5,6,7,8};
    int length4 = sizeof(array4) / sizeof(int);
    queue *q4 = initQueue();
    q4->addAll(q4, array4, length4);
    printf("test 4: %i \n", test4(q4));

    freeQueue(q1);
    freeQueue(q2);
    freeQueue(q3);
    freeQueue(q4);

    return 0;
}