
#include"SDL/SDL.h"
#include"GUI.h"

#define GameMode_HvC 0
#define GameMode_HvH 1
#define GameMode_CvC 2

SDL_Surface *gui_screen;	//This pointer will reference the backbuffer

int gui_init_video()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	gui_screen = SDL_SetVideoMode(320, 240, 32, SDL_ANYFORMAT /*SDL_DOUBLEBUF | SDL_FULLSCREEN*/);
	if (gui_screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
}

void gui_init(Player player_arr[2])
{
	
	gui_init_video();
	int GameMode=gui_main_menu();
	switch(GameMode)
	{
		case GameMode_HvC:
			gui_player_HvC_menu(player_arr);
			break;
		case GameMode_HvH:
			gui_player_HvH_menu(player_arr);
			break;
		case GameMode_CvC:
			gui_player_CvC_menu(player_arr);
			break;
	}

	gui_gameplay_window();
}

void gui_gameplay_window()
{

}

void gui_quit_window(GameState gameState)
{

}

int gui_main_menu()
{

}

void gui_player_HvC_menu(Player* player_arr)
{

}

void gui_player_HvH_menu(Player* player_arr)
{

}

void gui_player_CvC_menu(Player* player_arr)
{

}

int gui_play(GameState gameState,Player player)
{

}

void gui_refresh(GameState gameState,Player *player_arr)
{
	
}



