#include "menu_buy_oil_field.h"

byte menu_buy_oil_field(game_t* game, player_t* players, int current_player, factory_t* oil_fields, int field_count, SDL_Color bgcolor) {
	bool running = true;
	double time = SDL_GetTicks();
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	string s_no = string_create_from_cstring("NR");
	string s_company = string_create_from_cstring("FIRMA");
	string s_cost = string_create_from_cstring("CENA");

	label_t id_label = label_create(game->renderer, 36, s_no, white);
	label_t name_label = label_create(game->renderer, 36, s_company, white);
	label_t cost_label = label_create(game->renderer, 36, s_cost, white);
	string title = string_create_from_cstring("SPRZEDAZ PÓL NAFTOWYCH");
	string* s_ids = (string*)malloc(sizeof(string) * field_count);
	string* s_names = (string*)malloc(sizeof(string) * field_count);
	string* s_costs = (string*)malloc(sizeof(string) * field_count);
	string s_exit = string_create_from_cstring("POMIN TURE");
	string spaces = string_create_from_cstring("                                                                           ");
	string s_dollar = string_create_from_cstring("$");
	string s_current_money = string_create_from_cstring("AKTUALNY KAPITAL: ");
	{
		string tmp = int2string(players[current_player].money);
		string_append_range(&s_current_money, string_data(&tmp));
		string_append_range(&s_current_money, " $");
	}
	button_t* buttons = (button_t*)malloc(sizeof(button_t) * field_count);
	button_t exit_btn = button_create(game->renderer, s_exit, 36, 150, 500, white);
	label_t* id_labels = (label_t*)malloc(sizeof(label_t) * field_count);
	label_t* name_labels = (label_t*)malloc(sizeof(label_t) * field_count);
	label_t* cost_labels = (label_t*)malloc(sizeof(label_t) * field_count);
	label_t dollar_label = label_create(game->renderer, 36, s_dollar, bgcolor);
	label_t title_label = label_create(game->renderer, 36, title, bgcolor);
	label_t current_money_label = label_create(game->renderer, 36, s_current_money, purple);

	const int y_begin = 150;

	for (int i = 0; i < field_count; ++i) {
		char buff[32];

		memset(buff, ' ', 16);
		sprintf(buff, "%d", i + 1);
		s_ids[i] = string_create_from_cstring(buff);

		s_names[i] = string_create_from_cstring(oil_fields[i].name);

		memset(buff, ' ', 16);
		sprintf(buff, "%d", oil_fields[i].cost);
		s_costs[i] = string_create_from_cstring(buff);

		buttons[i] = button_create(game->renderer, spaces, 36, 60, y_begin + y + i * 40, white);

		id_labels[i] = label_create(game->renderer, 36, s_ids[i], bgcolor);
		name_labels[i] = label_create(game->renderer, 36, s_names[i], bgcolor);
		cost_labels[i] = label_create(game->renderer, 36, s_costs[i], bgcolor);
	}

	byte option = -1;
	const SDL_Rect yellow_rect = { 0,0, SCREEN_WIDTH, 60 };

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
			}
		}
		for (int i = 0; i < field_count; ++i) {
			button_update(&buttons[i], game->mouse);
		}

		for (int i = 0; i < field_count; ++i) {
			if (buttons[i].is_selected && mouse_click) {
				if (oil_fields[i].player_id != -1) continue;
				if (players[current_player].money < oil_fields[i].cost) continue;

				option = i;
				running = false;
				break;
			}
		}

		button_update(&exit_btn, game->mouse);
		if (exit_btn.is_selected && mouse_click) {
			option = -1;
			running = false;
			break;
		}

		SDL_SetRenderDrawColor(game->renderer, bgcolor.r, bgcolor.g, bgcolor.b, 255);
		SDL_RenderClear(game->renderer);

		SDL_SetRenderDrawColor(game->renderer, 214, 223, 123, 255);
		SDL_RenderFillRect(game->renderer, &yellow_rect);

		label_draw(&title_label, 80, 18);
		label_draw(&id_label, 50, 110);
		label_draw(&name_label, 110, 110);
		label_draw(&cost_label, 595, 110);
		for (int i = 0; i < field_count; ++i) {
			const SDL_Color color = oil_fields[i].player_id == -1 ? white : gray;
			button_draw(&buttons[i]);
			label_draw_on_rect(&id_labels[i], 60, y_begin + y + i * 40, color);
			label_draw_on_rect(&name_labels[i], 100, y_begin + y + i * 40, color);
			if (oil_fields[i].player_id == -1) label_draw_on_rect(&cost_labels[i], 565, y_begin + y + i * 40, color);
			label_draw_on_rect(&dollar_label, 720, y_begin + y + i * 40, color);
		}
		button_draw(&exit_btn);
		label_draw(&current_money_label, 100, 450);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

	for (int i = 0; i < field_count; ++i) {
		button_free(&buttons[i]);
		vector_free(&s_ids[i]);
		vector_free(&s_names[i]);
		vector_free(&s_costs[i]);
		button_free(&buttons[i]);
		label_free(&id_labels[i]);
		label_free(&name_labels[i]);
		label_free(&cost_labels[i]);
	}
	label_free(&id_label);
	label_free(&name_label);
	label_free(&cost_label);
	vector_free(&s_no);
	vector_free(&s_company);
	vector_free(&s_cost);
	free(buttons);
	free(s_ids);
	free(s_names);
	free(s_costs);
	free(id_labels);
	free(name_labels);
	free(cost_labels);
	label_free(&dollar_label);
	vector_free(&s_dollar);
	vector_free(&spaces);
	label_free(&title_label);
	button_free(&exit_btn);
	vector_free(&s_exit);

	return option;
}