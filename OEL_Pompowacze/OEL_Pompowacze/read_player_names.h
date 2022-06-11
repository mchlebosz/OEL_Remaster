#pragma once

#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "string.h"
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "inputbox.h"

vector read_player_names(game_t* game, int player_count) {

	int p_num = 1;
	vector players = svector_create();

	SDL_Color bgcolor = { 91, 47, 115 };
	inputbox_t box = input_create(game->renderer, 36, SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, 120, NULL, pink);
	box.active = true;
	string text = string_create_from_cstring("nazwa gracza nr 1");
	label label = label_create(game->renderer, 40, text, white);
	
	bool running = true;
	double time = SDL_GetTicks();
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
				int text_length = string_size(&box.text);

				if (text_length > 0 && c == SDLK_RETURN) {
					svector_push(&players, box.text);
					if (p_num == player_count) {
						running = false;
						break;
					}
					p_num++;
					string_remove(&text, string_size(&text) - 1);
					string_append(&text, '0' + p_num);
					label_free(&label);
					label = label_create(game->renderer, 40, text, white);
					inputbox_free(&box);
					box = input_create(game->renderer, 36, SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, 120, NULL, pink);
					box.active = true;
				}
				if (c == SDLK_BACKSPACE) inputbox_update_text(&box, c);
				else if (text_length < 12) inputbox_update_text(&box, c);
				break;
			}
			}
		}

		inputbox_update(&box, game->mouse, mouse_click);
		SDL_SetRenderDrawColor(game->renderer, 91, 47, 115, 255);
		SDL_RenderClear(game->renderer);

		label_draw(&label, SCREEN_WIDTH / 2 - label.rect.w / 2, SCREEN_HEIGHT / 2 - label.rect.h / 2 - 20);

		inputbox_draw(&box);
		
		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}
	
	label_free(&label);
	vector_free(&text);
	inputbox_free(&box);

	return players;
}