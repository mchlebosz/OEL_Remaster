// SDL2 Hello, World!
// This should display a pink screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include "mouse.h"
#include "button.h"
#include "string.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	SDL_Window* window = SDL_CreateWindow("OEL Pompowacze!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* screen = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	mouse_t mouse = mouse_create(renderer);

	if (window == NULL) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(1);
	};

	SDL_Rect rect = { 25, 25, 50, 50 };
	
	float x = rect.x;

	bool running = true;
	double time = SDL_GetTicks();
	
	SDL_Texture* txt = IMG_LoadTexture(renderer, "test.png");
	if (!txt) {
		printf("IMG_LoadTexture error: %s\n", IMG_GetError());
		exit(1);
	}
	
	//button_t button = button_create(renderer, "");
	

	while (running) {
		mouse_update(&mouse);
		double delta = (SDL_GetTicks() - time) / 1000.0;
		time = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}
		uint8_t* key = SDL_GetKeyboardState(0);
		

		if (key[SDL_SCANCODE_A]) {
			x += -100 * delta;
		}
		if (key[SDL_SCANCODE_D]) {
			x += 100 * delta;
		}
		rect.x = x;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 125, 0, 125, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderCopy(renderer, txt, NULL, &rect);
		SDL_RenderDrawRect(renderer, &rect);

		mouse_draw(renderer, &mouse);
		SDL_RenderPresent(renderer);
	}

	//SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_Delay(2000);
	//SDL_DestroyWindow(window);
	SDL_Color white = { 255,255,255 };
	Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	//SDL_FillRect(screen, NULL, black);

	string s = string_create();
	string_append_range(&s, "XDDD ez");
	print_text(screen, 50, 50, 24, white, &s);
	
	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);


	SDL_Delay(3000);


	// Don't forget to free your surface and texture


	SDL_Quit();
	return 0;
}