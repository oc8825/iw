#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_SIZE 1000

int heap[MAX_SIZE];
int heap_size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap[index] > heap[parent]) {
        swap(&heap[index], &heap[parent]);
        heapify_up(parent);
    }
}

void heapify_down(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    
    if (left < heap_size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < heap_size && heap[right] > heap[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapify_down(largest);
    }
}

void push(int value) {
    if (heap_size >= MAX_SIZE) {
        exit(2);
    }
    heap[heap_size] = value;
    heapify_up(heap_size);
    heap_size++;
}

int pop() {
    if (heap_size == 0) {
        exit(2);
    }
    int max = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapify_down(0);
    return max;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i], &endptr, 10);
        
        if (errno != 0 || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Error: command line argument not an integer\n");
            return 1;
        }
        
        push((int)val);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        if (i > 0) printf(" ");
        printf("%d", pop());
    }
    printf("\n");
    
    return 0;
}