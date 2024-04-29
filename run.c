#include "pdp11.h"
#include "commands.h"

void run()
{
    pc = 01000;
    Command comd;
    while (1)
    {
        comd = parse_cmd(read_cmd());
        comd.do_func();
        logger(TRACE, "\n");
        reg_dump();
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