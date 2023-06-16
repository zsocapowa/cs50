#include <stdio.h>
#include <cs50.h>

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_line(int n, char mark)
{
    for (int i = 0; i < n; i++) {
        printf("%c", mark);
    }
}

int main(void)
{
    char hashmark = '#';
    char spacemark = ' ';



    int max = get_size();
    int num_hashmarks = 1;

    while (num_hashmarks < max + 1)
    {
        int num_spaces = max - num_hashmarks;

        print_line(num_spaces, spacemark);
        print_line(num_hashmarks, hashmark);

        printf("  ");

        print_line(num_hashmarks, hashmark);
        // print_line(num_spaces, spacemark);

        printf("\n");
        num_hashmarks++;
    }
}



// cc -o mario mario.c -Wall -Werror -std=c11 -lcs50

