//
// string.h

#ifndef STRING_H
#define STRING_H

#include "basic_types.h"
#include "exceptions.h"
#include "vector.h"
#include "extended_vector.h"

typedef struct vector string;

string string_create();
string string_create_from_cstring(const char *cstring);
string* string_create_dynamic();

void string_append(string* s, char c);
void string_append_range(string* s, char* range);
char string_get(const string* const s, uint32 index);
void string_set(string* s, uint32 index, char c);
void string_remove(string* s, uint32 index);
char* string_data(const string* const s);
char* string_begin(const string* s);
char* string_end(const string* s);
size_t string_size(const string* const s);
string string_copy(const string* s);

#endif // !STRING_H