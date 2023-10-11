#include "utils.h"

int query_with_id(int s_nbr, int id)
{
    int result = 0;

    FILE *stock = fopen("stocks.txt","r+");
    char my_char;
    my_char = fgetc(stock);
    while (my_char != '\0' && my_char != '\n')
    {
        my_char = fgetc(stock);
    }
    for (int i=1; s_nbr>=i ; i++)
    {
        int pID,sID,curr_stock;
        char branch[16];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&curr_stock);
        if (pID == id)
        {
            result += curr_stock;
        }
    }
    fclose(stock);
    return result;
}

void create_list(int p_nbr, int s_nbr, char brand_name[])
{
    FILE *product = fopen("products.txt", "r+");
    FILE *stock = fopen("stocks.txt", "r+");
    float list[p_nbr][3];
    char my_char;
    int list_index = 0;

    my_char = fgetc(product);
    while (my_char != '\0'  && my_char != '\n')
    {
        my_char = fgetc(product);
    }
    for (int i=1; i <= s_nbr ; i++)
    {
        int pID;
        char type,name[16],brand[16];
        double price;
        fscanf(product,"%d,%c,%[^,],%[^,],%lf\n", &pID, &type, name, brand, &price);
        if (my_strcmp(brand_name, brand))
        {
            int total_stock = query_with_id(s_nbr, pID);
            if (list_index == 1)
            {
                printf("Total Stock: %d\n", total_stock);
            }
            
            list[list_index][0] = pID;
            list[list_index][1] = price;
            list[list_index][2] = total_stock;
            list_index++;
        }
    }
    fclose(product);
    fclose(stock);

    printf("\npID - Price - Total Stock\n");
    for (int i=0 ; list_index>i ; i++)
    {
        printf("%.0lf,%.2lf,%.0lf\n",list[i][0],list[i][1],list[i][2]);
    }
    printf("\n");
}

void brand_stock(int *p_nbr, int *s_nbr, char brand_name[16])
{
    create_list(*p_nbr, *s_nbr, brand_name);   
}