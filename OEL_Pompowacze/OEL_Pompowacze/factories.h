#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum factory_type {
	DRILL,
	PUMP,
	TRUCK
};

struct factory {
	char* name;
	int items_left;
	int cost;
	int cost_per_drill;
	int player_id;
};

typedef struct factory factory_t;

void read_line(FILE* file, char line[32]) {
	fgets(line, 32, file);
	for (int i = 0; i < 32; ++i) {
		if (line[i] > 127) line[i] = (char)((int)line[i] - 256);
	}
	line[31] = '\0';
}

void _load_random_names_from_file(FILE* file, factory_t* factories, int count) {
	char buff[16][32];
	memset(buff, 0, 16 * 32 * sizeof(char));

	char* line = NULL;
	
	int lines = 0;
	for (int i = 0; !feof(file); ++i) {
		read_line(file, buff[i]);
		lines++;
	}

	bool selected[16];
	memset(selected, false, 16 * sizeof(bool));

	for (int i = 0; i < count; ++i) {
		int index = rand() % lines;

		while (selected[index]) {
			index = rand() % lines;
		}
		selected[index] = true;

		factories[i].name = (char*)malloc(16 * sizeof(char));
		memset(factories[i].name, 0, 16 * sizeof(char));
		strcpy(factories[i].name, buff[index]);
	}
}

void load_factory_names_from_file(factory_t drill_factories[3], factory_t pump_factories[3], factory_t truck_factories[3]) {
	FILE* file = fopen("drill_factories.txt", "rt");
	_load_random_names_from_file(file, drill_factories, 3);
	fclose(file);

	file = fopen("pump_factories.txt", "rt");
	_load_random_names_from_file(file, pump_factories, 3);
	fclose(file);

	file = fopen("truck_factories.txt", "rt");
	_load_random_names_from_file(file, truck_factories, 3);
	fclose(file);
}



