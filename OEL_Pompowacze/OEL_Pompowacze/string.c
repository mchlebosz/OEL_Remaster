#include "string.h"

string string_create()
{
	vector v = cvector_create();
	cvector_push(&v, '\0');
	return *(string*)&v;
}

string string_create_from_cstring(const char* cstring)
{
	string s = string_create();
	string_append_range(&s, cstring);
	return s;
}

string* string_create_dynamic()
{
	vector* v = vector_create_dynamic(sizeof(char));
	cvector_push(v, '\0');
	return (string*)v;
}

void string_append(string* s, char c)
{
	vector_set(s, s->size - 1, &c);
	cvector_push(s, '\0');
}

void string_append_range(string* s, char* range)
{
	vector* v = s;
	
	vector_remove(v, v->size - 1);
	while (*range != '\0') {
		cvector_push(v, *range++);
	}
	cvector_push(v, '\0');
}

char string_get(const string* const s, uint32 index)
{
	return *(char*)vector_get(s, index);
}

void string_set(string* s, uint32 index, char c)
{
	if (index >= s->size - 1) exception_out_of_range();
	vector_set(s, index, &c);
}

void string_remove(string* s, uint32 index)
{
	if (index >= s->size - 1) exception_out_of_range();
	vector_remove(s, index);
}

char* string_data(const string* const s)
{
	return (char*)s->data;
}

char* string_begin(const string* s)
{
	return s->data;
}

char* string_end(const string* s)
{
	return (char*)((ptr_size)s->data + s->size);
}

size_t string_size(const string* const s)
{
	return s->size - 1;
}

string string_copy(const string* s)
{
	return string_create_from_cstring(s->data);
}




