#include "utils.h"

void my_strcpy(char *dest, char *src) // this is a function i wrote for copying strings
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int my_strlen(char *str) // this is a function i wrote for finding length of strings
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int my_strcmp(char *str1, char *str2) // this is a function i wrote for comparing strings
{
    int i = 0;
    if (str1 == NULL || str2 == NULL)
    {
        return -1;
    }
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}