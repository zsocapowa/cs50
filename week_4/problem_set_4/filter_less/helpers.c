#include <stdio.h>
#include <math.h>

#include "helpers.h"

typedef struct
{
    int h;
    int w;
}
Positions;


int adjust_max(int value)
    {
        return (value > 255) ? 255 : value;
    }

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE *blue_p = &image[h][w].rgbtBlue;
            BYTE *green_p = &image[h][w].rgbtGreen;
            BYTE *red_p = &image[h][w].rgbtRed;

            float blue = image[h][w].rgbtBlue;
            float green = image[h][w].rgbtGreen;
            float red = image[h][w].rgbtRed;

            BYTE average = round((red + green + blue) / 3.0);

            *blue_p = average;
            *green_p = average;
            *red_p = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE *blue_p = &image[h][w].rgbtBlue;
            BYTE *green_p = &image[h][w].rgbtGreen;
            BYTE *red_p = &image[h][w].rgbtRed;

            BYTE blue = image[h][w].rgbtBlue;
            BYTE green = image[h][w].rgbtGreen;
            BYTE red = image[h][w].rgbtRed;

            *blue_p = adjust_max(round(.272 * red + .534 * green + .131 * blue));
            *green_p = adjust_max(round(.349 * red + .686 * green + .168 * blue));
            *red_p = adjust_max(round(.393 * red + .769 * green + .189 * blue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        int middle = floor(width / 2);
        for (int w = 0; w < middle; w++)
        {
            int last_pixel_idx = width - 1;
            BYTE *blue_original = &image[h][w].rgbtBlue;
            BYTE *green_original = &image[h][w].rgbtGreen;
            BYTE *red_original = &image[h][w].rgbtRed;

            BYTE *blue_swap = &image[h][last_pixel_idx - w].rgbtBlue;
            BYTE *green_swap = &image[h][last_pixel_idx - w].rgbtGreen;
            BYTE *red_swap = &image[h][last_pixel_idx - w].rgbtRed;

            BYTE blue_temp = *blue_original;
            BYTE green_temp = *green_original;
            BYTE red_temp = *red_original;

            *blue_original =  *blue_swap;
            *green_original = *green_swap;
            *red_original = *red_swap;

            *blue_swap = blue_temp;
            *green_swap = green_temp;
            *red_swap = red_temp;

            *blue_swap = blue_temp;
            *green_swap = green_temp;
            *red_swap = red_temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
        RGBTRIPLE pixel;

        pixel.rgbtBlue = image[h][w].rgbtBlue;
        pixel.rgbtGreen = image[h][w].rgbtGreen;
        pixel.rgbtRed = image[h][w].rgbtRed;
        copy[h][w] = pixel;
        }
    }


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int p_num = 0;
            Positions pixel_position[9];

            pixel_position[p_num].h = h;
            pixel_position[p_num].w = w;
            p_num += 1;

            if (h - 1 >= 0)
            {
                pixel_position[p_num].h = h - 1;
                pixel_position[p_num].w = w;
                p_num += 1;

            }
            if (h + 1 < height)
            {
                pixel_position[p_num].h = h + 1;
                pixel_position[p_num].w = w;
                p_num += 1;

            }

            if (w - 1 >= 0)
            {
                pixel_position[p_num].h = h;
                pixel_position[p_num].w = w - 1;
                p_num += 1;

            }
            if (w + 1 < width)
            {
                pixel_position[p_num].h = h;
                pixel_position[p_num].w = w + 1;
                p_num += 1;

            }

            if (w - 1 >= 0 && h - 1 >= 0)
            {
                pixel_position[p_num].h = h - 1;
                pixel_position[p_num].w = w - 1;
                p_num += 1;

            }

            if (w - 1 >= 0 && h + 1 < height)
            {
                pixel_position[p_num].h = h + 1;
                pixel_position[p_num].w = w - 1;
                p_num += 1;

            }

            if (w + 1 < width && h - 1 >= 0)
            {
                pixel_position[p_num].h = h - 1;
                pixel_position[p_num].w = w + 1;
                p_num += 1;

            }

            if (w + 1 < width && h + 1 < height)
            {
                pixel_position[p_num].h = h + 1;
                pixel_position[p_num].w = w + 1;
                p_num += 1;

            }

            int raw_blue = 0;
            int raw_green = 0;
            int raw_red = 0;

            for (int i = 0; i < p_num; i++)
            {
                int h_l = pixel_position[i].h;
                int w_l = pixel_position[i].w;
                
                raw_blue += copy[h_l][w_l].rgbtBlue;
                raw_green += copy[h_l][w_l].rgbtGreen;
                raw_red += copy[h_l][w_l].rgbtRed;
            }

            BYTE *blue_p = &image[h][w].rgbtBlue;
            BYTE *green_p = &image[h][w].rgbtGreen;
            BYTE *red_p = &image[h][w].rgbtRed;

            *blue_p = round((float)raw_blue / p_num);
            *green_p = round((float)raw_green / p_num);
            *red_p = round((float)raw_red / p_num);
        }
    }
    return;
}
