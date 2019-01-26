#include"AI.h"
#include"GameGUI.h"
#include"struct.h"

#include"constant.h"

int GameMode=0;

int play(GameState gameState,Player player)
{
    int quit;
    if(player.identity==HUMAN) quit=gui_play(gameState,player);
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
        {
            quit=play(gameState,player1);
        }
        else quit=play(gameState,player2);
        if(quit)
        {
            gui_quit_window(quit);
            return;
        }
        else gui_refresh(gameState,player_arr);
    }
	
}

int main(int argc, char *argv[])
{
    while(1)
    {
        Game();
    }
    
    return 0;
}