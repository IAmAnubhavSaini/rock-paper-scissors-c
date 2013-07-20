/* Anubhav Saini
* July, 2013
* Game of rock paper scissors in language C
*/

#include<stdio.h>
#include "random_integers.c"
#include<string.h>

typedef enum player_choices PlayerChoice;
enum player_choices{
  PC_Random = 0x00,
  PC_Rock = 0x01,
  PC_Paper = 0x04,
  PC_Scissors = 0x10
};
int Choices[4]  = {PC_Random, PC_Rock, PC_Paper, PC_Scissors};
typedef enum game_results GameResults;
enum game_results{
  GR_Unknown,
  GR_Tie,
  GR_Player1_Wins,
  GR_Player2_Wins,
};
PlayerChoice get_player_input(void);
PlayerChoice get_computer_input(void);
PlayerChoice get_definite_player_choice(void);//to be fired when PC_Random choice has been choosen by player.
void generate_result(PlayerChoice []);
char *choice_to_string(PlayerChoice, char *);
void main(){
  char *choice_str;
  PlayerChoice human = get_player_input();
  PlayerChoice computer = get_computer_input();
  PlayerChoice choices[2];
  if(human == PC_Random){
    printf("\nPlayer chose: random,");
    human = get_definite_player_choice();
    printf("\nchoosing %s for player.", choice_to_string(human,choice_str));
  }
  else{
    printf("\nYou chose: %s", choice_to_string(human, choice_str));
  }
  if(computer == PC_Random){
    printf("\nComputer chose: random,");
    computer = get_definite_player_choice();
    printf("\nchoosing %s for computer.", choice_to_string(computer,choice_str));
  }
  else{
    printf("\nComputer chose: %s", choice_to_string(computer, choice_str));
  }

  choices[0] = human, choices[1] = computer;
  generate_result(choices);
}
PlayerChoice get_player_input(void){
  PlayerChoice choice;
  int userChoice;

  printf("\nYour choices are: 1.Rock 2.Paper 3.Scissors.\nPlease press appropriate digit: ");
  scanf("%d", &userChoice);
  switch(userChoice){
  case 1: choice = PC_Rock; break;
  case 2: choice = PC_Paper; break;
  case 3: choice = PC_Scissors; break;
  default: choice = PC_Random; break;
  }


  return choice;
}
PlayerChoice get_computer_input(void){
  int i = generate_limited_random_number(3);
  PlayerChoice choice = Choices[i];
  return choice;
}
PlayerChoice get_definite_player_choice(void){
  int i;
  PlayerChoice choice;
  do{
    i = generate_limited_random_number(3);
  }while(i==0);
  choice = Choices[i];
  return choice;
  /*Amazingly, whole thing can be written as:
  * int i; do{i = generate_limited_random_number(3);}while(i!=0); return Choices[i];
  */
}
void generate_result(PlayerChoice choices[]){
  PlayerChoice result = choices[0] | choices[1];
  char *choice_str;
  //printf("\nBitwise orred choices- %s | %s = %d", choice_to_string(choices[0], choice_str), choice_to_string(choices[1], choice_str), (int) result);
  switch(result){
  case 0x01: case 0x04: case 0x10:
    printf("\nTied."); break;
  case 0x05:
    printf("\nPaper wins."); break;
  case 0x14:
    printf("\nScissors wins.");break;
  case 0x11:
    printf("\nRock wins.");break;
  }
}
char *choice_to_string(PlayerChoice choice, char *choice_str){
  choice_str = (char *)malloc(sizeof(char)*9);
  switch(choice){
  case PC_Random: strcpy(choice_str, "Random\0"); break;
  case PC_Rock: strcpy(choice_str, "Rock\0"); break;
  case PC_Scissors: strcpy(choice_str, "Scissors\0"); break;
  case PC_Paper: strcpy(choice_str, "Paper\0"); break;
  }
  return choice_str;
}