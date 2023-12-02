#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

char *create_file_name(int num)
{
    char *file_name = malloc(8);
    if (num <= 9)
    {
        snprintf(file_name, sizeof(file_name), "00%d.jpg", num);
    }
    else
    {
        snprintf(file_name, sizeof(file_name), "0%d.jpg", num);
    }
    return file_name;
}


bool is_jpg_start(BYTE *array)
{
    bool first_three = (array[0] == 0xff && array[1] == 0xd8 && array[2] == 0xff);
    bool last = (array[3] >= 224 && array[3] <= 239);
    bool is_start = (first_three && last);
    return is_start;
}


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

    int num_images = 0;
    BYTE buffer[BLOCK_SIZE];
    while (fread(&buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {

        bool start = is_jpg_start(buffer);
        if (start)
        {
            char *outfile = create_file_name(num_images);
            FILE *outptr = fopen(outfile, "w");
            fwrite(&buffer, BLOCK_SIZE, 1, outptr);
            fclose(outptr);
            num_images += 1;
            free(outfile);
        }
        else
        {
            int current_num = num_images == 0 ? 0 : num_images - 1;
            char *outfile = create_file_name(current_num);
            FILE *outptr = fopen(outfile, "a");
            fwrite(&buffer, BLOCK_SIZE, 1, outptr);
            fclose(outptr);
            free(outfile);
        }
    }
    fclose(inptr);
}
