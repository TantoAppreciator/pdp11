#include "pdp11.h"
#include "commands.h"

void run()
{
    pc = 01000;
    Command comd;
    while (1)
    {
        // word w = w_read(pc);
        // logger(TRACE, "%06o %06o: ", pc, w);
        comd = parse_cmd(read_cmd());
        /*
        for (int i = 0; i < sizeof(cmd) / sizeof(Command); i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                logger(TRACE, "%s ", cmd[i].name);
                cmd[i].do_func();

                logger(TRACE, "\n");
                break;
            }
        }
        */
        comd.do_func();
        logger(TRACE, "\n");
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
    run();

    return 0;
}