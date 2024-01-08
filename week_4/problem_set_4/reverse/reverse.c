#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r+");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    WAVHEADER wh;
    fread(&wh, sizeof(WAVHEADER), 1, inptr);

    printf("Current File Position: %ld\n", ftell(inptr));

    if (check_format(wh) != 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 1;
    }

    fwrite(&wh, sizeof(WAVHEADER), 1, outptr);
    fclose(outptr);

    int block_size = get_block_size(wh);
    printf("Block sizeee: %i\n", block_size);

    // Find the size of the file
    fseek(inptr, 0, SEEK_END);
    long input_file_size = ftell(inptr);

    outptr = fopen(outfile, "a");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not reopen %s.\n", outfile);
        return 1;
    }

    int start = 0;

    while (ftell(inptr) > sizeof(WAVHEADER)) {

        fseek(inptr, -block_size, SEEK_CUR);
        int data_buffer[block_size];
        fread(&data_buffer, block_size, 1, inptr);
        fwrite(&data_buffer, block_size, 1, outptr);
        fseek(inptr, -block_size, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
}


int check_format(WAVHEADER header)
{
    char *format = "WAVE";
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != format[i]) {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    int block_size = (header.numChannels * header.bitsPerSample) / 8;
    printf("Block size: %i\n", block_size);
    return block_size;
}
