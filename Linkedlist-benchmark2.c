#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *linked_create() {
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}

void linked_free(linked *lnk) {
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void linked_add(linked *lnk, int item) {
    cell *new = (cell*)malloc(sizeof(cell));
    new->value = item;
    new->tail = lnk->first;
    lnk->first = new;
}

int linked_length(linked *lnk) {
    int count = 0;
    cell *nxt = lnk->first;

    while (nxt != NULL) {
        count++;
        nxt = nxt->tail;
    }
    return count;
}

bool linked_find(linked *lnk, int item) {
    cell *nxt = lnk->first;

    while (nxt != NULL) {
        if (nxt->value == item)
            return true;

        nxt = nxt->tail;
    }
    return false;
}

void linked_remove(linked *lnk, int item) {
    cell *nxt = lnk->first;
    cell *prv = NULL;

    while (nxt != NULL) {
        if (nxt->value == item) {
            if (prv == NULL) 
                lnk->first = nxt->tail;

            
            else 
                prv->tail = nxt->tail;

            free(nxt);
            return;
        }
        prv = nxt;
        nxt = nxt->tail;
    }
}

void linked_append(linked *a, linked *b) {
    if (a->first == NULL) {
        a->first = b->first;
        b->first = NULL;
        return;
    }

    cell *nxt = a->first;

    while (nxt->tail != NULL) 
        nxt = nxt->tail;

    nxt->tail = b->first;
    b->first = NULL;
}

linked *linked_init(int n) {
    linked *a = linked_create();
    for (int i = 0; i < n; i++) 
        linked_add(a, i);

    return a;
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000L;
}

int main() {
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000};
    int fixed_a = 1000;
    int repeats = 2000;

    for (int s = 0; s < (int)(sizeof(sizes)/sizeof(sizes[0])); s++) {

        long sum = 0;

        for (int r = 0; r < repeats; r++) {
            linked *a = linked_init(fixed_a);
            linked *b = linked_init(sizes[s]);
            struct timespec t_start, t_stop;
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            linked_append(a, b);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            sum += nano_seconds(&t_start, &t_stop);
            linked_free(a);
            linked_free(b);
        }
        long avg = sum / repeats;
        printf("a=%d, b=%d, avg=%ld ns\n", fixed_a, sizes[s], avg);
    }
    return 0;
}


