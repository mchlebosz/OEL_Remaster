//
// button.h

#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "mouse.h"
#include "label.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

struct button {
	SDL_Renderer* renderer;
	SDL_Texture* txt;
	SDL_Rect rect;
	bool is_selected;
};

typedef struct button button_t;

button_t button_create_from_image(SDL_Renderer* renderer, char* path, int x, int y, int w, int h);

button_t button_create(SDL_Renderer* renderer, string s, int font_size, int x, int y, SDL_Color text_color);

void button_update(button_t* button, mouse_t* mouse);

void button_draw(const button_t* button);

void button_free(const button_t* button);

#endif // !BUTTON_H