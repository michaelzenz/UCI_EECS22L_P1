#include"AI.h"
#include"GUI.h"
#include"struct.h"

#include"constant.h"

int GameMode=0;

int play(Player player)
{
    int quit;
    if(player.identity==HUMAN) quit=gui_play(player);
    else quit=ai_play(player);
    return quit;
}

void Game()
{
    Player player_arr[2];


	//gui_example();

    gui_init(player_arr);
    Player player1=player_arr[0],player2=player_arr[1];

    while(1)
    {
        int quit;
        if(env_get_playerTurn()==player1.color)
        {
            quit=play(player1);
        }
        else quit=play(player2);
        if(quit)
        {
            gui_quit_window(quit);
            return;
        }
        else gui_refresh();
    }
	
}

int main(int argc, char *argv[])
{
    while(1)
    {
        Game();
        env_reset();
    }
    
    return 0;
}