#include "utils.h"

void copy_to_file(char cpy_path[], char src_path[])
{
    FILE *cpy = fopen(src_path, "w+");
    FILE *src = fopen(cpy_path, "r+");
    char cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(cpy);
}

void copy_to_stocks()
{
    FILE *cpy = fopen("stocks.txt", "w+");
    FILE *src = fopen("cpy.txt", "r+");
    char cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(cpy);
}

int delete_product(int pid, int p_nbr, char file[], char cpy_fl[])
{
    FILE *src = fopen(file, "r+");
    FILE *cpy = fopen(cpy_fl, "w+");
    int n;
    char cursor;
    int flag = 0;

    cursor = fgetc(src);
    //skipping first line of file
    while (cursor != '\n')
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    if (p_nbr > 1)
        fprintf(cpy, "\n");
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        //if this line does not contains given product, just copy to copy.txt
        if (pid != n)
        {
            if (flag == 1 && file[0] == 'p')
                n--;
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n' && n + 1 != p_nbr)
                fprintf(cpy, "\n");
        }
        //else it does contains given product, just skip to the next line
        else
        {
            flag = 1;
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
                cursor = fgetc(src);
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_file(cpy_fl, file);
    return (1);
}

int add_product(int p_nbr) // this is the function that user adds product to file
{
    FILE *fp = fopen("products.txt", "r+");
    char type;
    char name[9];
    char brand[6];
    double price;

    // we input values one by one
    printf("Please enter type of the product: ");
    scanf(" %c", &type);
    printf("Please enter name of the product: ");
    scanf("%s", name);
    printf("Please enter brand of the product: ");
    scanf("%s", brand);
    printf("Please enter price of the product: ");
    scanf("%lf", &price);

    if (p_nbr == 0)
    {
        fprintf(fp, "%s", "pID,Type,Name,Brand,Price");
    }
    while (fgetc(fp) != EOF); // we go to the end of the line
    fprintf(fp, "\n%d,%c,%s,%s,%.2lf", p_nbr+1, type, name, brand, price);
    fclose(fp);
    return (1);
}

// this function determines the order of a feature for example "name" featrue is third one
int find_feature(char str[], char path[]) 
{
    FILE *fp = fopen(path, "r+");
    char cursor;
    int i;

    cursor = fgetc(fp);
    while (cursor != '\n' && cursor != EOF) // we look until EOF
    {
        while (cursor == str[i])// we check for the char that we read is compatible with the real feature
        {
            cursor = fgetc(fp);
            i++;
        }
        if (str[i] == '\0' && (cursor == ',' || cursor == '\n') ) // if str[i] == '\0' we understand that strigns are same
            return (1);
        cursor = fgetc(fp);
    }
    fclose(fp);
}

// this function used for updating a product that is already on file
int update_product(int p_nbr)
{
    int pid;
    char new_f[9];
    char updated_text[9];
    char cursor;
    int n;
    int cnt = 0;
    int comma = 0;
    int feature_place;

    FILE *src = fopen("products.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");

    //  We input one by one
    printf("Which product you want to update: ");
    scanf("%d", &pid);
    printf("Please enter the name of the future that you want to update: ");
    scanf("%s", new_f);
    printf("Please enter the name that you want to update as: ");
    scanf("%s", updated_text);
    
    // you cant change pid feature!!!!
    if (new_f[0] == 'p' && new_f[1] == 'I' && new_f[2] == 'D')
    {
        printf("pID can not be updated\n");
        return (0);
    }
    cursor = fgetc(src);
    while (cursor != '\n')// in here we find feature's place on order of the features
    {
        if (cursor == ',')
            cnt++;
        if (cursor == new_f[0] && find_feature(new_f, "products.txt") == 1)
            feature_place = cnt;
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fprintf(cpy, "\n");
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        if (pid != n) // we pass these ones beacues we want to change pid == n
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n')
                fprintf(cpy, "\n");
        }
        else // in here we found the line
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                if (comma != feature_place) // this mean this is not the future we want the change
                {
                    fprintf(cpy, "%c", cursor);
                    if (cursor == ',')
                        comma++;
                    cursor = fgetc(src);
                }
                else if (comma == feature_place)// this mean this is the future we want the change
                {
                    fprintf(cpy, "%s", updated_text); // we print the text instead of the one already there
                    cursor = fgetc(src);
                    while (cursor != ',' && cursor != EOF && cursor != '\n')
                    {
                        cursor = fgetc(src);
                    }
                    comma++;
                }
                if (cursor == '\n')
                    fprintf(cpy, "\n");
            }
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_file("cpy.txt", "products.txt");
}

// this is the function we add new features
int add_feature(int p_nbr)
{
    FILE *src = fopen("products.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");
    char cursor;
    char feature[9];
    int comma = 0;
    int cnt = 0;
    int flag = 0;
    printf("Enter the name of the new feature: ");
    scanf("%s", feature);
    
    cursor = fgetc(src);
    while (cursor != EOF)// in here we look until EOF and change the all file from the ends
    {
        while (cursor != '\n' && cursor != EOF)
        {
            fprintf(cpy, "%c", cursor);
            cursor = fgetc(src);
        }
        if (cursor == '\n')
            flag = 1;
        else if (cursor == EOF)
            flag = 2;
        if (cnt == 0)
            fprintf(cpy, ",%s", feature); // we add feature to first line
        else
            fprintf(cpy, ",%c", '0'); // we add 0 to all lines for new feature
        if (flag == 1)
        {
            fprintf(cpy, "\n");
            cursor = fgetc(src);
        }
        cnt++;
    }
    fclose(src);
    fclose(cpy);
    copy_to_file("cpy.txt", "products.txt");
}

int maxID(FILE *fl)
{
    int result = 0;
    char c;
    while ((c = fgetc(fl)))
    {
        if (c == EOF)
            break;
        if (c == '\n')
            result++;
    }
    return result;
}

int add_stock(int p_nbr) // this funciton adds new stocks to the file
{
    int sid;
    int pid;
    int current_stock;
    char branch[16];
    FILE *fp = fopen("stocks.txt", "r+");
    int s_nbr = maxID(fp);
    printf("Enter pID: ");
    scanf("%d", &pid);
    while (pid <= 0 || pid > p_nbr) // invalid pids
    {
        printf("Invalid pid\nEnter pID again: ");
        scanf("%d", &pid);
    }
    //we input one by one
    printf("Enter product's branch: ");
    scanf("%s", branch);
    printf("Enter product's current stock: ");
    scanf("%d", &current_stock);
    if (s_nbr == 0)
        fprintf(fp, "sID,pID,Branch,Current_stock");
    fprintf(fp, "\n%d,%d,%s,%d", s_nbr+1, pid, branch, current_stock);
    fclose(fp);
}

//this is the funciton used for delete teh stock
int delete_stock(int sid, int s_nbr)
{
    FILE *src = fopen("stocks.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");
    int n;
    char cursor;
    int flag = 0;

    cursor = fgetc(src);
    while (cursor != '\n')
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    if (s_nbr > 1)
    {
        fprintf(cpy, "\n");
    }
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        if (sid
     != n) // this is not the one we look for
        {
            if (flag == 1)
                n--;
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n' && n + 1 != s_nbr)
                fprintf(cpy, "\n");
        }
        else // this is the situation we look for
        {
            flag = 1;
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
                cursor = fgetc(src);
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_file("cpy.txt", "stocks.txt");
    return (1);
}

// this is the funciton we update stocks
int update_stock(int s_nbr)
{
    int sid;
    char new_f[16];
    char updated_text[16];
    char cursor;
    int n;
    int cnt = 0;
    int comma = 0;
    int feature_place;

    FILE *src = fopen("stocks.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");

    // we input one by one
    printf("Which product you want to update: ");
    scanf("%d", &sid);
    printf("Please enter the name of the future that you want to update: ");
    scanf("%s", new_f);
    printf("Please enter the value that you want to update as: ");
    scanf("%s", updated_text);
    
    if (new_f[0] == 's' && new_f[1] == 'I' && new_f[2] == 'D')
    {
        printf("sid can not be updated\n");
        return (0);
    }
    cursor = fgetc(src);
    while (cursor != '\n')
    {
        if (cursor == ',')
            cnt++;
        if (cursor == new_f[0] && find_feature(new_f, "stocks.txt") == 1)
            feature_place = cnt;            
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fprintf(cpy, "\n");
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        if (sid != n) // this is not the match
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n')
                fprintf(cpy, "\n");
        }
        else // in here ww will make the update
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                if (comma != feature_place)
                {
                    fprintf(cpy, "%c", cursor);
                    if (cursor == ',')
                        comma++;
                    cursor = fgetc(src);
                }
                else if (comma == feature_place)
                {
                    fprintf(cpy, "%s", updated_text);
                    cursor = fgetc(src);
                    while (cursor != ',' && cursor != EOF && cursor != '\n')
                    {
                        cursor = fgetc(src);
                    }
                    comma++;
                }
                if (cursor == '\n')
                    fprintf(cpy, "\n");
            }
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_file("cpy.txt", "stocks.txt");

}

void file_ops(int *p_nbr, int *s_nbr)
{
    int n = 1;
    int pid;
    int sid;

    while (n < 8)
    {
        printf("\n1) Add product\n");
        printf("2) Delete product\n");
        printf("3) Update product\n");
        printf("4) Add Feature\n");
        printf("5) Add Stock\n");
        printf("6) Delete Stock\n");
        printf("7) Update Stock\n");
        printf("8) Back to the main menu\n");
        printf("Choose an operation: ");
        scanf("%d", &n);

        switch(n)// i used switch case to make a chocice
        {
            case 1:
                add_product(*p_nbr);
                *p_nbr = *p_nbr + 1;
                break;
            case 2:
                printf("Enter the pID that you want to delete: ");
                scanf("%d", &pid);
                if (*p_nbr == 0 || pid > *p_nbr)
                {
                    printf("invalid pid");
                    return;
                }
                delete_product(pid, *p_nbr, "products.txt", "cpy.txt");
                *p_nbr = *p_nbr - 1;
                break;
            case 3:
                update_product(*p_nbr);
                break;
            case 4:
                add_feature(*p_nbr);
                break;
            case 5:
                add_stock(*p_nbr);
                *s_nbr = *s_nbr + 1;
                break;
            case 6:
                printf("Enter the sID that you want to delete: ");
                scanf("%d", &sid);
                if (*s_nbr == 0 || sid > *s_nbr)
                {
                    printf("invalid pid");
                    return;
                }
                delete_stock(sid, *s_nbr);
                *s_nbr = *s_nbr - 1;
                break;
            case 7:
                update_stock(*s_nbr);
                break;
        }
    }
}