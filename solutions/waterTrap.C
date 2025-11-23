#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    int n = argc - 1;
    int *heights = (int*)malloc(n * sizeof(int));
    if (!heights) {
        return 2;
    }
    
    for (int i = 0; i < n; i++) {
        char *endptr;
        errno = 0;
        
        long val = strtol(argv[i + 1], &endptr, 10);
        
        if (errno != 0 || *endptr != '\0' || val < 0 || val > INT_MAX) {
            fprintf(stderr, "Error: invalid height\n");
            free(heights);
            return 1;
        }
        
        heights[i] = (int)val;
    }
    
    long long total_water = 0;
    
    for (int i = 0; i < n; i++) {
        int max_left = 0;
        for (int j = 0; j < i; j++) {
            if (heights[j] > max_left) {
                max_left = heights[j];
            }
        }
        
        int max_right = 0;
        for (int j = i + 1; j < n; j++) {
            if (heights[j] > max_right) {
                max_right = heights[j];
            }
        }
        
        int water_level = (max_left < max_right) ? max_left : max_right;
        if (water_level > heights[i]) {
            total_water += water_level - heights[i];
        }
    }
    
    printf("%lld\n", total_water);
    free(heights);
    return 0;
}