#include "Server.h"

int get_random_port()
{
    struct sockaddr_in addr;
    int test_sock;
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(0); 
    test_sock = socket(AF_INET, SOCK_DGRAM, 0);
    while (addr.sin_port == 0) {
        bind(test_sock, (struct sockaddr *)&addr, sizeof(addr));
        int len = sizeof(addr);
        getsockname(test_sock, (struct sockaddr *)&addr, &len );
    }
    close(test_sock);
    printf("%d", addr.sin_port);
    return addr.sin_port;  
}

void send_udp_port_to_group(int project_id, Project* projects)
{
    int port = get_random_port();
    for(int i = 0; i < WAITING_LIST_LIMIT; i++)
    {
        char buf[50] = {0};
        strcat(buf, int_to_str(port));
        strcat(buf, "|");
        strcat(buf, int_to_str(i));
        strcat(buf, "|");
        send(projects[project_id].waiting_list[i], buf, strlen(buf), 0);
    }
}

int get_server_port(int argc, char* argv[])
{
    if (argc != 2)
        return DEFAULT_SERVER_PORT;
    else
    {
        return strtol(argv[1], NULL, 10);
    }
}

void write_server_startup_msg(int port)
{
    const char* server_run_msg = "Server Is Running On Port ";
    write(1, server_run_msg, strlen(server_run_msg));
    write(1, int_to_str(port), strlen(int_to_str(port)));
    const char* waiting_for_users_connect_msg = "\nWating For Users to connect\n";
    write(1, waiting_for_users_connect_msg, strlen(waiting_for_users_connect_msg));    
}

void send_available_projects_info(int fd, Project* projects)
{
    char projects_info[4000];
    strcat(projects_info, LINE_BREAKER);
    strcat(projects_info, "AVALIABLE PROJECTS LIST:\n");
    for(int i = 0; i < PROJECTS_COUNT; i++)
    {
        if (projects[i].sold != 1 && !is_full(projects[i]))
            strcat(projects_info, get_project_info(projects[i]));
    }
    strcat(projects_info, LINE_BREAKER);
    send(fd, projects_info, strlen(projects_info), 0);
}

void run_server_on_port(int port)
{
    Project* projects = get_initial_projects();

    struct sockaddr_in server_sin;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        const char* socket_creation_error_msg = "Socket Creation Error!\n";
        write(1, socket_creation_error_msg, strlen(socket_creation_error_msg));
        exit(EXIT_FAILURE);
    }

    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sin.sin_family = AF_INET;

    const int true_flag = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &true_flag, sizeof(int)) < 0)
    {
        const char* set_sock_option_error_msg = "Set Option Error!\n";
        write(1, set_sock_option_error_msg, strlen(set_sock_option_error_msg));
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)& server_sin, sizeof(server_sin)) == -1)
    {
        const char* bind_error_msg = "Bind Error!\n";
        write(1, bind_error_msg, strlen(bind_error_msg));
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CONNECTIONS) == -1)
    {
        const char* listen_error_msg = "Listen Error!\n";
        write(1, listen_error_msg, strlen(listen_error_msg));
        exit(EXIT_FAILURE);
    }

    write_server_startup_msg(port);

    struct sockaddr_in client_sin;
    int client_in_len;
    int new_server_fd = accept(server_fd, (struct sockaddr*)& client_sin, (socklen_t*)&client_in_len);
    if (new_server_fd == -1)
    {
        const char* accept_error_msg = "Accept Error!\n";
        write(1, accept_error_msg, strlen(accept_error_msg));
        exit(EXIT_FAILURE);
    }

    const char* user_accept_msg = "User Connected!\n";
    write(1, user_accept_msg, strlen(user_accept_msg));

    send_available_projects_info(new_server_fd, projects);
    char project_id_str[5];
    recv(new_server_fd, project_id_str, sizeof(project_id_str), 0);

    int is_group_ready = add_user_to_project(new_server_fd, atoi(project_id_str), projects);
    if (is_group_ready)
        send_udp_port_to_group(atoi(project_id_str), projects);

    char buf[MAX_BUFFER_SIZE];
    while (1)
    {
        // if ((client_in_len = recv(new_server_fd, buf, sizeof(buf), 0)))
        //     write(1, buf, strlen(buf));
    }
    close(server_fd);
    close(new_server_fd);
}
