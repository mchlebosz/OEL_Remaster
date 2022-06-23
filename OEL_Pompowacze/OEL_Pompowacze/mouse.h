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

mouse_t mouse_create(SDL_Renderer* renderer);

void mouse_update(mouse_t* m);

void mouse_draw(SDL_Renderer* renderer, mouse_t* m);

void mouse_free(mouse_t* m);
#endif // !MOUSE_H
