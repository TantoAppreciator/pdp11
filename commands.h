#pragma once
#include <stdio.h>
#include "mem.h"
#define NO_PARAM 0
#define HAS_SS 1
#define HAS_DD 2
#define HAS_NN 4
#define HAS_R 8
#define HAS_XX 16
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
    char param;
} Command;

typedef struct
{
    address adr;
    word val;
} Arg;

typedef struct
{
    char N;
    char Z;
    char V;
    char C;
} system_flags;

extern Arg ss, dd;

extern Command cmd[];

Arg get_mr(word w);
word read_cmd();
Command parse_cmd(word w);
void do_nothing();
void do_halt();
void do_mov();
void do_add();
void do_inc();
void do_sob();
void do_clr();
void do_br();
