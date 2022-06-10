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

#endif // GAME_H