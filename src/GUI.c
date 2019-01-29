

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
GtkWidget *button;

void gui_render()
{
  gdk_threads_enter();
  gtk_main() ;
  gdk_threads_leave();
}

int gui_init_window(int argc, char*argv[])//Here you init the window and start the main loop
{
  


  gtk_init(&argc, &argv) ;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
  gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ; 
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ; 

  gtk_widget_show_all(window) ; 

  // gdk_threads_init();
  // g_thread_new("render",(GThreadFunc)gui_render,NULL);
}

void gui_init(Player player_arr[2])
{
	
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
  //here you use window pointer to draw gameplay window
  //bind an event to listen to the click
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

//here you use window pointer to draw main menu
//bind an event to listen to the click
//then use a while loop to wait for the user click
//after that return the GameMode
//WARNING: you must use sleep(10) in your main loop
//because gtk creates a new thread to render the window
//thus you must let the main thread release some cpu resource for it to run

//WARNING: Don`t forget to unbind the event to click
int gui_main_menu()
{
        
}

//here you use window pointer to draw player menu
//bind an event to listen to the click
//then use a while loop to wait for the user click
//after that return the GameMode
//WARNING: you must use sleep(10) in your main loop
//because gtk creates a new thread to render the window
//thus you must let the main thread release some cpu resource for it to run

//WARNING: Don`t forget to unbind the event to click
void gui_player_HvC_menu(Player* player_arr)
{

}

void gui_player_HvH_menu(Player* player_arr)
{

}

void gui_player_CvC_menu(Player* player_arr)
{

}

//don`t worry about this part first
int gui_play(GameState *gameState,Player *player)
{
  
}

//here you will use the gameState to refresh the board
//just the board
//and don`t worry about the reset, if you use the logic of QV`s demo
//you just need to draw the board according to gameState->board, which is an 1D array
//if you want (x,y) coordinates, x=board[position]%8, y=board[position]/8
//specially, for the place where board[position]==0, which means there is no pieces there
//try this: if((x+y)%2==0) it`s a white square, else it`s a black square
//the reason is that, suppose the the first square in line1 is white, then 0%2==0,
//and the second is black, then 1%2==1
//but for line2, it just got reversed, which means that (0+1)%2==1
//and for black in the second column, (1+1)%2==0

//also, to get the chess icon path, for example, 
//if you want a White Pawn in a White Square
//then it`s "WhiteSquare"+"White"+"Pawn.jpg"
//use a strcat to create the file name, then use a char** array to record the strings
//if you can`t work this out, then leave it, I will show you in the meeting, but finish other part first

//by the way, all constants are defined in constant.h, have a look
void gui_refresh(GameState *gameState,Player *player_arr)
{
	
}



