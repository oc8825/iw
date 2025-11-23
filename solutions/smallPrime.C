#include <stdio.h>
#include <stdlib.h>

int is_valid_natural(char *str) {
    char *p = str;
    if (*p == '\0') return 0;
    while (*p != '\0') {
        if (*p < '0' || *p > '9') return 0;
        p++;
    }
    return 1;
}

int divisible_by_2(char *str) {
    char *p = str;
    while (*p != '\0') p++;
    p--;
    char last = *p;
    return (last == '0' || last == '2' || last == '4' || last == '6' || last == '8');
}

int divisible_by_3(char *str) {
    char *p = str;
    int sum = 0;
    while (*p != '\0') {
        sum += (*p - '0');
        p++;
    }
    return (sum % 3 == 0);
}

int divisible_by_5(char *str) {
    char *p = str;
    while (*p != '\0') p++;
    p--;
    char last = *p;
    return (last == '0' || last == '5');
}

int divisible_by_7(char *str) {
    char *p = str;
    int remainder = 0;
    while (*p != '\0') {
        remainder = (remainder * 10 + (*p - '0')) % 7;
        p++;
    }
    return (remainder == 0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    if (argc != 2) {
        return 2;
    }
    
    char *num_str = *(argv + 1);
    
    if (!is_valid_natural(num_str)) {
        return 2;
    }
    
    if (divisible_by_2(num_str)) {
        printf("2\n");
        return 0;
    }
    
    if (divisible_by_3(num_str)) {
        printf("3\n");
        return 0;
    }
    
    if (divisible_by_5(num_str)) {
        printf("5\n");
        return 0;
    }
    
    if (divisible_by_7(num_str)) {
        printf("7\n");
        return 0;
    }
    
    printf("0\n");
    return 0;
}