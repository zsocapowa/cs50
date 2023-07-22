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
    for (int i = size - 1; i >= 0; i--)
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

    string usr_input = get_string("plaintext: ");
    printf("ciphertext:  ");

    int input_size = strlen(usr_input);

    for (int i = 0; i < input_size; i++)
    {
        int start;
        int num_to_add;
        int ascii_value = usr_input[i];

        if (ascii_value >= 65 && ascii_value <= 90)
        {
            start = 65;
            num_to_add = (ascii_value - start + key) % 26;
        }
        else if (ascii_value >= 97 && ascii_value <= 122)
        {
            start = 97;
            num_to_add = (ascii_value - start + key) % 26;
        }
        else
        {
            start = ascii_value;
            num_to_add = 0;
        }

        int cipher_character = start + num_to_add;
        printf("%c", cipher_character);
    }
    printf("\n");
}

// gcc -o caesar caesar.c -lcs50 -lm
