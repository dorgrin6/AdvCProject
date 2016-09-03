#define _CRT_SECURE_NO_WARNINGS
#ifndef __GENERAL_DEFS_H
#define __GENERAL_DEFS_H
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MILLENNIUM 2000 // current millennium
#define NOT_DEFINED -1 // undefined object
#define SECONDS_IN_DAY 86400 // number of seconds in day
#define N 7 //size of short_term_command queue
#define INIT_SIZE 1 // initial size of string

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

//sort paramaters
#define NO_SORT 0
#define HIGHEST_FIRST 1
#define LOWEST_FIRST -1

typedef short int SI;
typedef unsigned char BYTE;
#endif





