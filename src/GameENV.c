#include"GameENV.h"

int playerTurn=1;



GameState env_init()
{
    GameState gameState;
    gameState.playerTurn=WHITE;
    gameState.scores=0;
    gameState.castling_arr[PLAYER1].Left=gameState.castling_arr[PLAYER1].Right=0;
    gameState.castling_arr[PLAYER2].Left=gameState.castling_arr[PLAYER2].Right=0;
    return gameState;
}

void env_play(GameState gameState, Player player)
{
    if(gameState.playerTurn!=player.id) return;

}

vector env_get_legal_moves(GameState gameState, Player player, int start_pt)
{
    vector legal_moves;
    switch(abs(gameState.board[start_pt]))
    {
        case PAWN:
            env_get_legal_pawn(gameState,start_pt);
            break;
    }

}

vector env_get_legal_pawn(GameState gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);

    int x=start_pt%8, y=start_pt/8;
    if(x-1>=0 && gameState.board[y*8+x-1]<0)vector_add(&legal_moves,y*8+x-1);
    else if(x+1<8 && gameState.board[y*8+x+1]<0)vector_add(&legal_moves,y*8+x+1);

    for(int i=0;i<2;i++)
    {
        y+=gameState.playerTurn*-1*1;//if playerTurn=1, then goes up, but for image, it should go up, which means y should decrease
        if(gameState.board[y*8+x]!=0)vector_add(&legal_moves,y*8+x);
    }
    return legal_moves;
}
