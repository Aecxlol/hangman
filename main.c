#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "./libs/main.h"

int main(int argc, char** argv)
{

    int choice = 0, lives = 10, nbWords = 0, count = 0, randomWordIndex = 0, i = 0, wordSize = 0, turn = 0, lettersToFind = 0, isGameOver = 0;
    const char* relativeFilePath = "dictionary/dictionary.txt";
    char randomWord[WORD_MAX_SIZE] = "", stringC[WORD_MAX_SIZE] = "", charactersHistory[30] = "", userLetter = 0;
    char* hiddenWord = NULL;

    FILE* file = NULL;

    file = fopen(relativeFilePath, "r");

    printf("=======================\n");
    printf("=====JEU DU PENDU======\n");
    printf("=======================\n");
    printf("\n*Chargement du dictionnaire...*\n");

    if(file == NULL){
        exit(0);
    }

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
    lettersToFind = wordSize - 2;
    hiddenWord = malloc(wordSize * sizeof(char));

    if(hiddenWord == NULL){
        exit(0);
    }

    for(i = 0; i < wordSize; i++){
        hiddenWord[i] = '*';
    }

    printf("*Le dictionaire a bien ete charge !*\n\n");
    printf("--MENU--\n");
    printf("1 - Jouer\n");
    printf("2 - Quitter\n");
    printf("Votre choix ? ");

    scanf("%d", &choice);

    switch(choice) {
        case 1:

            printf("\nBievenue dans le jeu du Pendu !\n");

            while(lives > 0){

                if(lettersToFind == 0){
                    printf("\n***Felicitations vous avez gagne ! Le mot a trouver ete : %s\n", randomWord);
                    exit(0);
                }

                if(turn > 0){
                    printf("\nVotre historique de coups : %s\n", charactersHistory);
                }

                printf("\nIl vous reste %d vies\n", lives);
                printf("Quel est le mot secret ? ");

                for(i = 0; i < wordSize - 1; i++){
                    if(randomWord[i] == toupper(userLetter)){
                        hiddenWord[i] = toupper(userLetter);
                        lettersToFind--;
                    }
                    printf("%c", hiddenWord[i]);
                }

                printf("\nProposez une lettre : ");

                scanf("%s", &userLetter);

                charactersHistory[turn] = toupper(userLetter);
                turn++;

                if(strchr(randomWord, toupper(userLetter)) == NULL){
                    lives--;
                    printf("\n-> La lettre %c ne se trouve pas dans le mot a trouver. Vous perdez une vie.\n", userLetter);
                }
            }

            printf("\nVous avez perdu :( le mot a trouver ete : %s", randomWord);
            break;

        case 2:
            exit(0);
            break;

        default:
            printf("\nChoix invalide.\n\n");
            break;
    }

    return 0;
}
