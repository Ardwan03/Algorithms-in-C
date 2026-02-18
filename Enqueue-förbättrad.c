#include "queuelist.h"
#include <stdlib.h>           
#include <stdio.h>
#include <time.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000L;
}

queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    q->last  = NULL;
    return q;
}

bool empty(queue *q) { 
    return q->first == NULL;
}

void enque(queue* q, int v) {
    node *nd = malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;

    if (q->last != NULL) {
        q->last->next = nd;
        q->last = nd;
    } 
    
    else {           
        q->first = nd;
        q->last  = nd;
    }
}

int dequeue(queue *q) {
    int res = 0;

    if (q->first != NULL) {
        node *old = q->first;
        res = old->value;
        q->first = old->next;

        if (q->first == NULL) 
            q->last = NULL;

        free(old);
    }

    return res;
}

int main() {
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000};
    int k = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < k; i++) {
        int N = sizes[i];
        queue *q = create_queue();
        struct timespec t_start, t_stop;
        clock_gettime(CLOCK_MONOTONIC, &t_start);

        for (int j = 0; j < N; j++)
            enque(q, j);

        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        long wall = nano_seconds(&t_start, &t_stop);
        printf("N=%d enque: %ld ns\n", N, wall);

        while (!empty(q))
            dequeue(q);

        free(q);
    }
    return 0;
}
