#include "Project.h"

void add_user_to_project(int fd, int project_id, Project* projects)
{
    if (project_id >= PROJECTS_COUNT || project_id < 0)
    {
        const char* invalid_project_id_msg = "Invalid Project Id Requestd!\n";
        write(1, invalid_project_id_msg, strlen(invalid_project_id_msg));
    }
    else if (projects[project_id].sold == 1)
    {
        const char* project_is_sold_msg = "Already Sold Project Requested!\n";
        write(1, project_is_sold_msg, strlen(project_is_sold_msg));
    }
    else if (is_full(projects[project_id]))
    {
        const char* project_waiting_list_is_full_msg = "Full Project Waiting List Requested!\n";
        write(1, project_waiting_list_is_full_msg, strlen(project_waiting_list_is_full_msg));
    }
    else{
        for (int i = 0; i < WAITING_LIST_LIMIT; i++)
        {
            if (projects[project_id].waiting_list[i] == -1)
            {
                projects[project_id].waiting_list[i] = fd;
                break;
            }
        }
        char successfully_added_to_project_msg[200];
        strcat(successfully_added_to_project_msg, "User Successfully added to Project ");
        strcat(successfully_added_to_project_msg, int_to_str(project_id));
        strcat(successfully_added_to_project_msg, "\n");
        write(1, successfully_added_to_project_msg, strlen(successfully_added_to_project_msg));
    }
}

int is_full(Project project)
{
    return get_waiting_list_full_count(project) == WAITING_LIST_LIMIT ? 1 : 0;
}

int get_waiting_list_full_count(Project project)
{
    int count = 0;
    for (int i = 0; i < WAITING_LIST_LIMIT; i++)
    {
        if(project.waiting_list[i] != EMPTY_WAITING_LIST_VALUE)
            count++;
    }
    return count;    
}

char* get_waiting_list_status(Project project)
{
    int count = get_waiting_list_full_count(project);

    char* status = (char*)malloc(50);

    if (is_full(project))
        return "FULL";
    else
    {
        char* status = (char*)malloc(50);
        int remaining = WAITING_LIST_LIMIT - count;
        strcat(status, int_to_str(remaining));
        strcat(status, " Remaining");
        return status;
    }
}

char* get_project_info(Project project)
{
    char* project_info = (char*)malloc(1000);
    strcat(project_info, "Project ID: ");
    strcat(project_info, int_to_str(project.id));
    strcat(project_info, "|");
    strcat(project_info, "Project Name: ");
    strcat(project_info, project.name);
    strcat(project_info, "|");
    strcat(project_info, "Waiting List Status: ");
    strcat(project_info, get_waiting_list_status(project));
    strcat(project_info, "\n");
    return project_info;
}

Project* get_initial_projects()
{
    Project* projects = malloc(sizeof(Project) * PROJECTS_COUNT);

    projects[0].id = 0;
    projects[0].name = "Web Scraping";
    
    projects[1].id = 1;
    projects[1].name = "Web Development";

    projects[2].id = 2;
    projects[2].name = "Socket Programming";

    projects[3].id = 3;
    projects[3].name = "Teaching Programming";

    projects[4].id = 4;
    projects[4].name = "Random Project";

    for (int i = 0; i < PROJECTS_COUNT; i++)
    {
        for (int j = 0; j < WAITING_LIST_LIMIT; j++)
            projects[i].waiting_list[j] = EMPTY_WAITING_LIST_VALUE;
        projects[i].sold = 0;
    }
    return projects;
}