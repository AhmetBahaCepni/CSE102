#include "utils.h"

int read_lines(char src_path[]) // this funciton goes to a file and count for lines
{
    FILE *src = fopen(src_path, "r+");
    int line = 0;
    char my_char;

    my_char = fgetc(src);
    while (my_char != EOF)
    {
        if (my_char == '\n')
        {
            line++;
        }
        my_char = fgetc(src);
    }

    fclose(src);
    return line;
}

void menu()
{
    int n = 1;
    int p_nbr = read_lines("products.txt");
    int s_nbr = read_lines("stocks.txt");
    while (n < 5)
    {
        printf("Welcome operator, please select an option to continue: \n\n");
        printf("1- File operations\n");
        printf("2- Query products\n");
        printf("3- Check stock status\n");
        printf("4- Stock control by brand\n");
        printf("5- Export report\n");
        printf("6- Exit operator\n");
        scanf("%d", &n);
        
        switch (n) // i used switch case to make a chocice
        {
            case 1:
                file_ops(&p_nbr, &s_nbr);
                break;
            case 2:
                search_product(&p_nbr, &s_nbr);
                break;
            case 3:
                stock_status(&p_nbr, &s_nbr);
                break;
            case 4:
                char brand_name[16];
                printf("Please enter the brand name for the list: ");
                scanf("%s", brand_name);
                brand_stock(&p_nbr, &s_nbr, brand_name);
                break;
            case 5:
                export_report(p_nbr, s_nbr, brand_name);
                break;
        }
    }
}

int main()
{
    menu();
    return (0);
}