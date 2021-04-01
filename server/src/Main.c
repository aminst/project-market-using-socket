#include "Server.h"

int main(int argc, char *argv[])
{
    run_server_on_port(get_server_port(argc, argv));
    return 0;
}