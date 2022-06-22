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
#include "menu_buy_factory_screen.h"
#include "menu_buy_item_from_factory.h"
#include "menu_set_item_cost.h"
#include "menu_buy_oil_field.h"

// string to upper
void _array_toupper(char* data) {
	int i = 0;
	while (data[i] != '\0') {
		data[i] = toupper(data[i]);
		i++;
	}
}
// initializes players' stats and sets to default
player_t* init_players(const vector* names) {
	player_t *players = malloc(sizeof(player_t) * names->size);
	for (int i = 0; i < names->size; ++i) {
		string name = svector_get(names, i);
		players[i].name = string_data(&name);
		_array_toupper(players[i].name);
		players[i].money = 72000 / names->size + 24000; // start money
		memset(players[i].drill_fac, (factory_t*)NULL, sizeof(factory_t*) * 3);
		memset(players[i].pump_fac, (factory_t*)NULL, sizeof(factory_t*) * 3);
		memset(players[i].trucks_fac, (factory_t*)NULL, sizeof(factory_t*) * 3);
		memset(players[i].oil_fields, (factory_t*)NULL, sizeof(factory_t*) * 6);
		players[i].drills = 0;
		players[i].pumps = 0;
		players[i].trucks = 0;
		players[i].oil = 0;
	}
	return players;
}

// assigns factory to player
void _buy_factory(player_t* players, int id, factory_t* factories, int factory_index, int factory_type) {
	if (players[id].money >= factories[factory_index].cost) {
		players[id].money -= factories[factory_index].cost;

		if (factory_type == DRILL) players[id].drill_fac[factory_index] = &factories[factory_index];
		else if (factory_type == PUMP) players[id].pump_fac[factory_index] = &factories[factory_index];
		else if (factory_type == TRUCK) players[id].trucks_fac[factory_index] = &factories[factory_index];
		else if (factory_type == OIL) players[id].oil_fields[factory_index] = &factories[factory_index];

		factories[factory_index].player_id = id;
	}
}

/*
	every oil field has field "items_left"
	every single dig cost_per_item is increased by 455-500
	when value reaches items_left up to 3*items_left, oil is available and player gains oil after next digs
*/
void _dig_oil_field(player_t* player, factory_t* oil_field) {
	if (player->drills <= 0) return;

	int min = oil_field->items_left;
	int max = 3 * oil_field->items_left;

	if (oil_field->cost_per_item >= max) return;

	player->drills--;

	int to_dig = 500 - rand() % 45;
	oil_field->cost_per_item += to_dig;

	int depth = oil_field->cost_per_item;
	if (depth < max) oil_field->buffer++;

	printf("{player: %s,  dug: %d, oil at: %d}", player->name, depth, oil_field->items_left);
	if (min <= depth && depth < max) {
		printf(" OIL!!! ");
	}
	puts("");
}
/*

	cost - how many times oil can be pumped
	buffer - pumps requeired
	cost_per_item - current depth
*/
void _pump_oil(player_t* player, factory_t* oil_field) {
	if (player->pumps <= 0) return;

	int min = oil_field->items_left;
	int max = 3 * oil_field->items_left;

	if (oil_field->cost_per_item < min) return;
	if (oil_field->cost <= 0) return;


	while (player->pumps > 0 && oil_field->buffer > 0) {
		oil_field->buffer--;
		player->pumps--;
	}


	if (oil_field->buffer == 0) {
		oil_field->cost--;
		player->oil += 8000 + 2000 * (rand() % 4);
	}
	printf("{to pump: %d}\n", oil_field->cost);
}

void players_dig_oil_fields(player_t* players, int player_count) {
	for (int i = 0; i < player_count; ++i) {
		for (int j = 0; j < 6; ++j) { // check every oil field
			if (players[i].oil_fields[j] == NULL) continue;

			// try dig
			_dig_oil_field(&players[i], players[i].oil_fields[j]);

			// place pumps (as many as possible) and pump oil (once)
			_pump_oil(&players[i], players[i].oil_fields[j]);
		}
	}
}

void _debug(player_t* players, int n) {
	for (int i = 0; i < n; ++i) {
		printf("[BEGIN] %s\n", players[i].name);
		printf("money: %d,  oil: %d\n", players[i].money, players[i].oil);
		printf("drills: %d,  pumps: %d,  trucks: %d\n", players[i].drills, players[i].pumps, players[i].trucks);
		for (int j = 0; j < 6; ++j) { // check every oil field
			if (players[i].oil_fields[j] == NULL) continue;
			printf("  - %s\n", players[i].oil_fields[j]->name);

		}
		printf("[END]\n\n");
	}
}

// main game loop
void start_loop(game_t* game) {
	// const int players_count = read_player_number(game);
	const int players_count = 2;

	// reading players' nicknames
	const vector names = read_player_names(game, players_count);
	player_t* players = init_players(&names); // players' structures, size=players_count

	vector pred = _generate_prices(0.1f, 2.1f); // in dollars $$$
	//draw_predicted_prices_screen(game, &pred);
	/*
	char* name;
	int pumps_left;
	int cost;
	int cost_per_pump;
	int player_id;
	*/
	const string titles[3] = {
		string_create_from_cstring("SPRZEDAZ FABRYK WIERTE£"),
		string_create_from_cstring("SPRZEDAZ ZAK£ADÓW POMP"),
		string_create_from_cstring("SPRZEDAZ FIRM TIRÓW")
	};
	const string titles_buy[3] = {
		string_create_from_cstring("SPRZEDAZ WIERTE£"),
		string_create_from_cstring("SPRZEDAZ POMP"),
		string_create_from_cstring("SPRZEDAZ TIRÓW")
	};
	const SDL_Color factory_buying_colors[4] = {
		{ 70, 56, 166 },
		{ 240, 67, 119 },
		{ 111, 184, 39 },
		{ 32, 32, 32 }
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
		{ NULL, 42, rand() % 9000 + 27000, -1, -1 },
		{ NULL, 30, rand() % 5000 + 23000, -1, -1 }
	};
	// second parameter is depth of oil, third - cost, forth - total meters dug
	factory_t oil_fields[6] = {
		{"", round1000(1950 + rand() % 3000), rand() % 70000 + 30000, 0, -1, 0},
		{"", round1000(950 + rand() % 2500), rand() % 15000 + 20000, 0, -1, 0},
		{"", round1000(400 + rand() % 3000), rand() % 30000 + 20000, 0, -1, 0},
		{"", round1000(1400 + rand() % 2500), rand() % 35000 + 15000, 0, -1, 0},
		{"", round1000(1400 + rand() % 4000), rand() % 10000 + 85000, 0, -1, 0},
		{"", round1000(3900 + rand() % 1500), rand() % 50000 + 80000, 0, -1, 0},
	};

	load_factory_names_from_file(drill_factories, pump_factories, truck_factories, oil_fields);
	for (int i = 0; i < 6; ++i) {
		printf("name: %s,  depth: %d,  cost: %d\n", oil_fields[i].name, oil_fields[i].items_left, oil_fields[i].cost);
	}

	bool running = true;
	int i = 0;

	while (running) {
		const int current_player = i % players_count;
		const int year = i / players_count;
		if (year == 20) {
			running = false;
			break;
		}
		i++;
		byte option = draw_main_menu_screen(game, players, current_player);
		switch (option) {
			// 0,1,2 - zakup fabryk
			case 0: {
				byte id = draw_buy_factory_screen(game, players, current_player, drill_factories, 3, factory_buying_colors[DRILL], titles[DRILL]);
				if (id == -1) break;
				_buy_factory(players, current_player, drill_factories, id, DRILL);
				break;
			}
			case 1: {
				byte id = draw_buy_factory_screen(game, players, current_player, pump_factories, 3, factory_buying_colors[PUMP], titles[PUMP]);
				if (id == -1) break;
				_buy_factory(players, current_player, pump_factories, id, PUMP);
				break;
			}
			case 2: {
				byte id = draw_buy_factory_screen(game, players, current_player, truck_factories, 3, factory_buying_colors[TRUCK], titles[TRUCK]);
				if (id == -1) break;
				_buy_factory(players, current_player, truck_factories, id, TRUCK);
				break;
			}
			// 3,4,5 - zakup przedmiotu
			case 3: {
				byte id = menu_buy_item(game, players, current_player, drill_factories, 3, gray, titles_buy[DRILL], DRILL);
				break;
			}
			case 4: {
				byte id = menu_buy_item(game, players, current_player, pump_factories, 3, gray, titles_buy[PUMP], PUMP);
				break;
			}
			case 5: {
				byte id = menu_buy_item(game, players, current_player, truck_factories, 3, gray, titles_buy[TRUCK], TRUCK);
				break;
			}
			// 6- - zakup pola naftowego
			case 6: {
				byte id = menu_buy_oil_field(game, players, current_player, oil_fields, 6, factory_buying_colors[OIL]);
				_buy_factory(players, current_player, oil_fields, id, OIL);
				oil_fields[id].cost = (oil_fields[id].items_left * 2) / 1000;
				printf("pumps: %d\n", oil_fields[id].cost);
				break;
			}
			
		}
		
		if (current_player == players_count - 1) { // end of year
			_debug(players, players_count);
			players_dig_oil_fields(players, players_count);
			
			// end of year screen....
		}
	}

	// TODO: draw summary screen!
	// ...
	// ...


	vector_free(&names);
}


#endif // MENU_H