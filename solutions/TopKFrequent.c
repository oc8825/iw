#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int value;
    int frequency;
} IntFreq;

int is_valid_integer(const char *str) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    
    return 1;
}

int compare_freq(const void *a, const void *b) {
    IntFreq *ia = (IntFreq *)a;
    IntFreq *ib = (IntFreq *)b;
    
    if (ia->frequency != ib->frequency) {
        return ib->frequency - ia->frequency;
    }
    
    return ia->value - ib->value;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    if (!is_valid_integer(argv[1])) {
        fprintf(stderr, "Error: command line argument not an integer\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    if (argc <= 2) {
        return 0;
    }
    
    int *numbers = malloc((argc - 2) * sizeof(int));
    if (!numbers) {
        return 2;
    }
    
    for (int i = 2; i < argc; i++) {
        if (!is_valid_integer(argv[i])) {
            fprintf(stderr, "Error: command line argument not an integer\n");
            free(numbers);
            return 1;
        }
        numbers[i - 2] = atoi(argv[i]);
    }
    
    int num_count = argc - 2;
    IntFreq *freq_array = malloc(num_count * sizeof(IntFreq));
    if (!freq_array) {
        free(numbers);
        return 2;
    }
    
    int unique_count = 0;
    
    for (int i = 0; i < num_count; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (freq_array[j].value == numbers[i]) {
                freq_array[j].frequency++;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            freq_array[unique_count].value = numbers[i];
            freq_array[unique_count].frequency = 1;
            unique_count++;
        }
    }
    
    qsort(freq_array, unique_count, sizeof(IntFreq), compare_freq);
    
    int output_count = (k < unique_count) ? k : unique_count;
    
    for (int i = 0; i < output_count; i++) {
        printf("%d", freq_array[i].value);
        if (i < output_count - 1) {
            printf(" ");
        }
    }
    
    if (output_count > 0) {
        printf("\n");
    }
    
    free(numbers);
    free(freq_array);
    return 0;
}