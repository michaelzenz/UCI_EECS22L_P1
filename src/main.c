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

void print_legal_moves(vector legal_moves, int start_pt)
{
    printf("Legal Moves are: \n");
    for(int i=0;i<legal_moves.count;i++)
    {
        printf("%d -> %d\n",start_pt,vector_get(&legal_moves,i));
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
    int check_end=0;
    while(1)
    {
        print_board(&gameState);
        if(gameState.playerTurn==player1.color)
        {
            check_end=env_check_end(&gameState,&player1);
            if(check_end)printf("player2 wins\n");
            printf("\nPlayer1 moves from: ");
            scanf("%d",&start_pt);
            legal_moves1=env_get_legal_moves(&gameState,&player1,start_pt);
            print_legal_moves(legal_moves1,start_pt);
            printf("to: ");
            scanf("%d",&end_pt);
            if(vector_contain(&legal_moves1,end_pt)!=1)continue;
            env_play(&gameState,&player1,start_pt,end_pt);
            vector_free(&legal_moves1);
        }
        else
        {
            check_end=env_check_end(&gameState,&player2);
            if(check_end)printf("player1 wins\n");
            printf("\nPlayer2 moves from: ");
            scanf("%d",&start_pt);
            legal_moves2=env_get_legal_moves(&gameState,&player2,start_pt);
            print_legal_moves(legal_moves2,start_pt);
            printf("to: ");
            scanf("%d",&end_pt);
            if(vector_contain(&legal_moves2,end_pt)!=1)continue;
            env_play(&gameState,&player2,start_pt,end_pt);
            vector_free(&legal_moves2);
        }
    }
}

//specially for aria
void test_gui_menu()
{
    Player player_arr[2];
    player_arr[0].id=0;
    player_arr[1].id=1;

    gui_init(player_arr);
    for(int i=0;i<2;i++)
    {
        printf("Player%d uses ",i+1);
        if(player_arr[i].color==WHITE)printf("White and is a ");
        else printf("Black and is a ");
        if(player_arr[i].identity==HUMAN)printf("Human\n");
        else printf("Computer\n");
    }
    
}

int main(int argc, char *argv[])
{
    //gui_init_window(argc,argv);
    // while(1)
    //     Game();

    test_env();
    //test_gui_menu();//specially created for aria to test
    
    
    return 0;
}