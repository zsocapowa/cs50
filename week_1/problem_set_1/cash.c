#include <cs50.h>
#include <stdio.h>


int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Input: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)  // 25 cent
{
    int quarters = cents/25;
    return quarters;
}

int calculate_dimes(int cents)  // 10 cent 
{
    int quarters = cents/10;
    return quarters;
}

int calculate_nickels(int cents)  // 5 cent
{
    int quarters = cents/5;
    return quarters;
}

int calculate_pennies(int cents)   // 1 cent
{
    int quarters = cents/1;
    return quarters;
}

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;
    printf("\n%s %i\n", "Quarters:", quarters);

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;
    printf("%s %i\n", "Dimes:", dimes);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;
    printf("%s %i\n", "Nickels:", nickels);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;
    printf("%s %i\n\n", "Pennies:", pennies);

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%s %i\n\n", "Number of coins:" ,coins);
}


// cc -o cash cash.c -Wall -Werror -std=c11 -lcs50
