#include "extended_vector.h"

vector cvector_create()
{
    return vector_create(sizeof(char));
}

vector ivector_create()
{
    return vector_create(sizeof(int));
}
vector fvector_create()
{
    return vector_create(sizeof(float));
}

vector dvector_create()
{
    return vector_create(sizeof(float));
}

vector svector_create()
{
    return vector_create(sizeof(string));
}

void cvector_push(vector* v, char value)
{
    vector_push(v, &value);
}

void ivector_push(vector* v, int value)
{
    vector_push(v, &value);
}

void fvector_push(vector* v, float value)
{
    vector_push(v, &value);
}

void dvector_push(vector* v, double value)
{
    vector_push(v, &value);
}

void svector_push(vector* v, string value)
{
    vector_push(v, &value);
}

char cvector_get(const vector* const v, uint32 index)
{
    return *(char*)vector_get(v, index);
}

int ivector_get(const vector* const v, uint32 index)
{
    return *(int*)vector_get(v, index);
}

float fvector_get(const vector* const v, uint32 index)
{
    return *(float*)vector_get(v, index);
}

double dvector_get(const vector* const v, uint32 index)
{
    return *(double*)vector_get(v, index);
}

string svector_get(const vector* const v, uint32 index)
{
    return *(string*)vector_get(v, index);
}

void ivector_sort(vector* v)
{
    intro_sort(v->data, v->size);
}

