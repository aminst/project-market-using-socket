#include "Utils.h"

char* int_to_str(int num)
{
    char digits[] = "0123456789";
    char temp[20];
    char* final = (char*)malloc(20);
    int i = 0, j = 0;
    do {
        temp[i++] = digits[num % 10];
        num /= 10;
    } while (num > 0);
    while(--i >= 0)
        final[j++] = temp[i];
    final[j] = '\0';
    return (char*) final;
}