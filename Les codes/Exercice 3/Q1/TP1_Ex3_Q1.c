#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction exécutée par le premier thread
void *Tache1(void *arg) {
    int i = 0;
    while (i < 5) { // Répéter 5 fois
        printf("Execution de Tache1\n"); // Afficher un message
        sleep(1); // Attendre 1 seconde
        i++;
    }
    return NULL;
}

// Fonction exécutée par le deuxième thread
void *Tache2(void *arg) {
    int j = 0;
    while (j < 3) { // Répéter 3 fois
        printf("Execution de Tache2\n"); // Afficher un message
        sleep(1); // Attendre 1 seconde
        j++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration des identifiants de thread
    
    // Création des deux threads pour les tâches Tache1 et Tache2
    pthread_create(&thread1, NULL, Tache1, NULL);
    pthread_create(&thread2, NULL, Tache2, NULL);
    
    // Attente de la fin de l'exécution des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return EXIT_SUCCESS;
}

