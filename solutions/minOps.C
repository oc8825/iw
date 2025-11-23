#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int parse_integer(const char* str, int* result) {
    char* endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    
    *result = (int)val;
    return 1;
}

int main(int argc, char* argv[]) {
    int N = argc - 1;
    
    if (N == 0) {
        return 0;
    }
    
    if (N == 1) {
        printf("Error: nums is empty.\n");
        return 1;
    }
    
    int k;
    if (!parse_integer(argv[N], &k)) {
        exit(2);
    }
    
    if (k <= 0) {
        printf("Error: k must be a positive integer.\n");
        return 1;
    }
    
    int* nums = (int*)malloc((N-1) * sizeof(int));
    if (!nums) {
        exit(2);
    }
    
    for (int i = 0; i < N-1; i++) {
        if (!parse_integer(argv[i+1], &nums[i])) {
            free(nums);
            exit(2);
        }
        
        if (nums[i] <= 0) {
            printf("Error: all values in nums must be positive.\n");
            free(nums);
            return 1;
        }
    }
    
    int* collected = (int*)calloc(k+1, sizeof(int));
    if (!collected) {
        free(nums);
        exit(2);
    }
    
    int collected_count = 0;
    int operations = 0;
    
    for (int i = N-2; i >= 0; i--) {
        operations++;
        
        if (nums[i] <= k && !collected[nums[i]]) {
            collected[nums[i]] = 1;
            collected_count++;
        }
        
        if (collected_count == k) {
            break;
        }
    }
    
    if (collected_count < k) {
        printf("Error: nums does not contain all integers 1..k.\n");
        free(nums);
        free(collected);
        return 1;
    }
    
    printf("%d\n", operations);
    
    free(nums);
    free(collected);
    return 0;
}