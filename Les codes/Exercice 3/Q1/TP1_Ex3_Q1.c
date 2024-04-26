#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction ex�cut�e par le premier thread
void *Tache1(void *arg) {
    int i = 0;
    while (i < 5) { // R�p�ter 5 fois
        printf("Execution de Tache1\n"); // Afficher un message
        sleep(1); // Attendre 1 seconde
        i++;
    }
    return NULL;
}

// Fonction ex�cut�e par le deuxi�me thread
void *Tache2(void *arg) {
    int j = 0;
    while (j < 3) { // R�p�ter 3 fois
        printf("Execution de Tache2\n"); // Afficher un message
        sleep(1); // Attendre 1 seconde
        j++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // D�claration des identifiants de thread
    
    // Cr�ation des deux threads pour les t�ches Tache1 et Tache2
    pthread_create(&thread1, NULL, Tache1, NULL);
    pthread_create(&thread2, NULL, Tache2, NULL);
    
    // Attente de la fin de l'ex�cution des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return EXIT_SUCCESS;
}

