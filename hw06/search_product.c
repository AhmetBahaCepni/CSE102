#include "utils.h"

void    list_products()
{
    FILE *src;
    char my_char;
    src = fopen("products.txt", "r+");

    printf("\n");
    my_char = fgetc(src);
    while (my_char != EOF)
    {
        printf("%c", my_char);
        my_char = fgetc(src);
    }
    printf("\n");
    fclose(src);
}

int find_feature_place(char feature[])
{
    FILE *fp = fopen("filtered.txt", "r+");
    char cursor = fgetc(fp);
    int i = 0;
    int cnt = 0;
    int comma = 0;

    while (cursor != '\n' && cursor != EOF)
    {
        i = 0;
        if (cursor == ',')
            comma++;
        while (cursor == feature[i])
        {
            cursor = fgetc(fp);
            i++;
        }
        if (feature[i] == '\0' && (cursor == ',' || cursor == '\n'))
        {
            fclose(fp);
            return (comma);
        }
        cursor = fgetc(fp);
    }
    fclose(fp);
    return (0);
}

void store_and_print_file(int p_nbr)
{
    FILE *filt = fopen("filtered.txt", "r+");
    char arr[p_nbr][50];
    char my_char;
    int filt_line = 0;
    int i;
    my_char = fgetc(filt);
    while (my_char != '\n')
    {
        my_char = fgetc(filt);
    }
    my_char = fgetc(filt);
    while (my_char != EOF)
    {
        i = 0;
        while (my_char != '\n' && my_char != EOF)
        {
            arr[filt_line][i] = my_char;
            my_char = fgetc(filt);
            i++;   
        }
        if (my_char != EOF)
        {
            my_char = fgetc(filt);
        }
        
        arr[filt_line][i] = '\0';    
        filt_line++;
    }

    int j = 0;
    printf("\nFiltered products are: \n");
    while (j < filt_line)
    {
        printf("%s\n", arr[j]);
        j++;
    }
    fclose(filt);
}

int filter_for_feature(int p_nbr, char feature_name[20], char feature_value[20],double min, double max)
{
    int n, i;
    int pID_deleted[p_nbr];
    int j = 0;
    int feature_place = 0;
    int comma = 0;
    double price;
    FILE *src = fopen("products.txt", "r+");

    char my_char = fgetc(src);

    feature_place = find_feature_place(feature_name);
    while (my_char != '\n')
        my_char = fgetc(src);
    while (my_char != EOF)
    {
        comma = 0;
        fscanf(src, "%d", &n);
        if (comma == ',')
            comma++;
        while (comma < feature_place)
        {
            my_char = fgetc(src);
            if (my_char == ',')
                comma++;
        }
        if (comma == 4)
        {
            fscanf(src, "%lf", &price);
            if (price < min || price > max)
            {
                pID_deleted[j] = n;
                j++;
            }
        }
        else
        {
            my_char = fgetc(src);
            i = 0;
            while (my_char != ',' && my_char != '\n' && my_char != '\0')
            {
                if (my_char == feature_value[i])
                {
                    i++;
                }
                my_char = fgetc(src);
            }
            if (feature_value[i] != '\0')
            {
                pID_deleted[j] = n;
                j++;
            }
        }
        while (my_char != '\n' && my_char != EOF)
                my_char = fgetc(src);
    }
    fclose(src);
    while (j-1 >= 0)
    {
        delete_product(pID_deleted[j-1], p_nbr, "filtered.txt", "cpy2.txt");
        j--;
    }
}
void filter_product(int p_nbr)//
{
    char filter[100];
    double min, max;

    printf("Please enter feature names you want to filter.(seperate them by coma (pID,name,type etc))\n");
    scanf("%s", filter);
    int i;

    copy_to_file("products.txt", "filtered.txt");
    int indx = 0;
    while (filter[indx] != '\0')
    {
        if (filter[indx] == ',') indx++;
        char feature_name[20];
        char feature_value[20];

        i=0;
        while(filter[indx] != ',' && filter[indx] != '\0')
        {
            feature_name[i] = filter[indx];
            indx++;
            i++;
        }
        feature_name[i] = '\0';
        if (my_strcmp(feature_name,"Price") == 1)
        {
            printf("Please enter the min and max price: ");
            scanf("%lf %lf",&min, &max);
        }
        indx++;
        i = 0;
        while(filter[indx] != ',' && filter[indx] != '\0')
        {
            feature_value[i] = filter[indx];
            indx++;
            i++;
        }
        feature_value[i] = '\0';
        filter_for_feature(p_nbr, feature_name, feature_value, min, max);
    }
    store_and_print_file(p_nbr);
}

void search_product(int *p_nbr, int *s_nbr)
{
    int n = 1;
    int pid;
    int sid;

    while (n < 3)
    {
        printf("\n1) List all products\n");
        printf("2) Filter products by feature\n");
        printf("3) Back to main menu\n");
        printf("Choose an operation: ");
        scanf("%d", &n);

        switch(n)// i used switch case to make a chocice
        {
            case 1:
                list_products();
                break;
            case 2:
                filter_product(*p_nbr);
                break;
        }
    }
}