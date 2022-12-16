#include "insert.h"

#include "stats.h"

// The function insertion_sort() uses the insertion method to perform a classic sort
// going through each element, and sorts the array from smallest to largest number
// Inputs: statistics count, the array, an the size of the array
// Outputs: none, it sorts the array.

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);
    for (uint32_t i = 1; i < n; i += 1) {
        uint32_t j = i;
        uint32_t temp = move(stats, A[i]);
        while ((j > 0) && (cmp(stats, temp, A[j - 1]) == -1)) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
    return;
}
