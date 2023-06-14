#include <cs50.h>
#include <stdio.h>
#include <string.h>

int get_long_lenght(long n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        count ++;
    }
    return count;
}

const char* card_type() {
  return "Flavio";
}



int main(void) 
{
    long n;
    n = get_long("Number: ");

    int num_digits;
    num_digits = get_long_lenght(n);
    printf("%i\n", num_digits);

    if (num_digits > 16)
    {
        printf("INVALID\n");
    }

    char str[num_digits];
    sprintf(str, "%ld", n);


    int first_sum = 0;
    int second_sum = 0;
    int iteration_num = 0;

    for (int i = num_digits -1; i >= 0; i --)
    {
        printf("%c\n", str[i]);
        int digit = str[i] - '0';
        if (iteration_num % 2 == 0) {
            second_sum += digit;
        }
        else {
            int target_num = digit * 2;
        
            int first_digit = target_num / 10;
            int second_digit = target_num % 10;

            first_sum += first_digit + second_digit;
        }
    
        iteration_num++;
    }

    int final_sum = first_sum + second_sum;
    printf("%i\n", final_sum);

    if (final_sum % 2 == 0){
        printf("VALID\n");
    }
    else {
        printf("INVALID\n");
    }
}


// cc -o credit credit.c -Wall -Werror -std=c11 -lcs50
