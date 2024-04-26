#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Première fonction à exécuter dans le premier thread
void *thread_func1(void *arg) {
    // Affichage du message du premier thread
    printf("Thread 1: Bonjour !\n");
    
    // Le thread se termine, retourne NULL
    return NULL;
}

// Deuxième fonction à exécuter dans le deuxième thread
void *thread_func2(void *arg) {
    // Affichage du message du deuxième thread
    printf("Thread 2: Salut !\n");
    
    // Le thread se termine, retourne NULL
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration des identifiants de thread
    
    // Création des deux threads en leur passant les fonctions correspondantes
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Attente de la fin de l'exécution des deux threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}

