/* Anubhav Saini
* July, 2013 - 2016
* Game of rock paper scissors in language C
*/

#include <stdio.h>
#include "random_integers.c"
#include "RockPaperScissors.h"
#include <string.h>

void main() {
    char * choiceString;
    PlayerChoice human = getPlayerInput();
    PlayerChoice computer = getComputerInput();
    PlayerChoice choices[2];
    if(human == PC_Random) {
        printf("\nPlayer chose: random,");
        human = getDefinitePlayerChoice();
        printf("\nchoosing %s for player.", choiceToString(human, choiceString));
    }
    else {
        printf("\nYou chose: %s", choiceToString(human, choiceString));
    }

    if(computer == PC_Random) {
        printf("\nComputer chose: random,");
        computer = getDefinitePlayerChoice();
        printf("\nchoosing %s for computer.", choiceToString(computer, choiceString));
    }
    else {
        printf("\nComputer chose: %s", choiceToString(computer, choiceString));
    }

    choices[0] = human;
    choices[1] = computer;
    generateResult(choices);
}

PlayerChoice getPlayerInput(void) {
    PlayerChoice choice;
    int userChoice;

    printf("\nYour choices are: 1.Rock 2.Paper 3.Scissors.\nPlease press appropriate digit: ");
    scanf("%d", &userChoice);
    switch(userChoice) {
    case 1:
        choice = PC_Rock; break;
    case 2:
        choice = PC_Paper; break;
    case 3:
        choice = PC_Scissors; break;
    default:
        choice = PC_Random; break;
    }
    return choice;
}

PlayerChoice getComputerInput(void) {
    int i = generateLimitedRandomNumber(3);
    PlayerChoice choice = choices[i];
    return choice;
}

PlayerChoice getDefinitePlayerChoice(void) {
    int i;
    PlayerChoice choice;
    do {
        i = generateLimitedRandomNumber(3);
    } while(i == 0);
    choice = choices[i];
    return choice;
    /* Amazingly, whole thing can be written as:
     * int i; do { i = generateLimitedRandomNumber(3); } while(i!=0); return choices[i];
     */
}

void generateResult(PlayerChoice choices[]) {
    PlayerChoice result = choices[0] | choices[1];
    char * choiceString;
    /* printf("\nBitwise orred choices- %s | %s = %d",
     * choiceToString(choices[0], choiceString),
     * choiceToString(choices[1], choiceString),
     * (int) result);
     */
    switch(result) {
    case 0x01:
    case 0x04:
    case 0x10:
        printf("\nTied."); break;
    case 0x05:
        printf("\nPaper wins."); break;
    case 0x14:
        printf("\nScissors wins."); break;
    case 0x11:
        printf("\nRock wins."); break;
    }
}

char * choiceToString(PlayerChoice choice, char * choiceString) {
    choiceString = (char *)malloc(sizeof(char) * 9);
    switch(choice) {
    case PC_Random:
        strcpy(choiceString, "Random\0"); break;
    case PC_Rock:
        strcpy(choiceString, "Rock\0"); break;
    case PC_Scissors:
        strcpy(choiceString, "Scissors\0"); break;
    case PC_Paper:
        strcpy(choiceString, "Paper\0"); break;
    }
    return choiceString;
}
