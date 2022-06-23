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
#include "menu_buy_factory_screen.h"


// returns bought factory id
byte menu_buy_oil_field(game_t* game, player_t* players, int current_player, factory_t* oil_fields, int field_count, SDL_Color bgcolor);