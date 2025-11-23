#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int findMin(int *nums, int numsSize) {
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return nums[left];
}

int main(int argc, char *argv[]) {
    if (argc <= 1) return 0;

    int *nums = (int *)malloc((argc - 1) * sizeof(int));
    if (!nums) {
        exit(2);
    }

    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i], &endptr, 10);
        if (errno != 0 || endptr == argv[i] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            printf("INVALID INTEGER\n");
            free(nums);
            exit(1);
        }
        nums[i - 1] = (int)val;
    }

    int min = findMin(nums, argc - 1);
    printf("%d\n", min);

    free(nums);
    return 0;
}