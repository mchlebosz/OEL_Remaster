#include "algorithms.h"

void insertion_sort(int* data, unsigned int n) {
    for (int i = 1, j; i < n; ++i) {
        int tmp = data[i];
        for (j = i - 1; j >= 0 && data[j] > tmp; --j) {
            data[j + 1] = data[j];
        }
        data[j + 1] = tmp;
    }
}

int _median(int* data, int a, int b, int c) {
    int x = data[a] - data[b], y = data[b] - data[c], z = data[a] - data[c];
    return x * y > 0 ? b : x * z > 0 ? c : a;
}

int _partition(int* data, int left, int right) {
    int pivot = _median(data, data[left], data[(left + right) / 2], data[right]);
    int i = left, j = right;
    while (true) {
        while (data[j] > pivot) j--;
        while (data[i] < pivot) i++;

        if (i < j) {
            swap(data[i], data[j]);
            i++; j--;
        }
        else {
            return j;
        }
    }
}

void _quick_sort(int* data, int left, int right) {
    if (left >= right) return;

    int piv = _partition(data, left, right);
    _quick_sort(data, left, piv);
    _quick_sort(data, piv + 1, right);
}

void quick_sort(int* data, unsigned int n) {
    _quick_sort(data, 0, n - 1);
}

void _heapify(int* data, int i, unsigned int n) {
    int root = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && data[left] > data[root]) root = left;
    if (right < n && data[right] > data[root]) root = right;

    if (root != i) {
        swap(data[i], data[root]);
        _heapify(data, root, n);
    }
}

void create_heap(int* data, unsigned int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        _heapify(data, i, n);
    }
}

void heap_sort(int* data, unsigned int n) {
    create_heap(data, n);

    for (int i = n - 1; i > 0; --i) {
        swap(data[0], data[i]);
        _heapify(data, 0, i);
    }
}

void _intro_sort(int* data, int left, int right, int depth) {
    if (left >= right) return;

    unsigned int size = right - left + 1;
    if (size < 16) return insertion_sort(data + left, size);
    if (depth <= 0) return heap_sort(data + left, size);

    int piv = _partition(data, left, right);
    _intro_sort(data, left, piv, depth - 1);
    _intro_sort(data, piv + 1, right, depth - 1);
}

void intro_sort(int* data, unsigned int n) {
    int max_depth = 2 * log(n);
    _intro_sort(data, 0, n - 1, max_depth);
}