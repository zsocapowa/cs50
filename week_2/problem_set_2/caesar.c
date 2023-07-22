#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    int key = 0;

    int n = 0;
    int size = strlen(argv[1]);
    for (int i = size -1; i >= 0; i--)
    {

        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
        else
        {
            int multiplier = pow(10, i);
            int current_digit = argv[1][n] - '0';
            key = key + (multiplier * current_digit);
            n++;
        }
    }

    if (key < 0)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    printf("%i\n", key);
}


// gcc -o caesar caesar.c -lcs50 -lm
