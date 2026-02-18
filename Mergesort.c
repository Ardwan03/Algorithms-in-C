#include <stdlib.h> // malloc, free, rand
#include <stdio.h> // printf
#include <stdbool.h> // bool, true, false
#include <time.h> // timespec, clock_gettime

long nano_seconds(struct timespec *t_start, struct timespec *t_stop)
{
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}

void merge(int *org, int *aux, int lo, int mid, int hi)
{
    for (int k = lo; k <= hi; k++) { // gå igenom orginella arrayen
        aux[k] = org[k]; // kopiera allt till den tillfälliga arrayen
    }

    int i = lo; // sätter i till första talet i arrayen (lo)
    int j = mid + 1; // sätter j till första talet i andra halvan av arrayen

    for (int k = lo; k <= hi; k++) { // Gå igenom hela arrayen
        if (i > mid) { // Om alla element i vänstra halvan redan är använda
            org[k] = aux[j]; // Ta nästa element från högra halvan och sätt till org[k]
            j++; // Gå vidare
        }
        else if (j > hi) { // Om j är större än sista talet
            org[k] = aux[i];
            i++;
        }

        else if (aux[i] <= aux[j]) {
            org[k] = aux[i];
            i++;
        }
        
        else {
            org[k] = aux[j];
            j++;
        }
    }
}

void sort(int *org, int *aux, int lo, int hi)
{
    if (lo != hi) {
        int mid = (lo + hi) / 2;

        sort(org, aux, lo, mid); // Sortera vänster halva

        sort(org, aux, mid + 1, hi); // Sortera höger halva

        merge(org, aux, lo, mid, hi); // Slå ihop delarna
    }
}

//Skapa en temporär array
void sort_top(int *org, int n) // sortera en array med längden n
{
    if (n == 0)
        return; // sluta när arrayen är tom

    int *aux = (int*)malloc(n * sizeof(int)); //Allokera minnen för den temporära arrayen
    sort(org, aux, 0, n - 1);
    free(aux); //frigör minnet.
}

// Skapa en array som jag kan anropa senare
int *mergesort(int n) // Skapar allt, skapar arrayen, fyller den med tal och sorterar.
{
    int *array = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        array[i] = rand();

    sort_top(array, n);
    return array;
}

int main()
{
    struct timespec t_start, t_stop;

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    int *array = mergesort(32000);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    long time = nano_seconds(&t_start, &t_stop);
    printf("Time: %ld ns\n", time);

    free(array);
}
