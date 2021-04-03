#ifndef PROJECT_H
#define PROJECT_H

typedef struct
{
    int id;
    char* name;
    int waiting_list[4];
} Project;

#endif