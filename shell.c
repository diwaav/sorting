#include "shell.h"

#include "stats.h"

#include <math.h>

// CITE: Professor Long's (I mean "Elmer's") power function from discord
// This function finds the power of a number
// Inputs : the number and its power
// Outputs: the number after the power has been applied

static inline uint64_t power(uint64_t a, uint64_t d) {
    uint64_t v = 1;
    for (uint64_t p = a; d > 0; d >>= 1) {
        if (d & 0x1) {
            v *= p;
        }
        p *= p;
    }
    return v;
}

// The function shell_sort() uses the shell method to sort through an array, creating a gap to
// compare two elements and decreasing the elements after moving to the end, until the
// gap is 1 element
// Inputs: statistics count, array, the size of the array
// Outputs: none, just sorts the array

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);
    uint32_t gap;
    uint32_t max_gap = log(3 + 2 * n) / log(3);

    for (uint32_t t = max_gap; t > 0; t--) {
        gap = (power(3, t) - 1) / 2;

        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while ((j >= gap) && (cmp(stats, temp, A[j - gap]) == -1)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
    return;
}
