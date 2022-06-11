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

typedef struct label label;

label label_create(SDL_Renderer* renderer, int font_size, string s, SDL_Color color) {
	TTF_Font* sans = TTF_OpenFont("Sans.ttf", font_size);
	SDL_Surface* surface = TTF_RenderText_Solid(sans, string_data(&s), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	label res;
	res.renderer = renderer;
	res.text = string_create_from_cstring(string_data(&s));
	res.texture = texture;
	SDL_QueryTexture(res.texture, NULL, NULL, &res.rect.w, &res.rect.h);
	TTF_CloseFont(sans);
	return res;
}

void label_draw(label* label, int x, int y) {
	label->rect.x = x;
	label->rect.y = y;
	SDL_RenderCopy(label->renderer, label->texture, NULL, &label->rect);
}

void label_free(label* label) {
	SDL_DestroyTexture(label->texture);
	vector_free(&label->text);
}

#endif // !LABEL_H
