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
#include "menu_read_player_names.h"
#include "predictions_graph.h"
#include "menu_factories.h"
#include "menu_player_options_screen.h"


void array_toupper(char* data) {
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
		array_toupper(players[i].name);
		players[i].money = 30000;
		memset(players[i].drill_fac, NULL, sizeof(factory_drill*) * 4);
		memset(players[i].pump_fac, NULL, sizeof(factory_pump*) * 3);
		memset(players[i].trucks_fac, NULL, sizeof(factory_trucks*) * 3);
	}
	return players;
}

void start_loop(game_t* game) {
	
	// const int players_count = read_player_number(game);
	const int players_count = 1;
	
	// reading players' nicknames
	vector names = read_player_names(game, players_count);
	player_t* players = init_players(&names); // players' structures, size=players_count
	
	vector pred = _generate_prices(0.1, 2.1); // in dollars $$$
	// draw_predicted_prices_screen(game, &pred);
	
	bool running = true;
	int i = 0;

	while (running) {
		const int current_player = i % players_count;
		const int year = i / players_count;
		i++;
		byte option = draw_main_menu_screen(game, players, current_player);

		if (option == -1) continue;
		
		
	}
	SDL_DestroyTexture(b.txt);

}


#endif // MENU_H