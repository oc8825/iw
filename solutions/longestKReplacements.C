#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 0;
    }
    
    if (argc > 3) {
        return 2;
    }
    
    char *s = argv[1];
    char *k_str = argv[2];
    
    // Check if string is empty
    if (strlen(s) == 0) {
        return 2;
    }
    
    // Validate string contains only A-Z
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < 'A' || s[i] > 'Z') {
            return 2;
        }
    }
    
    // Parse k
    char *endptr;
    long k_long = strtol(k_str, &endptr, 10);
    
    // Check if parsing was successful and k is non-negative
    if (*endptr != '\0' || k_long < 0 || k_long > 2147483647) {
        return 2;
    }
    
    int k = (int)k_long;
    int n = strlen(s);
    
    // Sliding window algorithm
    int freq[26] = {0};
    int left = 0;
    int max_freq = 0;
    int max_length = 0;
    
    for (int right = 0; right < n; right++) {
        // Add current character to window
        int char_index = s[right] - 'A';
        freq[char_index]++;
        
        // Update max frequency in current window
        if (freq[char_index] > max_freq) {
            max_freq = freq[char_index];
        }
        
        // Check if window is valid (replacements needed <= k)
        int window_size = right - left + 1;
        int replacements_needed = window_size - max_freq;
        
        // Shrink window if too many replacements needed
        while (replacements_needed > k) {
            int left_char_index = s[left] - 'A';
            freq[left_char_index]--;
            left++;
            
            // Recalculate max frequency
            max_freq = 0;
            for (int i = 0; i < 26; i++) {
                if (freq[i] > max_freq) {
                    max_freq = freq[i];
                }
            }
            
            window_size = right - left + 1;
            replacements_needed = window_size - max_freq;
        }
        
        // Update max length
        if (window_size > max_length) {
            max_length = window_size;
        }
    }
    
    printf("%d\n", max_length);
    return 0;
}