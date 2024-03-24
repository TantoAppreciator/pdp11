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
void load_file(const char *filename);
void usage(const char *progname);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argv[0]);
        exit(1);
    }
    load_file(argv[1]);
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
    while (2 == fscanf(stream, "%hx%x", &adr, &n))
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
void load_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror(filename);
        exit(1);
    }
    load_data(file);
    fclose(file);
}
void usage(const char *progname)
{
    printf("USAGE: %s flie\n file - PDP-11 execution file\n", progname);
}