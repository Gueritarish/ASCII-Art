#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char red, green,blue;
} PPMpixeldata;

typedef struct{
    int x,y;
    PPMpixeldata** data;
} PPMimage;

char* itoa(char* buffer,int n);


PPMimage* init_PPM(int x, int y);
PPMimage* read_ppm(const char* path);
void write_ppm(PPMimage* image,const char* path);
int max_pixel_color(PPMpixeldata pixel);
int mean_pixel_color(PPMpixeldata pixel);
int within_n_of(int color1, int color2, int n);
