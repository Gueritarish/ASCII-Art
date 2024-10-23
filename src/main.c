#include "display.h"
#include "ppm_data.h"
#include "update.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please provide one single path to a ppm picture.\n");
        return 1;
    }
    PPMimage* img = NULL;
    if (end_with(argv[1],".jpeg") || end_with(argv[1],".jpg"))
        img = read_jpeg(argv[1]);
    else if (end_with(argv[1],".png"))
        img = read_png(argv[1]);
    else if (end_with(argv[1],".ppm"))
        img = read_ppm(argv[1]);
    if(!img)
    {
        return 1;
    }
    // PPMimage* upd = divide_resolution(img,2);
    PPMimage* reduce = reduce_heigh(img);
    PPMimage* satur = saturate(reduce);
    display_picture(satur);
    free(img);
    // free(upd);
    free(reduce);
    free(satur);
    return 0;
}
