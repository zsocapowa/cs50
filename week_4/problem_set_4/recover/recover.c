#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    char *image_file = argv[1];
    FILE *inptr = fopen(image_file, "r");
    if (inptr == NULL)
    {
       printf("Could not open %s.\n", image_file);
       return 1;
    }
}

// gcc -o recover recover.c -lcs50
