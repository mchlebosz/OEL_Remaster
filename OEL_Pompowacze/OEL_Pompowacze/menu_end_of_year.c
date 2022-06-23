#include "menu_end_of_year.h"

string _ext_string_create_from_string_and_int(char* _String, int _Value) {
	string _S = string_create_from_cstring(_String);
	string_append_int(&_S, _Value);
	return _S;
}

string _ext_string_create_from_string_and_float(char* _String, float _Value) {
	string _S = string_create_from_cstring(_String);
	string_append_float(&_S, _Value);
	return _S;
}

void draw_year_summary_and_sell_oil(game_t* game, player_t* players, int player_count, vector* prices, int year) {
	for (int i = 0; i < player_count; ++i) {
		if (players[i].oil == 0) continue;
		int oil_to_sell = end_of_year_screen(game, players, i, prices, year);
		if (oil_to_sell == 0) continue;

		float price = fvector_get(prices, year);

		players[i].oil -= oil_to_sell;
		players[i].money += oil_to_sell * price;
	}
}

int end_of_year_screen(game_t* game, player_t* players, int current_player, vector* prices, int year) {
	const SDL_Color bgcolor = { 152, 105, 45 };
	const SDL_Color tmp_color = { 191, 233, 147 };
	const string s_player_name = string_create_from_cstring("W£ASCICIEL PÓL");
	const string s_player_name2 = string_create_from_cstring(players[current_player].name);
	const string s_year = string_create_from_cstring("ROK : ");
	const string s_year_value = _ext_string_create_from_string_and_int(" ", year + 1981);
	string s_oil_price = _ext_string_create_from_string_and_float("CENA SPRZEDAZY ROPY = ", fvector_get(prices, year));
	string_append_range(&s_oil_price, " $");
	const string s_pump_count = _ext_string_create_from_string_and_int("ILO$C POMP :  ", players[current_player].pumps);
	const string s_oil_amount = _ext_string_create_from_string_and_int("WYPOMPOWANO :  ", players[current_player].oil);
	const string s_truck_count = _ext_string_create_from_string_and_int("ILO$C TIRÓW :  ", players[current_player].trucks);
	const string s_max_load = _ext_string_create_from_string_and_int("MAX WYWÓZ :  ", players[current_player].trucks * 7000);
	const string s_drill_count = _ext_string_create_from_string_and_int("ILO$C WIERTE£ :  ", players[current_player].drills);
	string s_player_money = _ext_string_create_from_string_and_int("TWÓJ KAPITA£ :  ", players[current_player].money);
	string_append_range(&s_player_money, " $");
	const string s_how_many_you_sell = string_create_from_cstring("ILE LITRÓW ROPY SPRZEDAJESZ?");

	const label_t player_name_label = label_create(game->renderer, 36, s_player_name, bgcolor);
	const label_t player_name2_label = label_create(game->renderer, 36, s_player_name2, black);
	const label_t year_label = label_create(game->renderer, 36, s_year, black);
	const label_t year_value_label = label_create(game->renderer, 36, s_year_value, white);
	const label_t oil_price_label = label_create(game->renderer, 36, s_oil_price, blue);
	const label_t pump_count_label = label_create(game->renderer, 36, s_pump_count, black);
	const label_t oil_amount_label = label_create(game->renderer, 36, s_oil_amount, tmp_color);
	const label_t truck_count_label = label_create(game->renderer, 36, s_truck_count, black);
	const label_t max_load_label = label_create(game->renderer, 36, s_max_load, tmp_color);
	const label_t drill_count_label = label_create(game->renderer, 36, s_drill_count, black);
	const label_t player_money_label = label_create(game->renderer, 36, s_player_money, tmp_color);
	const label_t how_many_you_sell_label = label_create(game->renderer, 36, s_how_many_you_sell, black);

	inputbox_t input = input_create(game->renderer, 36, how_many_you_sell_label.rect.w + 50, 480, 180, 36, tmp_color);
	input.border_color = black;
	input.active = true;
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;
	bool running = true;
	int total_time = 0;
	double time_start = SDL_GetTicks();
	double time = time_start;
	SDL_Texture* truck_img = IMG_LoadTexture(game->renderer, "truck.png");

	const SDL_Rect truck_rect = { 40, 20, 373, 80 };

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
			case SDL_QUIT: {
				SDL_Quit();
				exit(0);
			}
			case SDL_MOUSEBUTTONDOWN: {
				mouse_click = true;
				break;
			}
			case SDL_KEYDOWN: {
				char c = get_pressed_key(event);
				int text_length = (int)string_size(&input.text);

				if (text_length > 0 && c == SDLK_RETURN) {
					int res = atoi(string_data(&input.text));
					if (res <= players[current_player].trucks * 7000 && res <= players[current_player].oil) {
						running = false;
						break;
					}
				}
				if (c == '\r') {}
				else if (c == '\b') inputbox_update_text(&input, c);
				else if ('0' <= c && c <= '9') inputbox_update_text(&input, c);
				break;
			}
			}
		}
		inputbox_update(&input, game->mouse, mouse_click);
		
		SDL_SetRenderDrawColor(game->renderer, bgcolor.r, bgcolor.g, bgcolor.b, 255);
		SDL_RenderClear(game->renderer);
		SDL_RenderCopy(game->renderer, truck_img, NULL, &truck_rect);
		label_draw_on_rect(&player_name_label, 500, 20, black);
		label_draw(&player_name2_label, 530, 60);

		label_draw(&year_label, 40, 100);
		label_draw(&year_value_label, 160, 100);

		label_draw(&oil_price_label, 40, 160);
		label_draw(&pump_count_label, 40, 220);
		label_draw(&oil_amount_label, 40, 260);
		label_draw(&truck_count_label, 40, 300);
		label_draw(&max_load_label, 40, 340);
		label_draw(&drill_count_label, 40, 380);
		label_draw(&player_money_label, 40, 420);
		label_draw(&how_many_you_sell_label, 40, 480);
		inputbox_draw(&input);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}
	SDL_DestroyTexture(truck_img);

	label_free(&player_name_label);
	label_free(&player_name2_label);
	label_free(&year_label);
	label_free(&year_value_label);
	label_free(&oil_price_label);
	label_free(&pump_count_label);
	label_free(&oil_amount_label);
	label_free(&truck_count_label);
	label_free(&max_load_label);
	label_free(&drill_count_label);
	label_free(&player_money_label);
	label_free(&how_many_you_sell_label);

	vector_free(&s_player_name);
	vector_free(&s_player_name2);
	vector_free(&s_year);
	vector_free(&s_year_value);
	vector_free(&s_oil_price);
	vector_free(&s_pump_count);
	vector_free(&s_oil_amount);
	vector_free(&s_truck_count);
	vector_free(&s_max_load);
	vector_free(&s_drill_count);
	vector_free(&s_how_many_you_sell);
	int res = atoi(string_data(&input.text));
	inputbox_free(&input);
	return res;
}