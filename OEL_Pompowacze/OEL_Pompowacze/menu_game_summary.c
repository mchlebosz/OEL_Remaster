#include "menu_game_summary.h"

void draw_game_summary(game_t* game, player_t* players, int player_count) {
	bool running = true;
	double time = SDL_GetTicks();
	const SDL_Color color = { 133, 122, 222 };

	string title = string_create_from_cstring("A OTO REZULTATY WALKI:");
	string s_player = string_create_from_cstring("GRACZ:");
	string s_money = string_create_from_cstring("KAPITA£:");
	string s_congratz = string_create_from_cstring("GRATULACJE ZWYCIEZCOM !");
	string* names = (string*)malloc(sizeof(string) * player_count);
	string* money = (string*)malloc(sizeof(string) * player_count);

	label_t title_label = label_create(game->renderer, 36, title, color);
	label_t player_label = label_create(game->renderer, 36, s_player, color);
	label_t money_label = label_create(game->renderer, 36, s_money, color);
	label_t congratz_label = label_create(game->renderer, 36, s_congratz, color);
	label_t* name_labels = (label_t*)malloc(sizeof(label_t) * player_count);
	label_t* money_labels = (label_t*)malloc(sizeof(label_t) * player_count);

	for (int i = 0; i < player_count; ++i) {
		names[i] = string_create_from_cstring(players[i].name);
		money[i] = _ext_string_create_from_string_and_int("", players[i].money);
		string_append_range(&money[i], " $");

		name_labels[i] = label_create(game->renderer, 36, names[i], color);
		money_labels[i] = label_create(game->renderer, 36, money[i], color);
	}


	const SDL_Rect line = { 0, 200, SCREEN_WIDTH, 10 };

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
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_click = true;
				break;
			}
		}

		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
		SDL_RenderClear(game->renderer);
		SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
		SDL_RenderFillRect(game->renderer, &line);

		label_draw(&title_label, 30, 70);
		label_draw(&player_label, 60, 158);
		label_draw(&player_label, 580, 158);

		for (int i = 0; i < player_count; ++i) {
			label_draw(&name_labels[i], 60, 220 + 38 * i);
			label_draw(&money_labels[i], 580, 220 + 38 * i);
		}

		label_draw(&congratz_label, 40, 220 + player_count * 38 + 80);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

	for (int i = 0; i < player_count; ++i) {
		label_free(&name_labels[i]);
		label_free(&money_labels[i]);
		vector_free(&names[i]);
		vector_free(&money[i]);
	}
	label_free(&title_label);
	label_free(&player_label);
	label_free(&money_label);
	label_free(&congratz_label);
	vector_free(&title);
	vector_free(&s_player);
	vector_free(&s_money);
	vector_free(&s_congratz);
	free(name_labels);
	free(money_labels);
}