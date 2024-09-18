#ifndef ARRAY_H
#define ARRAY_H

/**
 * Macro to push a value onto the array
 *
 * @array: Pointer to the array
 * @value: Value to be added to the array
*/

#define array_push(array, value)                                              \
    do {                                                                      \
        (array) = array_hold((array), 1, sizeof(*(array)));                   \
        (array)[array_length(array) - 1] = (value);                           \
    } while (0);

/**
 * Ensure the array can hold a specified number of elements
 *
 * @array: Pointer to the array
 * @count: Number of elements to ensure space for
 * @item_size: Size of each element in bytes
 * @return: Pointer to the array
 * */
void* array_hold(void* array, int count, int item_size);

/**
 * Get the number of elements in the array
 *
 * @array: Pointer to the array
 * @return: Nmuber of elements in the array, or 0 if array is NULL
 * */
int array_length(void* array);

/**
 * Free the memory allocated for the array
 *
 * @array: Pointer to the array
*/
void array_free(void* array);

#endif
