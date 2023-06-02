#include <cs50.h>
#include <stdio.h>

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);
    return n;
}

void print_grid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// cc -o mario mario.c -Wall -Werror -std=c11 -lcs50


int main(void)
{
    int n = get_size();
    print_grid(n);
}

