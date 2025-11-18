#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("0\n");
        return 0;
    }
    
    int *numbers = (int*)malloc((argc - 1) * sizeof(int));
    if (!numbers) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i], &endptr, 10);
        
        if (errno != 0 || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Error: command line argument not an integer\n");
            free(numbers);
            exit(1);
        }
        
        numbers[i - 1] = (int)val;
    }
    
    qsort(numbers, argc - 1, sizeof(int), compare);
    
    int max_length = 1;
    int current_length = 1;
    
    for (int i = 1; i < argc - 1; i++) {
        if (numbers[i] == numbers[i - 1]) {
            continue;
        } else if (numbers[i] == numbers[i - 1] + 1) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 1;
        }
    }
    
    if (current_length > max_length) {
        max_length = current_length;
    }
    
    printf("%d\n", max_length);
    free(numbers);
    return 0;
}