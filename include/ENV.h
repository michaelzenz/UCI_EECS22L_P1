#include"constant.h"
#include"stack.h"
#include"struct.h"
#include"string.h"

#ifndef GAMEENV_H
#define GAMEENV_H

#define EASY 1
#define MEDIUM 2
#define ADVANCED 3


//initialize the GameState
GameState env_init();

//free up the memory of the container
void env_free_container(GameState *gameState);

//the function to play chess on the board
void env_play(GameState *gameState, Player *player, int start_pt, int end_pt);

//check if is checkmate or king get captured
uchar env_check_end(GameState *gameState, Player *player);

//deep copy the current GameState
GameState env_copy_State(GameState *gameState);

//get all legal moves for different pieces, returns a vector
vector env_get_legal_moves(GameState *gameState, Player *player, int start_pt);
vector env_get_legal_pawn(GameState *gameState, int start_pt);
vector env_get_legal_knight(GameState *gameState, int start_pt);
vector env_get_legal_castle(GameState *gameState, int start_pt);
vector env_get_legal_bishop(GameState *gameState, int start_pt);
vector env_get_legal_queen(GameState *gameState, int start_pt);

//check_castling==1 if is checking castling availability
vector env_get_legal_king(GameState *gameState, Player *player, int start_pt, uchar check_castling);

//undo the last move
void env_undo(GameState *gameState);
#endif

