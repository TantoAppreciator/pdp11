#include "pdp11.h"
#include "commands.h"

Arg ss, dd;

Arg get_mr(word w)
{
}
void do_nothing() {}
void do_halt()
{
    reg_dump();
    logger(TRACE, "THE END\n");
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
    w_write(dd.adr, dd.val++);
}
void do_sob()
{
}