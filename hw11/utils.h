#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct family_node
{
    char *name;
    int age;
    int child_count;
    struct family_node *mother;
    struct family_node *father;
    struct family_node **childs; // array of persons
} family_node;

void my_strcpy(char *dest, char *src);
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
void add_children(family_node *parent, family_node *child, int gender);
void add_mother_and_father(family_node *child, family_node *mother, family_node *father);
family_node *create_person(char *name, int age);
family_node *find_person(family_node *root, char *name);
family_node *delete_person(family_node *root, char *name);
void fprintf_person(family_node *person, FILE *fp);
void update_txt_file(family_node *root, FILE *fp);
family_node *read_person(FILE *fp, family_node *root, family_node *spouse);
void fill_from_txt_file(family_node **root, char *filename);

#endif