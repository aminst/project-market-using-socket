#include "Project.h"

char* get_waiting_list_status(Project project)
{
    int count = 0;
    for (int i = 0; i < WAITING_LIST_LIMIT; i++)
    {
        if(project.waiting_list[i] != EMPTY_WAITING_LIST_VALUE)
            count++;
    }

    char* status = (char*)malloc(50);

    if (count == WAITING_LIST_LIMIT)
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