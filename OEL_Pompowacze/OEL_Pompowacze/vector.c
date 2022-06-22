#include "vector.h"

vector vector_create(uint32 type_size)
{
	vector v = { NULL, type_size, 0, 8 };
	v.data = (void*)malloc(type_size * (v.max_size + 1));
	return v;
}

vector* vector_create_dynamic(uint32 type_size)
{
	vector* v = (vector*)malloc(sizeof(vector));
	if (v) {
		*v = vector_create(type_size);
		return v;
	}
	exception_allocation_error();
	return NULL;
}

void vector_load_array(vector* v, void* array, uint32 array_size)
{
	free(v->data);
	*v = vector_create(v->type_size);
	_vector_resize(v, array_size);
	memcpy(v->data, array, array_size * v->type_size);
}

void vector_free(const vector* v)
{
	free(v->data);
}

void vector_push(vector* v, void* value)
{
	_vector_resize(v, 1);
	memcpy((void*)((ptr_size)v->data + ((ptr_size)v->size - 1) * (ptr_size)v->type_size), value, v->type_size);
}

void vector_push_range(vector* v, const vector* range)
{
	if (v->type_size != range->type_size) exception_wrong_type();

	_vector_resize(v, range->size);
	memcpy((void*)((ptr_size)v->data + (ptr_size)(v->size - range->size) * (ptr_size)v->type_size), range->data, v->type_size * range->size);
}

void vector_insert(vector* v, uint32 index, void* value)
{
	if (index > v->size) exception_out_of_range();

	_vector_resize(v, 1);
	ptr_size begin = (ptr_size)v->data + (ptr_size)index * v->type_size;
	memmove((void*)(begin + (ptr_size)v->type_size), (void*)begin, (v->size - index) * v->type_size);
	memcpy((void*)begin, value, v->type_size);
}

void vector_insert_range(vector* v, uint32 index, const vector* const range)
{
	if (v->type_size != range->type_size) exception_wrong_type();
	if (index > v->size) exception_out_of_range();

	_vector_resize(v, range->size);
	ptr_size begin = (ptr_size)v->data + (ptr_size)index * v->type_size;
	memmove((void*)(begin + (ptr_size)(v->type_size * range->size)), (void*)begin, (v->size - range->size) * v->type_size);
	memcpy((void*)begin, range->data, range->size * v->type_size);
}

void vector_remove(vector* v, uint32 index)
{
	ptr_size begin  = (ptr_size)v->data + (ptr_size)index * v->type_size;
	memmove((void*)begin, (void*)(begin + (ptr_size)v->type_size), (v->size - index) * v->type_size);
	_vector_resize(v, -1);
}

void vector_remove_range(vector* v, uint32 index, uint32 count)
{
	if (index + count > v->size) exception_out_of_range();

	ptr_size begin = (ptr_size)v->data + (ptr_size)index * v->type_size;
	memmove((void*)begin, (void*)(begin + (ptr_size)(v->type_size * count)), (v->size - index - count + 1) * v->type_size);
	_vector_resize(v, -(int)count);
}

void* vector_get(const vector* const v, uint32 index)
{
	if (!(0 <= index && index < v->size)) exception_out_of_range();
	return (void*)((ptr_size)v->data + (ptr_size)index * v->type_size);
}

void vector_set(vector*v, uint32 index, void* value)
{
	if (!(0 <= index && index < v->size)) exception_out_of_range();
	memcpy((ptr_size)v->data + index * (v->type_size), value, v->type_size);
}

void vector_reverse(vector* v)
{
	for (int i = 0; i < v->size / 2; ++i) {
		void* front = (ptr_size)v->data + i * (ptr_size)v->type_size;
		void* back = (ptr_size)v->data + (ptr_size)(v->size - i - 1) * v->type_size;
		void* first = malloc(v->type_size);
		void* second = malloc(v->type_size);
		memmove(first, front, v->type_size);
		memmove(second, back, v->type_size);
		memmove(front, second, v->type_size);
		memmove(back, first, v->type_size);
		free(first);
		free(second);
	}
}

void _vector_resize(vector* v, int32 delta)
{
	int old_size = v->max_size;
	while (v->size + delta > v->max_size) v->max_size <<= 1;
	while (v->size + delta < v->max_size / 3 && v->max_size > 8) v->max_size >>= 1;

	v->size += delta;
	
	if (old_size == v->max_size) return;
	

	void* tmp = realloc(v->data, (v->max_size + 1) * v->type_size);
	if (!tmp) exception_allocation_error();
	v->data = tmp;
}