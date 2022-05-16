#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "basic_types.h"
#include <math.h>

#ifdef swap
#undef swap
#endif // swap

#define swap(x,y) do\
   { ubyte swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1];\
       memcpy(swap_temp, &y, sizeof(x));\
       memcpy(&y, &x, sizeof(x));\
       memcpy(&x, swap_temp, sizeof(x));\
    } while (0)




void insertion_sort(int* data, unsigned int n);
void quick_sort(int* data, unsigned int n);
void heap_sort(int* data, unsigned int n);
void intro_sort(int* data, unsigned int n);

void create_heap(int* data, unsigned int n);

//int _median(int* data, int a, int b, int c);
//int _partition(int* data, int left, int right);
//void _quick_sort(int* data, int left, int right);
//void _heapify(int* data, int i, unsigned int n);
//void _intro_sort(int* data, int left, int right, int depth);

#endif // !ALGORITHMS_H
