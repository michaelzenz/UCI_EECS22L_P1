#include"struct.h"
#include"constant.h"
#include"ENV.h"
#include<time.h> 
#include<stdio.h> 
#include<stdlib.h> 

#ifndef AI_H
#define AI_H

#define MIN(X,Y) ((X)>(Y)?(Y):(X))
#define MAX(X,Y) ((X)>(Y)?(X):(Y))

void ai_print_board(GameState *gameState);//for printing log

//scores for different pieces at different position
extern int pos_scores_pawn[2][64];
extern int pos_scores_knights[2][64];
extern int pos_scores_bishops[2][64];
extern int pos_scores_rooks[2][64];
extern int pos_scores_queens[2][64];
extern int pos_scores_kings_mid[2][64];
extern int pos_scores_kings_end[2][64];

//scores of different pieces
extern int piece_scores[7];

//the global function for ai to select model and play
int ai_play(GameState *gameState,Player *player, int model);

//sum up the scores including pieces and location scores
int ai_sum_scores(GameState *gameState, Player *player);

//different model of AI to play
int ai_model1_play(GameState *gameState, Player *player);
int ai_model2_play(GameState *gameState, Player *player);

//Marshall`s experiment AI
int ai_easy_play(GameState *gameState, Player *player);

#endif