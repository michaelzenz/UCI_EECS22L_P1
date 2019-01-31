#include"AI.h"
#include"GUI.h"
#include"struct.h"
#include"constant.h"

int GameMode=0;
#define MODEL 1

int play(GameState *gameState,Player *player)
{
    int quit;
    
    if(player->identity==HUMAN) quit=gui_play(gameState,player);
    else quit=ai_play(gameState,player,MODEL);
    return quit;
}

void Game()
{
    Player player_arr[2];
    GameState gameState=env_init();
    gui_init(&gameState,player_arr);
    Player player1=player_arr[0],player2=player_arr[1];
    player1.id=PLAYER1;
    player2.id=PLAYER2;

    

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
void test_gui_menu(int argc, char *argv[])
{
    gui_init_window(argc,argv);
    Player player_arr[2];
    player_arr[0].id=0;
    player_arr[1].id=1;
    GameState gameState=env_init();
    gui_init(&gameState,player_arr);
    for(int i=0;i<2;i++)
    {
        printf("Player%d uses ",i+1);
        if(player_arr[i].color==WHITE)printf("White and is a ");
        else printf("Black and is a ");
        if(player_arr[i].identity==HUMAN)printf("Human\n");
        else printf("Computer\n");
    }
    
}

void AI_Contest(int model1,int model2)
{
    GameState gameState=env_init();
    Player player1,player2;
    player1.color=WHITE;
    player2.color=BLACK;
    player1.id=0;
    player2.id=1;
    player1.identity=player2.identity=COMPUTER;
    int quit=0;
    print_board(&gameState);

    FILE *fp = NULL;
    fp = fopen("TestLog/test", "w+");
    while(quit==0)
    {
        if(gameState.playerTurn==player1.color)quit=ai_play(&gameState,&player1,model1);
        else quit=ai_play(&gameState,&player2,model2);
        print_board(&gameState);
        fprint_board(&gameState,fp);
    }
    fclose(fp);
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

void Test_AI(int model)
{
    GameState gameState=env_init();
    Player player1,player2;
    player1.color=WHITE;
    player2.color=BLACK;
    player1.id=0;
    player2.id=1;
    player1.identity=COMPUTER;
    player2.identity=HUMAN;
    int quit=0;

    vector legal_moves;
    vector_init(&legal_moves);

    int start_pt,end_pt;
    int check_end=0;
    int score;
    while(quit==0)
    {
        print_board(&gameState);
        if(gameState.playerTurn==player1.color)
        {
            quit=ai_play(&gameState,&player1,model);
            if(quit==1)printf("player2 wins\n");
            else if(quit==2)printf("player1 wins\n");
        }
        else
        {
            check_end=env_check_end(&gameState,&player2);
            if(check_end)printf("player1 wins\n");
            printf("\nPlayer2 moves from: ");
            scanf("%d",&start_pt);
            legal_moves=env_get_legal_moves(&gameState,&player2,start_pt);
            print_legal_moves(legal_moves,start_pt);
            printf("to: ");
            scanf("%d",&end_pt);
            
            if(vector_contain(&legal_moves,end_pt)!=1)continue;
            env_play(&gameState,&player2,start_pt,end_pt);
            vector_free(&legal_moves);
            score=gameState.playerTurn*ai_sum_scores(&gameState,&player2);
            printf("Current Scores:%d\n",score);
            env_free_container(&gameState);
        }
    }
}

//specially for armando
void test_gamePlay_window(int argc, char *argv[])
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
}

int main(int argc, char *argv[])
{
    //gui_init_window(argc,argv);
    //test_gui_menu();//specially created for aria to test
    // while(1)
    //     Game();
    srand(time(0));
    //test_env();
    //Test_AI(1);
    //AI_Contest(1,1);
    //test_gamePlay_window(argc,argv);
    AI_ContestWithGUI(argc,argv,1,1);
    return 0;
}