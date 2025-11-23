#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    
    char *pattern = argv[1];
    char *pattern_ptr = pattern;
    int pattern_len = 0;
    
    while (*pattern_ptr) {
        pattern_len++;
        pattern_ptr++;
    }
    
    if (pattern_len == 0) {
        fprintf(stderr, "Error: invalid string\n");
        return 1;
    }
    
    if (argc == 2) {
        printf("-1\n");
        return 0;
    }
    
    for (int i = 2; i < argc; i++) {
        char *arg_ptr = argv[i];
        int arg_len = 0;
        while (*arg_ptr) {
            arg_len++;
            arg_ptr++;
        }
        if (arg_len == 0) {
            fprintf(stderr, "Error: invalid string\n");
            return 1;
        }
    }
    
    int haystack_len = 0;
    for (int i = 2; i < argc; i++) {
        char *arg_ptr = argv[i];
        while (*arg_ptr) {
            haystack_len++;
            arg_ptr++;
        }
    }
    
    if (haystack_len < pattern_len) {
        printf("-1\n");
        return 0;
    }
    
    int haystack_pos = 0;
    
    while (haystack_pos <= haystack_len - pattern_len) {
        int current_haystack_pos = 0;
        int arg_index = 2;
        char *current_pos = argv[arg_index];
        
        while (current_haystack_pos < haystack_pos && arg_index < argc) {
            if (*current_pos == '\0') {
                arg_index++;
                if (arg_index < argc) {
                    current_pos = argv[arg_index];
                }
            } else {
                current_pos++;
                current_haystack_pos++;
            }
        }
        
        if (arg_index >= argc) {
            break;
        }
        
        char *pat_ptr = pattern;
        int match_len = 0;
        int temp_arg_index = arg_index;
        char *temp_pos = current_pos;
        
        while (match_len < pattern_len && temp_arg_index < argc) {
            if (*temp_pos == '\0') {
                temp_arg_index++;
                if (temp_arg_index >= argc) {
                    break;
                }
                temp_pos = argv[temp_arg_index];
                continue;
            }
            
            if (*temp_pos != *pat_ptr) {
                break;
            }
            
            temp_pos++;
            pat_ptr++;
            match_len++;
        }
        
        if (match_len == pattern_len) {
            printf("%d\n", haystack_pos);
            return 0;
        }
        
        haystack_pos++;
    }
    
    printf("-1\n");
    return 0;
}