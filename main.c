#include <stdio.h>
#include <stdlib.h>
#include "./libs/main.h"

int main()
{

    int choice = 0, lives = 10, nbWords = 0, count = 0, randomWordIndex = 0;
    const char* relativeFilePath = "dictionary/dictionary.txt";
    char randomWord[WORD_MAX_SIZE] = "", stringC[WORD_MAX_SIZE] = "";
    FILE* file = NULL;

    file = fopen(relativeFilePath, "r");

    printf("=======================\n");
    printf("=====JEU DU PENDU======\n");
    printf("=======================\n");
    printf("\n*Chargement du dictionnaire...*\n");

    if(file != NULL){

        while(fgets(stringC, WORD_MAX_SIZE, file)!= NULL){
            nbWords++;
        }

        srand(time(NULL));
        randomWordIndex = rand() % nbWords;

        rewind(file);

        while(fgets(stringC, WORD_MAX_SIZE, file)!= NULL){
            count++;
            if(count == randomWordIndex){
                fgets(randomWord, WORD_MAX_SIZE, file);
            }
        }

        printf("RANDOM WORD : %s\n", randomWord);

        fclose(file);

        printf("*Le dictionaire a bien ete charge !*\n\n");
        printf("--MENU--\n");
        printf("1 - Jouer\n");
        printf("2 - Quitter\n");
        printf("Votre choix ? ");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nBievenue dans le jeu du Pendu !\n\n");
                printf("Il vous reste %d vies\n", lives);
                printf("Quel est le mot secret ? %s \n", randomWord);
                printf("Proposez une lettre : ");
                break;

            case 2:
                exit(0);
                break;

            default:
                printf("Choix invalide.");
                break;
        }
    }else {
        printf("*Une erreur a ete rencontree durant le chargement du fichier. Arret du programme...*");
        exit(0);
    }

    return 0;
}
