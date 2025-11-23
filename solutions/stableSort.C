#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int original_index;
} WordEntry;

int compare_words(const WordEntry *a, const WordEntry *b) {
    int len_a = strlen(a->word);
    int len_b = strlen(b->word);
    
    if (len_a != len_b) {
        return len_a - len_b;
    }
    
    int cmp = strcmp(a->word, b->word);
    if (cmp != 0) {
        return cmp;
    }
    
    return a->original_index - b->original_index;
}

void merge(WordEntry *arr, int left, int mid, int right, WordEntry *temp) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (compare_words(&arr[i], &arr[j]) <= 0) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void iterative_merge_sort(WordEntry *arr, int n) {
    WordEntry *temp = (WordEntry *)malloc(n * sizeof(WordEntry));
    if (!temp) {
        exit(2);
    }
    
    for (int curr_size = 1; curr_size < n; curr_size *= 2) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = left_start + 2 * curr_size - 1;
            
            if (mid >= n) {
                break;
            }
            
            if (right_end >= n) {
                right_end = n - 1;
            }
            
            merge(arr, left_start, mid, right_end, temp);
        }
    }
    
    free(temp);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    int word_count = argc - 1;
    WordEntry *words = (WordEntry *)malloc(word_count * sizeof(WordEntry));
    if (!words) {
        exit(2);
    }
    
    for (int i = 0; i < word_count; i++) {
        words[i].word = argv[i + 1];
        words[i].original_index = i;
    }
    
    iterative_merge_sort(words, word_count);
    
    for (int i = 0; i < word_count; i++) {
        printf("%s", words[i].word);
        if (i < word_count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(words);
    return 0;
}