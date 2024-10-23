#include "ppm_data.h"

#include <jpeglib.h>
#include <png.h>

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
    image->data = calloc(image->y,sizeof(PPMpixeldata*));
    for(int i = 0; i < image->y; i++)
    {
        image->data[i] = calloc(image->x, sizeof(PPMpixeldata));
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
    printf("height -> %d, width -> %d\n", height, width);
    while(fgetc(stream_img) != '\n'); // Get  rid of the Max Val ( which takes one line )
    int mean_red, mean_green, mean_blue;
    PPMimage* image = init_PPM(width,height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            char c =  fgetc(stream_img);
            image->data[i][j].red = c;
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

PPMimage* read_jpeg(const char *filename)
{
    struct jpeg_decompress_struct jds;
    struct jpeg_error_mgr jerr;
    FILE *file;
    JSAMPARRAY buffer;

    if ((file = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        return NULL;
    }

    jds.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&jds);
    jpeg_stdio_src(&jds, file);
    jpeg_read_header(&jds, TRUE);
    jpeg_start_decompress(&jds);

    PPMimage *image = init_PPM(jds.output_width, jds.output_height);

    while (jds.output_scanline < jds.output_height) {
        buffer = (*jds.mem->alloc_sarray)( (j_common_ptr) &jds, JPOOL_IMAGE, jds.output_width * jds.output_components, 1);
        jpeg_read_scanlines(&jds, buffer, 1);
        for (unsigned int x = 0; x < jds.output_width; x++) {
            if (jds.output_components == 3) { // RGB
                image->data[jds.output_scanline - 1][x].red = buffer[0][x * 3];
                image->data[jds.output_scanline - 1][x].green = buffer[0][x * 3 + 1];
                image->data[jds.output_scanline - 1][x].blue = buffer[0][x * 3 + 2];
            }
        }
    }

    jpeg_finish_decompress(&jds);
    jpeg_destroy_decompress(&jds);
    fclose(file);
    return image;
}


PPMimage* read_png(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return NULL;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        fprintf(stderr, "Could not create PNG read struct\n");
        return NULL;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(fp);
        fprintf(stderr, "Could not create PNG info struct\n");
        return NULL;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        fprintf(stderr, "Error during PNG creation\n");
        return NULL;
    }

    png_init_io(png, fp);
    png_read_info(png, info);
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    PPMimage *image = init_PPM(width, height);

    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    png_bytep *row_pointers = malloc(height * sizeof(png_bytep));
    
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));

    png_read_image(png, row_pointers);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image->data[y][x].red = row_pointers[y][x * 3];
            image->data[y][x].green = row_pointers[y][x * 3 + 1];
            image->data[y][x].blue = row_pointers[y][x * 3 + 2];
        }
    }

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);

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