#include "display.h"
#include "ppm_data.h"
#include "update.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please provide one single path to a ppm picture.\n");
        return 1;
    }
    PPMimage* img = read_ppm(argv[1]);
    if(!img)
    {
        return 1;
    }
    // PPMimage* upd = divide_resolution(img,2);
    PPMimage* reduce = reduce_heigh(img);
    // PPMimage* satur = saturate(reduce);
    display_picture(reduce);
    free(img);
    // free(upd);
    free(reduce);
    //free(satur);
    return 0;
}
