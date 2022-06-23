#pragma once

#ifndef MENU_H
#define MENU_H

#define _CRT_SECURE_NO_WARNINGS

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
#include "colors.h"
#include "menu_read_player_number.h"
#include "menu_read_player_names.h"
#include "predictions_graph.h"
#include "menu_player_options_screen.h"
#include "menu_buy_factory_screen.h"
#include "menu_buy_item_from_factory.h"
#include "menu_set_item_cost.h"
#include "menu_buy_oil_field.h"
#include "menu_end_of_year.h"
#include "menu_game_summary.h"

// string to upper
void _array_toupper(char* data);

// initializes players' stats and sets to default
player_t* init_players(const vector* names);

// assigns factory to player
void _buy_factory(player_t* players, int id, factory_t* factories, int factory_index, int factory_type);

/*
	every oil field has field "items_left"
	every single dig cost_per_item is increased by 455-500
	when value reaches items_left up to 3*items_left, oil is available and player gains oil after next digs
*/
void _dig_oil_field(player_t* player, factory_t* oil_field, FILE* logger);

/*
	items_left - depth
	cost - how many times oil can be pumped
	buffer - pumps requeired
	cost_per_item - current depth
*/
void _pump_oil(player_t* player, factory_t* oil_field, FILE* logger);

void players_dig_oil_fields(player_t* players, int player_count, FILE* logger);

void _log_players(game_t* game, player_t* players, int n);

// main game loop
void start_loop(game_t* game);

#endif // MENU_H