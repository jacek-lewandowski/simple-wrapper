#include <getopt.h>
#include <cstring>
#include "commands.h"
#include "utils.h"


int cmd_launch(int argc, char *argv[])
{
    return 0;
}

int cmd_kill(int argc, char *argv[])
{
    return 0;
}

int cmd_mkdir(int argc, char *argv[])
{
    return 0;
}

int cmd_rmdir(int argc, char *argv[])
{
    return 0;
}

int run_command(int argc, char *argv[])
{
    if (argc < 1)
    {
        log_error("Missing command");
    }

    optind = 1;
    opterr = 0;
    if (strcmp(argv[0], "launch") == 0)
    {
        return cmd_launch(argc, argv);
    }
    else if (strcmp(argv[0], "kill") == 0)
    {
        return cmd_kill(argc, argv);
    }
    else if (strcmp(argv[0], "mkdir") == 0)
    {
        return cmd_mkdir(argc, argv);
    }
    else if (strcmp(argv[0], "rmdir") == 0)
    {
        return cmd_rmdir(argc, argv);
    }
    else
    {
        log_error("Invalid command %s", argv[0]);
        return -1;
    }
}
