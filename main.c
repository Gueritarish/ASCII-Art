#include "ppm_data.h"
#include "update.h"

int main(void)
{
    PPMimage* img = read_ppm("pics/bonhomme.ppm");
    if(!img)
    {
        return 1;
    }
    
    printf("height : %d\nwidth : %d\n", img->y,img->x);

    PPMimage* upd = divide_resolution(img,2);
    PPMimage* satur = saturate(upd);
    printf("height : %d\nwidth : %d\n", upd->y,upd->x);
    write_ppm(satur,"picturetest.ppm");
    free(img);
    free(upd);
    free(satur);
    return 0;
}