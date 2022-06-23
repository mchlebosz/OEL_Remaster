//
// mouse.h

#pragma once

#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

struct mouse {
	SDL_Texture* txt;
	SDL_Rect rect;
	SDL_Rect point;
};

typedef struct mouse mouse_t;

mouse_t mouse_create(SDL_Renderer* renderer) {
	mouse_t m;
	m.txt = IMG_LoadTexture(renderer, "cursor.png");
	m.rect.w = 25;
	m.rect.h = 25;
	m.point.w = 1;
	m.point.h = 1;
	SDL_ShowCursor(false);
	return m;
}

void mouse_update(mouse_t* m) {
	SDL_GetMouseState(&m->rect.x, &m->rect.y);
	m->point.x = m->rect.x;
	m->point.y = m->rect.y;
}

void mouse_draw(SDL_Renderer* renderer, mouse_t* m) {
	SDL_RenderCopy(renderer, m->txt, NULL, &m->rect);
}

void mouse_free(mouse_t* m) {
	SDL_DestroyTexture(m->txt);
}
#endif // !MOUSE_H
