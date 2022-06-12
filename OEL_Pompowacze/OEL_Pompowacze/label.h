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

label_t label_create(SDL_Renderer* renderer, int font_size, string s, SDL_Color color) {
	TTF_Font* sans = TTF_OpenFont("Sans.ttf", font_size);
	SDL_Surface* surface = TTF_RenderText_Solid(sans, string_data(&s), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	label_t res;
	res.renderer = renderer;
	res.text = string_copy(&s);
	res.texture = texture;
	SDL_QueryTexture(res.texture, NULL, NULL, &res.rect.w, &res.rect.h);
	TTF_CloseFont(sans);
	return res;
}

void label_draw(label_t* label, int x, int y) {
	label->rect.x = x;
	label->rect.y = y;
	SDL_RenderCopy(label->renderer, label->texture, NULL, &label->rect);
}

void label_draw_on_rect(label_t* label, int x, int y, SDL_Color bg_color) {
	label->rect.x = x;
	label->rect.y = y;
	SDL_Rect rect = label->rect;
	rect.h = rect.h * 8 / 10;
	rect.y = rect.y + rect.h / 7;
	SDL_SetRenderDrawColor(label->renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
	SDL_RenderFillRect(label->renderer, &rect);
	SDL_RenderCopy(label->renderer, label->texture, NULL, &label->rect);
}

void label_free(label_t* label) {
	SDL_DestroyTexture(label->texture);
	vector_free(&label->text);
}

#endif // !LABEL_H
