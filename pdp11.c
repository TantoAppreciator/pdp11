#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MEMSIZE (64 * 1024)
typedef char byte;
typedef unsigned int Length;
typedef short word;
typedef word address;
byte mem[MEMSIZE];
void b_write(address adr, byte val);
byte b_read(address adr);
void w_write(address adr, word val);
word w_read(address adr);
void load_data(FILE *stream);
void mem_dump(address adr, int size);

int main()
{
    load_data(stdin);

    mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);

    return 0;
}

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
void load_data(FILE *stream)
{
    address adr;
    int n;
    while (2 == fscanf(stream, "%x%x", &adr, &n))
        for (int i = 0; i < n; i++)
        {
            unsigned int x;
            scanf("%x", &x);
            b_write(adr + i, x);
        }
}
void mem_dump(address adr, int size)
{
    for (int i = 0; i < size; i += 2)
        printf("%06o: %06o %04x\n", adr + i, w_read(adr + i) & 0xFFFF, w_read(adr + i) & 0xFFFF);
}