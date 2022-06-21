#pragma once

#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "string.h"
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "inputbox.h"
#include "factories.h"
#include "menu_read_player_number.h"
#include "menu_read_player_names.h"
#include "predictions_graph.h"
#include "menu_player_options_screen.h"
#include "menu_buy_drill_factory_screen.h"


void _array_toupper(char* data) {
	int i = 0;
	while (data[i] != '\0') {
		data[i] = toupper(data[i]);
		i++;
	}
}

player_t* init_players(vector* names) {
	player_t *players = malloc(sizeof(player_t) * names->size);
	for (int i = 0; i < names->size; ++i) {
		string name = svector_get(names, i);
		players[i].name = string_data(&name);
		_array_toupper(players[i].name);
		players[i].money = 50000;
		memset(players[i].drill_fac, NULL, sizeof(factory_t*) * 4);
		memset(players[i].pump_fac, NULL, sizeof(factory_t*) * 3);
		memset(players[i].trucks_fac, NULL, sizeof(factory_t*) * 3);
	}
	return players;
}

void _buy_factory(player_t* players, int id, factory_t* factories, int factory_index, int factory_type) {
	if (players[id].money >= factories[factory_index].cost) {
		players[id].money -= factories[factory_index].cost;

		if (factory_type == DRILL) players[id].drill_fac[factory_index] = &factories[factory_index];
		else if (factory_type == PUMP) players[id].pump_fac[factory_index] = &factories[factory_index];
		else if (factory_type == TRUCK) players[id].trucks_fac[factory_index] = &factories[factory_index];

		factories[factory_index].player_id = id;
	}
}

void start_loop(game_t* game) {
	// const int players_count = read_player_number(game);
	const int players_count = 1;

	// reading players' nicknames
	vector names = read_player_names(game, players_count);
	player_t* players = init_players(&names); // players' structures, size=players_count

	vector pred = _generate_prices(0.1, 2.1); // in dollars $$$
	//draw_predicted_prices_screen(game, &pred);
	/*
	char* name;
	int pumps_left;
	int cost;
	int cost_per_pump;
	int player_id;
	*/
	string titles[3] = {
		string_create_from_cstring("SPRZEDAZ FABRYK WIERTE£"),
		string_create_from_cstring("SPRZEDAZ ZAK£ADÓW POMP"),
		string_create_from_cstring("SPRZEDAZ FIRM TIRÓW")
	};

	SDL_Color factory_buying_colors[3] = {
		{ 70, 56, 166 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};

	factory_t drill_factories[3] = {
		{ NULL, 57, rand() % 10000 + 40000, -1, -1 },
		{ NULL, 57, rand() % 10000 + 40000, -1, -1 },
		{ NULL, 49, rand() % 8000 + 30000, -1, -1 }
	};

	factory_t pump_factories[3] = {
		{ NULL, 60, rand() % 8000 + 35000, -1, -1 },
		{ NULL, 60, rand() % 8000 + 35000, -1, -1 },
		{ NULL, 49, rand() % 6000 + 29000, -1, -1 }
	};
	
	factory_t truck_factories[3] = {
		{ NULL, 36, rand() % 6000 + 27000, -1, -1 },
		{ NULL, 42, rand() % 6000 + 27000, -1, -1 },
		{ NULL, 30, rand() % 5000 + 23000, -1, -1 }
	};

	load_factory_names_from_file(drill_factories, pump_factories, truck_factories);
	
	for (int i = 0; i < 3; ++i) {
		printf("%s\n", drill_factories[i].name);
	}

	bool running = true;
	int i = 0;

	while (running) {
		const int current_player = i % players_count;
		const int year = i / players_count;
		i++;
		byte option = draw_main_menu_screen(game, players, current_player);
		switch (option) {
			case 0: {
				byte id = draw_buy_factory_screen(game, players, current_player, drill_factories, 3, factory_buying_colors[current_player], titles[current_player]);
				_buy_factory(players, current_player, drill_factories, id, DRILL);
				if (option == -1) continue;
			}		
		}
		
		printf("money: %d\n", players[current_player].money);
	}
}


#endif // MENU_H