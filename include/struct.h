#ifndef STRUCT_H
#define STRUCT_H
#include"vector.h"
#include"constant.h"
#include<assert.h>

typedef struct _Player
{
    int id;
    int color;
    int identity;
    int difficulty;
} Player;

//the struct to record whether different direction of castling is legal
//left for left castling, right for right
typedef struct _Castling
{
    unsigned char Left;
    unsigned char Right;
} Castling;

//the container that contains all legal moves from pos
//pos is the location of the piece, legal_moves contains all legal destination
typedef struct _LegalMovesContainer
{
    int pos;
    vector legal_moves;
}LegalMovesContainer;

typedef struct _Node
{
    char log[STR_NODE_SIZE];
    struct _Node *next;
}Node;

//the struct containing all info for a move
typedef struct _Move{
    int piece;//the piece that are moved
    int start_pt;//the starting location
    int end_pt;//the destination
    int captured;//the captured piece
    int captured_pos;//where is the piece captured 
    int special_move;//if this move is a special move
    //the previous castling state, 1 is right illegal
    //2 is left illegal, 3 is both illegal
    int pre_castling_state;

} Move;

//contains all infomation that is necessary to recover a game
typedef struct _GameState
{
    int playerTurn;//the current player turn
    Castling castling_arr[2];//the castling state for the game
    int board[8*8];//the board
    LegalMovesContainer container[16];//the container that contains all legal moves
    int moves_vector_cnt;//how much container is in the container arr above
    Node *moves_stack;//the stack to record moves
} GameState;

typedef unsigned char uchar;

#endif