#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct timespec t_start, t_stop;

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}

long search(int n, int loop) {
    int *array = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        array[i] = rand() % (n * 2);

    int *keys = (int*)malloc(loop * sizeof(int));

    for (int i = 0; i < loop; i++)
        keys[i] = rand() % (n * 2);

    int sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int i = 0; i < loop; i++) {
        int key = keys[i];
        
        for (int j = 0; j < n; j++) {
            if (key == array[j]) {
                sum++;
                break;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int main() {
    int element []= {1000, 2000, 4000, 8000, 16000, 32000};
    int loop = 1000;

    for (int i = 0; i < 6; i++) {
        int n = element[i];
        long wall = search(n, loop);
        printf("time: %ld ns\n", wall);
    }
}
