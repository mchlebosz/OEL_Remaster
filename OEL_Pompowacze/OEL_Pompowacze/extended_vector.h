//
// extended_vector.h

#ifndef EXT_VECTOR_H
#define EXT_VECTOR_H

#include "basic_types.h"
#include "vector.h"
#include "algorithms.h"

// creates char vector (not a string)
vector cvector_create();

//creates integer vector
vector ivector_create();

//creates float vector
vector fvector_create();

//creates double (long float) vector
vector dvector_create();

// push_back char type value
void cvector_push(vector* v, char value);

// push_back integer type value
void ivector_push(vector* v, int value);

// push_back float type value
void fvector_push(vector* v, float value);

// push_back double type value
void dvector_push(vector* v, double value);

// get_at char type value
char cvector_get(const vector* const v, uint32 index);

// get_at int type value
int ivector_get(const vector* const v, uint32 index);

// get_at float type value
float fvector_get(const vector* const v, uint32 index);

// get_at double type value
double dvector_get(const vector* const v, uint32 index);

//sorts ascending an integer vector
void ivector_sort(vector* v);


#endif // !EXT_VECTOR_H
