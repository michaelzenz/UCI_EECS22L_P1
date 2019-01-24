#include"AI.h"
#include"GameGUI.h"

#define HUMAN 1
#define COMPUTER -1

int GameMode=0;

int play(Player player)
{
    int quit;
    if(player.identity==HUMAN)
        quit=gui_play();
    else
        quit=ai_play();
}

int Game()
{
    Player player1,player2;

    gui_init_video();

	//gui_example();

    gui_init(&player1,&player2);

    while(1)
    {
        int quit;
        if(playerTurn==player1.color)
            quit=play(player1);
        else
            quit=play(player2);
        if(quit)
            return;
        gui_refresh();
    }
	
}

int main(int argc, char *argv[])
{
    while(1)
    {
        int exit=Game();
        if(exit)
            break;
        Reset();
    }
    
    return 0;
}