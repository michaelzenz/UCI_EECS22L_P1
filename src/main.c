#include"AI.h"
#include"GUI.h"
#include"struct.h"
#include"constant.h"

int GameMode=0;

int play(GameState *gameState,Player *player)
{
    int quit;
    
    if(player->identity==HUMAN) quit=gui_play(gameState,player);
    else quit=ai_play(gameState,player);
    return quit;
}

void Game()
{
    Player player_arr[2];

    gui_init(player_arr);
    Player player1=player_arr[0],player2=player_arr[1];
    player1.id=PLAYER1;
    player2.id=PLAYER2;

    GameState gameState=env_init();

    while(1)
    {
        int quit;
        if(gameState.playerTurn==player1.color) 
            quit=play(&gameState,&player1);
        else 
            quit=play(&gameState,&player2);
        if(quit)
        {
            gui_quit_window(quit);
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
}

void test_env()
{
    GameState gameState=env_init();
    vector legal_moves1,legal_moves2;
    Player player1,player2;
    player1.color=WHITE;
    player2.color=BLACK;
    player1.id=0;
    player2.id=1;
    printf("player1 is WHITE, player2 is BLACK\n");
    int start_pt,end_pt;
    while(1)
    {
        print_board(&gameState);
        if(gameState.playerTurn==player1.color)
        {
            printf("\nPlayer1 moves from: ");
            scanf("%d",&start_pt);
            printf("to: ");
            scanf("%d",&end_pt);
            env_play(&gameState,&player1,start_pt,end_pt);

        }
        else
        {
            printf("\nPlayer2 moves from: ");
            scanf("%d",&start_pt);
            printf("to: ");
            scanf("%d",&end_pt);
            env_play(&gameState,&player2,start_pt,end_pt);
        }
    }
}

int main(int argc, char *argv[])
{
    gui_init_window(argc,argv);
    // while(1)
    //     Game();

    test_env();
    
    return 0;
}