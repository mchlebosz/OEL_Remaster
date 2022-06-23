#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum factory_type {
	DRILL = 0,
	PUMP = 1,
	TRUCK = 2,
	OIL = 3,
};

struct factory {
	char* name;
	int items_left;
	int cost;
	int cost_per_item;
	int player_id;
	int buffer;
};

typedef struct factory factory_t;

void read_line(FILE* file, char line[32]);

void _load_random_names_from_file(FILE* file, factory_t* factories, int count);

void load_factory_names_from_file(factory_t drill_factories[3], factory_t pump_factories[3], factory_t truck_factories[3], factory_t oil_fields[6]);
