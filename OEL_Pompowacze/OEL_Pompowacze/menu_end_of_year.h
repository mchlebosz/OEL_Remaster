#pragma once

#include <SDL.h>
#include "label.h"
#include "game.h"
#include "vector.h"
#include "extended_vector.h"
#include <stdlib.h>

void end_of_year_screen(game_t* game, player_t* players, int player_count) {
	const string title = string_create_from_cstring("PRZEWIDYWANE CENY ROPY NA RYNKU");
	const string subtitle = string_create_from_cstring("PRZYCI$NIJ DOWOLNY KLAWISZ");
	const label_t label = label_create(game->renderer, 38, title, white);
	const label_t sublabel = label_create(game->renderer, 28, subtitle, white);

	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;

	int total_time = 0;
	double time_start = SDL_GetTicks();
	double time = time_start;
	while (true) {
		// refreshrate cap
		double delta = (SDL_GetTicks() - time) / 1000.0;
		if (delta < game->max_frequency) continue;
		time = SDL_GetTicks();

		mouse_update(game->mouse);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_Quit();
				exit(0);
			}
			if (event.type == SDL_KEYDOWN) {
				label_free(&label);
				label_free(&sublabel);
				vector_free(&title);
				vector_free(&subtitle);
				return;
			}
		}

	}
}