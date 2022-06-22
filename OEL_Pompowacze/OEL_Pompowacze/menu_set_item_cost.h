#pragma once

#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "string.h"
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "inputbox.h"
#include "factories.h"

int menu_set_item_cost(game_t* game, SDL_Color bgcolor, const char* title) {

	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;

	double time = SDL_GetTicks();
	byte option = -1;
	bool running = true;

	const string text = string_create_from_cstring(title);
	const label_t label = label_create(game->renderer, 36, text, white);
	inputbox_t input = input_create(game->renderer, 36, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 10, 180, 15, black);

	const SDL_Rect rect = { 50,100,SCREEN_WIDTH - 100, 25 };

	while (running) {
		// refreshrate cap
		double delta = (SDL_GetTicks() - time) / 1000.0;
		if (delta < game->max_frequency) continue;
		time = SDL_GetTicks();

		mouse_update(game->mouse);
		bool mouse_click = false;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				SDL_Quit();
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_click = true;
				break;
			case SDL_KEYDOWN: {
				char c = get_pressed_key(event);
				int text_length = string_size(&input.text);

				if (text_length > 0 && c == SDLK_RETURN) {
					running = false;
					break;
				}
				if (c == '\b') inputbox_update_text(&input, c);
				else if ('0' <= c && c <= '9') inputbox_update_text(&input, c);
				break;
			}

			}
		}
		inputbox_update(&input, game->mouse, mouse_click);


		SDL_SetRenderDrawColor(game->renderer, 128, 128, 128, 255);
		SDL_RenderClear(game->renderer);

		SDL_Rect subbg_rect = { x, y, width, height };
		SDL_SetRenderDrawColor(game->renderer, bgcolor.r * 3 / 2, bgcolor.g * 3 / 2, bgcolor.b * 3 / 2, 255);
		SDL_RenderFillRect(game->renderer, &subbg_rect);

		SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(game->renderer, &rect);
		SDL_RenderDrawRect(game->renderer, &rect);
		inputbox_draw(&input);
		label_draw(&label, SCREEN_WIDTH / 2 - label.rect.w / 2, SCREEN_HEIGHT / 2 - 35);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

	label_free(&label);
	vector_free(&text);
	
	int res = atoi(string_data(&input.text));
	inputbox_free(&input);
	return res;
}