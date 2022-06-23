#include "menu_buy_item_from_factory.h"

byte menu_buy_item(game_t* game, player_t* players, int current_player, factory_t* factories, int factory_count, SDL_Color bgcolor, string title, int fac_type) {

	bool running = true;
	double time = SDL_GetTicks();
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	string s_no = string_create_from_cstring("NR");
	string s_company = string_create_from_cstring("FIRMA");
	string s_count = string_create_from_cstring("ZASOBY");
	string s_cost = string_create_from_cstring("CENA");

	label_t id_label = label_create(game->renderer, 36, s_no, white);
	label_t name_label = label_create(game->renderer, 36, s_company, white);
	label_t count_label = label_create(game->renderer, 36, s_count, white);
	label_t cost_label = label_create(game->renderer, 36, s_cost, white);

	string* s_ids = (string*)malloc(sizeof(string) * factory_count);
	string* s_names = (string*)malloc(sizeof(string) * factory_count);
	string* s_counts = (string*)malloc(sizeof(string) * factory_count);
	string* s_costs = (string*)malloc(sizeof(string) * factory_count);
	string s_exit = string_create_from_cstring("POMIN TURE");
	string spaces = string_create_from_cstring("                                                                           ");
	string s_dollar = string_create_from_cstring("$");
	button_t* buttons = (button_t*)malloc(sizeof(button_t) * factory_count);
	button_t exit_btn = button_create(game->renderer, s_exit, 36, 150, 500, white);
	label_t* id_labels = (label_t*)malloc(sizeof(label_t) * factory_count);
	label_t* name_labels = (label_t*)malloc(sizeof(label_t) * factory_count);
	label_t* count_labels = (label_t*)malloc(sizeof(label_t) * factory_count);
	label_t* cost_labels = (label_t*)malloc(sizeof(label_t) * factory_count);
	label_t dollar_label = label_create(game->renderer, 36, s_dollar, bgcolor);
	label_t title_label = label_create(game->renderer, 36, title, bgcolor);


	int y_begin = 200;
	byte option = -1;
	for (int i = 0, j = 0; i < factory_count; ++i) {
		char buff[32];

		memset(buff, ' ', 16);
		sprintf(buff, "%d", i + 1);
		s_ids[i] = string_create_from_cstring(buff);

		s_names[i] = string_create_from_cstring(factories[i].name);

		memset(buff, ' ', 16);
		sprintf(buff, "%d", factories[i].items_left);
		s_counts[i] = string_create_from_cstring(buff);

		memset(buff, ' ', 16);
		sprintf(buff, "%d", factories[i].cost_per_item);
		s_costs[i] = string_create_from_cstring(buff);
		buttons[i] = button_create(game->renderer, spaces, 36, 60, y_begin + y + j * 40, white);
		if (factories[i].player_id != -1) j++;


		id_labels[i] = label_create(game->renderer, 36, s_ids[i], bgcolor);
		name_labels[i] = label_create(game->renderer, 36, s_names[i], bgcolor);
		count_labels[i] = label_create(game->renderer, 36, s_counts[i], bgcolor);
		cost_labels[i] = label_create(game->renderer, 36, s_costs[i], bgcolor);
	}

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

		// update
		button_update(&exit_btn, game->mouse);
		for (int i = 0; i < factory_count; ++i) {
			button_update(&buttons[i], game->mouse);
		}

		if (mouse_click) {
			for (int i = 0; i < factory_count; ++i) {
				if (buttons[i].is_selected) { // buy items
					if (factories[i].player_id == -1) continue;
					int count = SHRT_MAX;
					while (count * factories[i].cost_per_item > players[current_player].money || count > factories[i].items_left) {
						count = menu_set_item_cost(game, bgcolor, "ILE SZTUK CHCESZ KUPIC? :");
					}
					factories[i].items_left -= count;	// transfer items

					switch (fac_type) {
					case DRILL:
						players[current_player].drills += count;
						break;
					case PUMP:
						players[current_player].pumps += count;
						break;
					case TRUCK:
						players[current_player].trucks += count;
						break;
					}

					int total_cost = count * factories[i].cost_per_item; // transfer money
					players[current_player].money -= total_cost;
					players[factories[i].player_id].money += total_cost;

					option = i;
					running = false;
					break;
				}
			}
			if (exit_btn.is_selected) {
				running = false;
				option = -1;
				break;
			}
		}


		// draw
		game_background_draw(game);

		label_draw(&id_label, 50, 150);
		label_draw(&name_label, 110, 150);
		label_draw(&count_label, 430, 150);
		label_draw(&cost_label, 595, 150);

		const int y_begin = 200;
		for (int i = 0, j = 0; i < factory_count; ++i) {
			if (factories[i].player_id == -1) continue;
			button_draw(&buttons[i]);
			label_draw_on_rect(&id_labels[i], 60, y_begin + y + j * 40, white);
			label_draw_on_rect(&name_labels[i], 100, y_begin + y + j * 40, white);
			label_draw_on_rect(&count_labels[i], 470, y_begin + y + j * 40, white);
			label_draw_on_rect(&cost_labels[i], 595, y_begin + y + j * 40, white);
			label_draw_on_rect(&dollar_label, 720, y_begin + y + j * 40, white);
			j++;
		}
		button_draw(&exit_btn);
		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

	// release resources
	for (int i = 0; i < factory_count; ++i) {
		button_free(&buttons[i]);
		vector_free(&s_ids[i]);
		vector_free(&s_names[i]);
		vector_free(&s_counts[i]);
		vector_free(&s_costs[i]);
		button_free(&buttons[i]);
		label_free(&id_labels[i]);
		label_free(&name_labels[i]);
		label_free(&count_labels[i]);
		label_free(&cost_labels[i]);
	}
	label_free(&id_label);
	label_free(&name_label);
	label_free(&count_label);
	label_free(&cost_label);
	free(buttons);
	free(s_ids);
	free(s_names);
	free(s_counts);
	free(s_costs);
	free(id_labels);
	free(name_labels);
	free(count_labels);
	free(cost_labels);
	label_free(&dollar_label);
	vector_free(&s_dollar);
	vector_free(&spaces);
	label_free(&title_label);
	button_free(&exit_btn);
	vector_free(&s_exit);

	vector_free(&s_no);
	vector_free(&s_company);
	vector_free(&s_count);
	vector_free(&s_cost);


	return option;
}