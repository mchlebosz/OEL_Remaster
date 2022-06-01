// SDL2 Hello, World!
// This should display a pink screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL.h>
#include <SDL_ttf.h>


#include <stdio.h>
#include "string.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void print_text(SDL_Surface* screen, int x, int y, int size, SDL_Color front, string* s) {
	TTF_Font* sans = TTF_OpenFont("Sans.ttf", size);

	SDL_Surface* textSurface = TTF_RenderText_Blended(sans, string_begin(s), front);

	SDL_Rect textLocation = { x, y, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(sans);
}

int main(int argc, char* args[])
{
	//SDL_DisplayMode dm;
	//SDL_GetCurrentDisplayMode(0, &dm);
	

	SDL_Renderer* renderer;
	SDL_Window* window; 
	SDL_Surface* screen = NULL;
	SDL_Texture* texture = NULL;


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	int rc = SDL_CreateWindowAndRenderer(
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer
	);

	//window = SDL_CreateWindow(
	//	"An SDL Window", // window title
	//	SDL_WINDOWPOS_UNDEFINED, // initial x position
	//	SDL_WINDOWPOS_UNDEFINED, // initial y position
	//	SCREEN_WIDTH, // width, in pixels
	//	SCREEN_HEIGHT, // height, in pixels
	//	SDL_WINDOW_FULLSCREEN_DESKTOP // flags - see below
	//);
	//
	//if (window == NULL) {
	//	// In the case that the window could not be made...
	//	printf("Could not create window: %s\n", SDL_GetError());
	//	return 1;
	//}



	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(1);
	};

	screen = SDL_CreateRGBSurface(0, 1920, 1080, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "OEL: Pompowacze, Remaster");

	//SDL_Delay(2000);
	//SDL_DestroyWindow(window);
	SDL_Color white = { 255,255,255 };
	SDL_Color pink = { 255,0,255 };
	SDL_Color red = { 255,0,0 };
	SDL_Color green = { 0,255,0 };
	SDL_Color blue = { 0,0,255 };
	SDL_Color yellow = { 255,255,0 };
	SDL_Color orange = { 255,165,0 };
	SDL_Color purple = { 128,0,128 };
	SDL_Color brown = { 165,42,42 };
	SDL_Color gray = { 128,128,128 };
	
	Uint32 black_map = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	Uint32 white_map = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	Uint32 grey_map = SDL_MapRGB(screen->format, 0x80, 0x80, 0x80);
	SDL_FillRect(screen, NULL, grey_map);

	string s = string_create();
	string_append_range(&s, "To ten, Tytul czy cos: OEL Pompowacze");
	print_text(screen, 50, 50, 24, red, &s);
	s = string_create();
	string_append_range(&s, "Jest totalnie chujowy antyaliasing");
	print_text(screen, 50, 100, 24, red, &s);

	
	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture

	SDL_Delay(3000);


	// Don't forget to free your surface and texture

	//Have we done it?


	SDL_Quit();
	return 0;
}