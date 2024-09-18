#pragma once

#include "ppm_data.h"

PPMimage* divide_resolution(PPMimage* img, int n);
PPMimage* saturate(PPMimage* img);
PPMimage* reduce_heigh(PPMimage* img);