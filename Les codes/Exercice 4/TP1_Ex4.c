#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Premi�re fonction � ex�cuter dans le premier thread
void *thread_func1(void *arg) {
    // Affichage du message du premier thread
    printf("Thread 1: Bonjour !\n");
    
    // Le thread se termine, retourne NULL
    return NULL;
}

// Deuxi�me fonction � ex�cuter dans le deuxi�me thread
void *thread_func2(void *arg) {
    // Affichage du message du deuxi�me thread
    printf("Thread 2: Salut !\n");
    
    // Le thread se termine, retourne NULL
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // D�claration des identifiants de thread
    
    // Cr�ation des deux threads en leur passant les fonctions correspondantes
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Attente de la fin de l'ex�cution des deux threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}

