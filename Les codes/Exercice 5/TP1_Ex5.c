#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Pour utiliser la fonction sleep

#define NUM_TASKS 5

// Structure pour repr�senter une t�che p�riodique
typedef struct {
    int id;     // Identifiant de la t�che
    int period; // P�riode d'ex�cution de la t�che
} PeriodicTask;

// Fonction ex�cut�e par chaque t�che p�riodique
void *taskFunction(void *arg) {
    // Conversion de l'argument en pointeur vers une structure PeriodicTask
    PeriodicTask *task = (PeriodicTask *) arg;

    int ancien_etat;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &ancien_etat); // Activation de l'annulation

    while (1) {
        // Attente de la p�riode sp�cifi�e avant la prochaine ex�cution
        sleep(task->period);

        // Affichage d'un message indiquant que la t�che est ex�cut�e
        printf("T�che %d ex�cut�e\n", task->id);

        // V�rification de la demande d'annulation
        pthread_testcancel();
    }
    return NULL;
}

int main() {
	int i;

    // D�finition des t�ches p�riodiques dans un tableau
    PeriodicTask tasks[] = {
        {1, 1},
        {2, 9},
        {3, 3},
        {4, 7},
        {5, 5}
    };

    // Cr�ation d'un thread pour chaque t�che
    pthread_t threads[NUM_TASKS];

    for (i = 0; i < NUM_TASKS; i++) {
        pthread_create(&threads[i], NULL, taskFunction, &tasks[i]);
    }

    // Attente 10 secondes avant d'annuler les threads
    sleep(10);

    // Annulation des threads apr�s 10 secondes
    for (i = 0; i < NUM_TASKS; i++) {
         pthread_cancel(threads[i]);
         pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}

