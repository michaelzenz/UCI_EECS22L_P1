
#include"SDL/SDL.h"
#include"GameENV.h"
#ifndef struct.h
#include struct.h
#endif



SDL_Surface *gui_screen;	//This pointer will reference the backbuffer

int gui_init_video();
int gui_free_video();
int gui_example();
int gui_init();
int gui_main_menu();
Player gui_player_menu();
int gui_play(Player player);