#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Fonction pour afficher un message � l'�cran
void *print_message(void *arg) {
    // Cast de l'argument vers une cha�ne de caract�res
    char *message;
    message = (char *)arg;
    
    // Affichage du message
    printf("%s \n", message);
    
    // Le thread se termine, retourne NULL
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread; // D�claration d'un identifiant de thread
    
    const char *message = "Bonjour, OUSSAMA"; // Message � afficher
    
    // Cr�ation du thread en lui passant la fonction print_message et le message comme argument
    pthread_create(&thread, NULL, print_message, (void *)message);
    
    // Attendre la fin de l'ex�cution du thread
    pthread_join(thread, NULL);
    
    return EXIT_SUCCESS;
}
