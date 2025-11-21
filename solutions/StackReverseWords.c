#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **data;
    int size;
    int capacity;
} Stack;

Stack* stack_create() {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->data = malloc(sizeof(char*));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = 1;
    return stack;
}

int stack_push(Stack *stack, char *str) {
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        char **new_data = realloc(stack->data, stack->capacity * sizeof(char*));
        if (!new_data) return -1;
        stack->data = new_data;
    }
    
    stack->data[stack->size] = str;
    stack->size++;
    return 0;
}

char* stack_pop(Stack *stack) {
    if (stack->size <= 0) return NULL;
    stack->size--;
    return stack->data[stack->size];
}

int stack_is_empty(Stack *stack) {
    return stack->size == 0;
}

void stack_destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

char* deep_copy_string(char *src) {
    char *p = src;
    int len = 0;
    
    while (*p) {
        len++;
        p++;
    }
    
    char *copy = malloc((len + 1) * sizeof(char));
    if (!copy) return NULL;
    
    char *src_ptr = src;
    char *dst_ptr = copy;
    
    while (*src_ptr) {
        *dst_ptr = *src_ptr;
        src_ptr++;
        dst_ptr++;
    }
    *dst_ptr = '\0';
    
    return copy;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    
    Stack *stack = stack_create();
    if (!stack) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char *copy = deep_copy_string(*(argv + i));
        if (!copy) {
            while (!stack_is_empty(stack)) {
                char *str = stack_pop(stack);
                free(str);
            }
            stack_destroy(stack);
            exit(2);
        }
        
        if (stack_push(stack, copy) != 0) {
            free(copy);
            while (!stack_is_empty(stack)) {
                char *str = stack_pop(stack);
                free(str);
            }
            stack_destroy(stack);
            exit(2);
        }
    }
    
    int first = 1;
    while (!stack_is_empty(stack)) {
        char *str = stack_pop(stack);
        if (!first) {
            printf(" ");
        }
        printf("%s", str);
        first = 0;
        free(str);
    }
    printf("\n");
    
    stack_destroy(stack);
    return 0;
}