#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void search_product(int *p_nbr, int *s_nbr);
void file_ops(int *p_nbr, int *s_nbr);
void copy_to_file(char cpy_path[], char src_path[]);
void copy_to_stocks();
int delete_product(int pid, int p_nbr, char src_path[], char cpy_path[]);
int add_product(int p_nbr);
int find_feature(char str[], char path[]);
int update_product(int p_nbr);
int add_feature(int p_nbr);
int maxID(FILE *fl);
int add_stock(int p_nbr);
int delete_stock(int sid, int s_nbr);
int update_stock(int s_nbr);
void stock_status(int *p_nbr, int *s_nbr);
void query_with_id_and_branch(int s_nbr, int id,char branch_inp[]);
void brand_stock(int *p_nbr, int *s_nbr, char brand_name[16]);
int my_strcmp(const char str1[], const char str2[]);
void export_report(int p_nbr, int s_nbr ,char brand[16]);



#endif