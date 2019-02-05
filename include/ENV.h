#include"constant.h"
#include"stack.h"
#include"struct.h"
#include"string.h"

#ifndef GAMEENV_H
#define GAMEENV_H

extern int playerTurn;


GameState env_init();
void env_free_container(GameState *gameState);
void env_play(GameState *gameState, Player *player, int start_pt, int end_pt);
uchar env_check_end(GameState *gameState, Player *player);
GameState env_copy_State(GameState *gameState);
vector env_get_legal_moves(GameState *gameState, Player *player, int start_pt);
vector env_get_legal_pawn(GameState *gameState, int start_pt);
vector env_get_legal_knight(GameState *gameState, int start_pt);
vector env_get_legal_castle(GameState *gameState, int start_pt);
vector env_get_legal_bishop(GameState *gameState, int start_pt);
vector env_get_legal_queen(GameState *gameState, int start_pt);
vector env_get_legal_king(GameState *gameState, int start_pt);
void env_undo(GameState *gameState);
#endif

