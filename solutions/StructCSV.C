#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024

struct Record {
    char **fields;
    size_t n_fields;
};

void split_csv(const char *csv, char ***fields, size_t *n_fields) {
    *fields = NULL;
    *n_fields = 0;

    char *line = strdup(csv);
    if (!line) {
        perror("strdup");
        exit(2);
    }

    char *token = strtok(line, ",");
    while (token) {
        *n_fields += 1;
        *fields = (char **)realloc(*fields, *n_fields * sizeof(char *));
        if (!*fields) {
            perror("realloc");
            free(line);
            exit(2);
        }
        (*fields)[*n_fields - 1] = strdup(token);
        if (!(*fields)[*n_fields - 1]) {
            perror("strdup");
            free(line);
            for (size_t i = 0; i < *n_fields - 1; i++) {
                free((*fields)[i]);
            }
            free(*fields);
            exit(2);
        }
        token = strtok(NULL, ",");
    }

    free(line);
}

void free_record(struct Record *record) {
    for (size_t i = 0; i < record->n_fields; i++) {
        free(record->fields[i]);
    }
    free(record->fields);
}

int compare_records(const void *a, const void *b, void *arg) {
    struct Record *record_a = (struct Record *)a;
    struct Record *record_b = (struct Record *)b;
    size_t sort_index = *(size_t *)arg;

    return strcmp(record_a->fields[sort_index], record_b->fields[sort_index]);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <column> <header> <row1> <row2> ...\n", argv[0]);
        return 1;
    }

    char *sort_column = argv[1];
    char *header = argv[2];
    char **headers;
    size_t n_headers;

    split_csv(header, &headers, &n_headers);

    size_t sort_index = -1;
    for (size_t i = 0; i < n_headers; i++) {
        if (strcmp(headers[i], sort_column) == 0) {
            sort_index = i;
            break;
        }
    }

    if (sort_index == -1) {
        fprintf(stderr, "Error: unknown column\n");
        for (size_t i = 0; i < n_headers; i++) {
            free(headers[i]);
        }
        free(headers);
        return 1;
    }

    struct Record *records = (struct Record *)malloc((argc - 3) * sizeof(struct Record));
    if (!records) {
        perror("malloc");
        for (size_t i = 0; i < n_headers; i++) {
            free(headers[i]);
        }
        free(headers);
        return 2;
    }

    for (size_t i = 0; i < argc - 3; i++) {
        split_csv(argv[i + 3], &records[i].fields, &records[i].n_fields);
        if (records[i].n_fields != n_headers) {
            fprintf(stderr, "Error: inconsistent row\n");
            for (size_t j = 0; j < i; j++) {
                free_record(&records[j]);
            }
            free(records);
            for (size_t j = 0; j < n_headers; j++) {
                free(headers[j]);
            }
            free(headers);
            return 1;
        }
    }

    size_t sort_index_copy = sort_index;
    qsort_r(records, argc - 3, sizeof(struct Record), compare_records, &sort_index_copy);

    for (size_t i = 0; i < argc - 3; i++) {
        for (size_t j = 0; j < records[i].n_fields; j++) {
            if (j > 0) {
                printf(",");
            }
            printf("%s", records[i].fields[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < argc - 3; i++) {
        free_record(&records[i]);
    }
    free(records);

    for (size_t i = 0; i < n_headers; i++) {
        free(headers[i]);
    }
    free(headers);

    return 0;
}