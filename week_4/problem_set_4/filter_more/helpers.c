#include <stdio.h>
#include <math.h>

#include "helpers.h"

typedef struct
{
    int h;
    int w;
}
Positions;


typedef struct
{
    int h;
    int w;
    int gx_m;
    int gy_m;
}
Kernels;

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height + 2][width + 2];
    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            RGBTRIPLE pixel;
            if (h == 0 || h == height + 1)
            {
                pixel.rgbtBlue = 0;
                pixel.rgbtGreen = 0;
                pixel.rgbtRed = 0;
            }
            else if (w == 0 || w == width + 1)
            {
                pixel.rgbtBlue = 0;
                pixel.rgbtGreen = 0;
                pixel.rgbtRed = 0;

            }
            else
            {
                pixel.rgbtBlue = image[h - 1][w - 1].rgbtBlue;
                pixel.rgbtGreen = image[h -1][w - 1].rgbtGreen;
                pixel.rgbtRed = image[h - 1][w - 1].rgbtRed;
            }
        copy[h][w] = pixel;
        }
    }
    //
    for (int h = 1; h < height + 1; h++)
    {
        for (int w = 1; w < width + 1; w++)
        {
            Kernels k_data[9];

            // 1st col
            k_data[0].h = h - 1;
            k_data[0].w = w - 1;
            k_data[0].gx_m = -1;
            k_data[0].gy_m = -1;

            k_data[1].h = h;
            k_data[1].w = w - 1;
            k_data[1].gx_m = -2;
            k_data[1].gy_m = 0;

            k_data[2].h = h + 1;
            k_data[2].w = w - 1;
            k_data[2].gx_m = -1;
            k_data[2].gy_m = 1;


            // middle col
            k_data[3].h = h - 1;
            k_data[3].w = w;
            k_data[3].gx_m = 0;
            k_data[3].gy_m = -2;

            k_data[4].h = h;
            k_data[4].w = w;
            k_data[4].gx_m = 0;
            k_data[4].gy_m = 0;

            k_data[5].h = h + 1;
            k_data[5].w = w;
            k_data[5].gx_m = 0;
            k_data[5].gy_m = 2;

            // last col
            k_data[6].h = h - 1;
            k_data[6].w = w + 1;
            k_data[6].gx_m = 1;
            k_data[6].gy_m = -1;

            k_data[7].h = h;
            k_data[7].w = w + 1;
            k_data[7].gx_m = 2;
            k_data[7].gy_m = 0;

            k_data[8].h = h + 1;
            k_data[8].w = w + 1;
            k_data[8].gx_m = 1;
            k_data[8].gy_m = 1;

            int gx_raw_blue = 0;
            int gx_raw_green = 0;
            int gx_raw_red = 0;

            int gy_raw_blue = 0;
            int gy_raw_green = 0;
            int gy_raw_red = 0;

            for (int i = 0; i < 9; i++)
            {
                int h_l = k_data[i].h;
                int w_l = k_data[i].w;
                int gx_m = k_data[i].gx_m;
                int gy_m = k_data[i].gy_m;

                gx_raw_blue += copy[h_l][w_l].rgbtBlue * gx_m;
                gx_raw_green += copy[h_l][w_l].rgbtGreen * gx_m;
                gx_raw_red += copy[h_l][w_l].rgbtRed * gx_m;

                gy_raw_blue += copy[h_l][w_l].rgbtBlue * gy_m;
                gy_raw_green += copy[h_l][w_l].rgbtGreen * gy_m;
                gy_raw_red += copy[h_l][w_l].rgbtRed * gy_m;
            }


            BYTE blue_f = adjust_max(round(sqrt(gx_raw_blue * gx_raw_blue + gy_raw_blue * gy_raw_blue)));
            BYTE green_f = adjust_max(round(sqrt(gx_raw_green * gx_raw_green + gy_raw_green * gy_raw_green)));
            BYTE red_f = adjust_max(round(sqrt(gx_raw_red * gx_raw_red + gy_raw_red * gy_raw_red)));

            BYTE *blue_p = &image[h - 1][w -1].rgbtBlue;
            BYTE *green_p = &image[h -1][w - 1].rgbtGreen;
            BYTE *red_p = &image[h -1][w - 1].rgbtRed;

            *blue_p = blue_f;
            *green_p = green_f;
            *red_p = red_f;
        }
    }

}


// ./filter -e images/yard.bmp out.bmp
