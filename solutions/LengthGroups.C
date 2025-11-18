#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bucket {
    int length;
    int count;
    char **words;
} Bucket;

int compare(const void *a, const void *b) {
    return ((Bucket *)a)->length - ((Bucket *)b)->length;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        return 0;
    }

    Bucket *buckets = NULL;
    int bucket_count = 0;

    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);
        int found = 0;

        for (int j = 0; j < bucket_count; j++) {
            if (buckets[j].length == len) {
                buckets[j].words = realloc(buckets[j].words, (buckets[j].count + 1) * sizeof(char *));
                if (buckets[j].words == NULL) {
                    exit(2);
                }
                buckets[j].words[buckets[j].count++] = argv[i];
                found = 1;
                break;
            }
        }

        if (!found) {
            buckets = realloc(buckets, (bucket_count + 1) * sizeof(Bucket));
            if (buckets == NULL) {
                exit(2);
            }
            buckets[bucket_count].length = len;
            buckets[bucket_count].count = 1;
            buckets[bucket_count].words = malloc((buckets[bucket_count].count) * sizeof(char *));
            if (buckets[bucket_count].words == NULL) {
                exit(2);
            }
            buckets[bucket_count].words[0] = argv[i];
            bucket_count++;
        }
    }

    qsort(buckets, bucket_count, sizeof(Bucket), compare);

    for (int i = 0; i < bucket_count; i++) {
        printf("%d: ", buckets[i].length);
        for (int j = 0; j < buckets[i].count; j++) {
            printf("%s", buckets[i].words[j]);
            if (j < buckets[i].count - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < bucket_count; i++) {
        free(buckets[i].words);
    }
    free(buckets);

    return 0;
}