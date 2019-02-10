#include"AI.h"
#include"GUI.h"
#include"struct.h"
#include"constant.h"

#define MODEL 1

int play(GameState *gameState,Player *player,int model)
{
    int quit;
    
    if(player->identity==HUMAN) quit=gui_play(gameState,player);
    else quit=ai_play(gameState,player,model);
    return quit;
}

void Game(int argc, char *argv[],int model)
{
    gui_init_window(argc,argv);

    Player player_arr[2];
    GameState gameState=env_init();
    Player player1,player2;
    gui_init(&gameState,player_arr);
    player1=player_arr[0];
    player2=player_arr[1];
    player1.id=PLAYER1;
    player2.id=PLAYER2;

    int quit=0;
    while(quit==0)
    {
        int quit;
        if(gameState.playerTurn==player1.color)
            quit=play(&gameState,&player1,model);
        else 
            quit=play(&gameState,&player2,model);
        stack_print_log(&(gameState.moves_stack));
        if(quit)
        {
            gui_refresh(&gameState,player_arr);
            gui_checkmate_window(&gameState,quit);
            return;
        }
        else gui_refresh(&gameState,player_arr);
    }
}

void print_board(GameState *gameState)
{
    for(int i=0;i<64;i++)
    {
        if(i%8==0)printf("\n");
        printf("%d\t",gameState->board[i]);
    }
    printf("\n*****************\n");
}

void fprint_board(GameState *gameState,FILE *fp)
{
    for(int i=0;i<64;i++)
    {
        if(i%8==0)printf("\n");
        fprintf(fp,"%d\t",gameState->board[i]);
    }
    fprintf(fp,"\n*****************\n");
}



void AI_Contest(int model1,int model2)
{
    int ContestTimes=100;

    GameState gameState=env_init();
    Player player1,player2;
    player1.color=WHITE;
    player2.color=BLACK;
    player1.id=0;
    player2.id=1;
    player1.identity=player2.identity=COMPUTER;
    int quit=0;

    FILE *fp = NULL;
    
    int round=0;
    int model1_wins=0,model2_wins=0,draw=0;
    for(int i=0;i<ContestTimes;i++)
    {
        fp = fopen("TestLog/test", "a");
        round=0;
        quit=0;
        while(quit==0)
        {
            if(gameState.playerTurn==player1.color)quit=ai_play(&gameState,&player1,model1);
            else quit=ai_play(&gameState,&player2,model2);
            //print_board(&gameState);
            //fprint_board(&gameState,fp);
            round++;
            if(round>=300)break;
        }
        if(quit==0) draw++;
        else if(quit==1) 
        {
            if(gameState.playerTurn==player1.color)model2_wins++;
            else model1_wins++;
        }
        else if(quit==2)
        {
            if(gameState.playerTurn==player1.color)model1_wins++;
            else model2_wins++;
        }
        fprintf(fp,"model1 wins %d times, model2 wins %d times, draw %d times\n",model1_wins,model2_wins,draw);
        fclose(fp);
    }
    

    
}


void AI_ContestWithGUI(int argc, char *argv[],int model1,int model2)
{
    gui_init_window(argc,argv);
    GameState gameState=env_init();
    Player player1,player2;
    player1.color=WHITE;
    player2.color=BLACK;
    player1.id=0;
    player2.id=1;
    player1.identity=player2.identity=COMPUTER;
    gui_gameplay_window(&gameState);

    int quit=0;
    while(quit==0)
    {
        if(gameState.playerTurn==player1.color)quit=ai_play(&gameState,&player1,model1);
        else quit=ai_play(&gameState,&player2,model2);
        // sleep(1);
        //print_board(&gameState);
        gui_refresh(&gameState,&player1);
    }
}


int main(int argc, char *argv[])
{   
    #ifdef SUPEROLD
    printf("\n\n\\********************\\\n");
    printf("You are seeing this message because you are using a very old version of Glib\n");
    printf("This is strongly NOT recommended because when TODAY`s HUMAN BEINGS download you project from Internet\n");
    printf("You expect them to install the latest glib instead of some outdated version\n");
    printf("But after all we can`t do anything to stop you.\n");
    printf("Even if you may not really want to\n");
    #endif
    srand(time(0));
    //gui_init_window(argc,argv);
    //test_gui_menu(argc,argv);//specially created for aria to test
    // while(1)
    Game(argc,argv,1);
    
    
    //test_env();
    //Test_AI(1);
    //AI_Contest(1,2);
    //test_gamePlay_window(argc,argv);
    //AI_ContestWithGUI(argc,argv,1,2);
    //Test_AI_withGUI(argc,argv,1);
    char any_to_quit;
    getchar();
    return 0;
}