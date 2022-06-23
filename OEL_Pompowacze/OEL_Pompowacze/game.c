#include "game.h"

void game_background_draw(game_t* game) {
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	SDL_SetRenderDrawColor(game->renderer, 143, 47, 101, 255);
	SDL_RenderClear(game->renderer);
	SDL_Rect subbg_rect = { x, y, width, height };
	SDL_SetRenderDrawColor(game->renderer, 91, 47, 115, 255);
	SDL_RenderFillRect(game->renderer, &subbg_rect);
}

int round1000(int x) {
	const float tmp = x / 1000.f;
	const float rounded = round(tmp);
	return (int)(rounded * 1000);
}

void log_f(FILE* file, const char* const _Format, ...) {
	va_list args;
	va_start(args, _Format);
	vfprintf(stdout, _Format, args);
	vfprintf(file, _Format, args);
	va_end(args);
}