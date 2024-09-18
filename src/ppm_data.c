#include "ppm_data.h"

char* itoa(char* buffer,int n)
{
    int i = 0;
    while(n != 0)
    {
        buffer[i] = n%10 + '0';
        n /= 10;
        i++;
    }
    for(int j = 0; j < i/2; j++)
    {
        char temp = buffer[j];
        buffer[j] = buffer[i-j-1];
        buffer[i-j-1] = temp;
    }
    buffer[i] = '\0';
    return buffer;
}

PPMimage* init_PPM(int x,int y)
{
    PPMimage* image = calloc(1,sizeof(PPMimage));
    image->x = x;
    image->y = y;
    image->data = calloc(y,sizeof(PPMpixeldata*));
    for(int i = 0; i < x; i++)
    {
        image->data[i] = calloc(x, sizeof(PPMpixeldata));
    }
    return image;
}

PPMimage* read_ppm(const char* path)
{
    FILE* stream_img  = fopen(path,"r");
    if(!stream_img)
    {
        return NULL; 
    }

    // Get Rid of the 'P6\n'
    if (fgetc(stream_img) != 'P' || fgetc(stream_img) != '6')
    {
        printf("Wrong format!\n");
        fclose(stream_img);
        return NULL;
    }

    if (fgetc(stream_img) == 13)
    {
        fgetc(stream_img);
    }

    // Get the width
    int width = 0;
    int c = fgetc(stream_img);
    while (c != ' ')
    {
        width = width * 10 + c - '0';
        c = fgetc(stream_img);
    }

    c = fgetc(stream_img); // '\n'
    // Get the height
    int height = 0;
    while(c != '\n')
    {
        height = height * 10 + c -'0';
        c = fgetc(stream_img);
    }

    while(fgetc(stream_img) != '\n'); // Get  rid of the Max Val ( which takes one line )

    PPMimage* image = init_PPM(width,height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->data[i][j].red = fgetc(stream_img);
            image->data[i][j].green = fgetc(stream_img);
            image->data[i][j].blue = fgetc(stream_img);
        }

    }

    // free(buff);
    fclose(stream_img);
    return image;
}

void write_ppm(PPMimage* image,const char* path)
{
    FILE* stream_img = fopen(path,"w");
    
    // Format of the PPM : P6
    fputc('P',stream_img);
    fputc('6',stream_img);
    fputc('\n',stream_img);

    // Write Dimension of the picture
    int width = image->x;
    int height = image->y;
    char* buffer = calloc(8,sizeof(char));
    char* str_w = itoa(buffer,width);
    for (int i = 0; str_w[i] != '\0'; i++)
    {
        fputc(str_w[i],stream_img);
    }
    fputc(' ',stream_img);
    char* str_h = itoa(buffer,height);
    for (int i = 0; str_h[i] != '\0'; i++)
    {
        fputc(str_h[i],stream_img);
    }
    free(buffer);
    fputc('\n',stream_img);
    
    // Write the max value for each bytes
    fputc('2',stream_img);
    fputc('5',stream_img);
    fputc('5',stream_img);
    fputc('\n',stream_img);

    // Write data
    for (int i = 0; i < image->y; i++)
    {
        for (int j = 0; j < image->x; j++)
        {
            fputc(image->data[i][j].red,stream_img);
            fputc(image->data[i][j].green,stream_img);
            fputc(image->data[i][j].blue,stream_img);
        }
    }
    fputc(EOF,stream_img);
    fclose(stream_img);
}

int max_pixel_color(PPMpixeldata pixel)
{
    int max = (pixel.red > pixel.green) ? pixel.red : pixel.green;
    max = (max > pixel.blue) ? max : pixel.blue;
    return max;
}

void display_pixel(PPMpixeldata pixel)
{
    // .:cP0@#
    if (max_pixel_color(pixel) < 32)
        printf("%c", ' ');

    else if (max_pixel_color(pixel) < 64)
        printf("%c", '.');
    
    else if (max_pixel_color(pixel) < 96)
        printf("%c", ':');
    
    else if (max_pixel_color(pixel) < 128)
        printf("%c", 'c');
    
    else if (max_pixel_color(pixel) < 160)
        printf("%c", 'P');
    
    else if (max_pixel_color(pixel) < 192)
        printf("%c", '0');
    
    else if (max_pixel_color(pixel) < 224)
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
            display_pixel(pic->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}