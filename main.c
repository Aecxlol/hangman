#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "./libs/main.h"

int main(int argc, char** argv)
{

    int choice = 0, lives = 10, nbWords = 0, count = 0, randomWordIndex = 0, i = 0, wordSize = 0;
    const char* relativeFilePath = "dictionary/dictionary.txt";
    char randomWord[WORD_MAX_SIZE] = "", stringC[WORD_MAX_SIZE] = "", userLetter = 0;
    char* test = NULL;
    int* hiddenWord = NULL;

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

        fclose(file);

        wordSize = strlen(randomWord);
        hiddenWord = malloc(wordSize * sizeof(int));

        if(hiddenWord == NULL){
            exit(0);
        }

        for(i = 0; i < wordSize; i++){
            hiddenWord[i] = 0;
        }

        printf("*Le dictionaire a bien ete charge !*\n\n");
        printf("--MENU--\n");
        printf("1 - Jouer\n");
        printf("2 - Quitter\n");
        printf("Votre choix ? ");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nBievenue dans le jeu du Pendu !\n\n");
                while(lives > 0){
                    printf("\nIl vous reste %d vies\n", lives);
                    printf("Quel est le mot secret ? ");
                    for(i = 0; i < wordSize - 1; i++){
                        if(randomWord[i] == toupper(userLetter)){
                            printf("%c", toupper(userLetter));
                        }else {
                            printf("*");
                        }
                    }
                    printf("\nProposez une lettre : ");

                    scanf("%s", &userLetter);

                    if(strchr(randomWord, toupper(userLetter)) == NULL){
                        lives--;
                        printf("\n->La lettre %c ne se trouve pas dans le mot a trouver. Vous perdez une vie.\n", userLetter);
                    }
                }
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
