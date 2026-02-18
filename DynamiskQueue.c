#include <stdlib.h> // Ger mig malloc och free
#include <stdio.h> // Ger mig printf
#include <stdbool.h> // Ger mig bool, true, false

typedef struct { // Definiera variabler
    int *array; // arrayen
    int antalElement; // antal element i kön.
    int arrayKapacitet; // arrayens storlek n, hur många element jag kan lagra.
    int first; // index i (första elementet).
    int last; // index k (första lediga platsen).
} queue;

queue *create_queue(int n) { // Funktion som skapar en ny kö med given startkapacitet (n).

    queue *kö = malloc(sizeof(queue));  // Allokera minne för kön.
    kö->array = malloc(sizeof(int) * n); // Allokera minne för arrayen som ska lagra elementen.

    kö->arrayKapacitet = n; // Spara hur många element arrayen maximalt kan lagra (n).
    kö->antalElement = 0; // Sätt antal element i kön till 0 (kön är tom).
    kö->first = 0; // Index för första elementet (first) startar på 0.
    kö->last = 0; // Index för nästa lediga plats (last) startar också på 0.

    return kö; // Returnera pekaren till den skapade kön.
}

void free_queue(queue *kö) { // Funktion som frigör allt minne kopplat till kön.
    free(kö->array); // Frigör först arrayen som innehåller elementen.
    free(kö); // Frigör sedan kön.
}

void expandera_queue(queue *kö) { // Funktion som gör arrayen större när kön är full.

    int nyKapacitet = kö->arrayKapacitet * 2; // Ny kapacitet får bli dubbel i storlek.
    int *nyArray = malloc(sizeof(int) * nyKapacitet); // Allokera ny array med större plats.

    if (nyArray == NULL) { // Kontrollera att malloc lyckades.
        printf("Kunde inte allokera ny array\n"); // Skriv felmeddelande.
        exit(1); // Avsluta programmet vid minnesfel.
    }

    for (int i = 0; i < kö->antalElement; i++) // Loopar över alla element som finns i kön.
        nyArray[i] = kö->array[(kö->first + i) % kö->arrayKapacitet]; // Kopiera i korrekt FIFO-ordning (wrap-aware).

    free(kö->array); // Frigör den gamla arrayen eftersom vi inte behöver den längre.
    kö->array = nyArray; // Byt så kön pekar på den nya arrayen.
    kö->arrayKapacitet = nyKapacitet; // Uppdatera kapaciteten till den nya storleken.
    kö->first = 0; // Nollställ first eftersom vi kopierade allt till början av nya arrayen.
    kö->last = kö->antalElement; // last ska nu peka på första lediga plats efter sista elementet.
}

void enqueue(queue *kö, int värde) { // Funktion som lägger till ett element sist i kön.

    if (kö->antalElement == kö->arrayKapacitet) { // Kontrollera om kön är full.
        expandera_queue(kö); // Gör arrayen större.
    }

    kö->array[kö->last] = värde; // Placera värdet på indexet för nästa lediga plats (last)
    kö->last = (kö->last + 1) % kö->arrayKapacitet; // Flytta last ett steg framåt med wrap-around via modulo
    kö->antalElement++; // Öka antalet element i kön med 1
}

int dequeue(queue *kö) { // Funktion som tar bort och returnerar första elementet i kön

    if (kö->antalElement == 0) { // Om kön är tom, inga element.
        printf("Kön är tom\n"); // Skriv felmeddelande.
        exit(1); // Avsluta programmet, eftersom det inte finns något att ta bort.
    }

    int värde = kö->array[kö->first]; // Hämta värdet på första positionen i kön (first).
    kö->first = (kö->first + 1) % kö->arrayKapacitet; // Flytta first ett steg framåt med wrap-around via modulo
    kö->antalElement--; // Minska antalet element i kön med 1

    return värde; // Returnera det borttagna värdet
}

int main() {

    queue *kö = create_queue(2); // Skapar en kö med liten kapacitet för att trigga resize.

    enqueue(kö, 10); // Lägg in 10.
    enqueue(kö, 20); // Lägg in 20, kön är full.
    enqueue(kö, 30); // Lägg in 30, ska anropa resize.

    printf("%d\n", dequeue(kö)); // Ska skriva 10.
    printf("%d\n", dequeue(kö)); // Ska skriva 20.
    printf("%d\n", dequeue(kö)); // Ska skriva 30.

    free_queue(kö); // Frigör minne
    return 0; // Avsluta
}






