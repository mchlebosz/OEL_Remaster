//
// button.h

#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "mouse.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

struct button {
	SDL_Texture* txt;
	SDL_Rect rect;
	bool is_selected;
};

typedef struct button button_t;

button_t button_create(SDL_Renderer* renderer, char* path, int x, int y, int w, int h) {
	button_t button;
	button.is_selected = false;
	button.txt = IMG_LoadTexture(renderer, path);
	button.rect.x = x;
	button.rect.y = y;
	button.rect.w = w;
	button.rect.h = h;
	
	
	return button;
}

void button_update(button_t* button, mouse_t* mouse) {
	button->is_selected = SDL_HasIntersection(&button->rect, &mouse->rect);
}

void button_draw(SDL_Renderer* renderer, button_t* button) {
	SDL_RenderCopy(renderer, button->txt, NULL, &button->rect);
}


#endif // !BUTTON_H