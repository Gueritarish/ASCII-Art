#include "display.h"

char* choose_color(PPMpixeldata pixel)
{
    {
        int px_max = max_pixel_color(pixel);
        if (within_n_of(px_max,mean_pixel_color(pixel),5))
            return WHITE;
        else if (pixel.red == px_max)
        {
            if (within_n_of(pixel.red,pixel.green,35))
            {
                if (within_n_of(pixel.red,pixel.green,5))
                {
                    return YELLOW;
                }
                else
                {
                    return ORANGE;
                }
            }
            else if (within_n_of(pixel.red,pixel.blue,5))
            {
                return PINK;
            }
            else
            {
                return RED;
            }
        }
        else if (pixel.green == px_max)
        {
            if (within_n_of(pixel.green,pixel.red,5))
            {
                return YELLOW;
            }
            else if (within_n_of(pixel.green,pixel.blue,5))
            {
                return CYAN;
            }
            else
            {
                return GREEN;
            }
        }
        else if (pixel.blue == px_max)
        {
            if (within_n_of(pixel.blue,pixel.green,5))
            {
                return CYAN;
            }
            else if (within_n_of(pixel.blue,pixel.red,25))
            {
                if (within_n_of(pixel.blue,pixel.red,5))
                {
                    return PINK;
                }
                else
                {
                    return PURPLE;
                }
            }
            else
            {
                return BLUE;
            }
        }
        else
        {
            return WHITE;
        }
    }
}

char* get_char_pixel(PPMpixeldata pixel)
{
    // .:cP0@#
    if (mean_pixel_color(pixel) < 45)
        return " ";

    else if (mean_pixel_color(pixel) < 95)
        return ".";
    
    else if (mean_pixel_color(pixel) < 130)
        return ":";
    
    else if (mean_pixel_color(pixel) < 160)
        return "c";
    
    else if (mean_pixel_color(pixel) < 185)
        return "P";
    
    else if (mean_pixel_color(pixel) < 205)
        return "0";
    
    else if (mean_pixel_color(pixel) < 220)
        return "@";
    
    else
        return "#";
    }

void display_picture_standard(PPMimage* pic)
{
    char* img = calloc(pic->x * pic->y * 8 + pic->y + 1,sizeof(char));
    size_t ind = 0;
    for (int i = 0; i < pic->y; i++)
    {
        for (int j = 0; j < pic->x; j++)
        {
            memcpy(img + ind, choose_color(pic->data[i][j]),7 * sizeof(char)); // Size 7
            ind += 7;
            memcpy(img + ind, get_char_pixel(pic->data[i][j]), sizeof(char)); // Size 1
            ind += 1;
        }
        memcpy(img + ind, "\n", sizeof(char));
        ind += 1;
    }
    memcpy(img + ind, "\n", sizeof(char));
    ind += 1;
    printf("%s\n",img);
    fflush(stdout);
    free(img);
}


void display_picture_true_color(PPMimage* pic)
{
    char* img = calloc(pic->x * pic->y * 20 + pic->y + 1,sizeof(char));
    size_t ind = 0;
    char* buff = calloc(32, sizeof(char));
    fflush(stdout);
    for (int i = 0; i < pic->y; i++)
    {
        for (int j = 0; j < pic->x; j++)
        {
            // "\033[38;2;RED;GREEN;BLUEm"
            memcpy(img + ind, "\033[38;2;",7 * sizeof(char)); // Size 7
            ind += 7;
            buff = itoa(buff,pic->data[i][j].red);
            memcpy(img + ind,buff, strlen(buff) * sizeof(char));
            ind += strlen(buff);

            memcpy(img + ind,";", sizeof(char));
            ind += 1;

            buff = itoa(buff,pic->data[i][j].green);
            memcpy(img + ind,buff, strlen(buff) * sizeof(char));
            ind += strlen(buff);
            memcpy(img + ind,";", sizeof(char));
            ind += 1;

            buff = itoa(buff,pic->data[i][j].blue);
            memcpy(img + ind,buff, strlen(buff) * sizeof(char));
            ind += strlen(buff); 
            memcpy(img + ind,"m", sizeof(char));
            ind += 1;

            memcpy(img + ind, get_char_pixel(pic->data[i][j]), sizeof(char));
            ind += 1;
        }
        memcpy(img + ind, "\n", sizeof(char));
        ind += 1;

    }
    //printf("%s\n",img);
    fwrite(img,sizeof(char),ind + 1, stdout);
    fflush(stdout);
    // FILE* file = fopen("img.log","w");
    // fprintf(file,"%s\n", img);
    // fclose(file);
    free(img);
    free(buff);
}
