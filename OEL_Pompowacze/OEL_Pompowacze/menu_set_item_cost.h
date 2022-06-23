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
#include "colors.h"

int menu_set_item_cost(game_t* game, SDL_Color bgcolor, const char* title);