#pragma once

#ifndef LABEL_H
#define LABEL_H

#include "string.h"
#include <SDL.h>
#include <SDL_ttf.h>


struct label {
	SDL_Renderer* renderer;
	string text;
	SDL_Texture* texture;
	SDL_Rect rect;
};

typedef struct label label_t;

label_t label_create(SDL_Renderer* renderer, int font_size, string s, SDL_Color color);

void label_draw(const label_t* label, int x, int y);

void label_draw_on_rect(label_t* label, int x, int y, SDL_Color bg_color);

void label_free(label_t* label);

#endif // !LABEL_H
