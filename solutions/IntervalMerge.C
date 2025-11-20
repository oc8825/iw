#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Interval {
    int start;
    int end;
};

int compare_intervals(const void *a, const void *b) {
    struct Interval *ia = (struct Interval *)a;
    struct Interval *ib = (struct Interval *)b;
    if (ia->start == ib->start) {
        return ia->end - ib->end;
    }
    return ia->start - ib->start;
}

int parse_interval(const char *str, struct Interval *interval) {
    char *endptr;
    long start = strtol(str, &endptr, 10);
    if (str == endptr || *endptr != '-') {
        return 0;
    }
    long end = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '\0' || start > end) {
        return 0;
    }
    interval->start = (int)start;
    interval->end = (int)end;
    return 1;
}

void merge_intervals(struct Interval *intervals, int *count) {
    int j = 0;
    for (int i = 1; i < *count; i++) {
        if (intervals[j].end + 1 >= intervals[i].start) {
            intervals[j].end = (intervals[j].end > intervals[i].end) ? intervals[j].end : intervals[i].end;
        } else {
            j++;
            intervals[j] = intervals[i];
        }
    }
    *count = j + 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    struct Interval *intervals = NULL;
    int count = 0;
    for (int i = 1; i < argc; i++) {
        struct Interval interval;
        if (!parse_interval(argv[i], &interval)) {
            fprintf(stderr, "Error: invalid interval\n");
            return 1;
        }
        intervals = realloc(intervals, (count + 1) * sizeof(struct Interval));
        if (intervals == NULL) {
            return 2;
        }
        intervals[count++] = interval;
    }

    qsort(intervals, count, sizeof(struct Interval), compare_intervals);

    merge_intervals(intervals, &count);

    for (int i = 0; i < count; i++) {
        printf("%d-%d", intervals[i].start, intervals[i].end);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(intervals);
    return 0;
}