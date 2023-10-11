#include "utils.h"

void my_strcpy(char *dest, char *src) // this is a copy function that i wrote
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int my_strlen(char *str) // this is a string length function that i wrote
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int my_strcmp(char *str1, char *str2) // this is a string compare function that i wrote
{
    int i = 0;
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