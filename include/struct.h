#include"vector.h"
#ifndef STRUCT_H
#define STRUCT_H

typedef struct _Player
{
    int id;
    int color;
    int identity;
    int difficulty;
} Player;

typedef struct _Castling
{
    unsigned char Left;
    unsigned char Right;
} Castling;

typedef struct _LegalMovesContainer
{
    int pos;
    vector legal_moves;
}LegalMovesContainer;

typedef struct _Move{
    int piece;
    int start_pt;
    int end_pt;
    int captured;
    int captured_pos;
    int special_move;
} Move;

typedef struct _GameState
{
    int playerTurn;
    Castling castling_arr[2];
    int board[8*8];
    LegalMovesContainer container[16];
    int moves_vector_cnt;
} GameState;

typedef unsigned char uchar;

#endif