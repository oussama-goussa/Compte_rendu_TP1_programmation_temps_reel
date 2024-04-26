#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Pour utiliser la fonction sleep

#define NUM_TASKS 5

// Structure pour représenter une tâche périodique
typedef struct {
    int id;     // Identifiant de la tâche
    int period; // Période d'exécution de la tâche
} PeriodicTask;

// Fonction exécutée par chaque tâche périodique
void *taskFunction(void *arg) {
    // Conversion de l'argument en pointeur vers une structure PeriodicTask
    PeriodicTask *task = (PeriodicTask *) arg;

    int ancien_etat;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &ancien_etat); // Activation de l'annulation

    while (1) {
        // Attente de la période spécifiée avant la prochaine exécution
        sleep(task->period);

        // Affichage d'un message indiquant que la tâche est exécutée
        printf("Tâche %d exécutée\n", task->id);

        // Vérification de la demande d'annulation
        pthread_testcancel();
    }
    return NULL;
}

int main() {
	int i;

    // Définition des tâches périodiques dans un tableau
    PeriodicTask tasks[] = {
        {1, 1},
        {2, 9},
        {3, 3},
        {4, 7},
        {5, 5}
    };

    // Création d'un thread pour chaque tâche
    pthread_t threads[NUM_TASKS];

    for (i = 0; i < NUM_TASKS; i++) {
        pthread_create(&threads[i], NULL, taskFunction, &tasks[i]);
    }

    // Attente 10 secondes avant d'annuler les threads
    sleep(10);

    // Annulation des threads après 10 secondes
    for (i = 0; i < NUM_TASKS; i++) {
         pthread_cancel(threads[i]);
         pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}

