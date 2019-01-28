
#include"SDL/SDL.h"
#include"ENV.h"
#include"struct.h"
#include"constant.h"
#include"stack.h"


#ifndef GAMEGUI_H
#define GAMEGUI_H

#define MAX_MSGLEN  100
#define SQUARE_SIZE 50
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)

enum GRID
{
    wKING,
	wRook,
	wKnight,
	wBishop,
	wQueen,
	wPawn,
        bKING,
	bRook,
	bKnight,
	bBishop,
	bQueen,
	bPawn

};


int gui_init_video();
int gui_free_video();
int gui_example();
void gui_init();
int gui_main_menu();
Player gui_player_menu();
int gui_play(GameState gameState,Player player);
void gui_quit_window();
void gui_refresh();

void gui_player_HvC_menu(Player* player_arr);
void gui_player_HvH_menu(Player* player_arr);
void gui_player_CvC_menu(Player* player_arr);

void gui_gameplay_window();

int gui_play(GameState gameState,Player player);

void gui_refresh(GameState gameState,Player *player_arr);

#endif
