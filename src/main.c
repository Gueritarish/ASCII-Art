#include "display.h"
#include "ppm_data.h"
#include "update.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    char* write_path = NULL;
    PPMimage* img = NULL;
    int options = get_options(argc, argv, &img, &write_path);
    if (options == HELP)
        return 0;
    else if (options == ERROR)
        return 1;
    else if(!img)
    {
        printf("Please provide a valid path to a picture.\n");
        return 1;
    }
    if ((options & MONO) != 0)
        img = saturate(img);
    
    if ((options & REDUCE1) != 0)
        img = divide_by_two(img);
    
    if ((options & REDUCE2) != 0)
        img = divide_by_two(img);
    if ((options & WRITE) != 0)
    {
        printf("%s\n",write_path);
        write_ppm(img, write_path);
    }
    img = reduce_heigh(img);
    if ((options & STANDARD_COLOR) != 0)
        display_picture_standard(img);
    else
        display_picture_true_color(img, options & VIVID);
    free_PPM(img);
    return 0;
}
