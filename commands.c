#include "pdp11.h"
#include "commands.h"

Arg ss, dd;

void do_nothing() {}
void do_halt()
{
    loger(TRACE, "THE END\n");
    exit(0);
}
void do_mov()
{
    w_write(dd.adr, ss.val);
}
void do_add()
{
    w_write(dd.adr, ss.val + dd.val);
}
void do_inc()
{
}
void do_sob()
{
}