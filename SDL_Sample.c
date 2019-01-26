// SDL_DisplaySmiley.c: Extended code with event processing and a smiley!  ;-)
// RD, 01/17/13.

#include "stdlib.h"
#include "SDL/SDL.h"

//#define WAIT		// wait some time to show the image
#define EVENTS		// process events and wait for window close

int main(int argc, char *argv[])
{
	SDL_Surface *screen;	//This pointer will reference the backbuffer
	SDL_Surface *image;	//This pointer will reference our bitmap sprite
	SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite
	SDL_Rect src, dest;	//These rectangles will describe the source and destination regions of our blit
	int x;
#ifdef EVENTS
	SDL_Event event;	/* Event structure */
	int Running;
#endif

	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	//Set the video mode to a window of size 320 by 240 pixels with 32 bits per pixel
	screen = SDL_SetVideoMode(320, 240, 32, SDL_ANYFORMAT /*SDL_DOUBLEBUF | SDL_FULLSCREEN*/);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	//Load the bitmap into a temporary surface, and check for success
	temp = SDL_LoadBMP("res/smiley.bmp");
	if (temp == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}
	
	//Convert the surface to the appropriate display format
	image = SDL_DisplayFormat(temp);
	
	return 0;

	/****************/
	Modify here
	/****************/
/****************/
/****************/
/****************/
/****************/
/****************/
}
