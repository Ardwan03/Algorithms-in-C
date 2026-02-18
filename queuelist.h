#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct queue {
    node *first;
    node *last;
} queue;

queue *create_queue();
bool empty(queue *q);
void enque(queue *q, int v);
int dequeue(queue *q);

#endif 
