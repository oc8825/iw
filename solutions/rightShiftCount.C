#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }

    int n = argc - 1;
    int *nums = (int*)malloc(n * sizeof(int));
    if (!nums) {
        printf("Invalid input\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *str = argv[i];
        
        if (!str || *str == '\0') {
            printf("Invalid input\n");
            free(nums);
            return 1;
        }
        
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] < '0' || str[j] > '9') {
                printf("Invalid input\n");
                free(nums);
                return 1;
            }
        }
        
        if (str[0] == '0' && str[1] != '\0') {
            printf("Invalid input\n");
            free(nums);
            return 1;
        }
        
        char *endptr;
        long val = strtol(str, &endptr, 10);
        
        if (*endptr != '\0' || val <= 0 || val > 2147483647) {
            printf("Invalid input\n");
            free(nums);
            return 1;
        }
        
        nums[i - 1] = (int)val;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j]) {
                printf("Invalid input\n");
                free(nums);
                return 1;
            }
        }
    }
    
    bool is_sorted = true;
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] >= nums[i + 1]) {
            is_sorted = false;
            break;
        }
    }
    
    if (is_sorted) {
        printf("0\n");
        free(nums);
        return 0;
    }
    
    int *temp = (int*)malloc(n * sizeof(int));
    if (!temp) {
        printf("-1\n");
        free(nums);
        return 0;
    }
    
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            temp[(i + k) % n] = nums[i];
        }
        
        bool sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (temp[i] >= temp[i + 1]) {
                sorted = false;
                break;
            }
        }
        
        if (sorted) {
            printf("%d\n", k);
            free(temp);
            free(nums);
            return 0;
        }
    }
    
    printf("-1\n");
    free(temp);
    free(nums);
    return 0;
}