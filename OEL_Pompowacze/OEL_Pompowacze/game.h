#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define GAME_LENGTH 32
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "mouse.h"
#include "factories.h"

#pragma warning(disable:6386)
#pragma warning(disable:6385)

struct game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	mouse_t* mouse;
	double max_frequency; //  (1/max_fps)
};

struct player {
	char* name;
	int money;
	factory_t* drill_fac[4];
	factory_t* pump_fac[3];
	factory_t* trucks_fac[3];
	factory_t* oil_fields[6];
	int drills;
	int pumps;
	int trucks;
	int oil;
};

typedef struct game game_t;
typedef struct player player_t;

//
// colors
const SDL_Color white = { 255,255,255 };
const SDL_Color pink = { 255,0,255 };
const SDL_Color red = { 255,0,0 };
const SDL_Color green = { 0,255,0 };
const SDL_Color blue = { 0,0,255 };
const SDL_Color yellow = { 255,255,0 };
const SDL_Color orange = { 255,165,0 };
const SDL_Color purple = { 128,0,128 };
const SDL_Color brown = { 165,42,42 };
const SDL_Color gray = { 128,128,128 };
const SDL_Color black = { 0,0,0 };
const SDL_Color internal_bg_color = { 91, 47, 115 };
const SDL_Color external_bg_color = { 143, 47, 101 };

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

inline int round1000(int x) {
	const float tmp = x / 1000.f;
	const float rounded = round(tmp);
	return (int)(rounded * 1000);
}

#endif // GAME_H