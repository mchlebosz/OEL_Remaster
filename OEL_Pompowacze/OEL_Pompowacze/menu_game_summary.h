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
#include "menu_end_of_year.h"
#include "colors.h"

void draw_game_summary(game_t* game, player_t* players, int player_count);