# Sorting [CSE 13S]
This program uses various sorting methods to sort integers in a random array. 
The user has the option to ask the program to print a certain number of elements, 
set the seed, and size of the array. 
The sorting algorithm options include heap sort, quick sort, shell sort, and insertion sort.

## Building
Build the program with:
```
$ make
```
You can check the formatting using:
```
$ make format
```
Remember to clean up afterwards so there are no object files or executables left over:
```
$ make clean
```

## Running
Run the program using:
```
$ ./sorting
```
followed by a command where:
```
-a performs all sorting algorithms
-e performs Heap Sort
-i performs Insert Sort
-s performs Shell Sort
-q performs Quicksort
-r set a random seed, with default as 13371453
-n set array size, with default as 100
-p set number of elements to print out from the array, with default as 100
-h help
```
User must provide a integer as input after -r, -n, or -p.
For example, ./sorting -e -n 10 -p 3

## Possible Errors
I was not able to find any errors that were different from the sorting file provided in resources while testing.
In general, errors were sent when numbers were too large. For example, "./sorting -e -n 1000000000000" would 
result in a "Segmentation fault (core dumped)" error because the size is too large.
