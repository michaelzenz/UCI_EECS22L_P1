
#include"ENV.h"
#define MIN(X,Y) (X)>(Y)?(Y):(X)
#define MAX(X,Y) (X)>(Y)?(X):(Y)
#define XY2ID(X,Y) ((Y)*8+X)

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
    gameState.moves_stack=NULL;
    return gameState;
}

void env_free_container(GameState *gameState)
{
    for(int i=0;i<gameState->moves_vector_cnt;i++)
        vector_free(&(gameState->container[i].legal_moves));
    gameState->moves_vector_cnt=0;
}

void env_play(GameState *gameState, Player *player, int start_pt, int end_pt)
{
    int s_piece=gameState->board[start_pt];
    int e_piece=gameState->board[end_pt];
    gameState->board[start_pt]=0;
    gameState->board[end_pt]=s_piece;
    gameState->playerTurn*=-1;
    Move move={s_piece,start_pt,end_pt,e_piece,end_pt,NOSPECIAL};
    char str_move[STR_NODE_SIZE];
    memset(str_move,'\0',sizeof(str_move));
    move2string(str_move,&move);
    stack_push(&(gameState->moves_stack),str_move);

}

void env_undo(GameState *gameState)
{
    if(!stack_isEmpty((gameState->moves_stack)))
    {
        char str_last_move[STR_NODE_SIZE];
        stack_pop(&(gameState->moves_stack),str_last_move);
        Move last_move=string2move(str_last_move);
        gameState->board[last_move.start_pt]=last_move.piece;
        gameState->board[last_move.end_pt]=BLANK;
        gameState->board[last_move.captured_pos]=last_move.captured;
        gameState->playerTurn*=-1;
    }

}


uchar env_check_end(GameState *gameState, Player *player)
{
    int K=-1;
    vector legal_moves;
    int pos=-1;
    uchar threatened=1;
    uchar end=1;
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            pos=y*8+x;
            if(gameState->board[pos]*gameState->playerTurn>0)
            {
                legal_moves=env_get_legal_moves(gameState,player,pos);
                if(legal_moves.count>0)
                {
                    gameState->container[gameState->moves_vector_cnt].pos=pos;
                    gameState->container[gameState->moves_vector_cnt].legal_moves=legal_moves;
                    gameState->moves_vector_cnt++;
                }
                else
                    continue;
                for(int i=0;i<legal_moves.count;i++)
                {
                    env_play(gameState,player,pos,vector_get(&legal_moves,i));
                    threatened=env_is_threatened(gameState,player);
                    env_undo(gameState);
                    if(threatened==0)
                    {
                        end=0;
                        break;
                    }
                    else if(threatened==2)end=2;
                }
                //here is the only position where vector_free is not necessary
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
    newState.moves_vector_cnt=0;
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
                    threatened_area[vector_get(&legal_moves,i)]=1;
                }
                vector_free(&legal_moves);
            }
        }
    }
    if(K==-1)return 2;
    else if(threatened_area[K]==1)return 1;
    else return 0;
}

vector env_get_legal_moves(GameState *gameState, Player *player, int start_pt)
{
    
    vector legal_moves;
    vector_init(&legal_moves);
    if(start_pt<0||start_pt>=64)return legal_moves;
    if(gameState->playerTurn*gameState->board[start_pt]<=0)return legal_moves;
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
    return legal_moves;
}

//board[pos]*playerTurn<0 -> enemy
//board[pos]*playerTurn>0 -> mime

vector env_get_legal_pawn(GameState *gameState, int start_pt)
{
    vector legal_moves;
    vector_init(&legal_moves);
    int x=start_pt%8, y=start_pt/8;

    int playerTurn=gameState->playerTurn;
    int maxStep=1;
    if((7-y*2)*playerTurn==-5)//means that pawn is on home row
        maxStep=2;
    for(int k=1;k<=maxStep;k++)
    {
        if(abs(7-(y+k*playerTurn*-1)*2)>7)break;
        if(gameState->board[XY2ID(x,y+k*playerTurn*-1)]*playerTurn==0)vector_add(&legal_moves,XY2ID(x,y+k*playerTurn*-1));
        else break;
    }
    for(int dx=-1;dx<=1;dx+=2)
    {
        if(abs(7-(y+playerTurn*(-1))*2)>7)break;
        if(x+dx<0||x+dx>7)continue;
        if(gameState->board[XY2ID(x+dx,y-playerTurn)]*playerTurn<0)vector_add(&legal_moves,XY2ID(x+dx,y-playerTurn));
    }
        
    //if(start_pt/8 == ((gameState->playerTurn>0)?6:1))//checking if on home row
       //{
          // if((gameState->board[(y+gameState->playerTurn*-1)*8+x]==0)&&(gameState->board[(y+2*gameState->playerTurn*-1)*8+x]*gameState->board[start_pt]<=0))
            //   vector_add(&legal_moves,(y+2*gameState->playerTurn*-1)*8+x);
           //checks if space ahead is clear and 2 ahead are clear or occupied by opposite color
        //}
              
    //y+=gameState->playerTurn*-1*1;//if playerTurn=1, then goes up, but for image, it should go up, which means y should decrease
    //checks if space ahead is empty/occupied by enemy
    //also checks if pawns are not on the last rows
    //if(((y+1<7)&&(y-1>0))  && (gameState->board[(y+gameState->playerTurn*-1)*8+x]*gameState->board[start_pt]<=0))
        //vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x));
    /*(gameState->board[(y+gameState->playerTurn*-1)*8+x]==0)||(*/

	//checks diagonal attacks
    //if((x+1>=0 && x+1<8 && y-1>=0 && y+1<8)&&(gameState->board[(y+gameState->playerTurn*-1)*8+x+1]*gameState->board[start_pt]<0))vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x+1));
    //if((x-1>=0 && x-1<8 && y-1>=0 && y+1<8)&&(gameState->board[(y+gameState->playerTurn*-1)*8+x-1]*gameState->board[start_pt]<0))vector_add(&legal_moves,((y+gameState->playerTurn*-1)*8+x-1));
                                                                                                                                                         
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

void env_get_legal_castling(GameState *gameState, vector *legal_moves, int start_pt)
{
    int x=start_pt%8, y=start_pt/8;
    int playerTurn=gameState->playerTurn;
    //space numbers are hardcoded in
    if(((y==7)&&(x==4))&&(playerTurn==1))//checks for king being in its original position
    {
        if(((gameState->board[56]==3)&&(gameState->board[57]==0))&&((gameState->board[58]==0)&&(gameState->board[59]==0)))//checks for left castle and empty spaces inbetween
        {
           vector_add(legal_moves,(58));
        }
        if((gameState->board[63]==3)&&((gameState->board[62]==0)&&(gameState->board[61]==0)))//checks for right castle and empty spaces inbetween
        {
            vector_add(legal_moves,(62));
        }
    }
       
    if(((y==0)&&(x==4))&&(playerTurn==-1))//checks for king being in its original position
    {
        if(((gameState->board[0]==-3)&&(gameState->board[1]==0))&&((gameState->board[2]==0)&&(gameState->board[3]==0)))//checks for left castle and empty spaces inbetween
        {
            vector_add(legal_moves,(2));
        }
        if((gameState->board[7]==-3)&&((gameState->board[5]==0)&&(gameState->board[6]==0)))
        {
            vector_add(legal_moves,(6));
        }
    }
}

vector env_get_legal_king(GameState *gameState, int start_pt)
{
    vector legal_moves1,legal_moves2,legal_moves3;
    vector_init(&legal_moves1);
    vector_init(&legal_moves2);
    vector_init(&legal_moves3);
    env_get_legal_cross(gameState,&legal_moves1,start_pt,1);
    env_get_legal_diagonal(gameState,&legal_moves2,start_pt,1);
    env_get_legal_castling(gameState,&legal_moves3,start_pt);//a third vector for castling
    vector_cat(&legal_moves1,&legal_moves2);
    vector_free(&legal_moves2);
    vector_cat(&legal_moves1,&legal_moves3);
    vector_free(&legal_moves3);
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
