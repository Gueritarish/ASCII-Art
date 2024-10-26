#include "utils.h"

#include <stdio.h>
#include <string.h>

int end_with(char *string, char* end)
{
    size_t str_size = strlen(string);
    size_t end_size = strlen(end);
    if (end_size > str_size)
        return 0;

    for (size_t i = str_size - end_size, j = 0; i < str_size; i++, j++)
    {
        if (string[i] != end[j])
            return 0;
    }
    return 1;
}

int start_with(char *string, char* start)
{
    size_t str_size = strlen(string);
    size_t start_size = strlen(start);
    if (start_size > str_size)
        return 0;
    for (size_t i = 0; i < start_size; i++)
    {
        if (string[i] != start[i])
            return 0;
    }
    return 1;
}

void usage()
{
    printf("NAME\n");
    printf("\tascii - small project to convert pictures in ascii art\n\n");
    printf("SYNOPSIS\n");
    printf("\tascii [OPTIONS]... [FILE]...\n\n");
    printf("DESCRIPTION\n");
    printf("\tDisplay an ASCII art of a the picture of which path is given\n\n");
    printf("\t-m, --mono\n\t\tshow the picture in black and white ( monochrome )\n\n");
    printf("\t-r, --reduce\n\t\thalve the size of the image ( can be used twice, above that will return an error )\n\n");
    printf("\t-std, --standard, --regular\n\t\tdisplay the ASCII using only the 8 Standard shell colors\n\t\tif your shell doesn't support 24 bit coloration, please use that\n\n");    
    printf("\t-w=[filename], --write[filename]\n\t\twrite the data of the picture (after modification ) inside .ppm file ( not in ascii art )\n\n");
    printf("\t-?, -h, --help\n\t\tdisplay this help and exit\n");
}

int get_options(int argc,char* argv[], PPMimage** img, char** writing_path)
{
    if (argc < 2)
        printf("Please provide at least the path to a picture, or call with --help.\n");
    int options = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i],"-?") == 0 || strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0)
        {
            usage();
            options = HELP;
            break;
        }
        else if (strcmp(argv[i],"-m") == 0 || strcmp(argv[i],"--mono") == 0)
        {
            if ((options & MONO) != 0)
            {
                printf("Arguments -m or --mono, given twice.\n");
                options = ERROR;
                break;
            }
            options |= MONO;
        }
        else if (strcmp(argv[i],"-r") == 0 || strcmp(argv[i],"--reduce") == 0)
        {
            if ((options & REDUCE2) != 0)
            {
                options = ERROR;
                printf("Arguments -r or --reduce given more than two times.\n");
                break;
            }
            if ((options & REDUCE1) != 0)
            {
                options |= REDUCE2;
            }
            options |= REDUCE1;
        }
        else if (strcmp(argv[i],"-std") == 0 || strcmp(argv[i],"--standard") == 0 || strcmp(argv[i],"--regular") == 0)
        {
            if ((options & STANDARD_COLOR) != 0)
            {
                options = ERROR;
                printf("Arguments -std, --standard or -- regulard, given twice.\n");
                break;
            }
            options |= STANDARD_COLOR;
        }
        else if (start_with(argv[i], "-w=") || start_with(argv[i],"--write="))
        {
            if (!end_with(argv[i], ".ppm"))
            {  
                options = ERROR;
                printf("The writing file must be a path with a .ppm extension.\n");
                break;
            }
            options |= WRITE;
            if (argv[i][1] == '-')
                *writing_path = argv[i] + 8;
            else
                *writing_path = argv[i] + 3;
        }
        else if (end_with(argv[i],".jpeg") || end_with(argv[i],".jpg"))
        {
            if (*img)
            {
                printf("Given two differents paths to a picture.\n");
                options = ERROR;
                break;
            }
            *img = read_jpeg(argv[i]);
            options |= SUCCESS;
        }
        else if (end_with(argv[i],".png"))
        {
            if (*img)
            {
                options = ERROR;
                printf("Given two differents paths to a picture.\n");
                break;
            }
            *img = read_png(argv[i]);
            options |= SUCCESS;
        }
        else if (end_with(argv[i],".ppm"))
        {
            if (*img)
            {
                printf("Given two differents paths to a picture.\n");
                options = ERROR;
                break;
            }
            *img = read_ppm(argv[i]);
            options |= SUCCESS;
        }
        else
        {
            options = ERROR;
            printf("Wrong argument given : %s\n",argv[i]);
            break;
        }
    }
    if ((options == ERROR || options == HELP) && *img)
        free_PPM(*img);
    return options;
}