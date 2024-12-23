#pragma once
#include "ppm_data.h"
#include "update.h"

/* 
**
**  https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
**
**  
**  Color_Off =  "\033[0m"     # Text Reset
**  Black     =  "\033[0;30m"  # Black
**  Red       =  "\033[0;31m"  # Red
**  Green     =  "\033[0;32m"  # Green
**  Yellow    =  "\033[0;33m"  # Yellow
**  Blue      =  "\033[0;34m"  # Blue
**  Purple    =  "\033[0;35m"  # Pink
**  Cyan      =  "\033[0;36m"  # Cyan
**  White     =  "\033[0;37m"  # White
**
**  IRed='\033[0;91m'         # Orange
**  IPurple='\033[0;95m'      # Purple
*/

#define COLOR_OFF "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PINK "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define ORANGE "\033[0;91m"
#define PURPLE "\033[0;95m"


char* choose_color(PPMpixeldata pixel);
char* get_char_pixel(PPMpixeldata pixel);
void display_picture_standard(PPMimage* pic);
void display_picture_true_color(PPMimage* pic, int vivid);
