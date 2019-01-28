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

void InitBoard()
{
        for(int i = 2; i<5; i++){
                for(int j=0; j<8; j++){
                        if((i+j)%2 == 0){
        Board[i][j] = WHITE;
        }
                        if((i+j)%2 == 1){
        Board[i][j] = BLACK;
        }
        }}
        Board[7][0] = wRook;
        Board[7][1] = wKnight;
        Board[7][2] = wBishop;
        Board[7][3] = wQueen;
        Board[7][4] = wKING;
        Board[7][5] = wBishop;
        Board[7][6] = wKnight;
        Board[7][7] = wRook;
        
	Board[6][0] = wPawn;
	Board[6][0] = wPawn;
	Board[6][1] = wPawn;
	Board[6][2] = wPawn;
	Board[6][3] = wPawn;
	Board[6][4] = wPawn;
	Board[6][5] = wPawn;
	Board[6][6] = wPawn;
	Board[6][7] = wPawn;
	
	Board[1][1] = bPawn;
	Board[1][2] = bPawn;
	Board[1][3] = bPawn;
	Board[1][4] = bPawn;
	Board[1][5] = bPawn;
	Board[1][6] = bPawn;
	Board[1][7] = bPawn;

        Board[0][0] = bRook;
        Board[0][1] = bKnight;
        Board[0][2] = bBishop;
        Board[0][3] = bQueen;
        Board[0][4] = bKING;
        Board[0][5] = bBishop;
        Board[0][6] = bKnight;
        Board[0][7] = bRook;


}

void ResetBoard()
{
        for(int i = 0; i<8; i++){
                for(int j=0; j<8; j++){
                        if((i+j)%2 == 0){
        Board[i][j] = WHITE;
        }
                        if((i+j)%2 == 1){
        Board[i][j] = BLACK;
        }
        }}
}

void ReverseGridColor(int g_x, int g_y)
{
        if(Board[g_x][g_y] == BLACK)
        {
                Board[g_x][g_y] = WHITE;
        }
        else
        {
                Board[g_x][g_y] = BLACK;
        }
}

void MoveTheKing(int g_x, int g_y)
{
        ResetBoard();
        Board[g_x][g_y] = wKing;
}


void DrawBoard()
{
        int i, j;

    for(i = 0; i < 8; i ++)
        {
                for(j = 0; j < 8; j ++)
                {
                        switch(Board[i][j])
                        {
                                case BLACK:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackSquare.jpg") ;
                                        break;
                                case WHITE:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteSquare.jpg") ;
                                        break;
                                case wKing:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteKing.jpg") ;
                                        break;
                                case wQueen:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteQueen.jpg") ;
                                        break;
                                case wBishop:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteBishop.jpg") ;
                                        break;
                                case wKnight:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteKnight.jpg") ;
                                        break;
                                case wRook:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhiteRook.jpg") ;
                                        break;
                                case wPawn:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/WhitePawn.jpg") ;
                                        break;
                                case bKing:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackKing.jpg") ;
                                        break;
                                case bQueen:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackQueen.jpg") ;
                                        break;
                                case bBishop:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackBishop.jpg") ;
                                        break;
                                case bKnight:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackKnight.jpg") ;
                                        break;
                                case bRook:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackRook.jpg") ;
                                        break;
                                case bPawn:
                                        chess_icon = gtk_image_new_from_file("./UCI_EECS22L_P1/src/BlackPawn.jpg") ;
                                        break;
                                default:
                                        break;

                        }
                        gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
                }
        }
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
        *g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
        *g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}

static void
print_hello (GtkWidget *widget,
     gpointer   data)
{
  g_print ("NUTTED!8==D~~~~~~~\n");
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
  int x1, y1 ;
  char words[MAX_MSGLEN] ;

  int coord_x, coord_y, grid_x, grid_y;

  struct BOARD *chess_board ;
  struct SQUARE *chess_piece ;
  struct SQUARE *piece_dest ;

  GdkModifierType state ;

  gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ;

  CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

  printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

  MoveTheKing(grid_x, grid_y);


    gtk_container_remove(GTK_CONTAINER(window), fixed) ;
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();

    /*set fixed*/

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ;

  return TRUE ;
}


void gui_gameplay_window()
{
int
main (int   argc,
      char *argv[])
{
  char str[MAX_MSGLEN];

  gtk_init(&argc, &argv) ;
  ResetBoard();

  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
  gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ;
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;


  /*register event handlers*/
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ;
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ;
  g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ;

  /*create a table and draw the board*/
  table = gtk_table_new (8, 8, TRUE) ;
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
  DrawBoard();

  fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
  gtk_container_add(GTK_CONTAINER(window), fixed) ;

//add button with new window2
        window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window2, "delete_event", G_CALLBACK(on_delete_event), NULL);
        gtk_container_set_border_width(GTK_CONTAINER(window2), 50);
        button = gtk_button_new_with_label("NUT!");
        g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
        gtk_container_add(GTK_CONTAINER(window2), button);
        gtk_widget_show(button);
        gtk_widget_show(window2);

  /*show the window*/
  gtk_widget_show_all(window) ;
  gtk_main() ;

  return 0 ;
}

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



