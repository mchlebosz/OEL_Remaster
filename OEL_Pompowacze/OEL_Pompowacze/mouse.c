#include "mouse.h"

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