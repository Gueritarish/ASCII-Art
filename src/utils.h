#pragma once

#include "ppm_data.h"

#define HELP -1
#define ERROR 0
#define MONO 1
#define REDUCE 2
#define WRITE 4
#define STANDARD_COLOR 8
#define SUCCESS 16

int end_with(char *string, char* end);
void usage();
int get_options(int argc,char* argv[], PPMimage** img, char** writing_path);