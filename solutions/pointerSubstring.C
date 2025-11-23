#include <stdio.h>
#include <stdlib.h>

int decode_utf8_char(const char *str, int *char_len) {
    const unsigned char *s = (const unsigned char *)str;
    
    if (*s == 0) {
        *char_len = 0;
        return 0;
    }
    
    if ((*s & 0x80) == 0) {
        *char_len = 1;
        return *s;
    } else if ((*s & 0xE0) == 0xC0) {
        if (s[1] == 0 || (s[1] & 0xC0) != 0x80) return -1;
        *char_len = 2;
        return ((*s & 0x1F) << 6) | (s[1] & 0x3F);
    } else if ((*s & 0xF0) == 0xE0) {
        if (s[1] == 0 || s[2] == 0 || (s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80) return -1;
        *char_len = 3;
        return ((*s & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    } else if ((*s & 0xF8) == 0xF0) {
        if (s[1] == 0 || s[2] == 0 || s[3] == 0 || (s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80 || (s[3] & 0xC0) != 0x80) return -1;
        *char_len = 4;
        return ((*s & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    }
    
    return -1;
}

int get_needle_length_in_codepoints(const char *needle) {
    int count = 0;
    const char *ptr = needle;
    
    while (*ptr != '\0') {
        int char_len;
        int codepoint = decode_utf8_char(ptr, &char_len);
        if (codepoint == -1) {
            printf("Invalid UTF-8 sequence encountered.\n");
            exit(1);
        }
        ptr += char_len;
        count++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 0;
    }
    
    const char *haystack = argv[1];
    const char *needle = argv[2];
    
    if (*needle == '\0') {
        return 0;
    }
    
    int needle_codepoint_len = get_needle_length_in_codepoints(needle);
    const char *haystack_ptr = haystack;
    
    while (*haystack_ptr != '\0') {
        const char *h_temp = haystack_ptr;
        const char *n_temp = needle;
        int match = 1;
        int matched_codepoints = 0;
        
        while (*n_temp != '\0' && matched_codepoints < needle_codepoint_len) {
            if (*h_temp == '\0') {
                match = 0;
                break;
            }
            
            int h_char_len, n_char_len;
            int h_codepoint = decode_utf8_char(h_temp, &h_char_len);
            int n_codepoint = decode_utf8_char(n_temp, &n_char_len);
            
            if (h_codepoint == -1 || n_codepoint == -1) {
                printf("Invalid UTF-8 sequence encountered.\n");
                return 1;
            }
            
            if (h_codepoint != n_codepoint) {
                match = 0;
                break;
            }
            
            h_temp += h_char_len;
            n_temp += n_char_len;
            matched_codepoints++;
        }
        
        if (match && matched_codepoints == needle_codepoint_len) {
            printf("%d\n", (int)(haystack_ptr - haystack));
            return 0;
        }
        
        int char_len;
        int codepoint = decode_utf8_char(haystack_ptr, &char_len);
        if (codepoint == -1) {
            printf("Invalid UTF-8 sequence encountered.\n");
            return 1;
        }
        
        haystack_ptr += char_len;
    }
    
    printf("-1\n");
    return 0;
}