//
// vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include "basic_types.h"
#include "exceptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector {
	void* data;
	uint32 type_size;
	uint32 size;
	uint32 max_size;
};

typedef struct vector vector;


vector vector_create(uint32 type_size);
vector* vector_create_dynamic(uint32 type_size);
void vector_load_array(vector* v, void* array, uint32 array_size);
void vector_free(vector* v);

void vector_push(vector* v, void* value);
void vector_push_range(vector* v, const vector* range);

void vector_insert(vector* v, uint32 index, void* value);
void vector_insert_range(vector* v, uint32 index, const vector* const range);

void vector_remove(vector* v, uint32 index);
void vector_remove_range(vector* v, uint32 index, uint32 count);

void* vector_get(const vector* const v, uint32 index);
void vector_set(vector*v, uint32 index, void* value);

void vector_reverse(vector* v);

void _vector_resize(vector* v, int32 delta);

#endif // !VECTOR_H