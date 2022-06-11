#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game.h"
#include "string.h"
#include "label.h"
#include "mouse.h"
#include "button.h"
#include "inputbox.h"

struct factory_drill {
	int drills_left;
	int cost;
	int cost_per_drill;
};

struct factory_pump {
	int pumps_left;
	int cost;
	int cost_per_pump;
};

struct factory_trucks {
	int trucks_left;
	int cost;
	int cost_per_truck;
};

typedef struct factory_drill factory_drill;
typedef struct factory_pump factory_pump;
typedef struct factory_trucks factory_trucks;

