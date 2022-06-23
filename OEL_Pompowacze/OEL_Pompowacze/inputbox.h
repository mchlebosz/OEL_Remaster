#pragma once

#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SDL.h>

#include "game.h"
#include "label.h"
#include "string.h"

struct inputbox {
	label_t lb;
	string text;
	bool active;
	int font_size;
	SDL_Color color;
	SDL_Rect rect;
	SDL_Color border_color;
};

typedef struct inputbox inputbox_t;


inputbox_t input_create(SDL_Renderer* renderer, int font_size, int x, int y, int w, int h, SDL_Color color);

void inputbox_update_text(inputbox_t* inputbox, char key);

void inputbox_update(inputbox_t* inputbox, mouse_t* mouse, bool mouse_click);

void inputbox_draw(inputbox_t* inputbox);

void inputbox_free(inputbox_t* inputbox);

char get_pressed_key(SDL_Event event);

#endif // !INPUTBOX_H

