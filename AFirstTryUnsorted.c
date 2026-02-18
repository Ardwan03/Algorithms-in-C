#include <stdlib.h> // Ger mig malloc och free
#include <stdio.h> // ger mig printf
#include <stdbool.h> // ger mig bool
#include <time.h> //ger mig tidsmätning

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) // tar två tider och returnerar skillnaden.
{
    return (t_stop->tv_nsec - t_start->tv_nsec) + 
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
           // tv_nsec nanosekunder delen
           // tv_sec sekunder delen
}

bool unsorted_search(int array[], int length, int key) // hämta array, längd, och tal
{
    for (int index = 0; index < length; index++) // loop går igenom hela arrayen
    {
        if (array[index] == key) // om talet hittad
        {
            return true; // returnera true
        }
    }
    return false; // om inte, returnera false
}

int main() {
    int length = 1000000; // Storleken på arrayen
    int *array = malloc(length * sizeof(int)); // Allokerar plats för en miljon element på heapen. Array pekar på första elementet

    for (int i = 0; i < length; i++) // Loop som går igenom arrayen
    {
        array[i] = rand(); // slumpa talen i arrayen
    }

    int key = -1; // gör så att talet finns inte med i arrayen, men sök igenom hela ändå

    struct timespec t_start, t_stop; // två tider, före och efter

    clock_gettime(CLOCK_MONOTONIC, &t_start); // starta tiden
    unsorted_search(array, length, key); // anropa metoden
    clock_gettime(CLOCK_MONOTONIC, &t_stop); // stoppa tiden

    long time = nano_seconds(&t_start, &t_stop); // beräknar skillnaden i nanosekunder
    printf("Time: %ld ns\n", time); // skriv ut resultatet

}
