#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_word_boundary(char c) {
    return !isalnum(c) && c != '_';
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: requires three command line arguments\n");
        exit(1);
    }
    
    char *wordToReplace = argv[1];
    char *replacementWord = argv[2];
    char *text = argv[3];
    
    int wordToReplaceLen = strlen(wordToReplace);
    int replacementWordLen = strlen(replacementWord);
    int textLen = strlen(text);
    
    if (wordToReplaceLen == 0) {
        printf("%s", text);
        exit(0);
    }
    
    char *result = (char*)malloc(textLen * 2 + replacementWordLen * 100);
    if (!result) {
        exit(2);
    }
    
    int resultIndex = 0;
    int i = 0;
    
    while (i < textLen) {
        if (strncmp(&text[i], wordToReplace, wordToReplaceLen) == 0) {
            int prevBoundary = (i == 0) || is_word_boundary(text[i - 1]);
            int nextBoundary = (i + wordToReplaceLen >= textLen) || is_word_boundary(text[i + wordToReplaceLen]);
            
            if (prevBoundary && nextBoundary) {
                strcpy(&result[resultIndex], replacementWord);
                resultIndex += replacementWordLen;
                i += wordToReplaceLen;
            } else {
                result[resultIndex++] = text[i++];
            }
        } else {
            result[resultIndex++] = text[i++];
        }
    }
    
    result[resultIndex] = '\0';
    printf("%s", result);
    
    free(result);
    exit(0);
}