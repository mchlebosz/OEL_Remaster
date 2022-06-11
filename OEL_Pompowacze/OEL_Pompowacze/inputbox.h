#pragma once

#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SDL.h>

#include "game.h"
#include "label.h"
#include "string.h"

struct inputbox {
	label lb;
	string text;
	bool active;
	int font_size;
	SDL_Color color;
	SDL_Rect rect;
};

typedef struct inputbox inputbox_t;


inputbox_t input_create(SDL_Renderer* renderer, int font_size, int x, int y, int w, int h, SDL_Color color) {
	inputbox_t input;
	input.text = string_create();
	input.lb = label_create(renderer, font_size, input.text, white);
	input.active = false;
	input.lb.rect.x = x;
	input.lb.rect.y = y;
	input.rect.w = w;
	input.rect.h = font_size + 10;
	input.rect.x = x;
	input.rect.y = y;
	input.font_size = font_size;
	input.color = color;
	return input;
}

void inputbox_update_text(inputbox_t* inputbox, char key) {
	if (key == -1) return;
	if (inputbox->active) {
		if (key == SDLK_BACKSPACE) {
			int remove_index = string_size(&inputbox->text) - 1;
			if (remove_index >= 0)
				string_remove(&inputbox->text, remove_index);
		} else {
			string_append(&inputbox->text, key);
		}
		label_free(&inputbox->lb);
		SDL_Renderer* renderer = inputbox->lb.renderer;
		inputbox->lb = label_create(renderer, inputbox->font_size, inputbox->text, inputbox->color);
		inputbox->lb.rect.x = inputbox->rect.x;
		inputbox->lb.rect.y = inputbox->rect.y;
	}
}

void inputbox_update(inputbox_t* inputbox, mouse_t* mouse, bool mouse_click) {
	int x = mouse->rect.x;
	int y = mouse->rect.y;
	if (mouse_click) {
		inputbox->active = inputbox->rect.x <= x && x <= inputbox->rect.x + inputbox->rect.w
			&& inputbox->rect.y <= y && y <= inputbox->rect.y + inputbox->rect.h;
	}
}

void inputbox_draw(inputbox_t* inputbox) {
	label_draw(&inputbox->lb, inputbox->rect.x + 3, inputbox->rect.y);
	SDL_SetRenderDrawColor(inputbox->lb.renderer, 255, 255, 255, 255); // draw border
	SDL_RenderDrawRect(inputbox->lb.renderer, &inputbox->rect);
}

char get_pressed_key(SDL_Event event) {
	for (int i = 'a'; i <= 'z'; ++i) {
		if (event.key.keysym.sym == i) {
			return i;
		}
	}
	for (int i = '0'; i <= '9'; ++i) {
		if (event.key.keysym.sym == i) {
			return i;
		}
	}
	if (event.key.keysym.sym == SDLK_BACKSPACE) {
		return '\b';
	}
	if (event.key.keysym.sym == SDLK_RETURN) {
		return '\r';
	}
	return -1;
}

#endif // !INPUTBOX_H
