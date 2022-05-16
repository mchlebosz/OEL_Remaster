
#ifndef CSTRING_H
#define CSTRING_H




#include "basic_types.h"
#include "vector.h"
#include "extended_vector.h"

typedef struct vector string;

string string_create();

void string_append(string* s, char c);
char string_get(const string* const s, uint32 index);
void string_set(string* s, uint32 index, char c);
void string_remove(string* s, uint32 index);
const char* string_data(const string* const s);
size_t string_size(const string* const s);

#endif