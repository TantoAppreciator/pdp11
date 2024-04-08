#pragma once
#include <stdio.h>
#include "mem.h"
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
} Command;

typedef struct
{
    address adr;
    word val;
} Arg;

extern Arg ss, dd;

Arg get_mr(word w);
void do_nothing();
void do_halt();
void do_mov();
void do_add();
void do_inc();
void do_sob();