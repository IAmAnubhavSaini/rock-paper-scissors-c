#ifndef ROCKPAPERSCISSORS
#define ROCKPAPERSCISSORS 1

typedef enum player_choices PlayerChoice;
enum player_choices {
    PC_Random = 0x00,
    PC_Rock = 0x01,
    PC_Paper = 0x04,
    PC_Scissors = 0x10
};

int choices[4] = {
    PC_Random,
    PC_Rock,
    PC_Paper,
    PC_Scissors
};

typedef enum gameResults GameResults;
enum gameResults {
    GR_Unknown,
    GR_Tie,
    GR_Player1_Wins,
    GR_Player2_Wins
};

PlayerChoice getPlayerInput(void);
PlayerChoice getComputerInput(void);
// To be fired when PC_Random choice has been choosen by player.
PlayerChoice getDefinitePlayerChoice(void);
void generateResult(PlayerChoice []);
char * choiceToString(PlayerChoice, char *);

#endif
