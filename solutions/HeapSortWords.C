#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 1000
#define MAX_WORD_LENGTH 1000

char heap[MAX_HEAP_SIZE][MAX_WORD_LENGTH];
int heap_size = 0;

void swap(int i, int j) {
    char temp[MAX_WORD_LENGTH];
    strcpy(temp, heap[i]);
    strcpy(heap[i], heap[j]);
    strcpy(heap[j], temp);
}

void heapify_up(int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (strcmp(heap[index], heap[parent]) < 0) {
        swap(index, parent);
        heapify_up(parent);
    }
}

void heapify_down(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    
    if (left < heap_size && strcmp(heap[left], heap[smallest]) < 0) {
        smallest = left;
    }
    if (right < heap_size && strcmp(heap[right], heap[smallest]) < 0) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(index, smallest);
        heapify_down(smallest);
    }
}

void push(char* word) {
    if (heap_size >= MAX_HEAP_SIZE) {
        exit(2);
    }
    if (strlen(word) >= MAX_WORD_LENGTH) {
        exit(2);
    }
    strcpy(heap[heap_size], word);
    heapify_up(heap_size);
    heap_size++;
}

char* pop() {
    if (heap_size == 0) {
        exit(2);
    }
    static char result[MAX_WORD_LENGTH];
    strcpy(result, heap[0]);
    heap_size--;
    if (heap_size > 0) {
        strcpy(heap[0], heap[heap_size]);
        heapify_down(0);
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        push(argv[i]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        if (i > 0) printf(" ");
        printf("%s", pop());
    }
    printf("\n");
    
    return 0;
}