// SDL2 Hello, World!
// This should display a pink screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "game.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "string.h"
#include "inputbox.h"
#include "predictions_graph.h"

void test() {



	
	exit(1);
}

int main(int argc, char* args[])
{
	srand(time(NULL));
	//test();
	
	const uint8 max_fps = 165;
	const double max_frequency = 1.0 / (double)max_fps;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	

	SDL_Window* window = SDL_CreateWindow("OEL Pompowacze:Remake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mouse_t* mouse = (mouse_t*)malloc(sizeof(mouse_t));
	if (mouse == NULL) {
		printf("Error allocating memory for mouse\n");
		return 1;
	}
	*mouse = mouse_create(renderer);

	game_t game = { window, renderer, mouse, max_frequency };

	if (window == NULL) {
		SDL_Quit();
		printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		exit(1);
	};

	
	
	/*
	SDL_Texture* txt = IMG_LoadTexture(renderer, "test.png");
	if (!txt) {
		printf("IMG_LoadTexture error: %s\n", IMG_GetError());
		exit(1);
	}
	*/
	
	start_loop(&game);
	
	SDL_Quit();
	return 0;
}