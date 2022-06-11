#pragma once

#include "game.h"
#include "vector.h"
#include "extended_vector.h"
#include <stdlib.h>

vector generate_prices(float min_price, float max_price) {
	vector prices = fvector_create();
	
	float mean_price = (min_price + max_price) / 2;
	fvector_push(&prices, mean_price);
	
	for (int i = 1; i < 20; ++i) {
		// create normal distribution number
		float nd = 0.f;
		for (int j = 0; j < 12; ++j) {
			nd += (rand() % 10) / 10.f;
		}
		// create modifier
		float modifier = ((rand() % (int)(max_price * 100.f)) / 100.f + min_price / 3.f - mean_price / 2.f) + (nd * mean_price / 2.f) / 2.f;
		
		// create new price
		float new_price = fvector_get(&prices, i - 1) + modifier;

		if (new_price < min_price) {
			new_price = min_price + fabs(modifier / 2.f);
		} else if (new_price > max_price) {
			new_price = max_price - fabs(modifier / 2.f);
		}
		new_price = roundf(new_price * 10) / 10;
		fvector_push(&prices, new_price);
	}
	return prices;
}

void prices_draw(SDL_Renderer* renderer, vector* prices) {
	for (int i = 0; i < prices->size; ++i) {
		int w = 25;
		int x = SCREEN_WIDTH / 2 - prices->size * w / 2 + i * w;
		int y = SCREEN_HEIGHT / 2 + 180;
		int h = fvector_get(prices, i) * -90;
		SDL_Rect rect = {x, y, w, h};
		SDL_SetRenderDrawColor(renderer, 143, 47, 101, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void prices_loop(game_t* game, vector* prices) {
	int total_time = 0;
	double time_start = SDL_GetTicks();
	double time = time_start;
	while (true) {
		// refreshrate cap
		double delta = (SDL_GetTicks() - time) / 1000.0;
		if (delta < game->max_frequency) continue;
		time = SDL_GetTicks();
		if (time - time_start > 3000) {
			break;
		}
		mouse_update(game->mouse);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {}

		SDL_SetRenderDrawColor(game->renderer, 91, 47, 115, 255);
		SDL_RenderClear(game->renderer);

		// draw graph
		prices_draw(game->renderer, prices);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}
}