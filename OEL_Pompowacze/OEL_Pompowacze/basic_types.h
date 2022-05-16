
#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include <stdbool.h>

typedef signed long long int int64;
typedef unsigned long long int uint64;

typedef signed long int int32;
typedef unsigned long int uint32;

typedef signed short int int16;
typedef unsigned short int uint16;

typedef signed char int8;
typedef unsigned char uint8;

typedef signed char byte;
typedef unsigned char ubyte;

#if _WIN64
typedef unsigned long long ptr_size;
typedef unsigned long long size_t;
#elif _WIN32
typedef unsigned long ptr_size;
typedef unsigned long size_t;
#else
typedef unsigned long long ptr_size;
typedef unsigned long long size_t;
#endif

#endif // !BASIC_TYPES_H
