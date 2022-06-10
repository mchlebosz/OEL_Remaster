#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include "game.h"
#include "string.h"
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "inputbox.h"

int read_player_number(game_t* game) {
	const string text = string_create_from_cstring("Podaj liczbe graczy! (2-4)");
	const label label = label_create(game->renderer, 40, text, purple);
	
	inputbox_t box = input_create(game->renderer, 26, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 10, 100, 100, green);

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
			case SDL_KEYUP: {
				char c = get_pressed_key(event);
				int text_length = string_size(&box.text);

				if (text_length == 1 && c == SDLK_RETURN) {
					return atoi(string_data(&box.text));
				}
				if (c == '\b') inputbox_update_text(&box, c);
				else if (text_length == 0 && '2' <= c && c <= '4') inputbox_update_text(&box, c);
				break;
			}
			}
		}

		inputbox_update(&box, game->mouse, mouse_click);
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
		SDL_RenderClear(game->renderer);

		inputbox_draw(&box);
		label_draw(&label, SCREEN_WIDTH / 2 - label.rect.w / 2, SCREEN_HEIGHT / 2 - label.rect.h / 2 - 20);
		mouse_draw(game->renderer, game->mouse);

		SDL_RenderPresent(game->renderer);
	}
}