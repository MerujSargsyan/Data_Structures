#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};
typedef struct Node node;

struct LinkedList {
    node *head;
    node *current;
    
    void (*createList)(struct LinkedList *list, int elementCount, int elements[]);
    void (*addNodeToEnd)(struct LinkedList *list, int value);
    void (*addNodeToHead)(struct LinkedList *list, int value);
    void (*addNodeAtNode)(struct LinkedList *list, int index, int value);
    void (*printList)(struct LinkedList *list, node *startNode);
    node *(*getHead)(struct LinkedList *list);
    node *(*searchList)(struct LinkedList *list, int value);
};
typedef struct LinkedList LinkedList;

void addNodeToEnd(LinkedList *list, int value) {
    node *n1 = malloc(sizeof(node));
    n1->value = value;
    n1->next = NULL;

    if(list->head == NULL) {
        list->head = n1;
    } else {
        list->current->next = n1;
    }
    list->current = n1;
}

void addNodeToHead(LinkedList *list, int value) {
    node *n1 = malloc(sizeof(node));
    n1->value = value;

    if(list->head == NULL) {
        list->head = n1;
    } else {
        n1->next = list->head->next;
        list->head->next = n1;
    }    
}

void addNodeAtNode(LinkedList *list, int index, int value) {
    node *newNode = malloc(sizeof(node));
    newNode->value = value;

    list->current = list->head;
    for(int i = 0; i < index; i++) {
        list->current = list->current->next;
    }
    node *rightNode = list->current->next;
    node *leftNode = list->current;
    leftNode->next = newNode;
    newNode->next = rightNode;
}

node *getHead(LinkedList *list) {
    return list->head;
}

void printList(LinkedList *list, node *startNode) {
    if(startNode == NULL) {
        return;
    }
    printf("%i -> ", startNode->value);
    printList(list, startNode->next);
}

void createList(LinkedList *list, int elementCount, int elements[]) {
    for(int i = 0; i < elementCount; i++) {
        addNodeToEnd(list, elements[i]);
    }
}

node *searchList(LinkedList *list, int element) {
    list->current = list->head;
    while(list->current != NULL && list->current->value != element) {
        list->current = list->current->next;
    }
    if(list->current == NULL) {
        return NULL;
    }
    return list->current;
}

void freeList(LinkedList *list) {
    node *current = list->head;
    node *next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

LinkedList initList() {
    LinkedList list;
    list.head = NULL;
    list.current = NULL;
    list.addNodeToEnd = addNodeToEnd;
    list.addNodeToHead = addNodeToHead;
    list.addNodeAtNode = addNodeAtNode;
    list.createList = createList;
    list.getHead = getHead;
    list.printList = printList;
    list.searchList = searchList;
    return list;
}

int main() {
    return 0;
}
//TO-DO: write test cases;