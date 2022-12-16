// CITE: TA Eugene's section for uint32_t *x = (uint32_t *) calloc(p_elements, sizeof(uint32_t))

#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// This function prints out information about how to properly use the sorting.c file
// Inputs: none
// Outputs: none
void message(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   A collection of comparison-based sorting algorithms.\n"
                    "\n"
                    "USAGE\n"
                    "   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              display program help and usage.\n"
                    "   -a              enable all sorts.\n"
                    "   -e              enable Heap Sort.\n"
                    "   -i              enable Insertion Sort.\n"
                    "   -s              enable Shell Sort.\n"
                    "   -q              enable Quick Sort.\n"
                    "   -n length       specify number of array elements (default: 100).\n"
                    "   -p elements     specify number of elements to print (default: 100).\n"
                    "   -r seed         specify random seed (default: 13371453).\n");
}

typedef enum { HEAP, SHELL, INSERTION, QUICK } Sorts;
#define OPTIONS "haeisqn:p:r:"

int main(int argc, char **argv) {
    // Declare default values, set, and mask
    Set chosen = empty_set();
    int option = 0;
    uint32_t r_seed = 13371453;
    uint32_t n_size = 100;
    uint32_t p_elements = 100;
    uint32_t mask = 0x3FFFFFFF; // bitmask to 30

    // As long as we have valid inputs, add the corresponding sort to the set
    // If help was chosen or something went wrong, send user to
    // the usage message and end the program
    while ((option = getopt(argc, argv, OPTIONS)) != -1) {
        switch (option) {
        case 'h': message(); return 0;
        case 'a':
            chosen = insert_set(HEAP, chosen);
            chosen = insert_set(SHELL, chosen);
            chosen = insert_set(INSERTION, chosen);
            chosen = insert_set(QUICK, chosen);
            break;
        case 'e': chosen = insert_set(HEAP, chosen); break;
        case 's': chosen = insert_set(SHELL, chosen); break;
        case 'i': chosen = insert_set(INSERTION, chosen); break;
        case 'q': chosen = insert_set(QUICK, chosen); break;
        case 'r': r_seed = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'n': n_size = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'p': p_elements = (uint32_t) strtoul(optarg, NULL, 10); break;
        default: message(); return 0;
        }
    }

    // If the uder did not specify a sort, encourage them to choose one and end the program
    if (chosen == empty_set()) {
        printf("Select at least one sort to perform.\n");
        message();
        return 0;
    }

    // Set the moves and compares, and set the random seed
    Stats statistics;
    reset(&statistics);
    srandom(r_seed);

    // Create the array using random masked elements
    uint32_t *array = (uint32_t *) calloc(n_size, sizeof(uint32_t));
    for (uint32_t i = 0; i < n_size; i += 1) {
        array[i] = random() & mask;
    }

    // If HEAP sort was choosen, perform the corresponding sort
    if (member_set(HEAP, chosen)) {
        heap_sort(&statistics, array, n_size);
        printf("Heap Sort, %u elements, %lu moves, %lu compares\n", n_size, statistics.moves,
            statistics.compares);
        if (n_size < p_elements) {
            p_elements = n_size;
        }
        for (uint32_t i = 0; i < p_elements; i += 1) {
            printf("%13" PRIu32, array[i]);
            if ((i == p_elements - 1) || ((i + 1) % 5 == 0)) {
                printf("\n");
            }
        }
    }

    // If SHELL sort was choosen, perform the corresponding sort
    if (member_set(SHELL, chosen)) {
        srandom(r_seed);
        for (uint32_t i = 0; i < n_size; i += 1) {
            array[i] = random() & mask;
        }
        shell_sort(&statistics, array, n_size);
        printf("Shell Sort, %u elements, %lu moves, %lu compares\n", n_size, statistics.moves,
            statistics.compares);
        if (n_size < p_elements) {
            p_elements = n_size;
        }
        for (uint32_t i = 0; i < p_elements; i += 1) {
            printf("%13" PRIu32, array[i]);
            if ((i == p_elements - 1) || ((i + 1) % 5 == 0)) {
                printf("\n");
            }
        }
    }

    // If INSERTION sort was choosen, perform the corresponding sort
    if (member_set(INSERTION, chosen)) {
        srandom(r_seed);
        for (uint32_t i = 0; i < n_size; i += 1) {
            array[i] = random() & mask;
        }
        insertion_sort(&statistics, array, n_size);
        printf("Insertion Sort, %u elements, %lu moves, %lu compares\n", n_size, statistics.moves,
            statistics.compares);
        if (n_size < p_elements) {
            p_elements = n_size;
        }
        for (uint32_t i = 0; i < p_elements; i += 1) {
            printf("%13" PRIu32, array[i]);
            if ((i == p_elements - 1) || ((i + 1) % 5 == 0)) {
                printf("\n");
            }
        }
    }

    // If QUICK sort was choosen, perform the corresponding sort
    if (member_set(QUICK, chosen)) {
        srandom(r_seed);
        for (uint32_t i = 0; i < n_size; i += 1) {
            array[i] = random() & mask;
        }
        quick_sort(&statistics, array, n_size);
        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", n_size, statistics.moves,
            statistics.compares);
        if (n_size < p_elements) {
            p_elements = n_size;
        }
        for (uint32_t i = 0; i < p_elements; i += 1) {
            printf("%13" PRIu32, array[i]);
            if ((i == p_elements - 1) || ((i + 1) % 5 == 0)) {
                printf("\n");
            }
        }
    }

    // Free the memory allocated to the array
    free(array);
    return 0;
}
