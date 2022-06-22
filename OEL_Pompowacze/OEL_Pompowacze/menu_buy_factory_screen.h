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
#include "menu_set_item_cost.h"

void _draw_title_rectangle(label_t* label) {
	SDL_Rect rect = {
		.x = 100,
		.y = label->rect.y - label->rect.h / 2,
		.w = 600,
		.h = label->rect.h * 2
	};
	SDL_SetRenderDrawColor(label->renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
	SDL_RenderFillRect(label->renderer, &rect);
	
	int x = SCREEN_WIDTH / 2 - label->rect.w / 2;
	label_draw(label, x, 100);
}

// returns bought factory id
byte draw_buy_factory_screen(game_t* game, player_t* players, int current_player, factory_t* factories, int factory_count, SDL_Color bgcolor, string title) {
	bool running = true;
	double time = SDL_GetTicks();
	const int x = 35;
	const int y = 20;
	const int width = SCREEN_WIDTH - x * 2;
	const int height = SCREEN_HEIGHT - y * 2;

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

	for (int i = 0; i < factory_count; ++i) {
		char buff[32];

		memset(buff, ' ', 16);
		sprintf(buff, "%d", i + 1);
		s_ids[i] = string_create_from_cstring(buff);

		s_names[i] = string_create_from_cstring(factories[i].name);

		memset(buff, ' ', 16);
		sprintf(buff, "%d", factories[i].items_left);
		s_counts[i] = string_create_from_cstring(buff);

		memset(buff, ' ', 16);
		sprintf(buff, "%d", factories[i].cost);
		s_costs[i] = string_create_from_cstring(buff);

		buttons[i] = button_create(game->renderer, spaces, 36, 60, y_begin + y + i * 40, white);

		
		id_labels[i] = label_create(game->renderer, 36, s_ids[i], bgcolor);
		name_labels[i] = label_create(game->renderer, 36, s_names[i], bgcolor);
		count_labels[i] = label_create(game->renderer, 36, s_counts[i], bgcolor);
		cost_labels[i] = label_create(game->renderer, 36, s_costs[i], bgcolor);
	}

	byte option = -1;

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
		for (int i = 0; i < factory_count; ++i) {
			button_update(&buttons[i], game->mouse);
		}
		
		for (int i = 0; i < factory_count; ++i) {
			if (buttons[i].is_selected && mouse_click) {
				if (factories[i].player_id != -1) continue;
				if (players[current_player].money < factories[i].cost) continue;
				int cost = menu_set_item_cost(game, bgcolor, "PODAJ CENE ZA JEDNA SZTUKE:");
				factories[i].cost_per_item = cost;
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

		_draw_title_rectangle(&title_label);
		
		for (int i = 0; i < factory_count; ++i) {
			const SDL_Color color = factories[i].player_id == -1 ? white : gray;
			button_draw(&buttons[i]);
			label_draw_on_rect(&id_labels[i], 60, y_begin + y + i * 40, color);
			label_draw_on_rect(&name_labels[i], 100, y_begin + y + i * 40, color);
			label_draw_on_rect(&count_labels[i], 470, y_begin + y + i * 40, color);
			label_draw_on_rect(&cost_labels[i], 595, y_begin + y + i * 40, color);
			label_draw_on_rect(&dollar_label, 720, y_begin + y + i * 40, color);
		}
		button_draw(&exit_btn);

		mouse_draw(game->renderer, game->mouse);
		SDL_RenderPresent(game->renderer);
	}

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
	// DO NOT FREE TITLE! vector_free(&title);
	label_free(&title_label);
	button_free(&exit_btn);
	vector_free(&s_exit);



	return option;
}	