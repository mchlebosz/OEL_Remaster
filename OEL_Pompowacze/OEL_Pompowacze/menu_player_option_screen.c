#include "menu_player_options_screen.h"

byte draw_main_menu_screen(game_t* game, player_t* players, int current_player) {
	bool running = true;
	double time = SDL_GetTicks();
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;

	// create strings
	const string s_title = string_create_from_cstring("DECYZJA NALEZY DO CIEBIE!");
	string s_player_name = string_create_from_cstring("GRACZ:  ");
	string_append_range(&s_player_name, players[current_player].name);
	string_append_range(&s_player_name, "    $= ");
	string_append_int(&s_player_name, players[current_player].money);

	const string s_buying = string_create_from_cstring("  KUPOWANIE  ");
	const string s_drill_factories = string_create_from_cstring("FABRYKI WIERTE£");
	const string s_pump_factories = string_create_from_cstring("ZAK£ADY POMP");
	const string s_trucks_factories = string_create_from_cstring("FIRMY Z TIRAMI");
	const string s_drills = string_create_from_cstring("WIERT£A");
	const string s_pumps = string_create_from_cstring("POMPY");
	const string s_trucks = string_create_from_cstring("TIRY");
	const string s_fields = string_create_from_cstring("POLA NAFTOWE");
	const string s_other_options = string_create_from_cstring("  POZOSTA£E MOZLIWO$CI  ");
	const string s_next_player = string_create_from_cstring("POMIN TURE");

	// create labels
	const label_t title_label = label_create(game->renderer, 32, s_title, white);
	const label_t player_name_label = label_create(game->renderer, 32, s_player_name, white);
	const label_t buying_label = label_create(game->renderer, 32, s_buying, internal_bg_color);
	const label_t other_options_label = label_create(game->renderer, 32, s_other_options, internal_bg_color);

	// create buttons
	const button_t drill_fac_btn = button_create(game->renderer, s_drill_factories, 32, 100, 176, black);
	const button_t pump_fac_btn = button_create(game->renderer, s_pump_factories, 32, 100, 208, white);
	const button_t truck_fac_btn = button_create(game->renderer, s_trucks_factories, 32, 100, 240, black);
	const button_t drills_btn = button_create(game->renderer, s_drills, 32, 100, 272, white);
	const button_t pumps_btn = button_create(game->renderer, s_pumps, 32, 100, 304, black);
	const button_t trucks_btn = button_create(game->renderer, s_trucks, 32, 100, 336, white);
	const button_t fields_btn = button_create(game->renderer, s_fields, 32, 100, 368, black);
	const button_t next_player_btn = button_create(game->renderer, s_next_player, 32, 100, 452, white);

	const SDL_Color cool_yellow = { 204, 191, 69 };

	byte result = -1;

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
		// check if buttons clicked
		button_update(&drill_fac_btn, game->mouse);
		button_update(&pump_fac_btn, game->mouse);
		button_update(&truck_fac_btn, game->mouse);
		button_update(&drills_btn, game->mouse);
		button_update(&pumps_btn, game->mouse);
		button_update(&trucks_btn, game->mouse);
		button_update(&next_player_btn, game->mouse);
		button_update(&fields_btn, game->mouse);

		if (mouse_click) {
			if (drill_fac_btn.is_selected) result = 0;
			if (pump_fac_btn.is_selected) result = 1;
			if (truck_fac_btn.is_selected) result = 2;
			if (drills_btn.is_selected) result = 3;
			if (pumps_btn.is_selected) result = 4;
			if (trucks_btn.is_selected) result = 5;
			if (fields_btn.is_selected) result = 6;

			if (next_player_btn.is_selected) {
				running = false;
				break;
			}

			if (result != -1) {
				running = false;
				break;
			}
		}

		game_background_draw(game);

		label_draw_on_rect(&title_label, 100, 30, cool_yellow);
		label_draw(&player_name_label, 100, 72);
		label_draw_on_rect(&buying_label, 100, 142, external_bg_color);
		label_draw_on_rect(&other_options_label, 100, 418, external_bg_color);

		// draw buttons
		button_draw(&drill_fac_btn);
		button_draw(&pump_fac_btn);
		button_draw(&truck_fac_btn);
		button_draw(&drills_btn);
		button_draw(&pumps_btn);
		button_draw(&trucks_btn);
		button_draw(&next_player_btn);
		button_draw(&fields_btn);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

	// free resources 
	vector_free(&s_title);
	vector_free(&s_player_name);
	vector_free(&s_buying);
	vector_free(&s_drill_factories);
	vector_free(&s_pump_factories);
	vector_free(&s_trucks_factories);
	vector_free(&s_drills);
	vector_free(&s_pumps);
	vector_free(&s_trucks);
	vector_free(&s_other_options);
	vector_free(&s_next_player);

	label_free(&title_label);
	label_free(&player_name_label);
	label_free(&buying_label);
	label_free(&other_options_label);

	button_free(&drill_fac_btn);
	button_free(&pump_fac_btn);
	button_free(&truck_fac_btn);
	button_free(&drills_btn);
	button_free(&pumps_btn);
	button_free(&trucks_btn);
	button_free(&next_player_btn);

	return result;
}
