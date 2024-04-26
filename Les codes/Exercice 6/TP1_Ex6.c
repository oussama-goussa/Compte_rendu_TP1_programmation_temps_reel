#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10   // Taille du tableau
#define NUM_THREADS 4    // Nombre de threads

int totalSum = 0;       // Variable pour stocker la somme totale

// Structure pour contenir les informations n�cessaires pour effectuer le calcul partiel
typedef struct {
    int *start;         // Pointeur vers le d�but du sous-tableau
    int *end;           // Pointeur vers la fin du sous-tableau
    pthread_mutex_t *lock; // Verrou pour synchroniser l'acc�s � la variable partag�e
} PartialSum;

// Fonction ex�cut�e par chaque thread pour calculer la somme partielle
void *sum_partial(void *args) {
    PartialSum *partial = (PartialSum *)args; // Conversion de l'argument en pointeur de type PartialSum

    int partialSum = 0; // Variable pour stocker la somme partielle

    // Parcours du sous-tableau et calcul de la somme partielle
    int *p;
    for (p = partial->start; p < partial->end; p++) {
        partialSum += *p;
    }

    // Verrouillage pour synchroniser l'acc�s � la variable partag�e
    pthread_mutex_lock(partial->lock);

    // Mise � jour de la somme totale avec la somme partielle calcul�e par ce thread
    totalSum += partialSum;

    // D�verrouillage du verrou
    pthread_mutex_unlock(partial->lock);

    // Fin du thread
    pthread_exit(NULL);
}

int main() {
    int array[ARRAY_SIZE];  // D�claration du tableau
    int i;

    // Initialisation du tableau avec des valeurs de votre choix
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    pthread_mutex_t lock;   // D�claration du verrou
    pthread_mutex_init(&lock, NULL);    // Initialisation du verrou

    pthread_t threads[NUM_THREADS]; // D�claration des identifiants de threads
    PartialSum thread[NUM_THREADS]; // D�claration des structures PartialSum pour chaque thread

    int taille = ARRAY_SIZE / NUM_THREADS; // Calcul de la taille de chaque sous-tableau

    // Cr�ation des threads et division du travail entre eux
    for (i = 0; i < NUM_THREADS; ++i) {
        // Remplissage des informations de la structure PartialSum pour le thread actuel
        thread[i].start = (array + i * taille); // Pointeur vers le d�but du sous-tableau
        thread[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * taille)); // Pointeur vers la fin du sous-tableau
        thread[i].lock = &lock; // Passage du verrou

        // Cr�ation du thread et appel de la fonction sum_partial avec les informations de la structure actuelle
        pthread_create(&threads[i], NULL, sum_partial, (void *)&thread[i]);
    }

    // Attente de la fin de l'ex�cution de tous les threads
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage de la somme totale
    printf("Somme totale : %d\n", totalSum);

    // Destruction du verrou
    pthread_mutex_destroy(&lock);

    return 0; // Fin du programme
}

