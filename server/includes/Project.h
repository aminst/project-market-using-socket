#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <string.h>

#include "Utils.h"

#define WAITING_LIST_LIMIT 5
#define EMPTY_WAITING_LIST_VALUE -1
#define PROJECTS_COUNT 5

typedef struct
{
    int id;
    char* name;
    int waiting_list[WAITING_LIST_LIMIT];
    int sold;
} Project;

char* get_project_info(Project project);
int get_waiting_list_full_count(Project project);
int is_full(Project project);
char* get_waiting_list_status(Project project);

Project* get_initial_projects();


#endif