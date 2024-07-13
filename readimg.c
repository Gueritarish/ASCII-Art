#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

typedef struct {
    unsigned char red, green,blue;
} PPMpixeldata;

typedef struct{
    size_t x,y;
    PPMpixeldata** data;
} PPMimage;

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

PPMimage* read_ppm(const char* path)
{
    FILE* stream_img  = fopen(path,"r");
    if(!stream_img)
    {
        return NULL; 
    }
    // Get Rid of the 'P6\n'
    if (!fgetc(stream_img) == 'P' || !fgetc(stream_img) == '6')
    {
        fclose(stream_img);
        return NULL;
    }
    fgetc(stream_img);

    // Get the width
    size_t width = 0;
    int c = fgetc(stream_img);
    while (c != ' ')
    {
        width = width * 10 + c - '0';
        c = fgetc(stream_img);
    }

    c = fgetc(stream_img);
    // Get the height
    size_t height = 0;
    while(c != '\n')
    {
        height = height * 10 + c -'0';
        c = fgetc(stream_img);
    }

    while(fgetc(stream_img) != '\n'); // Get  rid of the Max Val ( which takes one line )

    PPMimage* image = calloc(1,sizeof(PPMimage));
    image->x = width;
    image->y = height;
    image->data = calloc(height,sizeof(PPMpixeldata*));
    for(size_t i = 0; i < width; i++)
    {
        image->data[i] = calloc(width, sizeof(PPMpixeldata));
    }
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
    printf("%s\n",str_w);
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

int main(void)
{
    PPMimage* img = read_ppm("bonhomme.ppm");
    if(!img)
    {
        return 1;
    }
    
    printf("height : %ld\nwidth : %ld\n", img->y,img->x);
    write_ppm(img,"picturetest.ppm");
    free(img);
    return 0;
}