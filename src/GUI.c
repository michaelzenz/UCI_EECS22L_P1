


#include"GUI.h"

#define xy21d(x,y) (y*8+x)

/*Global Variables */

GtkWidget *window ;
GtkWidget *image;
GtkWidget *layout;
GtkWidget *fixed;
GtkWidget *chess_icon;
GtkWidget *table;
GtkWidget *button;
GtkWidget *vbox;

GdkPixbuf *main_menu_pixbuf = NULL;
GdkPixbuf *HvC_pixbuf = NULL;
GdkPixbuf *HvH_pixbuf = NULL;
GdkPixbuf *CvC_pixbuf = NULL;
GdkPixbuf *Background_pixbuf=NULL;

//Look up table
char *str_square[4]={"./res/WhiteSquare","./res/BlackSquare", "./res/SelectedSquare", "./res/LegalSquare"};
char *str_color[2]={"White","Black"};
char *str_piece[7]={"EmptySpace.jpg", "Pawn.jpg", "Knight.jpg", "Rook.jpg",  "Bishop.jpg", "Queen.jpg", "King.jpg"};

char *main_menu_path="res/MainMenu.png";
char *HvC_Menu_path="res/HvC_Menu.png";
char *Background_path="res/background.png";

// char icon[20];
// strcat(square[0]);
// strcat(icon,color[0]);
// strcat(icon,piece[0]);

// icon=="WhitePawnWhiteS.jpg";

GdkPixbuf *load_pixbuf_from_file (const char *filename)
{
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (filename, &error);
 
    if (pixbuf == NULL)
    {
        g_print ("Error loading file: %d : %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }
    return pixbuf;
}



void gui_render()
{
    gdk_threads_enter();
    gtk_main() ;
    gdk_threads_leave();
}

//Here you init the window and start the main loop
//Don`t do anything to this part if you don`t know what it`s doing
int gui_init_window(int argc, char*argv[])
{
    gtk_init(&argc, &argv) ;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
    gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
    gtk_window_set_title(GTK_WINDOW(window), "King Me!") ; 
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    //fill_with_content (vbox);

    gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK);


    gdk_threads_init();
#ifdef ANTEDILUVIAN
	g_thread_create((GThreadFunc)gui_render,NULL,TRUE,NULL);
#else
    g_thread_new("render",(GThreadFunc)gui_render,NULL);
#endif
}

void gui_init(GameState *gameState,Player player_arr[2])
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
    gui_gameplay_window(gameState);
}






static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer data)
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

//The callback for main menu window
gint main_menu_callback (GtkWidget *widget, GdkEvent  *event, gpointer data)
{
    int x, y;
    GdkModifierType state;
    gdk_window_get_pointer(widget->window,&x,&y,&state);
    int *GameMode=(int*)data;
    if(x>715&&x<879&&y>238&&y<264)
    {
        *GameMode=GameMode_HvC;
    }
    else if(x>702&&x<887&&y>287&&y<319)
    {
        *GameMode=GameMode_HvH;
    }
    else if(x>630&&x<958&&y>346&&y<367)
    {
        *GameMode=GameMode_CvC;
    }
    printf("GameMode:%d\n",*GameMode);
}

//draw the main menu and set callback
int gui_main_menu()
{
    gdk_threads_enter();//this is important, before you call any gtk_* or g_* or gdk_* functions, call this function first
    main_menu_pixbuf=load_pixbuf_from_file(main_menu_path);
    main_menu_pixbuf=gdk_pixbuf_scale_simple(main_menu_pixbuf,WINDOW_WIDTH,WINDOW_HEIGHT,GDK_INTERP_BILINEAR);
    
    image = gtk_image_new_from_pixbuf(main_menu_pixbuf);
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    int GameMode=0;
    gulong handlerID=g_signal_connect(window, "button_press_event", G_CALLBACK(main_menu_callback), &GameMode);
    gtk_widget_show_all(window);
    gdk_threads_leave();//after you finich calling gtk functions, call this
    while(GameMode==0)sleep(1);//must call sleep to release some cpu resources for gtk thread to run
    gdk_threads_enter();//again, you know what I am gonna say
    g_signal_handler_disconnect(window,handlerID);
    gdk_threads_leave();
    return GameMode;
}




//here you use window pointer to draw player menu
//bind an event to listen to the click
//then use a while loop to wait for the user click
//after that return the GameMode
//WARNING: you must use sleep(10) in your main loop
//because gtk creates a new thread to render the window
//thus you must let the main thread release some cpu resource for it to run

//WARNING: Don`t forget to unbind the event to click

/**************/
//Because the Callback of gtk only take one variable, so you can create a new struct

typedef struct _PlayerOptions{
    Player *player_arr;
    unsigned char play;
}PlayerOptions;

gint HvC_menu_callback (GtkWidget *widget, GdkEvent  *event, gpointer data)
{
    int x, y;
    GdkModifierType state;
    gdk_window_get_pointer(widget->window,&x,&y,&state);
    PlayerOptions *options=(PlayerOptions*)data;
    Player *player_arr=options->player_arr;
    printf("x:%d, y:%d\n",x,y);
    
}

void gui_player_HvC_menu(Player* player_arr)
{
    PlayerOptions options;
    options.player_arr=player_arr;
    options.play=0;

    gdk_threads_enter();
    HvC_pixbuf=load_pixbuf_from_file(HvC_Menu_path);
    HvC_pixbuf=gdk_pixbuf_scale_simple(HvC_pixbuf,WINDOW_WIDTH,WINDOW_HEIGHT,GDK_INTERP_BILINEAR);
    
    image = gtk_image_new_from_pixbuf(HvC_pixbuf);
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
    gulong handlerID=g_signal_connect(window, "button_press_event", G_CALLBACK(HvC_menu_callback), &options);
    gtk_widget_show_all(window);
    gdk_threads_leave();
    while(options.play==0)sleep(1);
    gdk_threads_enter();
    g_signal_handler_disconnect(window,handlerID);
    gdk_threads_leave();
}

void gui_player_HvH_menu(Player* player_arr)
{

}

void gui_player_CvC_menu(Player* player_arr)
{

}

void DrawBoard(GameState *gamestate)
{

    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT);

	int x, y;
	char path[50];
	for(int i = 0 ; i< 64; i++)
    {
        memset(path,'\0',sizeof(path));
        x = (i)%8;
        y = (i)/8;
        
        strcat(path,str_square[(x+y)%2]);

        if(gamestate->board[i]==BLANK)strcat(path,str_piece[BLANK]);
        else
        {
            int color=gamestate->board[i]/abs(gamestate->board[i]);
            int colorID=MAX(color*-1,0);
            strcat(path, str_color[colorID]);
            strcat(path,str_piece[abs(gamestate->board[i])]);
        }

        chess_icon=gtk_image_new_from_file(path);
        gtk_table_attach(GTK_TABLE(table), chess_icon, x, x+1, y, y+1, GTK_FILL, GTK_FILL, 0, 0);
    }

    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), table, BOARD_BORDER_LEFT, BOARD_BORDER_UP);
    gtk_container_add(GTK_CONTAINER(layout), fixed);
    gtk_widget_show_all(window);

}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
        *g_x = (c_x - BOARD_BORDER_LEFT) / SQUARE_SIZE;
        *g_y = (c_y - BOARD_BORDER_UP) / SQUARE_SIZE;
}


//selects piece with click
void Select_Piece(GtkWidget *widget, GdkEvent *event, gpointer data){

	int pixelX, pixelY, gridX, gridY, index, piece;
	
	//IDK what this is
 	GdkModifierType state;
	
	//gets the location of where the person clicked
	gdk_window_get_pointer(widget->window, &pixelX, &pixelY, &state);

	//change pixel to xy coordinates
	CoordToGrid(pixelX, pixelY, &gridX, &gridY);

	//change xy to 1D and label as index
	old_index = xy21d(gridX, gridY);

	//gets info of what piece is on that space
	//selected_piece = gameState->board[index];
}

//selects target space with click
void Select_Movement(GtkWidget *widget, GdkEvent *event, gpointer data)
{

	int pixelX, pixelY, gridX, gridY, index, piece;
	
	//IDK what this is
 	GdkModifierType state;
	
	//gets the location of where the person clicked
	gdk_window_get_pointer(widget->window, &pixelX, &pixelY, &state);

	//change pixel to xy coordinates
	CoordToGrid(pixelX, pixelY, &gridX, &gridY);

	//change xy to 1D and label as index
	new_index = xy21d(gridX, gridY);
}

//checks if move selection is legal
void Legal_Move_Check(GameState *gameState){
	//idk how our move list works yet
}

//Moves the selected Piece
void Move_Piece(GameState *gameState){
	
	//moves piece to new space
	gameState->board[new_index] = selected_piece;
	//erases piece from old position
	gameState->board[old_index] = 0;
	//update board, idk if this should be here or outside the function
	DrawBoard(gameState);
}


void gui_gameplay_window(GameState *gameState)
{
	/*create a table and draw the board*/
    gdk_threads_enter();//this is important, before you call any gtk_* or g_* or gdk_* functions, call this function first
    
    Background_pixbuf=load_pixbuf_from_file(Background_path);
    Background_pixbuf=gdk_pixbuf_scale_simple(Background_pixbuf,WINDOW_WIDTH,WINDOW_HEIGHT,GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(Background_pixbuf);
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    DrawBoard(gameState);
//accept mouse press
    gdk_threads_leave();

    //when mouse presses window callback (TBD)
  	//g_signal_connect(window, "button_press_event", G_CALLBACK( TBD ), NULL) ;
}

int check_MoveMade=0;
int check_legal_start=0;
int move_start=-1;
int move_end=-1;
vector cur_legal_moves;

void gui_play_callback(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    int pixelX, pixelY, gridX, gridY, index, piece;
    GameState *gameState=(GameState*)data;
	
	//IDK what this is
 	GdkModifierType state;
	
	//gets the location of where the person clicked
	gdk_window_get_pointer(widget->window, &pixelX, &pixelY, &state);

	//change pixel to xy coordinates
	CoordToGrid(pixelX, pixelY, &gridX, &gridY);
    int pos=gridY*8+gridX;

    printf("pX: %d, pY: %d, gX: %d, gY: %d\n",pixelX,pixelY,gridX,gridY);

    if(!check_legal_start)
    {
        int move_vector_cnt=gameState->moves_vector_cnt;
        for(int i=0;i<move_vector_cnt;i++)
        {
            if(pos==gameState->container[i].pos)
            {
                cur_legal_moves=gameState->container[i].legal_moves;
                int vector_cnt=cur_legal_moves.count;
                for(int i=0;i<vector_cnt;i++)
                {
                    
                }
                check_legal_start=1;
                move_start=pos;
                break;
            }
        }
    }
    else 
    {
        if(vector_contain(&cur_legal_moves,pos))
        {
            move_end=pos;
            check_MoveMade=1;
        }
        else
        {
            check_legal_start=0;
            move_end=-1;
            move_start=-1;
        }
        
    }
    
    
}

//don`t worry about this part first
int gui_play(GameState *gameState,Player *player)
{
    env_check_end(gameState,player);
	gdk_threads_enter();
    gulong handlerID=g_signal_connect(window, "button_press_event", G_CALLBACK(gui_play_callback), gameState);
    gdk_threads_leave();
    while(check_MoveMade==0){
        sleep(1);
    }
    gdk_threads_enter();
    g_signal_handler_disconnect(window,handlerID);
    gdk_threads_leave();
    env_play(gameState,player,move_start,move_end);
    move_start=-1;
    move_start=-1;
    check_legal_start=0;
    check_MoveMade=0;
    env_free_container(gameState);
  	return 0 ;

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
    gdk_threads_enter();//this is important, before you call any gtk_* or g_* or gdk_* functions, call this function first
    

    gtk_container_remove(GTK_CONTAINER(layout), fixed) ; 
    
    DrawBoard(gameState);

    gdk_threads_leave();
}

void gui_checkmate_window(int winner)
{
  /*register event handlers*/
//   g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ;

}


