#include "pdp11.h"
#include "commands.h"
Command cmd[] = {
    {0170000, 010000, "mov", do_mov},
    {0170000, 060000, "add", do_add},
    {0177777, 000000, "halt", do_halt},
    {0177700, 005200, "inc", do_inc},
    {0177000, 077000, "sob", do_sob},
    {0000000, 000000, "unknown", do_nothing},
};
void run()
{
    pc = 01000;
    while (1)
    {
        word w = w_read(pc);
        loger(TRACE, "%06o %06o: ", pc, w);
        pc += 2;
        for (int i = 0; i < sizeof(cmd) / sizeof(Command); i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                loger(TRACE, "%s ", cmd[i].name);
                cmd[i].do_func();

                loger(TRACE, "\n");
                break;
            }
        }
        /*if (w == 0)
            do_halt();
        else if ((w & 0xF000) == 010000) // 01SSDD
        {
            printf("mov ");
            do_mov();
        }
        else if ((w & 0xF000) == 060000) // 01SSDD
        {
            printf("add ");
            do_add();
        }*/
    }
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argv[0]);
        exit(1);
    }
    load_file(argv[1]);
    loger(TRACE, "hello\n");
    run();
}