#include "utils.h"

void update_books_from_file(Book **bookList)
{
    FILE *file = fopen(BOOKS_FILE, "r");
    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    char isbn[20], title[50], author[50];
    int publicationYear, reservedStatus;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d", isbn, title, author, &publicationYear, &reservedStatus) != EOF)
    {
        Book *newBook = (Book *)malloc(sizeof(Book));
        newBook->isbn = (char *)malloc(sizeof(char) * (my_strlen(isbn) + 1));
        newBook->title = (char *)malloc(sizeof(char) * (my_strlen(title) + 1));
        newBook->author = (char *)malloc(sizeof(char) * (my_strlen(author) + 1));
        my_strcpy(newBook->isbn, isbn);
        my_strcpy(newBook->title, title);
        my_strcpy(newBook->author, author);
        newBook->publicationYear = publicationYear;
        newBook->reservedStatus = reservedStatus;
        newBook->next = NULL;
        if (*bookList == NULL)
        {
            *bookList = newBook;
        }
        else
        {
            Book *temp = *bookList;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newBook;
        }
        fgetc(file);
    }
    fclose(file);
}

void update_students_from_file(Student **studentList)
{
    FILE *file = fopen(STUDENTS_FILE, "r");
    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    char name[50], id[20], isbn[20];
    while (fscanf(file, "%[^,],%[^,],%s", name, id, isbn) != EOF)
    {
        // now we should search for id in studentList and if there is no student with this id, we should create a new student
        // if there are a student with this id, we should add the book to the borrowedBooks list of this student
        Student *temp = *studentList;
        while (temp != NULL && my_strcmp(temp->id, id) != 0)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            // there is no student with this id
            Student *newStudent = (Student *)malloc(sizeof(Student));
            newStudent->name = (char *)malloc(sizeof(char) * (my_strlen(name) + 1));
            newStudent->id = (char *)malloc(sizeof(char) * (my_strlen(id) + 1));
            my_strcpy(newStudent->name, name);
            my_strcpy(newStudent->id, id);
            newStudent->borrowedBooks = NULL;
            newStudent->next = NULL;
            if (*studentList == NULL)
            {
                *studentList = newStudent;
            }
            else
            {
                Student *temp = *studentList;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newStudent;
            }
            temp = newStudent;
        }
        // now we should add the book to the borrowedBooks list of this student
        Book *newBook = (Book *)malloc(sizeof(Book));
        newBook->isbn = (char *)malloc(sizeof(char) * (my_strlen(isbn) + 1));
        my_strcpy(newBook->isbn, isbn);
        newBook->next = NULL;
        if (temp->borrowedBooks == NULL)
        {
            temp->borrowedBooks = newBook;
        }
        else
        {
            Book *tempBook = temp->borrowedBooks;
            while (tempBook->next != NULL)
            {
                tempBook = tempBook->next;
            }
            tempBook->next = newBook;
        }
        fgetc(file);
    }
    fclose(file);
}

void update_books_to_file(Book *bookList)
{
    FILE *file = fopen(BOOKS_FILE, "w");
    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    Book *temp = bookList;
    while (temp != NULL)
    {
        fprintf(file, "%s,%s,%s,%d,%d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->reservedStatus);
        temp = temp->next;
    }
    fclose(file);
}

void update_students_to_file(Student *studentList)
{
    // a student can have more than 1 book and i store them in seperate lines
    FILE *file = fopen(STUDENTS_FILE, "w");
    if (file == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    Student *temp = studentList;
    while (temp != NULL)
    {
        Book *tempBook = temp->borrowedBooks;
        while (tempBook != NULL)
        {
            fprintf(file, "%s,%s,%s\n", temp->name, temp->id, tempBook->isbn);
            tempBook = tempBook->next;
        }
        temp = temp->next;
    }
    fclose(file);
}

void print_books(Book *bookList)
{
    Book *temp = bookList;
    while (temp != NULL)
    {
        printf("%s %s %s %d %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->reservedStatus);
        temp = temp->next;
    }
}

int count_borrowed_books(Student *student)
{
    int count = 0;
    Book *temp = student->borrowedBooks;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void add_book(Book **bookList, char *isbn, char *title, char *author, int publicationYear, int method)
{
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->isbn = (char *)malloc(sizeof(char) * (my_strlen(isbn) + 1));
    newBook->title = (char *)malloc(sizeof(char) * (my_strlen(title) + 1));
    newBook->author = (char *)malloc(sizeof(char) * (my_strlen(author) + 1));
    my_strcpy(newBook->isbn, isbn);
    my_strcpy(newBook->title, title);
    my_strcpy(newBook->author, author);
    newBook->publicationYear = publicationYear;
    newBook->reservedStatus = 0;
    newBook->next = NULL;
    if (*bookList == NULL)
    {
        *bookList = newBook;
    }
    else
    {
        if (method == 0)
        {
            // FIFO
            Book *temp = *bookList;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newBook;
        }
        else
        {
            // LIFO
            newBook->next = *bookList;
            *bookList = newBook;
        }
    }
}

void delete_book(Book **bookList, char *isbn)
{
    if (*bookList == NULL)
    {
        printf("There is no book in the library!\n");
        return;
    }
    if (my_strcmp((*bookList)->isbn, isbn) == 0)
    {
        Book *temp = *bookList;
        *bookList = (*bookList)->next;
        free(temp->isbn);
        free(temp->title);
        free(temp->author);
        free(temp);
        return;
    }
    Book *temp = *bookList;
    while (temp->next != NULL && my_strcmp(temp->next->isbn, isbn) != 0)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        printf("There is no book with this isbn!\n");
        return;
    }
    Book *temp2 = temp->next;
    temp->next = temp->next->next;
    free(temp2->isbn);
    free(temp2->title);
    free(temp2->author);
    free(temp2);
}

void update_book(Book *bookList, char *isbn, char *feature, char *value)
{
    Book *temp = bookList;
    while (temp != NULL && my_strcmp(temp->isbn, isbn) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("There is no book with this isbn!\n");
        return;
    }
    if (my_strcmp(feature, "title") == 0)
    {
        free(temp->title);
        temp->title = (char *)malloc(sizeof(char) * (my_strlen(value) + 1));
        my_strcpy(temp->title, value);
    }
    else if (my_strcmp(feature, "author") == 0)
    {
        free(temp->author);
        temp->author = (char *)malloc(sizeof(char) * (my_strlen(value) + 1));
        my_strcpy(temp->author, value);
    }
    else if (my_strcmp(feature, "publication year") == 0)
    {
        temp->publicationYear = atoi(value);
    }
    else
    {
        printf("There is no feature with this name!\n");
    }
}


void swap_node(Book *node1, Book *node2)
{
    //initializing a temporary node
    Book *tmp = (Book *)malloc(sizeof(Book));
    tmp->isbn = (char *)malloc(sizeof(char) * strlen(node1->isbn));
    tmp->title = (char *)malloc(sizeof(char) * strlen(node1->title));
    tmp->author = (char *)malloc(sizeof(char) * strlen(node1->author));

    //coppies the node1 to the temporary node
    strcpy(tmp->isbn, node1->isbn);
    strcpy(tmp->title, node1->title);
    strcpy(tmp->author, node1->author);
    tmp->publicationYear = node1->publicationYear;
    tmp->reservedStatus = node1->reservedStatus;

    //coppies the node2 to the node1
    strcpy(node1->isbn, node2->isbn);
    strcpy(node1->title, node2->title);
    strcpy(node1->author, node2->author);
    node1->publicationYear = node2->publicationYear;
    node1->reservedStatus = node2->reservedStatus;

    //coppies the temporary node to the node2
    strcpy(node2->isbn, tmp->isbn);
    strcpy(node2->title, tmp->title);
    strcpy(node2->author, tmp->author);
    node2->publicationYear = tmp->publicationYear;
    node2->reservedStatus = tmp->reservedStatus;

    free(tmp->author);
    free(tmp->title);
    free(tmp->isbn);
    free(tmp);
}

void filter_and_sort_books(Book *book, int filterChoice, char* filter, int sortChoice)
{
    Book *tmp = NULL;
    Book *tmp2 = NULL;
    if (filterChoice == 0)//filter by author
    {
        printf("\n\nBOOKS WROTE BY %s", filter);
        while (book != NULL)
        {
            // if the book is found
            if (strcmp(book->author, filter) == 0)
                add_book(&tmp, book->isbn, book->title, book->author, book->publicationYear, 1);
            book = book->next;
        }
    }
    else if (filterChoice == 1)//filter by publication year
    {
        printf("BOOKS PUBLISHED IN %s", filter);
        while (book != NULL)
        {
            // if the book is found
            if (book->publicationYear == atoi(filter))
                add_book(&tmp, book->isbn, book->title, book->author, book->publicationYear, 1);
            book = book->next;
        }
    }
    if (!tmp)
    {
        printf("\nNO BOOKS FOUND\n\n");
        return;
    }
    tmp2 = tmp;
    //printBooks(tmp);
    if (sortChoice == 0)//sort by title
    {
        printf(" AND SORTED BY TITLE\n");
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->title, tmp->next->title) > 0)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    else if (sortChoice == 1)//sort by author
    {
        printf(" AND SORTED BY AUTHOR\n");
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->author, tmp->next->author) > 0)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    else if (sortChoice == 2)//sort by publication year
    {
        printf(" AND SORTED BY PUBLICATION YEAR\n");
        while (tmp->next != NULL)
        {
            if (tmp->publicationYear > tmp->next->publicationYear)
            {
                swap_node(tmp, tmp->next);
                tmp = tmp2;
            }
            else
                tmp = tmp->next;
        }
    }
    print_books(tmp2);
}

void reverse_book_list(Book **bookList)
{
    Book *prev = NULL;
    Book *current = *bookList;
    Book *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *bookList = prev;
    printf("The book list is succesfully reversed!\n");
}

void search_books(Book *bookList, int searchChoice, char *searchValue)
{
    Book *temp = bookList;
    int count = 0;
    while (temp != NULL)
    {
        if (searchChoice == 0)
        {
            // search by isbn
            if (my_strcmp(temp->isbn, searchValue) == 0)
            {
                printf("%s %s %s %d %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->reservedStatus);
                count++;
                return;
            }
        }
        else if (searchChoice == 1)
        {
            // search by author
            if (my_strcmp(temp->author, searchValue) == 0)
            {
                printf("%s %s %s %d %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->reservedStatus);
                count++;
            }
        }   
        else
        {
            // search by title
            if (my_strcmp(temp->title, searchValue) == 0)
            {
                printf("%s %s %s %d %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->reservedStatus);
                count++;
            }
        }
        temp = temp->next;
    }
    if (count == 0)
        printf("There is no book with this search criteria!\n");
}

void borrow_book(Book *bookList, Student *studentList, char *isbn)
{
    Book *temp = bookList;
    while (temp != NULL && my_strcmp(temp->isbn, isbn) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("There is no book with this isbn!\n");
        return;
    }
    if (temp->reservedStatus == 1)
    {
        printf("This book is already reserved!\n");
        return;
    }
    temp->reservedStatus = 1;
    char id[20];
    printf("Enter your id: ");
    scanf(" %[^\n]", id);
    Student *tempStudent = studentList;
    while (tempStudent != NULL && my_strcmp(tempStudent->id, id) != 0)
    {
        tempStudent = tempStudent->next;
    }
    if (tempStudent == NULL)
    {
        printf("There is no student with this id!\n");
        return;
    }
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->isbn = (char *)malloc(sizeof(char) * (my_strlen(isbn) + 1));
    my_strcpy(newBook->isbn, isbn);
    newBook->next = NULL;
    if (tempStudent->borrowedBooks == NULL)
    {
        tempStudent->borrowedBooks = newBook;
    }
    else
    {
        Book *tempBook = tempStudent->borrowedBooks;
        while (tempBook->next != NULL)
        {
            tempBook = tempBook->next;
        }
        tempBook->next = newBook;
    }
}

void return_book(Book *bookList, Student *studentList, char *isbn)
{
    Book *temp = bookList;
    while (temp != NULL && my_strcmp(temp->isbn, isbn) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("There is no book with this isbn!\n");
        return;
    }
    if (temp->reservedStatus == 0)
    {
        printf("This book is already available!\n");
        return;
    }
    temp->reservedStatus = 0;
    char id[20];
    printf("Enter your id: ");
    scanf(" %[^\n]", id);
    Student *tempStudent = studentList;
    while (tempStudent != NULL && my_strcmp(tempStudent->id, id) != 0)
    {
        tempStudent = tempStudent->next;
    }
    if (tempStudent == NULL)
    {
        printf("There is no student with this id!\n");
        return;
    }
    if (tempStudent->borrowedBooks == NULL)
    {
        printf("You have not borrowed any book!\n");
        return;
    }
    if (my_strcmp(tempStudent->borrowedBooks->isbn, isbn) == 0)
    {
        Book *tempBook = tempStudent->borrowedBooks;
        tempStudent->borrowedBooks = tempStudent->borrowedBooks->next;
        free(tempBook->isbn);
        free(tempBook);
        return;
    }
    Book *tempBook = tempStudent->borrowedBooks;
    while (tempBook->next != NULL && my_strcmp(tempBook->next->isbn, isbn) != 0)
    {
        tempBook = tempBook->next;
    }
    if (tempBook->next == NULL)
    {
        printf("You have not borrowed this book!\n");
        return;
    }
    Book *tempBook2 = tempBook->next;
    tempBook->next = tempBook->next->next;
    free(tempBook2->isbn);
    free(tempBook2);
}

// main should have a menu created with switch case statements
int main(void)
{
    int choice;
    Book *bookList = NULL;
    Student *studentList = NULL;
    update_books_from_file(&bookList);
    update_students_from_file(&studentList);

    while (choice < 9)
    {
        printf("\nWelcome to the Library Management System!\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Update Book\n");
        printf("4. Filter and Sort Books\n");
        printf("5. Reverse Book List\n");
        printf("6. Search Books\n");
        printf("7. Borrow Book\n");
        printf("8. Return Book\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                char isbn[20], title[50], author[50];
                int publicationYear, method;
                printf("Enter the ISBN number of the book: ");
                scanf(" %[^\n]", isbn);
                printf("Enter the title of the book: ");
                scanf(" %[^\n]", title);
                printf("Enter the author of the book: ");
                scanf(" %[^\n]", author);
                printf("Enter the publication year of the book: ");
                scanf("%d", &publicationYear);
                printf("Enter the book management method (0 for FIFO, 1 for LIFO): ");
                scanf("%d", &method);
                add_book(&bookList, isbn, title, author, publicationYear, method);
                update_books_to_file(bookList);
                break;
            }
            case 2:
            {
                char isbn[20];
                printf("Enter the ISBN number of the book: ");
                scanf(" %[^\n]", isbn);
                delete_book(&bookList, isbn);
                update_books_to_file(bookList);
                break;
            }
            case 3:
            {
                char isbn[20], feature[20], value[50];
                printf("Enter the ISBN number of the book: ");
                scanf(" %[^\n]", isbn);
                printf("Enter the name of the feature to be updated \n(title, author, or publication year): ");
                scanf(" %[^\n]", feature);
                printf("Enter the new value for that feature: ");
                scanf(" %[^\n]", value);
                update_book(bookList, isbn, feature, value);
                update_books_to_file(bookList);
                break;
            }
            case 4:
            {
                int filterChoice, sortChoice;
                char filter[50];
                printf("Enter the filter choice (0 for filtering by author, 1 for filtering by publication year): ");
                scanf("%d", &filterChoice);
                printf("Enter the filter criteria: ");
                scanf(" %[^\n]", filter);
                printf("Enter the sort choice (0 for sorting by title, 1 for sorting by author, 2 for sorting by publication year): ");
                scanf("%d", &sortChoice);
                filter_and_sort_books(bookList, filterChoice, filter, sortChoice);
                break;
            }
            case 5:
            {
                reverse_book_list(&bookList);
                break;
            }
            case 6:
            {
                int searchChoice;
                char searchValue[50];
                printf("Enter the search choice (0 for searching by ISBN number, 1 for searching by author, 2 for searching by title): ");
                scanf("%d", &searchChoice);
                printf("Enter the search value: ");
                scanf(" %[^\n]", searchValue);
                search_books(bookList, searchChoice, searchValue);
                break;
            }
            case 7:
            {
                char isbn[20];
                printf("Enter the ISBN number of the book: ");
                scanf(" %[^\n]", isbn);
                borrow_book(bookList, studentList, isbn);
                update_students_to_file(studentList);
                break;
            }
            case 8:
            {
                char isbn[20];
                printf("Enter the ISBN number of the book: ");
                scanf(" %[^\n]", isbn);
                return_book(bookList, studentList, isbn);
                update_students_to_file(studentList);
                break;
            }
            case 9:
            {
                printf("Terminating ...\n");
                break;
            }
        }
    }

    return 0;
}