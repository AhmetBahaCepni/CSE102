#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>

# define IGNORED_FILE "./ignore.txt"
# define INPUT_FILE "./input.txt"
# define DICT_FILE "./dictionary.txt"
# define MAX_WORD_SIZE 15
# define THRESHOLD 6
# define INPUT_MAX_WORD 300000


int			find_line(char *str, char dict[][MAX_WORD_SIZE]);
int			whats_occoruence(char words[][MAX_WORD_SIZE], char *str, int read_nbr);
int			read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]);
int			ft_strlen(const char *str);
int			read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]);
double      calculate_distance(double vector1[], double vector2[]);
int			ft_atoi(const char *str, int len);
int			check_ignore_letters(char ch);
void		learn_dict_vars(char *file_name, int flag);
int			find_closest(char *str, char dict[][MAX_WORD_SIZE]);
double      dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold);
int         ft_strcat(char *dest, char *src, int j);
int			histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE+5+20]);
int			check_is_ignored(char word[]);
int			my_assign_fnct(char arr[][MAX_WORD_SIZE], char str[], int indx);
void        fill_histogram(char hist[][MAX_WORD_SIZE + 5 + 20], char *argv[], const int occurence[], char dict[][MAX_WORD_SIZE]);

# endif
