#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void calculcate_readability_index(string text);


int main(void) 
{
    string usr_input = get_string("Text: ");
    calculcate_readability_index(usr_input);

//     int num_letters = count_letters(usr_input);
//     printf("Number of letters: %i\n", num_letters);

//     int num_words = count_words(usr_input);
//     printf("Number of words: %i\n", num_words);

//     int num_sentences = count_sentences(usr_input);
//     printf("Number of sentences: %i\n", num_sentences);
}

int count_letters(string text)
{
    int letters = 0;
    int n = 0;
    while (text[n] != '\0')
    {
        int ascii_value = text[n];
        if ((65 <= ascii_value && ascii_value <= 90) || (97 <= ascii_value && ascii_value <= 122))
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


void calculcate_readability_index(string text)
{
    int letters = count_letters(text);
    // printf("Number of letters: %i\n", letters);

    int words = count_words(text);
    // printf("Number of words: %i\n", words);

    int sentences = count_sentences(text);
    // printf("Number of sentences: %i\n", sentences);

    float L = (float) letters / words * 100;
    // printf("Value of L: %f\n", L);

    float S = (float) sentences / words * 100;
    // printf("Value of S: %f\n", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("Float index %f\n", index);

    int rounded_index = round(index);

    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rounded_index);
    }
}


// gcc -o readability readability.c -lcs50 -lm
// cc -o readability readability.c -Wall -Werror -std=c11 -lcs50