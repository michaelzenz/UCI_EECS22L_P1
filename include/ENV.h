#include"constant.h"
#include"stack.h"
#include"struct.h"

#ifndef GAMEENV_H
#define GAMEENV_H

extern int playerTurn;


GameState env_init();
void env_play(GameState gameState, Player player);
vector env_get_legal_moves(GameState gameState, Player player, int start_pt);
vector env_get_legal_pawn(GameState gameState, int start_pt);
int env_check_end_game(GameState gameState);
uchar env_is_threatened(GameState,Player);
#endif

