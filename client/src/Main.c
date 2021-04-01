#include "Client.h"

int main(int argc, char *argv[])
{
    run_client(get_server_port(argc, argv));
    return 0;
}