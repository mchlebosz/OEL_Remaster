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

button_t button_create_from_image(SDL_Renderer* renderer, char* path, int x, int y, int w, int h) {
	button_t button;
	button.renderer = renderer;
	button.is_selected = false;
	button.txt = IMG_LoadTexture(renderer, path);
	button.rect.x = x;
	button.rect.y = y;
	button.rect.w = w;
	button.rect.h = h;
	
	return button;
}

button_t button_create(SDL_Renderer* renderer, string s, int font_size, int x, int y, SDL_Color text_color) {
	label lb = label_create(renderer, font_size, s, text_color);
	button_t button;
	button.renderer = renderer;
	button.is_selected = false;
	button.txt = lb.texture;
	button.rect = lb.rect;
	button.rect.x = x;
	button.rect.y = y;
	return button;
}

void button_update(button_t* button, mouse_t* mouse) {
	int x = mouse->rect.x;
	int y = mouse->rect.y;
	button->is_selected = button->rect.x <= x && x <= button->rect.x + button->rect.w 
		&& button->rect.y <= y && y <= button->rect.y + button->rect.h;
}

void button_draw(button_t* button) {
	// SDL_SetRenderDrawColor(button->renderer, 125, 0, 125, 255); // fill button inside
	// SDL_RenderFillRect(button->renderer, &button->rect);

	SDL_RenderCopy(button->renderer, button->txt, NULL, &button->rect);
	
	// SDL_SetRenderDrawColor(button->renderer, 255, 255, 255, 255); // draw border
	// SDL_RenderDrawRect(button->renderer, &button->rect);
}


#endif // !BUTTON_H