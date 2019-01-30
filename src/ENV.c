
#include"ENV.h"
#define MIN(X,Y) (X)>(Y)?(Y):(X)
#define MAX(X,Y) (X)>(Y)?(X):(Y)

int initial_board[64]={CASTLE_B,KNIGHT_B,BISHOP_B,QUEEN_B,KING_B,BISHOP_B,KNIGHT_B,CASTLE_B,
                        PAWN_B,PAWN_B,PAWN_B,PAWN_B,PAWN_B,PAWN_B,PAWN_B,PAWN_B,
                        BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
                        BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
                        BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
                        BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
                        PAWN_W,PAWN_W,PAWN_W,PAWN_W,PAWN_W,PAWN_W,PAWN_W,PAWN_W,
                        CASTLE_W,KNIGHT_W,BISHOP_W,QUEEN_W,KING_W,BISHOP_W,KNIGHT_W,CASTLE_W};

GameState env_init()
{
    GameState gameState;
    gameState.playerTurn=WHITE;
    gameState.castling_arr[PLAYER1].Left=gameState.castling_arr[PLAYER1].Right=0;
    gameState.castling_arr[PLAYER2].Left=gameState.castling_arr[PLAYER2].Right=0;
    gameState.moves_vector_cnt=0;
    memcpy(gameState.board,initial_board,sizeof(int)*64);
    return gameState;
}

void env_play(GameState *gameState, Player *player, int start_pt, int end_pt)
{
    if(gameState->playerTurn!=player->color) return;
    int s_piece=gameState->board[start_pt];
    int e_piece=gameState->board[end_pt];
    gameState->board[start_pt]=0;
    gameState->board[end_pt]=s_piece;
    gameState->playerTurn*=-1;
    Move move={s_piece,start_pt,end_pt,e_piece,end_pt,NOSPECIAL};
    // char str_move[20];
    // move2string(str_move,&move);
    // gameState->moves_stack.log=str_move;
    //stack_push(&(gameState->moves_stack),str_move,sizeof(str_move));

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
            legal_moves=env_get_legal_pawn(gameState,start_pt);
            break;
        case KNIGHT:
            legal_moves=env_get_legal_knight(gameState,start_pt);
            break;
        case CASTLE:
            legal_moves=env_get_legal_castle(gameState,start_pt);
            break;
        case BISHOP:
            legal_moves=env_get_legal_bishop(gameState,start_pt);
            break;
        case QUEEN:
            legal_moves=env_get_legal_queen(gameState,start_pt);
            break;
        case KING:
            legal_moves=env_get_legal_king(gameState,start_pt);
            break;
    }
}

//board[pos]*playerTurn<0 -> enemy
//board[pos]*playerTurn>0 -> mime

vector env_get_legal_pawn(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);

    int x=start_pt%8, y=start_pt/8;
    if(x-1>=0 && gameState->board[y*8+x-1]<0)vector_add(&legal_moves,y*8+x-1);
    else if(x+1<8 && gameState->board[y*8+x+1]<0)vector_add(&legal_moves,y*8+x+1);

    if(start_pt/8 == ((gameState->playerTurn>0)?6:1))//checking if on home row
       {
           if((gameState->board[(y+gameState->playerTurn*-1)*8+x]==0)&&(gameState->board[(y+2*gameState->playerTurn*-1)*8+x]*gameState->board[start_pt]<=0))
               vector_add(&legal_moves,(y+2*gameState->playerTurn*-1)*8+x);
           //checks if space ahead is clear and 2 ahead are clear or occupied by opposite color
        }
              
    //y+=gameState->playerTurn*-1*1;//if playerTurn=1, then goes up, but for image, it should go up, which means y should decrease
    //checks if space ahead is empty/occupied by enemy
    //also checks if pawns are not on the last rows
    if(((y+1<7)&&(y-1>0))  && (gameState->board[(y+gameState->playerTurn*-1)*8+x]*gameState->board[start_pt]<=0))
        vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x));
    /*(gameState->board[(y+gameState->playerTurn*-1)*8+x]==0)||(*/
    
    //(x>=0 && x<8 && y>=0 && y<8)&&

	//checks diagonal attacks
    if((x+1>=0 && x+1<8 && y-1>=0 && y+1<8)&&(gameState->board[(y+gameState->playerTurn*-1)*8+x+1]*gameState->board[start_pt]<0))vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x+1));
    if((x-1>=0 && x-1<8 && y-1>=0 && y+1<8)&&(gameState->board[(y+gameState->playerTurn*-1)*8+x-1]*gameState->board[start_pt]<0))vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x-1));
                                                                                                                                                         
    return legal_moves;
}

void env_get_legal_cross(GameState *gameState, vector *legal_moves, int start_pt, int step)
{
    int x=start_pt%8, y=start_pt/8;
    int playerTurn=gameState->playerTurn;
    int xMax=MIN(x+step+1,8), xMin=MAX(x-step,0);
    int yMax=MIN(y+step+1,8), yMin=MAX(y-step,0);
    for(int i=y+1;i<yMax;i++)//iterates through the y in one direction
    {
        if(gameState->board[i*8+x]==0)
        {
            vector_add(legal_moves,(i*8+x));
        }
        else if (gameState->board[i*8+x]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+x));//adds opponents space
            break;//ternimates loop
        }
        else
            break;
    }
                       
    for(int i=y-1;i>=yMin;i--)
    {
        if(gameState->board[i*8+x]==0)
        {
            vector_add(legal_moves,(i*8+x));
        }
        else if (gameState->board[i*8+x]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+x));//adds opponents space
            break;//ternimates loop
        }
        else
            break;
    }
    
    for(int i=x+1;i<xMax;i++)//iterates through the y in one direction
    {
        if(gameState->board[y*8+i]==0)
        {
            vector_add(legal_moves,(y*8+i));//adds every empty space
        }
        else if (gameState->board[y*8+i]*playerTurn<0)
        {
            vector_add(legal_moves,(y*8+i));//adds opponents space
            break;//ternimates loop
        }
        else
            break;
   }
    for(int i=x-1;i>=xMin;i--)
    {
        if(gameState->board[y*8+i]==0)
        {
            vector_add(legal_moves,(y*8+i));
        }
        else if (gameState->board[y*8+i]*playerTurn<0)
        {
            vector_add(legal_moves,(y*8+i));//adds opponents space
            break;//ternimates loop
        }
        else
            break;
    }

}

void env_get_legal_diagonal(GameState *gameState, vector *legal_moves, int start_pt, int step)
{
    int x=start_pt%8, y=start_pt/8;
    int playerTurn=gameState->playerTurn;
        int xMax=MIN(x+step+1,8), xMin=MAX(x-step,0);
    int yMax=MIN(y+step+1,8), yMin=MAX(y-step,0);
    for(int i=y+1,j=x+1 ; i<yMax && j<xMax ; i++, j++)//iterates through the x,y in one direction
    {
        if(gameState->board[i*8+j]==0)
        {
              vector_add(legal_moves,(i*8+j));//adds every empty space
        }
        else if (gameState->board[i*8+j]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+j));//adds opponents space
            break;//ternimates loop
        }
        else
        {
            break;//terminates if something blocks its path
        }
    }
    
    for(int i=y+1,j=x-1 ; i<yMax && j>=xMin ; i++, j--)//iterates through the x,y in one direction
    {
        if(gameState->board[i*8+j]==0)
        {
            vector_add(legal_moves,(i*8+j));//adds every empty space
        }
        else if (gameState->board[i*8+j]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+j));//adds opponents space
            break;//ternimates loop
        }
        else
        {
            break;//terminates if something blocks its path
        }
   }

    for(int i=y-1,j=x-1 ; i>=yMin && j>=xMin ; i--, j--)//iterates through the x,y in one direction
    {
        if(gameState->board[i*8+j]==0)
        {
            vector_add(legal_moves,(i*8+j));//adds every empty space
        }
        else if (gameState->board[i*8+j]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+j));//adds opponents space
            break;//ternimates loop
        }
        else
        {
            break;//terminates if something blocks its path
        }
    }
    
    for(int i=y-1,j=x+1 ; i>=yMin && j<xMax ; i--, j++)//iterates through the x,y in one direction
    {
        if(gameState->board[i*8+j]==0)
        {
            vector_add(legal_moves,(i*8+j));//adds every empty space
        }
        else if (gameState->board[i*8+j]*playerTurn<0)
        {
            vector_add(legal_moves,(i*8+j));//adds opponents space
            break;//ternimates loop
        }
        else
        {
            break;//terminates if something blocks its path
        }
    }
}

vector env_get_legal_castle(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);
    env_get_legal_cross(gameState,&legal_moves,start_pt,8);
    return legal_moves;
}

vector env_get_legal_bishop(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);
    env_get_legal_diagonal(gameState,&legal_moves,start_pt,8);
    return legal_moves;
}

vector env_get_legal_queen(GameState *gameState, int start_pt)
{
    vector legal_moves1,legal_moves2;
    vector_init(&legal_moves1);
    vector_init(&legal_moves2);
    env_get_legal_cross(gameState,&legal_moves1,start_pt,8);
    env_get_legal_diagonal(gameState,&legal_moves2,start_pt,8);
    vector_cat(&legal_moves1,&legal_moves2);
    vector_free(&legal_moves2);
    return legal_moves1;
}

vector env_get_legal_king(GameState *gameState, int start_pt)
{
    vector legal_moves1,legal_moves2;
    vector_init(&legal_moves1);
    vector_init(&legal_moves2);
    env_get_legal_cross(gameState,&legal_moves1,start_pt,1);
    env_get_legal_diagonal(gameState,&legal_moves2,start_pt,1);
    vector_cat(&legal_moves1,&legal_moves2);
    vector_free(&legal_moves2);
    return legal_moves1;
}

vector env_get_legal_knight(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);
    int x=start_pt%8, y=start_pt/8;
    
    //jumps that are +/- 2 in the y
    if((x+1<8 && y+2<8)&&(gameState->board[((y+2)*8+(x+1))]*gameState->board[start_pt]<=0))
    {
        vector_add(&legal_moves,((y+2)*8+(x+1)));
    }
    if((x-1>=0 && y+2<8)&&(gameState->board[((y+2)*8+(x-1))]*gameState->board[start_pt]<=0))
    {
        vector_add(&legal_moves,((y+2)*8+(x-1)));
    }
    if((x+1<8 && y-2>=0)&&(gameState->board[((y-2)*8+(x+1))]*gameState->board[start_pt]<=0))
    {
        vector_add(&legal_moves,((y-2)*8+(x+1)));
    }
    if((x-1>=0 && y-2>=0)&&(gameState->board[((y-2)*8+(x-1))]*gameState->board[start_pt]<=0))
    {
        vector_add(&legal_moves,((y-2)*8+(x-1)));
    }
    
    //jumps that are +/- 2 in the x
    if((x+2<8 && y+1<8)&&gameState->board[((y+1)*8+(x+2))]*gameState->board[start_pt]<=0)
    {
        vector_add(&legal_moves,((y+1)*8+(x+2)));
    }
    if((x-2>=0 && y+1<8)&&gameState->board[((y+1)*8+(x-2))]*gameState->board[start_pt]<=0)
    {
        vector_add(&legal_moves,((y+1)*8+(x-2)));
    }
    if((x+2<8 && y-1>=0)&&gameState->board[((y-1)*8+(x+2))]*gameState->board[start_pt]<=0)
    {
        vector_add(&legal_moves,((y-1)*8+(x+2)));
    }
    if((x-2>=0 && y-1>=0)&&gameState->board[((y-1)*8+(x-2))]*gameState->board[start_pt]<=0)
    {
        vector_add(&legal_moves,((y-1)*8+(x-2)));
    }
    
    return legal_moves;
}
