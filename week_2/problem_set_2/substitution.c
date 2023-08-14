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

    int size = strlen(argv[1]);

    if (size != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    char lowercase_key[size + 1];
    for (int i = 0; i < size; i++)
    {
        char current_lower = tolower(argv[1][i]);
        if (!isalpha(current_lower))
        {
            printf("Invalid key: %c is not an alphabetic letter.\n", current_lower);
            return 1;
        }
        else
        {
            for (int y = 0; y < size; y++)
            {
                char inner_char_lower = tolower(argv[1][y]);
                if (i != y && current_lower == inner_char_lower)
                {
                    printf("Invalid key: %c is a duplicated letter.\n", current_lower);
                    return 1;
                }
            }
            lowercase_key[i] = current_lower;
        }
    }
    lowercase_key[26] = '\0';

    string usr_input = get_string("plaintext: ");
    printf("ciphertext:  ");

    int input_size = strlen(usr_input);

    for (int i = 0; i < input_size; i++)
    {

        int original_ascii = usr_input[i];
        if ((original_ascii >= 65 && original_ascii <= 90) || (original_ascii >= 97 && original_ascii <= 122))
        {
            char current_lower = tolower(usr_input[i]);
            int ascii_value = current_lower;
            int c_index = ascii_value - 97;

            if (isupper(usr_input[i]))
            {
                char cipher_character = toupper(lowercase_key[c_index]);
                printf("%c", cipher_character);
            }
            else
            {
                char cipher_character = lowercase_key[c_index];
                printf("%c", cipher_character);
            }
        }
        else
        {
            printf("%c", usr_input[i]);
        }
    }
    printf("\n");
}

// gcc -o substitution caesar.c -lcs50 -lm
// style50 substitution.c
// check50 cs50/problems/2023/x/substitution
