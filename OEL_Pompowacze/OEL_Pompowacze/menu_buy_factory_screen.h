#pragma once

#define _CRT_SECURE_NO_WARNINGS

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

void _draw_title_rectangle(label_t* label);

// returns bought factory id
byte draw_buy_factory_screen(game_t* game, player_t* players, int current_player, factory_t* factories, int factory_count, SDL_Color bgcolor, string title);