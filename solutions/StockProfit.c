#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parse_natural_number(const char* s) {
    if (s == NULL || *s == '\0') {
        return -1;
    }
    
    if (*s == '+' || *s == '-') {
        return -1;
    }
    
    if (*s == '0' && *(s + 1) != '\0') {
        return -1;
    }
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) {
            return -1;
        }
    }
    
    long num = strtol(s, NULL, 10);
    if (num < 0 || num > 2147483647) {
        return -1;
    }
    
    return (int)num;
}

int max_profit(int* prices, int length) {
    if (length < 2) {
        return 0;
    }
    
    int min_price = prices[0];
    int max_profit_val = 0;
    
    for (int i = 1; i < length; i++) {
        int current_price = prices[i];
        
        int profit = current_price - min_price;
        
        if (profit > max_profit_val) {
            max_profit_val = profit;
        }
        
        if (current_price < min_price) {
            min_price = current_price;
        }
    }
    
    return max_profit_val;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("0\n");
        return 0;
    }
    
    int* prices = malloc((argc - 1) * sizeof(int));
    if (prices == NULL) {
        fprintf(stderr, "Error: not a valid number\n");
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        int price = parse_natural_number(argv[i]);
        if (price == -1) {
            fprintf(stderr, "Error: not a valid number\n");
            free(prices);
            return 1;
        }
        prices[i - 1] = price;
    }
    
    int profit = max_profit(prices, argc - 1);
    printf("%d\n", profit);
    
    free(prices);
    return 0;
}