#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "game.h"
#include "factories.h"
#include "vector.h"
#include "extended_vector.h"
#include "string.h"
#include "label.h"
#include "button.h"
#include "inputbox.h"
#include "colors.h"

string _ext_string_create_from_string_and_int(char* _String, int _Value);

string _ext_string_create_from_string_and_float(char* _String, float _Value);

void draw_year_summary_and_sell_oil(game_t* game, player_t* players, int player_count, vector* prices, int year);

int end_of_year_screen(game_t* game, player_t* players, int current_player, vector* prices, int year);