#include "utils.h"

void fillLinkedList(Node **head) // this function fills the linked list with random data
{
    srand(time(NULL)); //randomize the random function
    int i, j, k, l, m, n, o;
    int random = rand() % 11 + 10; // random number between 10 and 20
    Node *temp = *head;
    for (i = 0; i < random; i++)
    {
        int random2 = rand() % 4; // random number between 0 and 3 for asset type
        if (random2 == 0) // if random2 is 0 then we should create asset1
        {
            Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1));
            strcpy(asset1->type, "Asset1"); // copy asset type to asset1->type
            for (j = 0; j < 1; j++)
            {
                asset1->ivals[j] = rand() % 100; // fill asset1->ivals with random numbers between 0 and 99
            }
            for (k = 0; k < 1; k++)
            {
                asset1->svals[k] = (double)rand() / (double)(RAND_MAX / 100); // fill asset1->svals with random double nums between 0 and 99
            }
            if (temp == NULL) // if temp is null there are no list
            {
                temp = (Node *)malloc(sizeof(Node));
                temp->data = asset1;
                temp->next = NULL;
                *head = temp;
            }
            else // if temp is not null then we should go to the end of the linked list and create a new node and assign it
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = (Node *)malloc(sizeof(Node));
                temp->next->data = asset1;
                temp->next->next = NULL;
            }
        }
        else if (random2 == 1) // if random2 is 1 then we should create asset2
        {
            Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));
            strcpy(asset2->type, "Asset2"); // copy asset type to asset2->type
            for (l = 0; l < 2; l++)
            {
                asset2->svals[l] = (double)rand() / (double)(RAND_MAX / 100); // fill asset2->svals with random double nums between 0 and 99
            }
            for (m = 0; m < 2; m++)
            {
                asset2->ivals[m] = rand() % 100; // fill asset2->ivals with random numbers between 0 and 99
            }
            if (temp == NULL) // if temp is null there are no list
            {
                temp = (Node *)malloc(sizeof(Node));
                temp->data = asset2;
                temp->next = NULL;
                *head = temp;
            }
            else // if temp is not null then we should go to the end of the linked list and create a new node and assign it
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = (Node *)malloc(sizeof(Node));
                temp->next->data = asset2;
                temp->next->next = NULL;
            }
        }
        else if (random2 == 2) // if random2 is 2 then we should create asset3
        {
            Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));
            strcpy(asset3->type, "Asset3"); // copy asset type to asset3->type
            for (n = 0; n < 10; n++)
            {
                asset3->string1[n] = rand() % 26 + 97; // fill asset3->string1 with random lowercase letters. (ascii code of lowercase letters are between 97 and 122)
            }
            for (o = 0; o < 10; o++)
            {
                asset3->string2[o] = rand() % 26 + 97; // fill asset3->string2 with random lowercase letters. (ascii code of lowercase letters are between 97 and 122)
            }
            if (temp == NULL) // if temp is null there are no list
            {
                temp = (Node *)malloc(sizeof(Node));
                temp->data = asset3;
                temp->next = NULL;
                *head = temp;
            }
            else // if temp is not null then we should go to the end of the linked list and create a new node and assign it            {
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = (Node *)malloc(sizeof(Node));
                temp->next->data = asset3;
                temp->next->next = NULL;
            }
        }
        else if (random2 == 3) // if random2 is 3 then we should create asset4
        {
            Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));
            strcpy(asset4->type, "Asset4"); // copy asset type to asset4->type
            asset4->value1 = (double)rand() / (double)(RAND_MAX / 100); // fill asset4->value1 with random double nums between 0 and 99
            asset4->value2 = (float)rand() / (float)(RAND_MAX / 100); // fill asset4->value2 with random float nums between 0 and 99
            asset4->value3 = (double)rand() / (double)(RAND_MAX / 100); // fill asset4->value3 with random double nums between 0 and 99
            if (temp == NULL) // if temp is null there are no list
            {
                temp = (Node *)malloc(sizeof(Node));
                temp->data = asset4;
                temp->next = NULL;
                *head = temp;
            }
            else // if temp is not null then we should go to the end of the linked list and create a new node and assign it
            {
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = (Node *)malloc(sizeof(Node));
                temp->next->data = asset4;
                temp->next->next = NULL;
            }
        }
    }
}

void serializeLinkedList(Node *head)
{
    FILE *fp = fopen("linkedlist.bin", "wb");
    Node *temp = head;
    while (temp != NULL)
    {
        // we will write to the file according to the type of the struct
        if (my_strcmp(((Asset1 *)temp->data)->type, "Asset1") == 0) 
        {
            fwrite(temp->data, sizeof(Asset1), 1, fp);
        }
        else if (my_strcmp(((Asset2 *)temp->data)->type, "Asset2") == 0)
        {
            fwrite(temp->data, sizeof(Asset2), 1, fp);
        }
        else if (my_strcmp(((Asset3 *)temp->data)->type, "Asset3") == 0)
        {
            fwrite(temp->data, sizeof(Asset3), 1, fp);
        }
        else if (my_strcmp(((Asset4 *)temp->data)->type, "Asset4") == 0)
        {
            fwrite(temp->data, sizeof(Asset4), 1, fp);
        }
        temp = temp->next;
    }
    printf("Serialization is completed. All assets stored at \"linkedlist.bin\"\n");
    fclose(fp);
}

void cpy_data(void *dest, void *src) // this function copies the data from src to dest
{
    if (my_strcmp(((Asset1 *)src)->type, "Asset1") == 0)
    {
        strcpy(((Asset1 *)dest)->type, ((Asset1 *)src)->type);
        ((Asset1 *)dest)->ivals[0] = ((Asset1 *)src)->ivals[0];
        ((Asset1 *)dest)->svals[0] = ((Asset1 *)src)->svals[0];
    }
    else if (my_strcmp(((Asset2 *)src)->type, "Asset2") == 0)
    {
        strcpy(((Asset2 *)dest)->type, ((Asset2 *)src)->type);
        ((Asset2 *)dest)->svals[0] = ((Asset2 *)src)->svals[0];
        ((Asset2 *)dest)->svals[1] = ((Asset2 *)src)->svals[1];
        ((Asset2 *)dest)->ivals[0] = ((Asset2 *)src)->ivals[0];
        ((Asset2 *)dest)->ivals[1] = ((Asset2 *)src)->ivals[1];
    }
    else if (my_strcmp(((Asset3 *)src)->type, "Asset3") == 0)
    {
        strcpy(((Asset3 *)dest)->type, ((Asset3 *)src)->type);
        strcpy(((Asset3 *)dest)->string1, ((Asset3 *)src)->string1);
        strcpy(((Asset3 *)dest)->string2, ((Asset3 *)src)->string2);
    }
    else if (my_strcmp(((Asset4 *)src)->type, "Asset4") == 0)
    {
        strcpy(((Asset4 *)dest)->type, ((Asset4 *)src)->type);
        ((Asset4 *)dest)->value1 = ((Asset4 *)src)->value1;
        ((Asset4 *)dest)->value2 = ((Asset4 *)src)->value2;
        ((Asset4 *)dest)->value3 = ((Asset4 *)src)->value3;
    }
}

void deserializeLinkedList(Node **head)
{
    FILE *fp = fopen("linkedlist.bin", "rb");
    int r;
    char type[20];
    Node *temp = NULL;
    Asset1 *temp1 = (Asset1 *)malloc(sizeof(Asset1));
    Asset2 *temp2 = (Asset2 *)malloc(sizeof(Asset2));
    Asset3 *temp3 = (Asset3 *)malloc(sizeof(Asset3));
    Asset4 *temp4 = (Asset4 *)malloc(sizeof(Asset4));
    int i = 0;  

    
    // we read as size of type because we will read the type of the struct first
    // after we find the type of the struct we use fseek to go back and read the all struct 
    while (fread(type,sizeof(type),1,fp))
    {
        if(my_strcmp(type, "Asset1") == 0) // if my_strcmp returns 0 it means strings match
        {
            fseek(fp, -sizeof(type), SEEK_CUR); // we go back to the beginning of the struct
            fread(temp1, sizeof(Asset1), 1, fp); // we read the struct
            temp = (Node *)malloc(sizeof(Node));
            temp->data = (Asset1 *)malloc(sizeof(Asset1));
            cpy_data(temp->data, temp1); // we copy the data from temp1 to temp->data
            temp->next = NULL;
            if(*head == NULL) // if head is null then we should assign temp to head
            {
                *head = temp;
            }
            else // if head is not null then we go to the end of the lsit and place it there
            {
                Node *temp2 = *head;
                while(temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = temp;
            }
        }
        // i will not comment the other if statements because they are the same as the first one
        else if(my_strcmp(type, "Asset2") == 0)
        {
            fseek(fp, -sizeof(type), SEEK_CUR);
            fread(temp2, sizeof(Asset2), 1, fp);
            temp = (Node *)malloc(sizeof(Node));
            temp->data = (Asset2 *)malloc(sizeof(Asset2));
            cpy_data(temp->data, temp2);
            temp->next = NULL;
            if(*head == NULL)
            {
                *head = temp;
            }
            else
            {
                Node *temp2 = *head;
                while(temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = temp;
            }
        }
        else if(my_strcmp(type, "Asset3") == 0)
        {
            fseek(fp, -sizeof(type), SEEK_CUR);
            fread(temp3, sizeof(Asset3), 1, fp);
            temp = (Node *)malloc(sizeof(Node));
            temp->data = (Asset3 *)malloc(sizeof(Asset3));
            cpy_data(temp->data, temp3);
            temp->next = NULL;
            if(*head == NULL)
            {
                *head = temp;
            }
            else
            {
                Node *temp2 = *head;
                while(temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = temp;
            }
        }
        else if(my_strcmp(type, "Asset4") == 0)
        {
            fseek(fp, -sizeof(type), SEEK_CUR);
            fread(temp4, sizeof(Asset4), 1, fp);
            temp = (Node *)malloc(sizeof(Node));
            temp->data = (Asset4 *)malloc(sizeof(Asset4));
            cpy_data(temp->data, temp4);
            temp->next = NULL;
            if(*head == NULL)
            {
                *head = temp;
            }
            else
            {
                Node *temp2 = *head;
                while(temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = temp;
            }
        }
        temp = temp->next;
    }
    fclose(fp);
    printf("--------------------------------\n");
    printf("Deserialization is completed.\n");
    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);
}

void printLinkedList(Node *head)
{
    Node *temp = head;
    while (temp != NULL) // we print the linked list according to the type of the struct
    {
        if (my_strcmp(((Asset1 *)temp->data)->type, "Asset1") == 0)
        {
            printf("%s --> ", ((Asset1 *)temp->data)->type);
            printf("%d, ", ((Asset1 *)temp->data)->ivals[0]);
            printf("%lf\n", ((Asset1 *)temp->data)->svals[0]);
        }
        else if (my_strcmp(((Asset2 *)temp->data)->type, "Asset2") == 0)
        {
            printf("%s --> ", ((Asset2 *)temp->data)->type);
            printf("%lf, ", ((Asset2 *)temp->data)->svals[0]);
            printf("%lf, ", ((Asset2 *)temp->data)->svals[1]);
            printf("%d, ", ((Asset2 *)temp->data)->ivals[0]);
            printf("%d\n", ((Asset2 *)temp->data)->ivals[1]);
        }
        else if (my_strcmp(((Asset3 *)temp->data)->type, "Asset3") == 0)
        {
            printf("%s --> ", ((Asset3 *)temp->data)->type);
            printf("%s, ", ((Asset3 *)temp->data)->string1);
            printf("%s\n", ((Asset3 *)temp->data)->string2);
        }
        else if (my_strcmp(((Asset4 *)temp->data)->type, "Asset4") == 0)
        {
            printf("%s --> ", ((Asset4 *)temp->data)->type);
            printf("%lf, ", ((Asset4 *)temp->data)->value1);
            printf("%f, ", ((Asset4 *)temp->data)->value2);
            printf("%lf\n", ((Asset4 *)temp->data)->value3);
        }
        temp = temp->next;
    }
}

int main()
{
    Node *head = NULL;
 
    fillLinkedList(&head);
    printf("Generated linked list:\n\n");
    printLinkedList(head); // original linked list
    printf("--------------------------------\n");
    serializeLinkedList(head); // we write the head to the file

    Node *temp = NULL;
    deserializeLinkedList(&temp); // we read as temp which is NULL at the beginning
    printf("Reconstructed linked list:\n\n");
    printLinkedList(temp); // reconstructed linked list

    return 0;
}