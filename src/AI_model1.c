#include"AI.h"
#define MAXSTEP 3
#define CHECK_SCORE




int ai_model1_simulate(GameState *gameState, Player *player, int depth)
{
    uchar check=env_check_end(gameState,player);
    if(check)return gameState->playerTurn*-99999999;
    else if(depth>=MAXSTEP)return ai_sum_scores(gameState,player);

    int MaxScore=-99999999;
    int score;
    int moves_cnt=gameState->moves_vector_cnt;
    int playerTurn=gameState->playerTurn;
    for(int i=0;i<moves_cnt;i++)
    {
        int start_pt=gameState->container[i].pos;
        vector legal_moves=gameState->container[i].legal_moves;
        int cnt=legal_moves.count;
        for(int k=0;k<cnt;k++)
        {
            GameState simulation;
            simulation=env_copy_State(gameState);
            env_play(&simulation,player,start_pt,vector_get(&legal_moves,k));
            score=playerTurn*ai_model1_simulate(&simulation,player,depth+1);
            MaxScore=MAX(MaxScore,score);
        }
    }
    env_free_container(gameState);
    return MaxScore*playerTurn;
}

int ai_model1_play(GameState *gameState, Player *player)
{
    int check_end=env_check_end(gameState,player);
    if(check_end) return 1;
    int MaxScore=-99999999;
    int score;
    vector BestMovesID,MovesStart,MovesEnd,Scores;
    vector_init(&BestMovesID);
    vector_init(&MovesStart);
    vector_init(&MovesEnd);
    vector_init(&Scores);
    int moves_vector_cnt=gameState->moves_vector_cnt;
    int AllMovesCnt=0,BestMovesCnt=0;
    for(int i=0;i<moves_vector_cnt;i++)
    {
        int start_pt=gameState->container[i].pos;
        vector legal_moves=gameState->container[i].legal_moves;
        int cnt=legal_moves.count;
        for(int k=0;k<cnt;k++)
        {
            int end_pt=vector_get(&legal_moves,k);
            vector_add(&MovesStart,start_pt);
            vector_add(&MovesEnd,end_pt);
            GameState simulation;
            simulation=env_copy_State(gameState);
            env_play(&simulation,player,start_pt,end_pt);
            score=gameState->playerTurn*ai_model1_simulate(&simulation,player,1);
            vector_add(&Scores,score);
            MaxScore=MAX(MaxScore,score);
            AllMovesCnt++;
        }
    }

    
    for(int i=0;i<AllMovesCnt;i++)
    {
        if(vector_get(&Scores,i)==MaxScore)
        {
            vector_add(&BestMovesID,i);
            BestMovesCnt++;
        }
        
    }
    int id=vector_get(&BestMovesID,rand()%BestMovesCnt);
    #ifdef CHECK_SCORE
    printf("It is %d playing\n",gameState->playerTurn);
    printf("Current Score is %d\n",ai_sum_scores(gameState,player));
    #endif
    env_play(gameState,player,vector_get(&MovesStart,id),vector_get(&MovesEnd,id));
    #ifdef CHECK_SCORE
    printf("The player has decided to move from %d to %d\n",vector_get(&MovesStart,id),vector_get(&MovesEnd,id));
    printf("After making the move, the score is %d\n",ai_sum_scores(gameState,player));
    #endif
    vector_free(&BestMovesID);
    vector_free(&MovesStart);
    vector_free(&MovesEnd);
    vector_free(&Scores);
    env_free_container(gameState);
    return 0;
}


int ai_easy_play(GameState *gameState, Player *player)
{
    int check_end=env_check_end(gameState,player);
    if(check_end) return 1;
    int MaxScore=-1;
    int CurMaxScore;
    vector BestMovesID,MovesStart,MovesEnd,Scores;
    vector_init(&BestMovesID);
    vector_init(&MovesStart);
    vector_init(&MovesEnd);
    vector_init(&Scores);
    int moves_vector_cnt=gameState->moves_vector_cnt;
    int AllMovesCnt=0;
    for(int i=0;i<moves_vector_cnt;i++)
    {
        int start_pt=gameState->container[i].pos;
        vector legal_moves=gameState->container[i].legal_moves;
        int cnt=legal_moves.count;
        //if (cnt > 3)//forces it to only consider half of its options
        //{
            //cnt = cnt/2;
        //}
        int justOne = 0;
        for(int k=0;k<cnt;k++)
        {
            if ((justOne == 0)||((rand()%1 == 0)&&(justOne == 1)))
            {
                int end_pt=vector_get(&legal_moves,k);
                vector_add(&MovesStart,start_pt);
                vector_add(&MovesEnd,end_pt);
                GameState simulation;
                simulation=env_copy_State(gameState);
                env_play(&simulation,player,start_pt,end_pt);
                CurMaxScore=ai_model1_simulate(&simulation,player,1);
                vector_add(&Scores,CurMaxScore);
                MaxScore=MAX(MaxScore,CurMaxScore);
                AllMovesCnt++;
            }
        }
    }
    for(int i=0;i<AllMovesCnt;i++)
        if(vector_get(&Scores,i)==MaxScore)vector_add(&BestMovesID,i);
    int id=vector_get(&BestMovesID,rand()%AllMovesCnt);
    env_play(gameState,player,vector_get(&MovesStart,id),vector_get(&MovesEnd,id));
    vector_free(&BestMovesID);
    vector_free(&MovesStart);
    vector_free(&MovesEnd);
    vector_free(&Scores);
    env_free_container(gameState);
    return 0;
}
