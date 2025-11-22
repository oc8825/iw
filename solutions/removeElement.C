#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parse_natural_number(const char* str, unsigned long* result) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    
    char* endptr;
    unsigned long num = strtoul(str, &endptr, 10);
    
    if (*endptr != '\0') {
        return 0;
    }
    
    *result = num;
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: invalid number\n");
        return 1;
    }
    
    unsigned long target;
    if (!parse_natural_number(argv[1], &target)) {
        fprintf(stderr, "Error: invalid number\n");
        return 1;
    }
    
    if (argc == 2) {
        printf("\n");
        return 0;
    }
    
    unsigned long* filtered_list = (unsigned long*)malloc((argc - 2) * sizeof(unsigned long));
    if (filtered_list == NULL) {
        exit(2);
    }
    
    int filtered_count = 0;
    
    for (int i = 2; i < argc; i++) {
        unsigned long num;
        if (!parse_natural_number(argv[i], &num)) {
            free(filtered_list);
            fprintf(stderr, "Error: invalid number\n");
            return 1;
        }
        
        if (num != target) {
            filtered_list[filtered_count] = num;
            filtered_count++;
        }
    }
    
    if (filtered_count > 0) {
        for (int i = 0; i < filtered_count; i++) {
            if (i > 0) {
                printf(" ");
            }
            printf("%lu", filtered_list[i]);
        }
    }
    printf("\n");
    
    free(filtered_list);
    return 0;
}