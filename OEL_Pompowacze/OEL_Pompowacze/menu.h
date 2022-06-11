#pragma once

#ifndef MENU_H
#define MENU_H

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
#include "menu_read_player_number.h"
#include "predictions_graph.h"

void start_loop(game_t* game) {
	vector pred = generate_prices(1, 4);
	prices_loop(game, &pred);
	
	const int player_number = read_player_number(game);
	printf("%d", player_number);
	bool running = true;
	double time = SDL_GetTicks();

	string s = string_create_from_cstring("dodaj gracza!");
	button_t b = button_create(game->renderer, s, 30, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, green);
	inputbox_t box = input_create(game->renderer, 26, 70, 70, 100, 100, green);

	while (running) {
		// refreshrate cap
		double delta = (SDL_GetTicks() - time) / 1000.0;
		if (delta < game->max_frequency) continue;
		time = SDL_GetTicks();

		mouse_update(game->mouse);

		// handle events
		bool mouse_click = false;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_click = true;
				break;
			case SDL_KEYUP: {
				char c = get_pressed_key(event);

				inputbox_update_text(&box, c);
				break;
			}
			}
		}
		uint8_t* key = SDL_GetKeyboardState(0); // keys down



		button_update(&b, game->mouse);
		inputbox_update(&box, game->mouse, mouse_click);


		if (b.is_selected && mouse_click) {
			printf("button clicked\n");
		}

		if (box.active) {

		}


		// clear renderer
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
		SDL_RenderClear(game->renderer);

		button_draw(&b);
		inputbox_draw(&box);

		mouse_draw(game->renderer, game->mouse);

		SDL_RenderPresent(game->renderer);
	}
	SDL_DestroyTexture(b.txt);

}


#endif // MENU_H