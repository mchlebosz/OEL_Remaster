#pragma once

#include <SDL.h>
#include "label.h"
#include "game.h"
#include "vector.h"
#include "extended_vector.h"
#include <stdlib.h>
#include "colors.h"

vector _generate_prices(float min_price, float max_price);

void _prices_draw(SDL_Renderer* renderer, vector* prices);

void draw_predicted_prices_screen(game_t* game, vector* prices);