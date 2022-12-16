#include "quick.h"

#include "stats.h"

// The function partition() forms the parting point for quicksort
// Inputs: statistics count, array, the low and high variable to consider while forming part
// Outputs: the partitian point

uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j += 1) {
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return (i + 1);
}

// The quick_sorter() function seperates the array by finding the partitian and then sorting
// the left and right side of the partition
// Inputs: statistics count, array, the low (1) and high (size)
// Outputs: none

void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p;
        p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
    return;
}

// The function quick_sort() is the main sorter function in this file, and sends the array that
// needs to be sorted to the quick_sorter() function.
// Inputs: statistics count, array, and size of array
// Outputs: none

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);
    quick_sorter(stats, A, 1, n);
    return;
}
