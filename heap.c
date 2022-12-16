#include "heap.h"

#include "stats.h"

#include <math.h>
#include <stdbool.h>

// The function max_child() returns the max child of a branch by comparing
// the left and right children
// Inputs: statistics count, array, the number we are on (first) and last
// Outputs: the largest value between the children

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if ((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) == 1)) {
        return right;
    } else {
        return left;
    }
}

// The function fix_heap() fixes the array to be a heap again
// Inputs: statistics count, the array, and the first and last (first is 1 and last
// is size just as in main)
// Outputs: none, just fixes the heap

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while ((mother <= floor(last / 2)) && (found != true)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
    return;
}

// The function build_heap() build the heap given an array so its in a "tree" formation
// Inputs: statistics count, the array, and the first (1) and last (size of array)
// Outputs: none

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > (first - 1); father -= 1) {
        fix_heap(stats, A, father, last);
    }
    return;
}

// The function heap_sort() is our main sorting function in this file, and sorts an array
// from the largest to smallest element by forming a tree where the top is
// the max and the children on the bottom are the smaller elements.
// Inputs: statistics count, the array, and the size of the array
// Outputs: none, it sorts the array.

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    reset(stats);
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}
