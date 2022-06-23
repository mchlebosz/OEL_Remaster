#pragma once

#ifndef GAME_H
#define GAME_H
#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define GAME_LENGTH 28
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "mouse.h"
#include "factories.h"

#pragma warning(disable:6386)
#pragma warning(disable:6385)

//
// colors
struct colors {
	SDL_Color _white;
	SDL_Color _pink;
	SDL_Color _red;
	SDL_Color _green;
	SDL_Color _blue;
	SDL_Color _yellow;
	SDL_Color _orange;
	SDL_Color _purple;
	SDL_Color _brown;
	SDL_Color _gray;
	SDL_Color _black;
	SDL_Color _internal_bg_color;
	SDL_Color _external_bg_color;
};
typedef struct colors colors_t;

struct game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	mouse_t* mouse;
	double max_frequency; //  (1/max_fps)
	FILE* logger;
	colors_t _colors;
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

void game_background_draw(game_t* game);

int round1000(int x);

void log_f(FILE* file, const char* const _Format, ...);

#endif // GAME_H