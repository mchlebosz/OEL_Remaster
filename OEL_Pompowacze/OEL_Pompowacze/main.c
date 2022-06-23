// SDL2 Hello, World!
// This should display a pink screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "game.h"
#include "menu.h"
#include "mouse.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* args[])
{
	srand(time(NULL));
	//test();
	
	const uint8 max_fps = 165;
	const double max_frequency = 1.0 / (double)max_fps;
	
	FILE* log_file = fopen("logs.oel.txt", "wt");
	if (!log_file) log_file = stdout;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	

	SDL_Window* window = SDL_CreateWindow("OEL Pompowacze:Remake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mouse_t* mouse = (mouse_t*)malloc(sizeof(mouse_t));
	if (mouse == NULL) {
		log_f(log_file, "Error allocating memory for mouse\n");
		return 1;
	}
	*mouse = mouse_create(renderer);

	game_t game = { window, renderer, mouse, max_frequency };

	SDL_Color white1 = { 255,255,255 };
	SDL_Color pink1 = { 255,0,255 };
	SDL_Color red1 = { 255,0,0 };
	SDL_Color green1 = { 0,255,0 };
	SDL_Color blue1 = { 0,0,255 };
	SDL_Color yellow1 = { 255,255,0 };
	SDL_Color orange1 = { 255,165,0 };
	SDL_Color purple1 = { 128,0,128 };
	SDL_Color brown1 = { 165,42,42 };
	SDL_Color gray1 = { 128,128,128 };
	SDL_Color black1 = { 0,0,0 };
	SDL_Color internal_bg_color1 = { 91, 47, 115 };
	SDL_Color external_bg_color1 = { 143, 47, 101 };
	game._colors._white = white1;
	game._colors._pink = pink1;
	game._colors._red = red1;
	game._colors._green = green1;
	game._colors._blue = blue1;
	game._colors._yellow = yellow1;
	game._colors._orange = orange1;
	game._colors._purple = purple1;
	game._colors._brown = brown1;
	game._colors._gray = gray1;
	game._colors._black = black1;
	game._colors._internal_bg_color = internal_bg_color1;
	game._colors._external_bg_color = external_bg_color1;

	if (window == NULL) {
		SDL_Quit();
		log_f(log_file, "SDL_CreateWindow error: %s\n", SDL_GetError());
		exit(1);
	};
	
	

	game.logger = log_file;

	start_loop(&game);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	fclose(game.logger);
	SDL_Quit();
	return 0;
}