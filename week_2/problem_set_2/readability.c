#include <cs50.h>
#include <stdio.h>

int count_letters(string text);

int main(void) 
{
    string usr_input = get_string("Text: ");
    int num_letters = count_letters(usr_input);
    printf("%i\n", num_letters);
}

int count_letters(string text)
{
    int letters = 0;
    int n = 0;
    while (text[n] != '\0')
    {
        int ascii_value = text[n];
        if ((41 <= ascii_value && ascii_value <= 90) || (97 <= ascii_value && ascii_value <= 122))
        {
            letters++;
        }
        n++;
    }
    return letters;
}



// gcc -o readability readability.c -lcs50
// cc -o readability readability.c -Wall -Werror -std=c11 -lcs50