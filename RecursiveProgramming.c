#include <stdlib.h>   // Ger mig malloc, free, rand
#include <stdio.h>    // Ger mig printf
#include <stdbool.h>  // Ger mig bool, true, false
#include <time.h>     // Ger mig timespec och clock_gettime

long nano_seconds(struct timespec *t_start, struct timespec *t_stop)
// Tar två tider och returnerar skillnaden i nanosekunder
{
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
           // tv_nsec = nanosekunder-delen
           // tv_sec  = sekunder-delen (omvandlas till ns)
}

// Skapar en sorterad array utan dubbletter
int *sorted(int n)
{
    int *array = (int*)malloc(n * sizeof(int)); // allokerar minne på heapen
    int nxt = 0; // senaste värdet

    for (int i = 0; i < n; i++) // loopar igenom arrayen
    {
        nxt += rand() % 10 + 1; // ökar med ett positivt steg
        array[i] = nxt; // arrayen blir strikt sorterad
    }

    return array; // returnerar pekaren
}

bool recursive(int array[], int length, int key, int first, int last) {
    int index = (first + last) / 2;

    if (array[index] == key) {
        return true;
    }

    if (array[index] < key && index < last) {
        return recursive(array, length, key, index + 1, last);
    }

    if (array[index] > key && index > first) {
        return recursive(array, length, key, first, index - 1);
    }

    return false;
}

int main()
{
    int length = 1000000; // storleken på arrayen
    int *array = sorted(length); // skapa sorterad array

    int key = -1; // tal som inte finns i arrayen

    struct timespec t_start, t_stop; // tider före och efter

    clock_gettime(CLOCK_MONOTONIC, &t_start); // starta tidsmätning
    recursive(array, length, key, 0, length - 1); // direkt anrop, exakt enligt skelettet
    clock_gettime(CLOCK_MONOTONIC, &t_stop); // stoppa tidsmätning

    long time = nano_seconds(&t_start, &t_stop); // beräkna tiden
    printf("Time: %ld ns\n", time); // skriv ut resultatet

    free(array); // städa upp minnet
    return 0; // avsluta programmet korrekt
}
