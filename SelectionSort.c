#include <stdlib.h> // Ger mig malloc, free, rand
#include <stdio.h> // Ger mig printf
#include <stdbool.h> // Ger mig bool, true, false
#include <time.h> // Ger mig timespec och clock_gettime

long nano_seconds(struct timespec *t_start, struct timespec *t_stop)
// Tar två tider och returnerar skillnaden i nanosekunder
{
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
           // tv_nsec = nanosekunder-delen
           // tv_sec  = sekunder-delen (omvandlas till ns)
}

// Skapa en array som jag kan anropa senare
int *selectionsort(int n)
{
    int *array = malloc(n * sizeof(int)); // Skapa minne på heapen
    for (int i = 0; i < n; i++) // Gå igenom hela arrayen
        array[i] = rand(); // Lägg random tal i varje index

    for (int i = 0; i < n - 1; i++) { // gå igenom arrayen men skiti sista varvet.
        int candidate = i; // sätt talet i platsen candidate.

        for (int j = i; j < n; j++) { // Gå igenom hela arrayen
            if (array[j] < array[candidate]) { // if satsen som avgör
                candidate = j; // ett mindre tal har hittats
            }
        }

        int tillfällig = array[i];
        array[i] = array[candidate];
        array[candidate] = tillfällig;
    }

    return array;
}


int main()
{
    struct timespec t_start, t_stop; // tider före och efter

    clock_gettime(CLOCK_MONOTONIC, &t_start); // starta tidsmätning
    int *array = selectionsort(32000); // Anropa metoden
    clock_gettime(CLOCK_MONOTONIC, &t_stop); // stoppa tidsmätning

    long time = nano_seconds(&t_start, &t_stop); // beräkna tiden
    printf("Time: %ld ns\n", time); // skriv ut resultatet
    
    free(array); // frigör heapen
}
