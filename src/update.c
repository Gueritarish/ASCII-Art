#include "update.h"

#include "ppm_data.h"

PPMimage* divide_by_two(PPMimage* img)
{
    int h = (img->y % 2 == 0) ? img->y /2 : img->y/2 -1;
    int w = (img->x % 2 == 0) ? img->x /2 : img->x/2 -1;
    PPMimage* pic = init_PPM(w,h);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            pic->data[i][j].red = ( img->data[2 * i][2 * j].red + img->data[2 * i + 1][2 * j].red + img->data[2 * i][2 * j + 1].red + img->data[2 * i +1][2 * j +1].red)/4;
            pic->data[i][j].green = ( img->data[2 * i][2 * j].green + img->data[2 * i + 1][2 * j].green + img->data[2 * i][2 * j + 1].green + img->data[2 * i +1][2 * j +1].green)/4;
            pic->data[i][j].blue = ( img->data[2 * i][2 * j].blue + img->data[2 * i + 1][2 * j].blue + img->data[2 * i][2 * j + 1].blue + img->data[2 * i +1][2 * j +1].blue)/4;
        }
    }
    free_PPM(img);
    img = pic;
    return pic;
}

PPMimage* saturate(PPMimage* img)
{
    PPMimage* pic = init_PPM(img->x,img->y);
    for (int i = 0; i < img->y; i++)
    {
        for (int j = 0; j < img->x; j++)
        {
            int satur = max_pixel_color(img->data[i][j]) - 1;
            pic->data[i][j].red = satur;
            pic->data[i][j].green = satur;
            pic->data[i][j].blue = satur;
        }
    }
    free_PPM(img);
    img = pic;
    return pic;
}

PPMimage* reduce_heigh(PPMimage* img)
{
    int h = (img->y % 2 == 0) ? img->y /2 : img->y / 2 -1;
    PPMimage* pic = init_PPM(img->x,h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < img->x; j++)
        {
            pic->data[i][j].red = (img->data[2 * i][j].red + img->data[2 * i + 1][j].red) / 2;
            pic->data[i][j].blue = (img->data[2 * i][j].blue + img->data[2 * i + 1][j].blue) / 2; 
            pic->data[i][j].green = (img->data[2 * i][j].green + img->data[2 * i + 1][j].green) / 2; 
        }        
    }
    free_PPM(img);
    img = pic;
    return pic;
}