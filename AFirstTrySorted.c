#include <stdlib.h> // Ger mig malloc och free
#include <stdio.h> // Ger mig printf
#include <stdbool.h> // Ger mig bool, true, false
#include <time.h> // Ger mig tidsmätning (timespec, clock_gettime)

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) 
// Tar två tider och returnerar skillnaden i nanosekunder
{
    return (t_stop->tv_nsec - t_start->tv_nsec) + 
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
           // tv_nsec = nanosekunder-delen
           // tv_sec  = sekunder-delen (omvandlas till ns)
}

int *sorted(int n)
{
    int *array = (int*)malloc(n * sizeof(int)); // allokerar minne för arrayen på heapen
    int nxt = 0; // håller senaste värdet

    for (int i = 0; i < n; i++) // loopar igenom hela arrayen
    {
        nxt += rand() % 10 + 1; // ökar med ett positivt steg
        array[i] = nxt; // sparar värdet i arrayen
    }

    return array; // returnerar pekaren till arrayen
}

bool sorted_search(int array[], int length, int key)
{
    for (int index = 0; index < length; index++) // loopar genom arrayen
    {
        if (array[index] == key) // om talet hittas
            return true; // returnera true

        if (array[index] > key) // om värdet blir större än key
            return false; // kan avbryta direkt
    }
    return false; // om talet inte finns
}

int main()
{
    int length = 1000000; // storleken på arrayen
    int *array = sorted(length); // skapa sorterad array

    int key = array[length-1] + 1;

    struct timespec t_start, t_stop; // två tider: före och efter

    clock_gettime(CLOCK_MONOTONIC, &t_start); // starta tidsmätning
    sorted_search(array, length, key); // anropa sökfunktionen
    clock_gettime(CLOCK_MONOTONIC, &t_stop); // stoppa tidsmätning

    long time = nano_seconds(&t_start, &t_stop); // beräkna tiden i nanosekunder
    printf("Time: %ld ns\n", time); // skriv ut resultatet

    free(array); // städar upp minnet
    return 0; // avsluta programmet korrekt
}
