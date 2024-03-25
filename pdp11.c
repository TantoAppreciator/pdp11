#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#define MEMSIZE (64 * 1024)
#define DEBUG 0
#define TRACE 1
#define INFO 2
#define ERROR 3
int log_level = 0;
typedef char byte;
typedef unsigned int Length;
typedef short word;
typedef word address;
byte mem[MEMSIZE];
word reg[8];
void b_write(address adr, byte val);
byte b_read(address adr);
void w_write(address adr, word val);
word w_read(address adr);
void load_data(FILE *stream);
void mem_dump(address adr, int size);
void load_file(const char *filename);
void usage(const char *progname);
void log(int level, char *format, ...);
int set_log_level(int level);

int main(int argc, char *argv[])
{
    /*if (argc == 1)
    {
        usage(argv[0]);
        exit(1);
    }
    load_file(argv[1]); // /home/olivee/C/test.txt
    mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);*/
    log(INFO, "%d%d%d", 3, 4, 5);
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
    unsigned int adr;
    unsigned int n;
    while (2 == fscanf(stream, "%x%x", &adr, &n))
        for (int i = 0; i < n; i++)
        {
            unsigned int x;
            fscanf(stream, "%x", &x);
            printf("%x: %x\n", adr + i, x);
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
void log(int level, char *format, ...)
{
    if (level < log_level)
        return;
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
int set_log_level(int level)
{
    int prev_level = log_level;
    log_level = level;
    return prev_level;
}