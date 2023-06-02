#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long n;
    // long card = 4003600000000014;
    n = get_long("card?");
    printf("%li", n);

// long int num = 1234567890;
// int i;

// for (i = 0; i < sizeof(long int); i++) {
//     printf("%ld ", num & 0xff);
//     num >>= 8;
// }

}

// card number is stored in a database - when used, the creditor will now whom to bill
// AM: 34, 37 / MasterCard: 51, 52, 53, 54, 55 / Visa: 4
// checksum - detect typos without db query 
// Luhn's Algorithm - determine if a credit card number is (syntactically) valid as follows:


// cc -o credit credit.c -Wall -Werror -std=c11 -lcs50
