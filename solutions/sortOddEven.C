#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntArray;

void init_array(IntArray *array) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

void free_array(IntArray *array) {
    free(array->data);
}

bool append_to_array(IntArray *array, int value) {
    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        int *new_data = (int *)realloc(array->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return false;
        }
        array->data = new_data;
        array->capacity = new_capacity;
    }
    array->data[array->size++] = value;
    return true;
}

void selection_sort(IntArray *array) {
    for (size_t i = 0; i < array->size - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < array->size; j++) {
            if (array->data[j] < array->data[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = array->data[i];
            array->data[i] = array->data[min_idx];
            array->data[min_idx] = temp;
        }
    }
}

bool is_valid_natural_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    for (const char *p = str; *p; p++) {
        if (*p < '0' || *p > '9') {
            return false;
        }
    }
    long value = strtoul(str, NULL, 10);
    return value <= INT32_MAX;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }

    IntArray odds;
    IntArray evens;
    init_array(&odds);
    init_array(&evens);

    int *numbers = (int *)malloc((argc - 1) * sizeof(int));
    if (numbers == NULL) {
        return 2;
    }

    for (int i = 1; i < argc; i++) {
        if (!is_valid_natural_number(argv[i])) {
            free(numbers);
            free_array(&odds);
            free_array(&evens);
            return 2;
        }
        numbers[i - 1] = atoi(argv[i]);
    }

    for (int i = 0; i < argc - 1; i++) {
        for (int j = i + 1; j < argc - 1; j++) {
            if (numbers[i] == numbers[j]) {
                free(numbers);
                free_array(&odds);
                free_array(&evens);
                return 2;
            }
        }
    }

    for (int i = 0; i < argc - 1; i++) {
        if (numbers[i] % 2 == 0) {
            if (!append_to_array(&evens, numbers[i])) {
                free(numbers);
                free_array(&odds);
                free_array(&evens);
                return 2;
            }
        } else {
            if (!append_to_array(&odds, numbers[i])) {
                free(numbers);
                free_array(&odds);
                free_array(&evens);
                return 2;
            }
        }
    }

    free(numbers);

    selection_sort(&odds);
    selection_sort(&evens);

    for (size_t i = 0; i < odds.size; i++) {
        printf("%d", odds.data[i]);
        if (i < odds.size - 1) {
            printf(" ");
        }
    }
    printf("\n");

    for (size_t i = 0; i < evens.size; i++) {
        printf("%d", evens.data[i]);
        if (i < evens.size - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free_array(&odds);
    free_array(&evens);

    return 0;
}