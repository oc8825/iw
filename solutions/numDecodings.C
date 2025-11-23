#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check argument count
    if (argc == 1)
    {
        return 0;
    }

    if (argc != 2)
    {
        fprintf(stderr, "Error: expected 1 argument\n");
        return 1;
    }

    char *s = argv[1];
    int len = strlen(s);

    // Validate input - must contain only digits
    for (int i = 0; i < len; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            fprintf(stderr, "Error: invalid input\n");
            return 1;
        }
    }

    // Handle empty string case
    if (len == 0)
    {
        printf("1\n");
        return 0;
    }

    // Dynamic programming array
    int *dp = (int *)malloc((len + 1) * sizeof(int));
    if (dp == NULL)
    {
        return 2;
    }

    // Initialize base cases
    dp[0] = 1;                     // Empty string has one way to decode
    dp[1] = (s[0] != '0') ? 1 : 0; // First character valid if not '0'

    // Fill dp array
    for (int i = 2; i <= len; i++)
    {
        dp[i] = 0;

        // Single digit case (1-9)
        if (s[i - 1] >= '1' && s[i - 1] <= '9')
        {
            dp[i] += dp[i - 1];
        }

        // Two digit case (10-26)
        if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] >= '0' && s[i - 1] <= '6'))
        {
            dp[i] += dp[i - 2];
        }
    }

    int result = dp[len];
    free(dp);

    printf("%d\n", result);
    return 0;
}