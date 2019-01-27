#include"vector.h"
#ifndef STRUCT_H
#define STRUCT_H

typedef struct Player
{
    int id;
    int color;
    int identity;
    int difficulty;
} Player;

typedef struct Castling
{
    unsigned char Left;
    unsigned char Right;
} Castling;

typedef struct GameState
{
    int playerTurn;
    Castling castling_arr[2];
    int board[8*8];
} GameState;

typedef unsigned char uchar;

#endif