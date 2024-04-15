#include <stdio.h>
#include "mem.h"
static byte mem[MEMSIZE];
word reg[8];
void b_write(address adr, byte val)
{
    if (adr < 8)
    {
        reg[adr] = val;
        return;
    }
    mem[adr] = val;
}
byte b_read(address adr)
{
    if (adr < 8)
        return reg[adr] & 0xFF;
    return mem[adr] & 0xFF;
}
void w_write(address adr, word val)
{
    if (adr < 8)
    {
        reg[adr] = val;
        return;
    }
    byte b1 = val;
    mem[adr] = b1;
    byte b2 = (val >> 8);
    mem[adr + 1] = b2;
}
word w_read(address adr)
{
    if (adr < 8)
        return reg[adr] & 0xFF;
    byte b1 = mem[adr];
    byte b2 = mem[adr + 1];
    word w = b2;
    w = w << 8;
    w = w | (0xFF & b1);
    return w & 0xFFFF;
}
