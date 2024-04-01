#include <stdio.h>
#include "mem.h"
static byte mem[MEMSIZE];
word reg[8];
void b_write(address adr, byte val)
{
    mem[adr] = val;
}
byte b_read(address adr)
{
    return mem[adr] & 0xFF;
}
void w_write(address adr, word val)
{
    byte b1 = val;
    mem[adr] = b1;
    byte b2 = (val >> 8);
    mem[adr + 1] = b2;
}
word w_read(address adr)
{
    byte b1 = mem[adr];
    byte b2 = mem[adr + 1];
    word w = b2;
    w = w << 8;
    w = w | (0xFF & b1);
    return w & 0xFFFF;
}
