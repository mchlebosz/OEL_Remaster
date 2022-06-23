#include "menu_read_player_number.h"

int read_player_number(game_t* game) {
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	const string text = string_create_from_cstring("Podaj liczbe graczy! (2-4)");
	const label_t label = label_create(game->renderer, 40, text, white);

	SDL_Color bgcolor = { 91, 47, 115 };
	inputbox_t box = input_create(game->renderer, 36, SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, 120, 0, pink);

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
				int text_length = (int)string_size(&box.text);

				if (text_length == 1 && c == SDLK_RETURN) {
					running = false;
					break;
				}
				if (c == '\b') inputbox_update_text(&box, c);
				else if (text_length == 0 && '2' <= c && c <= '4') inputbox_update_text(&box, c);
				break;
			}
			}
		}

		inputbox_update(&box, game->mouse, mouse_click);
		game_background_draw(game);

		inputbox_draw(&box);

		SDL_Rect yellow_rect = { x, label.rect.y + 7, width, label.rect.h - 8 };
		SDL_SetRenderDrawColor(game->renderer, 204, 191, 69, 255);
		SDL_RenderFillRect(game->renderer, &yellow_rect);

		label_draw(&label, SCREEN_WIDTH / 2 - label.rect.w / 2, SCREEN_HEIGHT / 2 - label.rect.h / 2 - 20);
		mouse_draw(game->renderer, game->mouse);

		SDL_RenderPresent(game->renderer);
	}

	int count = atoi(string_data(&box.text));

	vector_free(&text);
	label_free(&label);
	inputbox_free(&box);

	return count;
}