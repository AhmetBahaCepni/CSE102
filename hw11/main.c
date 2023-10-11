#include "utils.h"

// this function adds a child to a parent
void add_children(family_node *parent, family_node *child, int gender)
{
    parent->child_count++;
    parent->childs = (family_node **)realloc(parent->childs, sizeof(family_node *) * parent->child_count);
    parent->childs[parent->child_count - 1] = child;
    if (gender == 0)
    {
        child->father = parent;
    }
    else
    {
        child->mother = parent;
    }   
}

// this function adds a mother or/and father to a child
void add_mother_and_father(family_node *child, family_node *mother, family_node *father)
{
    if(child->mother == NULL)
    {
        child->mother = mother;
        mother->child_count++;
        if(mother->childs == NULL)
            mother->childs = (family_node **)malloc(sizeof(family_node *));
        else
            mother->childs = (family_node **)realloc(mother->childs, sizeof(family_node *) * mother->child_count);
        mother->childs[mother->child_count - 1] = child;
    }
    if(child->father == NULL)
    {
        child->father = father;
        father->child_count++;
        if(father->childs == NULL)
            father->childs = (family_node **)malloc(sizeof(family_node *));
        else
            father->childs = (family_node **)realloc(father->childs, sizeof(family_node *) * father->child_count);
        father->childs[father->child_count - 1] = child;
    }
}

// this function creates a person and returns it
family_node *create_person(char *name, int age)
{
    family_node *person = (family_node *)malloc(sizeof(family_node));
    person->name = (char *)malloc(sizeof(char) * 20);
    my_strcpy(person->name, name);
    person->age = age;
    person->child_count = 0;
    person->childs = NULL;
    person->mother = NULL;
    person->father = NULL;
    return person;
}

// this function finds a person in the family tree and returns it
family_node *find_person(family_node *root, char *name)
{
    family_node *temp;
    if (root == NULL)
    {
        return NULL;
    }
    if (my_strcmp(root->name, name) == 0)
    {
        return root;
    }
    if (root->father != NULL && my_strcmp(root->father->name, name) == 0)
    {
        return root->father;
    }
    if (root->mother != NULL && my_strcmp(root->mother->name, name) == 0)
    {
        return root->mother;
    }
    else
    {
        for (int i = 0; i < root->child_count; i++)
        {
            temp = find_person(root->childs[i], name);
            if (temp != NULL)
            {
                return temp;
            }
        }
    }
    return NULL;
}

// this function deletes a person with the childrens from the family tree and returns the root
family_node *delete_person(family_node *root, char *name)
{
    family_node *person = find_person(root, name);
    if (person->child_count != 0)
    {
        printf("%s has children, are you sure you want to delete %s? (y/n): ", name, name);
        char answer;
        scanf(" %c", &answer);
        if (answer != 'y' && answer != 'Y')
        {
            printf("Deletion cancelled\n");
            return root;
        }
        int child_count = person->child_count;
        for (int i = 0; i < child_count; i++)
        {
            delete_person(person->childs[i], person->childs[i]->name);
        }
    }
    if (person->mother != NULL)
    {
        if(person->mother->childs != NULL)
        {
            for (int i = 0; i < person->mother->child_count; i++)
            {
                if (my_strcmp(person->mother->childs[i]->name, person->name) == 0)
                {
                    for (int j = i; j < person->mother->child_count - 1; j++)
                    {
                        person->mother->childs[j] = person->mother->childs[j + 1];
                    }
                    person->mother->child_count--;
                    person->father->child_count--;
                    person->mother->childs = (family_node **)realloc(person->mother->childs, sizeof(family_node *) * person->mother->child_count);
                    break;
                }
            }
        }
    }
    if (person->father != NULL)
    {
        if(person->father->childs != NULL)
        {
            for (int i = 0; i < person->father->child_count; i++)
            {
                if (my_strcmp(person->father->childs[i]->name, person->name) == 0)
                {
                    for (int j = i; j < person->father->child_count - 1; j++)
                    {
                        person->father->childs[j] = person->father->childs[j + 1];
                    }
                    person->father->child_count--;
                    person->mother->child_count--;
                    person->father->childs = (family_node **)realloc(person->father->childs, sizeof(family_node *) * person->father->child_count);
                    break;
                }
            }
        }
    }
    free(person->name);
    free(person->childs);
    free(person);
    return root;
}

// this function prints a person to a file
void fprintf_person(family_node *person, FILE *fp)
{
    fprintf(fp, "%s/%d/%d,", person->name, person->age, person->child_count);
    if (person->father != NULL)
        fprintf(fp, "%s,", person->father->name);
    else
        fprintf(fp, "NULL,");
    if (person->mother != NULL)
        fprintf(fp, "%s", person->mother->name);
    else
        fprintf(fp, "NULL");
    if (person->childs != NULL)
    {
        for (int i = 0; i < person->child_count; i++)
        {
            fprintf(fp, ",%s", person->childs[i]->name);
        }
        fprintf(fp, "\n");
    }
    else
        fprintf(fp, ",NULL\n");
}

// this function updates the txt file with the family tree
void update_txt_file(family_node *root, FILE *fp)
{
    family_node *temp;

    // we need to print all persons in family tree

    temp = root;
    fprintf_person(temp, fp);
    if (temp->child_count != 0)
    {
        if (temp->childs[0]->father->name == temp->name) // this means root is a father
        {
            fprintf_person(temp->childs[0]->mother, fp);
        }
        else if (temp->childs[0]->mother->name == temp->name)
        {
            fprintf_person(temp->childs[0]->father, fp);
        }
        for (int i = 0; i < temp->child_count; i++)
        {
            update_txt_file(temp->childs[i], fp);
        }
    }
}

// this function reads a person from a file and returns it
family_node *read_person(FILE *fp, family_node *root, family_node *spouse)
{
    char temp_char;
    char *token;
    int age;
    int child_count;
    char father_name[20];
    char mother_name[20];
    char *child_name;
    char name[20];

    family_node *temp;
    family_node *temp2;

    temp = (family_node *)malloc(sizeof(family_node));
    temp->name = (char *)malloc(sizeof(char) * 20);

    fscanf(fp, " %[^/]/%d/%d,", name, &age, &child_count);
    strcpy(temp->name, name);
    temp->age = age;
    temp->child_count = child_count;
    fscanf(fp, " %[^,],", father_name);

    if (my_strcmp(father_name, "NULL") == 0)
    {
        temp->father = NULL;
    }
    else if (my_strcmp(father_name, root->name) == 0 || my_strcmp(father_name, spouse->name) == 0)
    {
        if (my_strcmp(father_name, root->name) == 0)
            temp->father = root;
        else
            temp->father = spouse;
    }
    fscanf(fp, " %[^,]", mother_name);
    
    if (my_strcmp(mother_name, "NULL") == 0)
    {
        temp->mother = NULL;
    }
    else if (my_strcmp(mother_name, spouse->name) == 0 || my_strcmp(mother_name, root->name) == 0)
    {
        if (my_strcmp(mother_name, root->name) == 0)
            temp->mother = root;
        else
            temp->mother = spouse;
    }
    fscanf(fp, "%c", &temp_char);
    while (temp_char != '\n')
    {
        fscanf(fp, "%c", &temp_char);
    }
    if (child_count != 0)
    {
        
        temp2 = (family_node *)malloc(sizeof(family_node));
        temp2->name = (char *)malloc(sizeof(char) * 20);

        fscanf(fp, " %[^/]/%d/%d,", name, &age, &child_count);
        strcpy(temp2->name, name);
        temp2->age = age;
        temp2->child_count = child_count;

        fscanf(fp, " %[^,],", father_name);
        if (my_strcmp(father_name, "NULL") == 0)
        {
            temp2->father = NULL;
        }
        else if (my_strcmp(father_name, root->name) == 0 || my_strcmp(father_name, spouse->name) == 0)
        {
            if (my_strcmp(father_name, root->name) == 0)
                temp2->father = root;
            else
                temp2->father = spouse;
        }

        fscanf(fp, " %[^,]", mother_name);
        if (my_strcmp(mother_name, "NULL") == 0)
        {
            temp2->mother = NULL;
        }
        else if (my_strcmp(mother_name, spouse->name) == 0 || my_strcmp(mother_name, root->name) == 0)
        {
            if (my_strcmp(mother_name, root->name) == 0)
                temp2->mother = root;
            else
                temp2->mother = spouse;
        }
        fscanf(fp, "%c", &temp_char);
        while (temp_char != '\n')
        {
            fscanf(fp, "%c", &temp_char);
        }
        temp->childs = (family_node **)malloc(sizeof(family_node *) * child_count);
        for (int i = 0; i < child_count; i++)
        {
            temp->childs[i] = read_person(fp, temp, temp2);
        }
    }
    else
    {
        temp->childs = NULL;
    }
    return temp;
}

// this function fills the family tree from a txt file
void fill_from_txt_file(family_node **root, char *filename)
{
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    if (fp == NULL)
    {
        printf("Error while opening file %s\n", filename);
        exit(1);
    }
    *root = read_person(fp, 0, 0);
    fclose(fp);
}

int main()
{
    family_node *root;
    int choice;

    choice = 0;
    while (choice < 4)
    {
        printf("\n***********************\n");
        printf("Family Tree System Menu\n");
        printf("1- Add Family Tree\n");
        printf("2- Remove Family Tree\n");
        printf("3- Load Family Tree\n");
        printf("4- Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                int choice2;

                choice2 = 0;
                while (choice2 < 3)
                {
                    printf("\n***********************\n");
                    printf("1- Add Node\n");
                    printf("2- Save Family Tree\n");
                    printf("3- Exit\n");
                    printf("> ");
                    scanf("%d", &choice2);

                    switch (choice2)
                    {
                        case 1:
                            char name[20];
                            int age;
                            int gender;
                            char mother_name[20];
                            char father_name[20];

                            printf("Enter the name of the Person: ");
                            scanf("%s", name);
                            printf("Enter the age of the Person: ");
                            scanf("%d", &age);
                            printf("What is the gender (0 for male and 1 for female): ");
                            scanf("%d", &gender);
                            if(root != NULL) // if root is not null then we need to ask for mother and father
                            {
                                printf("Enter the name of the Mother: ");
                                scanf("%s", mother_name);
                                printf("Enter the name of the Father: ");
                                scanf("%s", father_name);
                            }
                            else // if root is null then we need to set mother and father to null
                            {
                                my_strcpy(mother_name, "NULL");
                                my_strcpy(father_name, "NULL");
                            }
                            if(root == NULL)    // if root is null then we need to create a new person
                            {
                                root = create_person(name, age);
                            }
                            else   // if root is not null then we need to find mother and father and add the person as a child
                            {
                                family_node *mother = find_person(root, mother_name);
                                family_node *father = find_person(root, father_name);
                                if(mother == NULL && father == NULL)    // if both mother and father are null we cant place the child
                                {
                                    printf("Mother or Father not found\n");
                                    break;
                                }
                                if(mother == NULL) // if mother is null then we need to create a new person and add the child as a child
                                {
                                    mother = create_person(mother_name, age+25);
                                    add_children(father, create_person(name, age), 0);
                                    add_mother_and_father(father->childs[father->child_count - 1], mother, father);                                    
                                }
                                else if(father == NULL) // if father is null then we need to create a new person and add the child as a child
                                {
                                    father = create_person(father_name, age+25);
                                    add_children(mother, create_person(name, age), 1);
                                    add_mother_and_father(mother->childs[mother->child_count - 1], mother, father);
                                }
                                else // if both mother and father are not null we dont need to create them
                                {
                                    add_children(father, create_person(name, age), 0);
                                    add_mother_and_father(father->childs[father->child_count - 1], mother, father);
                                }
                            }
                            printf("Node added successfully\n");
                            break;
                        case 2:
                            printf("Enter the name of the file: ");
                            char filename[20];
                            scanf("%s", filename);
                            FILE *fp = fopen(filename, "w");
                            if (fp == NULL)
                            {
                                printf("Error while opening file %s\n", filename);
                                exit(1);
                            }
                            update_txt_file(root, fp); // we need to update the txt file with the family tree
                            fclose(fp);
                            printf("Family Tree saved successfully\n");
                            break;
                        case 3:
                            printf("Terminating...\n");
                            break;
                    }
                }
                break;
            case 2:
                printf("Enter the name of the txt file you want to delete: ");
                char filename1[20];
                scanf("%s", filename1);
                remove(filename1); // remove function deletes the file from the directory
                printf("Family Tree deleted successfully\n");
                break;
            case 3:
                char filename2[20];
                printf("Listing family trees: \n");
                system("ls *.txt\n"); // system functions are used to perform shell commands in c program. ls command lists files and folders in a directory, *.txt means it will only list files with .txt extension
                printf("Enter the name of the txt file you want to load: ");
                scanf("%s", filename2);
                printf("%s has been selected\n", filename2);
                fill_from_txt_file(&root, filename2); // we need to fill the family tree from the txt file
                
                int choice3;

                choice3 = 0;
                while (choice3 < 5)
                {
                    printf("\n***********************\n");
                    printf("1- Add New Person\n");
                    printf("2- Remove a Person\n");
                    printf("3- Print a persons nuclear family\n");
                    printf("4- Search relatives\n");
                    printf("5- Exit\n");
                    printf("> ");
                    scanf("%d", &choice3);

                    switch(choice3)
                    {
                        case 1: // this part looks like the same as the part in add_family_tree part
                            char name[20];
                            char mother_name[20];
                            char father_name[20];
                            int age;

                            printf("Enter the name of the Person: ");
                            scanf("%s", name);
                            printf("Enter the age of the Person: ");
                            scanf("%d", &age);
                            printf("Enter mother's name: ");
                            scanf("%s", mother_name);
                            printf("Enter father's name: ");
                            scanf("%s", father_name);
                            
                            family_node *mother = find_person(root, mother_name);
                            family_node *father = find_person(root, father_name);
                            if(mother == NULL && father == NULL)
                            {
                                printf("Mother or Father not found\n");
                                break;
                            }
                            if(mother == NULL)
                            {
                                mother = create_person(mother_name, age+25);
                                add_children(father, create_person(name, age), 0);
                                add_mother_and_father(father->childs[father->child_count - 1], mother, father);                                    
                            }
                            else if(father == NULL)
                            {
                                father = create_person(father_name, age+25);
                                add_children(mother, create_person(name, age), 1);
                                add_mother_and_father(mother->childs[mother->child_count - 1], mother, father);
                            }
                            else
                            {
                                add_children(father, create_person(name, age), 0);
                                add_mother_and_father(father->childs[father->child_count - 1], mother, father);
                            }
                            printf("Person added successfully\n");

                            FILE *fp = fopen(filename2, "w");
                            update_txt_file(root, fp);
                            fclose(fp);
                            break;
                        case 2:
                            char name1[20];

                            printf("Enter the name of the person you want to delete: ");
                            scanf("%s", name1);
                            root = delete_person(root, name1);
                            printf("Person removed successfully\n");
                            
                            FILE *fp2 = fopen(filename2, "w");
                            update_txt_file(root, fp2); // we need to update the txt file with the family tree
                            fclose(fp2);
                            break;
                        case 3: // nuclear family of a person is the person's mother, father and childrens
                            char name2[20];

                            printf("Enter the name of the person you want to print nuclear family of: "); 
                            scanf("%s", name2);
                            family_node *person = find_person(root, name2);
                            if(person == NULL)
                            {
                                printf("Person not found\n");
                                break;
                            }
                            printf("Nuclear family of %s: \n", person->name);

                            if(person->mother != NULL)
                                printf("Mother: %s\n", person->mother->name);
                            else
                                printf("No Mother\n");
                            if(person->father != NULL)
                                printf("Father: %s\n", person->father->name);
                            else
                                printf("No Father\n");
                            if(person->child_count != 0)
                            {
                                printf("Children: ");
                                for(int i = 0; i < person->child_count; i++)
                                {
                                    if(i == person->child_count - 1)
                                        printf("%s\n", person->childs[i]->name);
                                    else
                                        printf("%s, ", person->childs[i]->name);
                                }
                            }
                            else
                            {
                                printf("No children\n");
                            }
                            break;
                        case 4:
                            char name3[20];
                            int choice4;
                            printf("Enter the name of the person you want to search relatives of: ");
                            scanf("%s", name3);
                            family_node *person2 = find_person(root, name3); // first we need to find the person
                            if(person2 == NULL)
                            {
                                printf("Person not found\n");
                                break;
                            }

                            printf("Select the relative you want to search for: \n");
                            printf("1- Parents\n");
                            printf("2- Spouse\n");
                            printf("3- Children\n");
                            printf("4- Grandparents\n");
                            printf("5- Cousins\n");
                            scanf("%d", &choice4);

                            switch(choice4)
                            {
                                case 1: // parents
                                    printf("Printing parents of %s: \n", person2->name);
                                    if(person2->mother != NULL)
                                        printf("Mother: %s\n", person2->mother->name);
                                    else
                                        printf("No Mother\n");
                                    if(person2->father != NULL)
                                        printf("Father: %s\n", person2->father->name);
                                    else
                                        printf("No Father\n");
                                    break;
                                case 2: // spouse, we can find spouse by mother or father of a child of them
                                    printf("Printing spouse of %s: \n", person2->name);
                                    if(person2->child_count != 0)
                                    {
                                        if(my_strcmp(person2->childs[0]->father->name, person2->name) == 0)
                                            printf("Spouse: %s\n", person2->childs[0]->mother->name);
                                        else
                                            printf("Spouse: %s\n", person2->childs[0]->father->name);
                                    }
                                    else
                                        printf("No spouse\n");
                                    break;
                                case 3: // children
                                    printf("Printing children of %s: \n", person2->name);
                                    if(person2->child_count != 0)
                                    {
                                        printf("Children: ");
                                        for(int i = 0; i < person2->child_count; i++)
                                        {
                                            if(i == person2->child_count - 1)
                                                printf("%s\n", person2->childs[i]->name);
                                            else
                                                printf("%s, ", person2->childs[i]->name);
                                        }
                                    }
                                    else
                                    {
                                        printf("No children\n");
                                    }
                                    break;
                                case 4: // grandparents, we can find grandparents by parents of mother or father of a person
                                    printf("Printing grandparents of %s: \n", person2->name);
                                    if(person2->mother != NULL)
                                    {
                                        if(person2->mother->mother != NULL)
                                            printf("Grandmother: %s\n", person2->mother->mother->name);
                                        else
                                            printf("No Grandmother from mothers side\n");
                                        if(person2->mother->father != NULL)
                                            printf("Grandfather: %s\n", person2->mother->father->name);
                                        else
                                            printf("No Grandfather from mothers side\n");
                                    }
                                    else
                                    {
                                        printf("No Grandparents from mothers side\n");
                                    }
                                    if(person2->father != NULL)
                                    {
                                        if(person2->father->mother != NULL)
                                            printf("Grandmother: %s\n", person2->father->mother->name);
                                        else
                                            printf("No Grandmother from fathers side\n");
                                        if(person2->father->father != NULL)
                                            printf("Grandfather: %s\n", person2->father->father->name);
                                        else
                                            printf("No Grandfather from fathers side\n");
                                    }
                                    else
                                    {
                                        printf("No Grandparents from fathers side\n");
                                    }
                                    break;
                                case 5:// cousins, we can find cousins by childs of childs of grandparents
                                    printf("Printing cousins of %s: \n", person2->name);
                                    if(person2->mother != NULL)
                                    {
                                        if(person2->mother->father != NULL)
                                        {
                                            if(person2->mother->father->child_count != 1)
                                            {
                                                printf("Cousins from mothers side: ");
                                                for(int i = 0; i < person2->mother->father->child_count; i++)
                                                {
                                                    if(my_strcmp(person2->mother->father->childs[i]->name, person2->mother->name) != 0) // persons mothers childs cant be a cousin
                                                    {
                                                        for(int j = 0; j < person2->mother->father->childs[i]->child_count; j++)
                                                        {
                                                            if(j == person2->mother->father->childs[i]->child_count - 1)
                                                                printf("%s\n", person2->mother->father->childs[i]->childs[j]->name);
                                                            else
                                                                printf("%s, ", person2->mother->father->childs[i]->childs[j]->name);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                                printf("No Cousins from mothers side\n");
                                        }
                                        else
                                            printf("No Cousins from mothers side\n");
                                    }
                                    else
                                    {
                                        printf("No Cousins from mothers side\n");
                                    }
                                    if(person2->father != NULL)
                                    {
                                        if(person2->father->father != NULL)
                                        {
                                            if(person2->father->father->child_count != 1)
                                            {
                                                printf("Cousins from fathers side: ");
                                                for(int i = 0; i < person2->father->father->child_count; i++)
                                                {
                                                    if(my_strcmp(person2->father->father->childs[i]->name, person2->father->name) != 0) // persons fathers childs cant be a cousin
                                                    {
                                                        for(int j = 0; j < person2->father->father->childs[i]->child_count; j++)
                                                        {
                                                            if(j == person2->father->father->childs[i]->child_count - 1)
                                                                printf("%s\n", person2->father->father->childs[i]->childs[j]->name);
                                                            else
                                                                printf("%s, ", person2->father->father->childs[i]->childs[j]->name);
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                                printf("No Cousins from fathers side\n");
                                        }
                                        else
                                            printf("No Cousins from fathers side\n");
                                    }
                                    else
                                    {
                                        printf("No Cousins from fathers side\n");
                                    }
                                    break;
                            }
                    }
                }
                
                break;
            case 4:
                printf("Terminating...\n");
                break;
        }
    }
}