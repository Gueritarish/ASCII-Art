#include "display.h"

void choose_color(PPMpixeldata pixel)
{
    {
        int px_max = max_pixel_color(pixel);
        if (within_n_of(px_max,mean_pixel_color(pixel),10))
            printf("%s",WHITE);
        else if (pixel.red == px_max)
        {
            if (within_n_of(pixel.red,pixel.green,5))
            {
                printf("%s",YELLOW);
            }
            else if (within_n_of(pixel.red,pixel.blue,5))
            {
                printf("%s",PURPLE);
            }
            else
            {
                printf("%s",RED);
            }
        }
        else if (pixel.green == px_max)
        {
            if (within_n_of(pixel.green,pixel.red,5))
            {
                printf("%s",YELLOW);
            }
            else if (within_n_of(pixel.green,pixel.blue,5))
            {
                printf("%s",CYAN);
            }
            else
            {
                printf("%s",GREEN);
            }
        }
        else if (pixel.blue == px_max)
        {
            if (within_n_of(pixel.blue,pixel.green,5))
            {
                printf("%s",CYAN);
            }
            else if (within_n_of(pixel.blue,pixel.red,5))
            {
                printf("%s",PURPLE);
            }
            else
            {
                printf("%s",BLUE);
            }
        }
        else
        {
            printf("%s",WHITE);
        }
    }
}

void display_pixel(PPMpixeldata pixel)
{
    // .:cP0@#
    if (max_pixel_color(pixel) < 50)
        printf("%c", ' ');

    else if (max_pixel_color(pixel) < 100)
        printf("%c", '.');
    
    else if (max_pixel_color(pixel) < 140)
        printf("%c", ':');
    
    else if (max_pixel_color(pixel) < 175)
        printf("%c", 'c');
    
    else if (max_pixel_color(pixel) < 200)
        printf("%c", 'P');
    
    else if (max_pixel_color(pixel) < 220)
        printf("%c", '0');
    
    else if (max_pixel_color(pixel) < 240)
        printf("%c", '@');
    
    else
        printf("%c", '#');
    }

void display_picture(PPMimage* pic)
{
    for (int i = 0; i < pic->y; i++)
    {
        for (int j = 0; j < pic->x; j++)
        {
            choose_color(pic->data[i][j]);
            display_pixel(pic->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf(COLOR_OFF);
}