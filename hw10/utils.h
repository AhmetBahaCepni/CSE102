#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

# define BOOKS_FILE "books.txt"
// books.txt format: ISBN number, title, author, publication year, reserved reservedStatus
# define STUDENTS_FILE "students.txt"
// students.txt format: name, ID, isbn number of one borrowed books.

typedef struct Book
{
    char *isbn;
    char *title;
    char *author;
    int publicationYear;
    int reservedStatus;
    struct Book *next;
} Book;

typedef struct Student
{
    char *name;
    char *id;
    Book *borrowedBooks;
    struct Student *next;
} Student;

void my_strcpy(char *dest, char *src);
int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
void update_books_from_file(Book **bookList);
void update_students_from_file(Student **studentList);
void update_books_to_file(Book *bookList);
void update_students_to_file(Student *studentList);
void print_books(Book *bookList);
void print_students(Student *studentList);
int count_borrowed_books(Student *student);
void add_book(Book **bookList, char *isbn, char *title, char *author, int publicationYear, int method);
void delete_book(Book **bookList, char *isbn);
void update_book(Book *bookList, char *isbn, char *feature, char *value);
void swap_node(Book *node1, Book *node2);
void filter_and_sort_books(Book *book, int filterChoice, char* filter, int sortChoice);
void reverse_book_list(Book **bookList);
void search_books(Book *bookList, int searchChoice, char *searchValue);
void borrow_book(Book *bookList, Student *studentList, char *isbn);
void return_book(Book *bookList, Student *studentList, char *isbn);

#endif