#include"struct.h"
#include"constant.h"
#include"ENV.h"
#include<time.h> 
#include<stdio.h> 
#include<stdlib.h> 

#ifndef AI_H
#define AI_H

#define MIN(X,Y) (X)>(Y)?(Y):(X)
#define MAX(X,Y) (X)>(Y)?(X):(Y)

typedef struct _SimpleMove{
    int start_pt;
    int end_pt;
}SimpleMove;

int ai_play(GameState *gameState,Player *player, int model);
void env_reset();

extern int pos_scores_pawn[2][64];
extern int pos_scores_knights[2][64];
extern int pos_scores_bishops[2][64];
extern int pos_scores_rooks[2][64];
extern int pos_scores_queens[2][64];
extern int pos_scores_kings_mid[2][64];
extern int pos_scores_kings_end[2][64];

extern int piece_scores[6];

int ai_sum_scores(GameState *gameState, Player *player);

int ai_model1_play(GameState *gameState, Player *player);

int ai_easy_play(GameState *gameState, Player *player);

#endif
