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

int get_max(int n, ...)
{
    va_list ptr;

    va_start(ptr, n);
    int max = va_arg(ptr, int);   
    int temp;
    for (int i = 1; i < n; i++)
    {
        // Accessing current variable
        // and pointing to next one
        temp = va_arg(ptr, int);
        if (temp > max)
            max = temp;
    }
    // Ending argument list traversal
    va_end(ptr);
 
    return max;
}

int get_second_max(int n, ...)
{
    va_list ptr;

    va_start(ptr, n);
    int max = va_arg(ptr, int);
    int second = va_arg(ptr, int);
    int temp;
    if (second > max)
    {
        temp = second;
        second = max;
        max = temp;
    }
    
    for (int i = 1; i < n; i++)
    {
        // Accessing current variable
        // and pointing to next one
        temp = va_arg(ptr, int);
        if (temp > second)
        {
            if (temp > max)
            {
                second = max;
                max = temp;
            }
            else
            {
                second = temp;
            }
        }
    }
    // Ending argument list traversal
    va_end(ptr);
    return second;
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
    printf("height -> %d, width -> %d\n", height, width);
    while(fgetc(stream_img) != '\n'); // Get  rid of the Max Val ( which takes one line )
    int mean_red, mean_green, mean_blue;
    PPMimage* image = init_PPM(width,height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image->data[i][j].red = fgetc(stream_img);
            image->data[i][j].green = fgetc(stream_img);
            image->data[i][j].blue = fgetc(stream_img);
            mean_red += image->data[i][j].red;
            mean_green += image->data[i][j].green;
            mean_blue += image->data[i][j].blue;
        }

    }
    mean_red = mean_red / ( image->x * image->y );
    mean_green = mean_green / ( image->x * image->y );
    mean_blue = mean_blue / ( image->x * image->y );
    
    int first,second;
    
    if (mean_red > mean_green)
    {
        if (mean_red > mean_blue)
        {
            first = mean_red;
            second = (mean_blue > mean_green) ? mean_blue : mean_green;
        }
        else
        {
            first = mean_blue;
            second = mean_red;
        }
    }
    else
    {
        if (mean_green > mean_blue)
        {
            first = mean_green;
            second = (mean_blue > mean_red) ? mean_blue : mean_red;
        }
        else
        {
            first = mean_blue;
            second = mean_green;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (second == first)
            {
                if (mean_red == first)
                    image->data[i][j].red /= 1.05;
                if (mean_green == first)
                    image->data[i][j].green /= 1.05;
                if (mean_blue == first)
                    image->data[i][j].blue /= 1.05;             
            }
            else
            {
               if (mean_red == first)
                    image->data[i][j].red /= 1.1;
                if (mean_green == first)
                    image->data[i][j].green /= 1.1;
                if (mean_blue == first)
                    image->data[i][j].blue /= 1.1;

                if (mean_red == second)
                    image->data[i][j].red /= 1.05;
                if (mean_green == second)
                    image->data[i][j].green /= 1.05;
                if (mean_blue == second)
                    image->data[i][j].blue /= 1.05;  

            }
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


int mean_pixel_color(PPMpixeldata pixel)
{   
    return (pixel.red + pixel.blue + pixel.green) / 3;
}

int within_n_of(int color1, int color2, int n)
{
    if (color1 >= color2 - n && color1 <= color2 + n)
        return 1;
    return 0;
}