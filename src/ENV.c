
#include"ENV.h"


GameState env_init()
{
    GameState gameState;
    gameState.playerTurn=WHITE;
    gameState.castling_arr[PLAYER1].Left=gameState.castling_arr[PLAYER1].Right=0;
    gameState.castling_arr[PLAYER2].Left=gameState.castling_arr[PLAYER2].Right=0;
    gameState.moves_vector_cnt=0;
    return gameState;
}

void env_play(GameState *gameState, Player *player, int start_pt, int end_pt)
{
    if(gameState->playerTurn!=player->id) return;
    int s_piece=gameState->board[start_pt];
    int e_piece=0;
    if(gameState->board[end_pt]!=0) e_piece=gameState->board[end_pt];
    gameState->board[start_pt]=0;
    gameState->board[end_pt]=s_piece;
    
}


uchar env_check_end(GameState *gameState, Player *player)
{
    int K=-1;
    vector legal_moves;
    int pos=-1;
    uchar threatened=1;
    uchar end=1;
    GameState check_state;
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            pos=y*8+x;
            if(gameState->board[pos]*gameState->playerTurn>0)
            {
                legal_moves=env_get_legal_moves(gameState,player,pos);
                gameState->container[gameState->moves_vector_cnt].pos=pos;
                gameState->container[gameState->moves_vector_cnt].legal_moves=legal_moves;
                gameState->moves_vector_cnt++;
                for(int i=0;i<legal_moves.count;i++)
                {
                    
                    check_state=env_copy_State(gameState);
                    env_play(&check_state,player,pos,vector_get(&legal_moves,i));
                    threatened=env_is_threatened(&check_state,player);
                    if(threatened==0)end=0;
                }
            }
        }
    }
    return end;
}

GameState env_copy_State(GameState *gameState)
{
    GameState newState;
    memcpy(newState.board,gameState->board,64*sizeof(int));
    newState.playerTurn=gameState->playerTurn;
    newState.castling_arr[0]=gameState->castling_arr[0];
    newState.castling_arr[1]=gameState->castling_arr[1];
    return newState;
}

uchar env_is_threatened(GameState *gameState,Player *player)
{
    int pos=-1;
    vector legal_moves;
    uchar threatened_area[8*8];
    memset(threatened_area,0,sizeof(uchar)*8*8);
    int K=-1;
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            pos=y*8+x;
            if(gameState->board[pos]*gameState->playerTurn*-1==KING) K=pos;
            else if(gameState->board[pos]*gameState->playerTurn>0)
            {
                legal_moves=env_get_legal_moves(gameState,player,pos);
                for(int i=0;i<legal_moves.count;i++)
                {
                    threatened_area[vector_get(&legal_moves,pos)]=1;
                }
            }
        }
    }
    if(threatened_area[K]==1)return 1;
    else return 0;
}

vector env_get_legal_moves(GameState *gameState, Player *player, int start_pt)
{
    vector legal_moves;
    switch(abs(gameState->board[start_pt]))
    {
        case PAWN:
            env_get_legal_pawn(gameState,start_pt);
            break;
    }

}

vector env_get_legal_pawn(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);

    int x=start_pt%8, y=start_pt/8;
    if(x-1>=0 && gameState->board[y*8+x-1]<0)vector_add(&legal_moves,y*8+x-1);
    else if(x+1<8 && gameState->board[y*8+x+1]<0)vector_add(&legal_moves,y*8+x+1);

    for(int i=0;i<2;i++)
    {
        y+=gameState->playerTurn*-1*1;//if playerTurn=1, then goes up, but for image, it should go up, which means y should decrease
        if(gameState->board[y*8+x]!=0)vector_add(&legal_moves,y*8+x);
    }
    return legal_moves;
}
