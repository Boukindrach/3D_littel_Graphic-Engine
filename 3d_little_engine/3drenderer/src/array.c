#include <stdio.h>
#include <stdlib.h>
#include "array.h"

// Macors for accessing array metadata
#define ARRAY_RAW_DATA(array) ((int*)(array) - 2)
#define ARRAY_CAPACITY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_OCCUPIED(array) (ARRAY_RAW_DATA(array)[1])

/**
 * Ensures the array can hold a specified number of elements
 *
 * @array: Pointer to the array.
 * @count: Number of elements to ensure space for
 * @item_size: Size of each element in bytes
 * @return: Pointer to the array  
 * */
void* array_hold(void* array, int count, int item_size) {
    if (array == NULL) {
	// Create a new array
        int raw_size = (sizeof(int) * 2) + (item_size * count);
        int* base = (int*)malloc(raw_size);
        base[0] = count;  // capacity
        base[1] = count;  // occupied
        return base + 2;
    } else if (ARRAY_OCCUPIED(array) + count <= ARRAY_CAPACITY(array)) {
	// Array has enough capacity, just update occupied count
        ARRAY_OCCUPIED(array) += count;
        return array;
    } else {
	// Need to resize the array
        int needed_size = ARRAY_OCCUPIED(array) + count;
        int double_curr = ARRAY_CAPACITY(array) * 2;
        int capacity = needed_size > double_curr ? needed_size : double_curr;
        int occupied = needed_size;
        int raw_size = sizeof(int) * 2 + item_size * capacity;
        int* base = (int*)realloc(ARRAY_RAW_DATA(array), raw_size);
        base[0] = capacity;
        base[1] = occupied;
        return base + 2;
    }
}

/**
 * Get the number of elements in the array
 *
 * @array: Pointer to the array
 * @return: Number of elements in the array, or 0 if array is NULL
 */
int array_length(void* array) {
    return (array != NULL) ? ARRAY_OCCUPIED(array) : 0;
}

/**
 * Free the memory allocated for the array
 *
 * @array: Pointer to the array
 * */
void array_free(void* array) {
    if (array != NULL) {
        free(ARRAY_RAW_DATA(array));
    }
}
