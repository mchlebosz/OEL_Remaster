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
#include "colors.h"

// returns selected option's id
byte draw_main_menu_screen(game_t* game, player_t* players, int current_player);