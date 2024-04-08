#include "pdp11.h"
#include "commands.h"

Arg ss, dd;

Command cmd[] = {
    {0170000, 010000, "mov", do_mov},
    {0170000, 060000, "add", do_add},
    {0177777, 000000, "halt", do_halt},
    {0177700, 005200, "inc", do_inc},
    {0177000, 077000, "sob", do_sob},
    {0000000, 000000, "unknown", do_nothing},
};

Arg get_mr(word w)
{
    Arg res;
    int r = w & 7;
    int m = (w >> 3) & 7;
    switch (m)
    {
    case 0:
        res.adr = r;
        res.val = reg[r];
        logger(TRACE, "R%d", r);
        break;
    case 1:
        res.adr = reg[r];
        res.val = w_read(res.adr);
        logger(TRACE, "(R%d)", r);
        break;
    case 2:
        res.adr = reg[r];
        res.val = w_read(res.adr);
        reg[r] += 2;
        if (r == 7)
            logger(TRACE, "#%o", res.val);
        else
            logger(TRACE, "(R%d)+", r);
        break;
    default:
        logger(ERROR, "Mode %d is not implemented yet\n", m);
        exit(1);
    }
    return res;
}
word read_cmd()
{
    word res = w_read(pc);
    return res;
}
Command parse_cmd(word w)
{
    Command res;
    for (int i = 0; i < sizeof(cmd) / sizeof(Command); i++)
    {
        if ((w & cmd[i].mask) == cmd[i].opcode)
        {
            res = cmd[i];
        }
    }
    return res;
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