#include "predictions_graph.h"

vector _generate_prices(float min_price, float max_price) {
	vector prices = fvector_create();

	float mean_price = (min_price + max_price) / 2;
	fvector_push(&prices, mean_price);

	for (int i = 1; i < GAME_LENGTH; ++i) {
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
			new_price = min_price + (float)fabs(modifier / 2.f);
		}
		else if (new_price > max_price) {
			new_price = max_price - (float)fabs(modifier / 2.f);
		}
		new_price = roundf(new_price * 10) / 10;
		fvector_push(&prices, new_price);
	}
	return prices;
}

void _prices_draw(SDL_Renderer* renderer, vector* prices) {
	for (int i = 0; i < prices->size; ++i) {
		int w = 640 / GAME_LENGTH;
		int x = SCREEN_WIDTH / 2 - prices->size * w / 2 + i * w;
		int y = SCREEN_HEIGHT / 2 + 220;
		int h = (int)(fvector_get(prices, i) * -200);
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderDrawColor(renderer, 143, 47, 101, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void draw_predicted_prices_screen(game_t* game, vector* prices) {
	const string title = string_create_from_cstring("PRZEWIDYWANE CENY ROPY NA RYNKU");
	const string subtitle = string_create_from_cstring("PRZYCI$NIJ DOWOLNY KLAWISZ");
	const label_t label = label_create(game->renderer, 38, title, white);
	const struct label sublabel = label_create(game->renderer, 28, subtitle, white);

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

		game_background_draw(game);

		// draw graph
		_prices_draw(game->renderer, prices);
		SDL_Rect yellow_rect = { x, y, width, label.rect.h - 15 };
		SDL_SetRenderDrawColor(game->renderer, 204, 191, 69, 255);
		SDL_RenderFillRect(game->renderer, &yellow_rect);

		label_draw(&label, SCREEN_WIDTH / 2 - label.rect.w / 2, 10);
		label_draw(&sublabel, SCREEN_WIDTH / 2 - sublabel.rect.w / 2, label.rect.h);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}
}