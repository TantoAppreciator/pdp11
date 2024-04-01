#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#define DEBUG 0
#define TRACE 1
#define INFO 2
#define ERROR 3
void load_data(FILE *stream);
void mem_dump(address adr, int size);
void load_file(const char *filename);
void usage(const char *progname);
void loger(int level, char *format, ...);
int set_log_level(int level);