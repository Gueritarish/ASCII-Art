#include "update.h"

#include "ppm_data.h"

PPMimage* divide_resolution(PPMimage* img,int n)
{
    int h = (img->y % n == 0) ? img->y /n : img->y/n -1;
    int w = (img->x % n == 0) ? img->x /n : img->x/n -1;
    PPMimage* pic = init_PPM(w,h);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            pic->data[i][j].red = ( img->data[n * i][n * j].red + img->data[n * i + 1][n * j].red + img->data[n * i][n * j + 1].red + img->data[n * i +1][n * j +1].red)/4;
            pic->data[i][j].green = ( img->data[n * i][n * j].green + img->data[n * i + 1][n * j].green + img->data[n * i][n * j + 1].green + img->data[n * i +1][n * j +1].green)/4;
            pic->data[i][j].blue = ( img->data[n * i][n * j].blue + img->data[n * i + 1][n * j].blue + img->data[n * i][n * j + 1].blue + img->data[n * i +1][n * j +1].blue)/4;
        }
    }
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
    return pic;
}