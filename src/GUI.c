/*
#include"SDL/SDL.h"
*/

#include <gtk/gtk.h>
#include"GUI.h"
#include <stdio.h>


#define GameMode_HvC 0
#define GameMode_HvH 1
#define GameMode_CvC 2

/*Global Variables */

GtkWidget *window ;
GtkWidget *fixed ;
GtkWidget *chess_icon ;
GtkWidget *table ;
GtkWidget *window2;
GtkWidget *button;
enum GRID Board[8][8];

SDL_Surface *gui_screen;	//This pointer will reference the backbuffer

int gui_init_video()
{
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

void InitBoard()
{
}

void ResetBoard()
{
}

void ReverseGridColor(int g_x, int g_y)
{
}




void DrawBoard()
{
        
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
        *g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
        *g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}



static gboolean
on_delete_event (GtkWidget *widget,
         GdkEvent  *event,
         gpointer   data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */

  g_print ("delete event occurred\n");
  gtk_main_quit();
  return FALSE;
}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{
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



