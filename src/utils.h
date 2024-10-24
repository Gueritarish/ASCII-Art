#pragma once

#include "ppm_data.h"

#define HELP -1
#define ERROR 0
#define MONO 1
#define REDUCE1 2
#define REDUCE2 4
#define WRITE 8
#define STANDARD_COLOR 16
#define SUCCESS 32

int end_with(char *string, char* end);
int end_with(char *string, char* start);
void usage();
int get_options(int argc,char* argv[], PPMimage** img, char** writing_path);