
#include"SDL/SDL.h"
#include"GameENV.h"
#include"struct.h"
#include"constant.h"
#include"stack.h"


#ifndef GAMEGUI_H
#define GAMEGUI_H



int gui_init_video();
int gui_free_video();
int gui_example();
void gui_init();
int gui_main_menu();
Player gui_player_menu();
int gui_play(Player player);
void gui_quit_window();
void gui_refresh();

void gui_player_HvC_menu(Player* player_arr);
void gui_player_HvH_menu(Player* player_arr);
void gui_player_CvC_menu(Player* player_arr);

void gui_gameplay_window();

int gui_play(Player player);

void gui_refresh();

#endif