
#include"ENV.h"
#include<string.h>
#include"struct.h"
#include"constant.h"
#include"stack.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>


#ifndef GAMEGUI_H
#define GAMEGUI_H

#define MAX_MSGLEN  100
#define SQUARE_SIZE 50
#define WINDOW_BORDER 0
#define BOARD_BORDER 0
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

#define GameMode_HvC 1
#define GameMode_HvH 2
#define GameMode_CvC 3

int gui_init_window(int argc, char*argv[]);

void gui_init(GameState *gameState,Player player_arr[2]);

int gui_main_menu();

void gui_player_HvC_menu(Player* player_arr);
void gui_player_HvH_menu(Player* player_arr);
void gui_player_CvC_menu(Player* player_arr);

void gui_gameplay_window(GameState *gameState);

int gui_play(GameState *gameState,Player *player);

void gui_refresh(GameState *gameState,Player *player_arr);

void gui_checkmate_window(int winner);

#endif
