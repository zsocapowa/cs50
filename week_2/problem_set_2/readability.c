#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculcate_readability_index(string text);


int main(void) 
{
    string usr_input = get_string("Text: ");
    int num_letters = count_letters(usr_input);
    printf("%i\n", num_letters);
    int num_words = count_words(usr_input);
    printf("%i\n", num_words);
    int num_sentences = count_sentences(usr_input);
    printf("%i\n", num_sentences);
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


int count_words(string text)
{
    int words = 1;
    int n = 0;
    while (text[n] != '\0')
    {
        int ascii_value = text[n];
        if ((32 == ascii_value))
        {
            words++;
        }
        n++;
    }
    return words;
}


int count_sentences(string text)
{
    int sentences = 0;
    int n = 0;
    while (text[n] != '\0')
    {
        int ascii_value = text[n];
        if ((21 == ascii_value || ascii_value == 46 || ascii_value == 63))
        {
            sentences++;
        }
        n++;
    }
    return sentences;
}


int calculcate_readability_index(string text);
{
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    double L = (letters / words) * 100 
}


// gcc -o readability readability.c -lcs50
// cc -o readability readability.c -Wall -Werror -std=c11 -lcs50