#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int is_valid_integer(const char *str)
{
    if (!str || *str == '\0')
        return 0;

    int i = 0;
    if (str[0] == '-')
    {
        if (str[1] == '\0')
            return 0;
        i = 1;
    }

    for (; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }

    return 1;
}

int compare_ints(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib)
        return -1;
    if (ia > ib)
        return 1;
    return 0;
}

typedef struct
{
    int a, b, c;
} Triplet;

int compare_triplets(const void *a, const void *b)
{
    const Triplet *ta = (const Triplet *)a;
    const Triplet *tb = (const Triplet *)b;

    if (ta->a != tb->a)
        return ta->a - tb->a;
    if (ta->b != tb->b)
        return ta->b - tb->b;
    return ta->c - tb->c;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return 0;
    }

    int *nums = (int *)malloc((argc - 1) * sizeof(int));
    if (!nums)
        exit(2);

    for (int i = 1; i < argc; i++)
    {
        if (!is_valid_integer(argv[i]))
        {
            printf("Invalid integer input.\n");
            free(nums);
            return 1;
        }

        char *endptr;
        long val = strtol(argv[i], &endptr, 10);
        if (*endptr != '\0')
        {
            printf("Invalid integer input.\n");
            free(nums);
            return 1;
        }

        nums[i - 1] = (int)val;
    }

    int n = argc - 1;

    clock_t start_time = clock();

    qsort(nums, n, sizeof(int), compare_ints);

    Triplet *triplets = (Triplet *)malloc(n * n * sizeof(Triplet));
    if (!triplets)
    {
        free(nums);
        exit(2);
    }

    int triplet_count = 0;

    for (int i = 0; i < n - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = n - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0)
            {
                triplets[triplet_count].a = nums[i];
                triplets[triplet_count].b = nums[left];
                triplets[triplet_count].c = nums[right];
                triplet_count++;

                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;

                left++;
                right--;
            }
            else if (sum < 0)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }

    clock_t end_time = clock();

    for (int i = 0; i < triplet_count; i++)
    {
        printf("%d %d %d\n", triplets[i].a, triplets[i].b, triplets[i].c);
    }

    int time_ms = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    printf("TIME_MS: %d\n", time_ms);

    free(nums);
    free(triplets);

    return 0;
}