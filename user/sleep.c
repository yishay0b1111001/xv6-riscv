#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
    if (argc < 2) {
        write(1, "sleep: missing operand\n", 23);
        exit(0);
    }

    int sleep_for = atoi(argv[1]);
    sleep(sleep_for);
    exit(0);
}
