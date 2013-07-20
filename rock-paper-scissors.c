/* Anubhav Saini
* July, 2013
* Game of rock paper scissors in language C
*/

#include<stdio.h>

typedef struct game_elements GameElements;
struct game_elements{
  GE_Unknown = 0x00,
    GE_Rock = 0x01,
    GE_Paper = 0x04,
    GE_Scissors = 0x10
};
typedef struct game_results GameResults;
struct game_results{
  GR_Unknown,
    GR_Tie,
    GR_Player1_Wins,
    GR_Player2_Wins,
};
void main(){

}