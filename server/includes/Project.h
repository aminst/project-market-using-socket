#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <string.h>

#include "Utils.h"

#define WAITING_LIST_LIMIT 5
#define EMPTY_WAITING_LIST_VALUE -1

typedef struct
{
    int id;
    char* name;
    int waiting_list[WAITING_LIST_LIMIT-1];
    int sold;
} Project;

char* get_project_info(Project project);
char* get_waiting_list_status(Project project);

#endif