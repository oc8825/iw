#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int is_valid_integer(const char *str) {
    if (!str || *str == '\0') return 0;
    
    int i = 0;
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }
    
    if (str[i] == '\0') return 0;
    
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') return 0;
        i++;
    }
    
    return 1;
}

long long parse_integer(const char *str) {
    long long result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[i] == '+') {
        i++;
    } else if (str[i] == '-') {
        sign = -1;
        i++;
    }
    
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return sign * result;
}

int longest_increasing_subsequence(long long *arr, int n) {
    if (n == 0) return 0;
    
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    int max_length = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > max_length) {
            max_length = dp[i];
        }
    }
    
    free(dp);
    return max_length;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    long long *numbers = (long long *)malloc((argc - 1) * sizeof(long long));
    
    for (int i = 1; i < argc; i++) {
        if (!is_valid_integer(argv[i])) {
            fprintf(stderr, "Error: invalid integer argument\n");
            free(numbers);
            return 1;
        }
        numbers[i - 1] = parse_integer(argv[i]);
    }
    
    int lis_length = longest_increasing_subsequence(numbers, argc - 1);
    printf("%d\n", lis_length);
    
    free(numbers);
    return 0;
}