#include <cs50.h>
#include <stdio.h>

const int N = 3;

float avarage(int length ,int array[]);

int main(void)
{
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Avarage: %f\n", avarage(N ,scores));
}


float avarage(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}

