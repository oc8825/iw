#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    if (argc != 3) {
        fprintf(stderr, "Error: expected 2 arguments\n");
        return 1;
    }
    
    char *s = argv[1];
    char *k_str = argv[2];
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '0' && s[i] != '1') {
            fprintf(stderr, "Error: invalid binary string\n");
            return 1;
        }
    }
    
    char *endptr;
    long k_long = strtol(k_str, &endptr, 10);
    
    if (*endptr != '\0' || k_long < 0 || k_str[0] == '\0') {
        fprintf(stderr, "Error: invalid k\n");
        return 1;
    }
    
    int k = (int)k_long;
    int len = strlen(s);
    
    int best_start = -1;
    int best_length = len + 1;
    
    for (int start = 0; start < len; start++) {
        int ones_count = 0;
        
        for (int end = start; end < len; end++) {
            if (s[end] == '1') {
                ones_count++;
            }
            
            int current_length = end - start + 1;
            
            if (ones_count == k) {
                if (current_length < best_length) {
                    best_start = start;
                    best_length = current_length;
                } else if (current_length == best_length) {
                    if (strncmp(s + start, s + best_start, current_length) < 0) {
                        best_start = start;
                    }
                }
            }
            
            if (ones_count > k) {
                break;
            }
        }
    }
    
    if (best_start != -1) {
        for (int i = 0; i < best_length; i++) {
            putchar(s[best_start + i]);
        }
        putchar('\n');
    } else {
        putchar('\n');
    }
    
    return 0;
}