#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    int size;
    int capacity;
} Stack;

Stack* stack_create() {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->data = malloc(16);
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = 16;
    return stack;
}

int stack_push(Stack *stack, char c) {
    if (stack->size >= stack->capacity) {
        int new_capacity = stack->capacity * 2;
        char *new_data = realloc(stack->data, new_capacity);
        if (!new_data) return 0;
        
        stack->data = new_data;
        stack->capacity = new_capacity;
    }
    
    stack->data[stack->size++] = c;
    return 1;
}

char stack_pop(Stack *stack) {
    if (stack->size == 0) return '\0';
    return stack->data[--stack->size];
}

int stack_empty(Stack *stack) {
    return stack->size == 0;
}

void stack_destroy(Stack *stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int is_opening_bracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

int is_closing_bracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

int matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    
    Stack *stack = stack_create();
    if (!stack) {
        exit(2);
    }
    
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        int len = strlen(arg);
        
        for (int j = 0; j < len; j++) {
            char c = arg[j];
            
            if (is_opening_bracket(c)) {
                if (!stack_push(stack, c)) {
                    stack_destroy(stack);
                    exit(2);
                }
            } else if (is_closing_bracket(c)) {
                if (stack_empty(stack)) {
                    stack_destroy(stack);
                    printf("unbalanced\n");
                    return 0;
                }
                
                char opening = stack_pop(stack);
                if (!matches(opening, c)) {
                    stack_destroy(stack);
                    printf("unbalanced\n");
                    return 0;
                }
            }
        }
    }
    
    if (stack_empty(stack)) {
        printf("balanced\n");
    } else {
        printf("unbalanced\n");
    }
    
    stack_destroy(stack);
    return 0;
}