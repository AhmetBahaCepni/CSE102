#include "utils.h"

int my_strcmp(const char str1[], const char str2[])
{
    int i;

    i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
        i++;
    }
    if ((str1[i] != str2[i]) && (str1[i] == '\0' || str2[i] == '\0'))
    {
        return 0;
    }
    return 1;
}

void query_with_id_and_branch(int s_nbr, int id,char branch_inp[])
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
        printf("%d,%d,%s,%d\n",sID,pID,branch,curr_stock);
        if (pID == id && my_strcmp(branch_inp,branch))
        {
            result += curr_stock;
        }
    }
    fclose(stock);
    printf("Total stock of the product is %d\n", result);
}


void list_with_branch(int s_nbr, char branch_inp[16])
{
    FILE *stock = fopen("stocks.txt","r+");
    char my_char;
    my_char = fgetc(stock);
    while (my_char != '\0'  && my_char != '\n')
    {
        my_char = fgetc(stock);
    }
    printf("sID,pID,Branch,Stock\n");
    for (int i=1; i <= s_nbr ; i++)
    {
        int pID,sID,curr_stock;
        char branch[16];
        fscanf(stock,"%d,%d,%[^,],%d\n", &sID, &pID, branch, &curr_stock);
        if (my_strcmp(branch_inp,branch))
        {
            printf("%d,%d,%s,%d\n",sID,pID,branch,curr_stock);
        }
    }
    fclose(stock);
}

void list_no_stock_branch(int s_nbr, char branch_inp[])
{
    FILE *stock = fopen("stocks.txt","r+");
    char my_char;
    my_char = fgetc(stock);
    while (my_char != '\0'  && my_char != '\n')
    {
        my_char = fgetc(stock);
    }
    printf("sID,pID,Branch,Stock\n");
    for (int i=1; s_nbr>=i ; i++)
    {
        int pID,sID,curr_stock;
        char branch[16];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sID,&pID,branch,&curr_stock);
        if (curr_stock == 0 && my_strcmp(branch_inp,branch))
        {
            printf("%d,%d,%s,%d\n",sID,pID,branch,curr_stock);
        }
    }
    fclose(stock);
}

void stock_status(int *p_nbr, int *s_nbr)
{
    int n = 1;
    int pid;
    int sid;

    while (n < 4)
    {
        printf("\nOption 1: query stock with product id and branch name.\n");
        printf("Option 2: list the stocks of all product in a specified branch\n");
        printf("Option 3: list the out-of-stock products in a specified branch.\n");
        printf("Option 4: Back to main menu.\n");
        printf("Choose an operation: ");
        scanf("%d", &n);

        switch(n)// i used switch case to make a chocice
        {
            case 1:
                char branch_inp1[16];
                int pID;
                printf("Please enter product id and branch name in order: ");
                scanf("%d %s", &pID, branch_inp1);
                query_with_id_and_branch(*s_nbr, pID, branch_inp1);
                break;
            case 2:
                char branch_inp2[16];
                printf("Please enter the branch name for the list: ");
                scanf("%s", branch_inp2);
                list_with_branch(*s_nbr, branch_inp2);
                break;
            case 3:
                char branch_inp3[16];
                printf("Please enter the branch name for the list: ");
                scanf("%s", branch_inp3);
                list_no_stock_branch(*s_nbr, branch_inp3);
                break;
        }
    }
}