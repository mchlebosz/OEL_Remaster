#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "mouse.h"

struct game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	mouse_t* mouse;
	double max_frequency; //  (1/max_fps)
};

typedef struct game game_t;

//
// colors
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
SDL_Color black = { 0,0,0 };

void game_background_draw(game_t* game) {
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	SDL_SetRenderDrawColor(game->renderer, 143, 47, 101, 255);
	SDL_RenderClear(game->renderer);
	SDL_Rect subbg_rect = { x, y, width, height };
	SDL_SetRenderDrawColor(game->renderer, 91, 47, 115, 255);
	SDL_RenderFillRect(game->renderer, &subbg_rect);
}

#endif // GAME_H