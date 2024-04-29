#include "pdp11.h"
#include "commands.h"

Arg ss, dd;
unsigned int nn, r;
signed char xx;
char b;
system_flags psw;
Command cmd[] = {
    {0170000, 0110000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 060000, "add", do_add, HAS_SS | HAS_DD},
    {0177777, 000000, "halt", do_halt, NO_PARAM},
    {0177700, 005200, "inc", do_inc, HAS_DD},
    {0177000, 077000, "sob", do_sob, HAS_NN | HAS_R},
    {0177700, 0105000, "clr", do_clr, HAS_DD},
    {0177700, 0005000, "clr", do_clr, HAS_DD},
    {0000000, 000000, "unknown", do_nothing, NO_PARAM},
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
        logger(TRACE, "R%d ", r);
        break;
    case 1:
        res.adr = reg[r];
        res.val = w_read(res.adr);
        logger(TRACE, "(R%d) ", r);
        break;
    case 2:
        res.adr = reg[r];
        if (b)
        {
            res.val = b_read(res.adr);
            if (r < 6)
                reg[r] += 1;
            else
                reg[r] += 2;
        }
        else
        {
            res.val = w_read(res.adr);
            reg[r] += 2;
        }
        if (r == 7)
            logger(TRACE, "#%o ", res.val);
        else
            logger(TRACE, "(R%d)+ ", r);
        break;
    case 4:
        if (b)
            if (r < 6)
                reg[r] -= 1;
            else
                reg[r] -= 2;
        else
            reg[r] -= 2;
        res.adr = reg[r];
        if (b)
            res.val = b_read(res.adr);
        else
            res.val = w_read(res.adr);
        logger(TRACE, "-(R%d) ", r);
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
    logger(TRACE, "%06o %06o : ", pc, res);
    pc += 2;
    return res;
}
Command parse_cmd(word w)
{
    Command res = {};
    for (int i = 0;; i++)
    {
        if ((w & cmd[i].mask) == cmd[i].opcode)
        {
            b = (w >> 15) & 01;
            res = cmd[i];
            logger(TRACE, "%s ", cmd[i].name);
            if (res.param & HAS_SS)
                ss = get_mr(w >> 6);
            if (res.param & HAS_DD)
                dd = get_mr(w);
            if (res.param & HAS_NN)
                nn = w & 077;
            if (res.param & HAS_R)
                r = (w >> 6) & 07;
            if (res.param & HAS_XX)
                xx = w & 077;
            return res;
        }
    }
    return res;
}
void set_NZ(word w)
{
    if (w == 0)
        psw.Z = 1;
    else
        psw.Z = 0;
    if (b)
        psw.N = (w >> 7) & 1;
    else
        psw.N = (w >> 15) & 1;
}
void set_C(dword w)
{
    if (b)
        psw.C = (w >> 8) & 1;
    else
        psw.C = (w >> 16) & 1;
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
    setNZ(ss.val);
    if (b)
        b_write(dd.adr, ss.val);
    else
        w_write(dd.adr, ss.val);
}
void do_add()
{
    dword res = (dword)ss.val + dd.val;
    w_write(dd.adr, res);
    set_NZ(res);
    set_C(res);
}
void do_inc()
{
    word res = dd.val++;
    w_write(dd.adr, res);
    set_NZ(res);
}
void do_sob()
{
    reg[r]--;
    if (reg[r] != 0)
        pc = pc - 2 * nn;
}
void do_clr()
{
    if (b)
        b_write(dd.adr, 0);
    else
        w_write(dd.adr, 0);
    psw.N = 0;
    psw.Z = 1;
    psw.C = 0;
}