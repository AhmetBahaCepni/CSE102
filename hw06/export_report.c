#include "utils.h"

void    my_query_stock(int pid,int s_nbr , int *min, int *max, int *median)
{
    int sid, n, indx = 0;
    int list[s_nbr];
    int i = 0, j = 0;
    char cursor;
    int current_stock;
    FILE *stock = fopen("stocks.txt","r+");

    cursor = fgetc(stock);
    while (cursor != '\n')
        cursor = fgetc(stock);
    while (i < s_nbr)
    {
        char str[20];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sid,&n,str,&current_stock);
        if (pid == n)
        {
            list[indx] = current_stock;
            indx++;
        }
        i++;
    }
    fclose(stock);
    i = 0;
    int tmp = 0;
    if (indx == 0)
    {
        *min = 0;
        *max = 0;
        *median = 0;
    }
    else
    {
        while (i < indx-1)
        {
            j = i + 1;
            while (j < indx)
            {
                if (list[j] < list[i])
                {
                    tmp = list[j];
                    list[j] = list[i];
                    list[i] = tmp;
                }
                j++;
            }
            i++;
        }
        *min = list[0];
        *max = list[indx - 1];
        *median = list[(indx/2)];
    }
}

void export_report(int p_nbr, int s_nbr ,char brand[16])
{
    int min,max,median;
    FILE *product = fopen("products.txt","r");
    FILE *report = fopen("report.txt","w+");
    fprintf(report,"pID - Min Stock - Max Stock - Median Stock\n");
    char c;
    while ((c = fgetc(product)) &&  c != '\n' && c != EOF); //
    for (int i = 0; i < p_nbr; i++)
    {
        int pID;
        char type;
        char name[20];
        double price;
        char tmp_brand[16];
        fscanf(product,"%d,%c,%[^,],%[^,],%lf",&pID, &type, name, tmp_brand, &price);
        if (my_strcmp(tmp_brand,brand) == 1)
        {
            my_query_stock(pID , s_nbr, &min, &max, &median); // this function find imin,median,max stock of the given brand and print it to the report.txt check function for detailed explanation.
            fprintf(report,"%d,%d,%d,%d\n",pID,min,max,median);
        }
        while ((c = fgetc(product)) &&  c != '\n' && c != EOF); //
    }
    fclose(product);
    fclose(report);

    report = fopen("report.txt","r");
    c = fgetc(report);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(report);
    }
    fclose(report);
}