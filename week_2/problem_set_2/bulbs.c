#include <cs50.h>
#include <stdio.h>
#include <string.h>


void print_bulb(int bit);
void convert_int_to_binary(int ascii_value);


int main(void)
{
    string usr_input = get_string("Message: ");
    int size = strlen(usr_input);


    for (int i = 0; i < size; i++)
    {
        int ascii_value = usr_input[i];
        convert_int_to_binary(ascii_value);
        printf("\n");
    }
}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}




void convert_int_to_binary(int ascii_value)
{
    int binary_array[8] = { 0 };
    int n = 0;


    while (ascii_value != 0)
    {
        binary_array[n] = ascii_value % 2;
        ascii_value /= 2; 
        n++;
    }


    
    for (int i = 7; i >= 0; i--)
    {
        print_bulb(binary_array[i]);
    }
}



// gcc -o bulbs bulbs.c -lcs50
