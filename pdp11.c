#include "pdp11.h"
static int log_level = 0;

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
void reg_dump()
{
    printf("\n");
    for (int i = 0; i < 8; i++)
        printf("r%d:%o ", i, reg[i]);
    printf("\n");
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
void logger(int level, char *format, ...)
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