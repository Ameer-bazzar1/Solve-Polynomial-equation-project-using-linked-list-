#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *OUTDATA="patients_hash_data";
char *INPUT="patients.txt";
FILE *input;
#define MAX_CHAR 100
struct information
{

    char Name[MAX_CHAR];
    char Gender[MAX_CHAR];
    char Date_of_admission[MAX_CHAR];
    char Date_of_birth[MAX_CHAR];
    char Illness[MAX_CHAR];
    char Address[MAX_CHAR];
    char Blood[MAX_CHAR];

};
struct avlNode
{
    struct information info;
    struct avlNode*Right;
    struct avlNode*Left;
    int Height;

};
struct Node
{
    char Illness[MAX_CHAR];
    struct Node *next;
};
struct  Node*split_sort(struct Node *head);
struct Node *mergeSort(struct Node *head);
struct Node *merge(struct Node *firsthalf, struct Node *secondhalf);
int getHeight (struct avlNode *avl);
int MAX (int x, int y);
struct  avlNode* singleRotateRight(struct  avlNode* y);
struct  avlNode* Rotate_Left_Right(struct  avlNode* K3);
struct  avlNode* singleRotateLeft(struct  avlNode*x);
struct  avlNode* Rotate_Right_left(struct  avlNode* K3);
void print(struct avlNode * Avl, char Illness[MAX_CHAR]);
void insert_from_avl_to_hash(struct information *array,struct avlNode * Avl,int flag);
void read_File();
void remove_Spaces(char *str);
int getBalanceFactor(struct avlNode*N);
struct avlNode * split(struct avlNode * Avl,char Data[MAX_CHAR]);
struct avlNode *insert (struct avlNode * Avl,char Name[MAX_CHAR],char Gender[MAX_CHAR],char Date_of_admission[MAX_CHAR]
                        ,char Date_of_birth[MAX_CHAR]
                        ,char Illness[MAX_CHAR]
                        ,char Address[MAX_CHAR]
                        ,char Blood[MAX_CHAR]);
struct avlNode * insert_New_patient(struct avlNode * Avl);
struct avlNode * find(struct avlNode *Avl,char Name[MAX_CHAR]);
void Update(struct avlNode *Avl);
void push(struct Node** head_ref, char Illness[MAX_CHAR]);
void menu();
void  start();
struct avlNode *Avl_Tree=NULL;
struct Node* Illness_list = NULL;
struct avlNode*FindMin( struct avlNode *avl );
void print_in_order(struct avlNode * Avl);
void removeDuplicates(struct Node* head);
struct avlNode* deleteNode(struct avlNode*root, char key[MAX_CHAR]);
void  print_in_File_in_order(FILE * out1, struct avlNode*Avl);
int Max( int L, int R );
void export(struct avlNode*Avl);
//--------------------------------------------------------------------------------------------------
int counter;
int prime_size;
int size_table;
int is_prime (int x);
unsigned int hash(char *key );
unsigned int hash2(unsigned int key);
unsigned int hash1(unsigned int key);
int prime (int x,int sel);
struct information* insert_Hash(struct information*array1,char Name[MAX_CHAR],char Gender[MAX_CHAR],char Date_of_admission[MAX_CHAR]
                                ,char Date_of_birth[MAX_CHAR]
                                ,char Illness[MAX_CHAR]
                                ,char Address[MAX_CHAR]
                                ,char Blood[MAX_CHAR],int *flag);
struct information*split_hash(struct information*array1,char Data[MAX_CHAR],int *flag);
void print_hash(struct information* hash);
void insert_New_Hash(struct information*table,int *flag);
void remove_element(struct information*array1,char Name[MAX_CHAR]);
void search(struct information*table,char Name[MAX_CHAR]);
void print_in_File_Hash(FILE * out1, struct information*hash);
void deleteNode_list(struct Node** head_ref, char key[MAX_CHAR]);
struct information*  re_Hashing(struct information* New_Hash);
void print_hash_file( FILE *out1,struct information* hash);
void menu2();
struct information *HashTable;
void export_HASH(struct information*hash,int flag);
void menu3();
//---------------------------------------------------------------------------------------------------------------
int main()
{
    start();
    return 0;
}
void  start()
{
    menu();
    int select=0;
    char Data[MAX_CHAR];
    printf("Please enter :");
    /**
    *   this while to handle errors from user example if him enter 'a'
    *    its error because must enter integer and make sure he read a file Firstly
    */
    while (scanf("%d",&select) != 1)
    {

        printf("\nplease enter again : ");
        while(getchar() != '\n');
    }
    while (select!=8)
    {
        switch (select)
        {
        case 1:
            counter=0;
            read_File();
            printf("Thank you you are load Data Successfully !\n");
            break;
        case 2:
            Avl_Tree = insert_New_patient(Avl_Tree);
            printf("Thank you!\n");
            counter++;

            break;
        case 3:
            if(Avl_Tree==NULL)
            {
                printf("The avl tree is empty\n");
            }
            else
            {
                Update(Avl_Tree);
                printf("Thank you!\n");
            }
            break;
        case 4:
            if(Avl_Tree==NULL)
            {
                printf("The avl tree is empty\n");
            }
            else
            {
                printf("*********************************************************\n");
                print_in_order(Avl_Tree);
            }
            break;
        case 5:
            if(Avl_Tree==NULL)
            {
                printf("The avl tree is empty\n");
            }
            else
            {
                printf("1. if you need print list of Patients have the Specific illness\n");
                printf("2. if you need print list of Patients of all illness\n");
                printf("3. Close\n");
                printf("Please enter : ");
                while (scanf("%d",&select) != 1)
                {

                    printf("\nplease enter again : ");
                    while(getchar() != '\n');
                }
                while (select != 3)
                {
                    Illness_list = mergeSort(Illness_list);
                    removeDuplicates(Illness_list);
                    struct Node *temp = Illness_list;
                    printf("\n**********************************************\n");
                    int state = 0;
                    if (select == 1)
                    {
                        printf("Please enter Name of Illness : ");
                        scanf(" %[^\n]s", Data);
                        remove_Spaces(Data);
                        while (temp != NULL)
                        {
                            if (strcasecmp(Data, temp->Illness) == 0)
                            {
                                state = 1;
                                break;
                            }
                            temp = temp->next;
                        }
                        if (state == 0)
                        {
                            printf("There are no patients with this Illness \n");
                            printf("**********************************************\n");
                        }
                        else
                            print(Avl_Tree, Data);
                    }
                    else if (select == 2)
                    {

                        while (temp != NULL)
                        {
                            printf(" Illness : %s", temp->Illness);
                            printf("\n**********************************************\n");
                            print(Avl_Tree, temp->Illness);
                            temp = temp->next;
                        }
                    }
                    else if (select==3)
                    {
                        break;
                    }
                    printf("1. if you need print list of Patients have the Specific illness\n");
                    printf("2. if you need print list of Patients of all illness\n");
                    printf("3. Close\n");
                    printf("Please enter : ");
                    while (scanf("%d",&select) != 1)
                    {

                        printf("\nplease enter again : ");
                        while(getchar() != '\n');
                    }
                }
            }
            break;
        case 6:
            if(Avl_Tree==NULL)
            {
                printf("The avl tree is empty\n");
            }
            else
            {
                printf("Please enter Name of patient : ");
                scanf(" %[^\n]s", Data);
                remove_Spaces(Data);
                Avl_Tree = deleteNode(Avl_Tree, Data);
            }
            break;
        case 7:
            if(Avl_Tree==NULL)
            {
                printf("The avl tree is empty\n");
            }
            else
            {
                export(Avl_Tree);
                printf("Thank you Result Already in File !\n");
            }
            break;
        default:
            printf("Please select from menu \n");
        }
        if (select ==7)
        {

            size_table = 0;
            struct information *array;
            int initial = 0;
            int flag = 0;
            if (Avl_Tree!=NULL)
            {
                counter = prime(2 * counter, 1);
                prime_size = prime(counter, 0);
                array = (struct information *) malloc(sizeof(struct information) * (counter));
                while (initial < counter)
                {
                    array[initial].Name[0] = '\0';
                    initial++;
                }
                insert_from_avl_to_hash(array, Avl_Tree, flag);
            }
            else
            {
                counter=0;
                input = fopen(INPUT, "r");
                while (!feof(input))
                {
                    fgets(Data, MAX_CHAR, input);
                    if (Data[0] == '\n')
                    {
                        continue;
                    }
                    ++counter;
                }
                counter = prime(2 * counter, 1);
                prime_size = prime(counter, 0);
                array = (struct information *) malloc(sizeof(struct information) * (counter));
                while (initial < counter)
                {
                    array[initial].Name[0] = '\0';
                    initial++;
                }
                rewind(input);
                while (!feof(input))
                {
                    //read line from File
                    fgets(Data, MAX_CHAR, input);
                    //if found new line then not store him in linked list
                    if (Data[0] == '\n')
                        continue;
                    remove_Spaces(Data);
                    HashTable = split_hash(array, Data, &flag);
                }
            }
            menu2();
            char mod = '%';
            printf("Please enter :");
            scanf("%d", &select);
            while (1)
            {
                switch (select)
                {
                case 1:
                    print_hash(HashTable);
                    break;
                case 2:
                    printf("Table size is %d and %d is filled\n",counter,size_table);
                    break;
                case 3:
                    printf("****************************************************************************************************\n");
                    printf("The Hash Function that has been used in this program is the Double Hash function\n");
                    printf("Where i from 0 to the hash table ,it increases every collision,and h1(x) = (key %c TABLE_SIZE) and h2(x)=R - (x %c R) \n",
                           mod, mod);
                    printf("where R is first smaller prime number of TABLE_SIZE\n");
                    printf("And x is involves all characters in the key and \n");
                    printf("can generally be expected to distribute the keys well. \n");
                    printf("****************************************************************************************************\n");
                    break;
                case 4:
                    insert_New_Hash(HashTable, &flag);
                    if (flag == 1)
                    {
                        HashTable = re_Hashing(HashTable);
                    }
                    printf("Thank you!\n");
                    break;
                case 5:
                    printf("Please enter Name of Patient :");
                    scanf(" %[^\n]s", Data);
                    remove_Spaces(Data);
                    search(HashTable, Data);

                    break;
                case 6:
                    printf("Please enter Name of Patient :");
                    scanf(" %[^\n]s", Data);
                    remove_Spaces(Data);
                    remove_element(HashTable, Data);
                    break;
                case 7:
                    printf("1) Print Hash Table without empty spots \n ");
                    printf("2) Print Hash Table including empty spots  \n");
                    printf("Please enter :");
                    while (scanf("%d",&select) != 1||(select>2||select<1))
                    {
                        printf("1) Print Hash Table without empty spots \n ");
                        printf("2) Print Hash Table including empty spots  \n");
                        printf("Please enter correct:");

                    }
                    if (select==1)
                    {
                        export_HASH(HashTable,1);
                    }
                    else if(select==2)
                    {
                        export_HASH(HashTable,2);
                    }
                    printf("Thank you Result Already in File !\n");
                    break;
                case 8:
                    printf("Good bye ! ");
                    exit(1);
                default:
                    printf("Please select from menu");
                    break;
                }

                menu2();
                printf("Please enter :");
                while (scanf("%d",&select) != 1)
                {

                    printf("\nplease enter again : ");
                    while(getchar() != '\n');

                }
            }
        }
        else
        {

            menu();
            printf("Please enter :");
            while (scanf("%d",&select) != 1)
            {

                printf("\nplease enter again : ");
                while(getchar() != '\n');

            }
        }
    }
    fclose(input);
}
void menu()
{
    printf("Choose From menu\n"
           "******************************************************************\n"
           "*          1. read File to load Data of Patients                 *\n"
           "*          2. Insert a new patient                               *\n"
           "*          3. Find a patient                                     *\n"
           "*          4. print all patients in lexicographic order          *\n"
           "*          5. print all patients that have the same illness      *\n"
           "*          6. Delete a patient from the system                   *\n"
           "*          7. Save all information in file patients_hash.data    *\n"
           "******************************************************************\n");
}
void menu2()
{
    printf("Choose From menu\n"
           "******************************************************************\n"
           "*          1.Print Hash Table including empty spots              *\n"
           "*          2.Print out size table                                *\n"
           "*          3.Print out used hash function                        *\n"
           "*          4.Insert a new record to hash table                   *\n"
           "*          5.Search for a specific word                          *\n"
           "*          6.Delete a specific record                            *\n"
           "*          7.Save hash table to file                             *\n"
           "*          8.Exit and close the program                          *\n"
           "******************************************************************\n");
}
void  menu3()
{
    printf("Choose From menu\n"
           "************************************************\n"
           "*          1. Update Name                      *\n"
           "*          2. Update Gender                    *\n"
           "*          3. Update Date of admission         *\n"
           "*          4. Update Date of birth             *\n"
           "*          5. Update Illness                   *\n"
           "*          6. Update Address                   *\n"
           "*          7. Update Blood                     *\n"
           "*          8. Quit                             *\n"
           "************************************************\n");
}
void export(struct avlNode*Avl)
{
    FILE *out;
    out= fopen(OUTDATA,"w");
    print_in_File_in_order(out, Avl);
    fclose(out);
}
void export_HASH(struct information*hash,int flag)
{
    FILE *out;
    out= fopen(OUTDATA,"w");
    if (flag==1)
        print_in_File_Hash(out, hash);
    else if (flag==2)
        print_hash_file(out,hash);
    fclose(out);
}


void print_in_File_in_order(FILE * out1, struct avlNode*Avl)
{
    if(Avl!=NULL)
    {
        print_in_File_in_order(out1,Avl->Left);
        fprintf(out1,"\nName: %s\n", Avl->info.Name);
        fprintf(out1,"Gender: %s\n",  Avl->info.Gender);
        fprintf(out1,"Date of admission(ddmmyyyy): %s\n",  Avl->info.Date_of_admission);
        fprintf(out1,"Date of birth(ddmmyyyy): %s\n",  Avl->info.Date_of_birth);
        fprintf(out1,"Illness: %s\n",  Avl->info.Illness);
        fprintf(out1,"Address: %s\n",  Avl->info.Address);
        fprintf(out1,"Blood: %s\n",  Avl->info.Blood);
        fprintf(out1,"***************************************************************\n");
        print_in_File_in_order(out1,Avl->Right);
    }
}
void print_in_File_Hash(FILE * out1, struct information*hash)
{
    int k=0;
    for (int i = 0; i < counter; i++)
    {
        if (hash[i].Name[0] !='\0')
        {
            fprintf(out1, "***************************************************************\n");
            fprintf(out1,"%d: \n",(k+1));
            fprintf(out1, "\nName: %s\n", hash[i].Name);
            fprintf(out1, "Gender: %s\n", hash[i].Gender);
            fprintf(out1, "Date of admission(ddmmyyyy): %s\n", hash[i].Date_of_admission);
            fprintf(out1, "Date of birth(ddmmyyyy): %s\n", hash[i].Date_of_birth);
            fprintf(out1, "Illness: %s\n", hash[i].Illness);
            fprintf(out1, "Address: %s\n", hash[i].Address);
            fprintf(out1, "Blood: %s\n", hash[i].Blood);
            fprintf(out1, "***************************************************************\n");
            ++k;
        }
    }

}

/* The function removes duplicates from a sorted list */
void removeDuplicates(struct Node* head)
{
    /* Pointer to traverse the linked list */
    struct Node* current = head;

    /* Pointer to store the next pointer of a node to be deleted*/
    struct Node* next_next;

    /* do nothing if the list is empty */
    if (current == NULL)
        return;

    /* Traverse the list till last node */
    while (current->next != NULL)
    {
        /* Compare current node with next node */
        if (strcmp(current->Illness,current->next->Illness)==0)
        {
            /* The sequence of steps is important*/
            next_next = current->next->next;
            free(current->next);
            current->next = next_next;
        }
        else /* This is tricky: only advance if no deletion */
        {
            current = current->next;
        }
    }
}
void read_File()
{

    input = fopen(INPUT, "r");
//Check if the file is Null this meaning the file not found then exit from program
    if (input == NULL)
    {

        printf("Error! opening file");

        exit(1);
    }
    char Data[MAX_CHAR];


    while (!feof(input))
    {

        //read line from File
        fgets(Data, MAX_CHAR, input);

//if found new line then not store him in linked list
        if (Data[0] == '\n')
        {
            continue;
        }
        remove_Spaces(Data);
        Avl_Tree = split(Avl_Tree, Data);
        ++counter;
    }
    fclose(input);
}
/**
 * This function will remove all space in the line
 * @param str
 */
void remove_Spaces(char *str)
{
    /*
     * keep counter  incremented until found space
     * If current character
     * is not space then place it at index counter
     * If the character encountered is an empty space, skip the character.
     */
    int counter1 = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ')
        {
            str[counter1] = str[i];
            counter1++;
        }
    str[counter1] = '\0';
}
/**
 * get Height of Avl tree
 * @param avl
 * @return
 */
int getHeight (struct avlNode *avl)
{
    if(avl==NULL)
        return -1;
    else
        return avl->Height;
}
/**
 * get Maximum Integer from two integer
 * @param avl
 * @return
 */
int MAX (int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}
struct  avlNode* singleRotateLeft(struct  avlNode*x)
{

    struct  avlNode* y;

    y = x->Right;

    x->Right  = y->Left;

    y->Left = x;

    x->Height = 1 + MAX(getHeight(x->Left), getHeight(x->Right));

    y->Height = 1 + MAX(getHeight(x), getHeight(y->Right));

    return y;
}
struct  avlNode* singleRotateRight(struct  avlNode* y)
{

    struct  avlNode* x;

    x= y->Left;

    y->Left  = x->Right;

    x->Right = y;

    y->Height = 1 + MAX(getHeight(y->Right), getHeight(y->Left));

    x->Height = 1 + MAX(getHeight(y), getHeight(x->Left));

    return x;
}
struct  avlNode* Rotate_Left_Right(struct  avlNode* K3)
{

    K3->Left  = singleRotateLeft(K3->Left);

    return singleRotateRight(K3);
}
struct  avlNode* Rotate_Right_left(struct  avlNode* K3)
{

    K3->Right  = singleRotateRight(K3->Right);

    return singleRotateLeft(K3);
}
struct avlNode *insert (struct avlNode * Avl,char Name[MAX_CHAR],char Gender[MAX_CHAR],char Date_of_admission[MAX_CHAR]
                        ,char Date_of_birth[MAX_CHAR]
                        ,char Illness[MAX_CHAR]
                        ,char Address[MAX_CHAR]
                        ,char Blood[MAX_CHAR])
{

    if((Avl) ==NULL)
    {

        (Avl)  =malloc(sizeof (struct avlNode));
        if( Avl == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy((Avl) ->info.Name,Name);

            strcpy((Avl) ->info.Gender,Gender);

            strcpy((Avl) ->info.Date_of_admission,Date_of_admission);

            strcpy((Avl) ->info.Date_of_birth,Date_of_birth);

            strcpy((Avl) ->info.Illness,Illness);

            strcpy((Avl) ->info.Address,Address);

            strcpy((Avl) ->info.Blood,Blood);

            (Avl) ->Height=0;

            (Avl) ->Left= (Avl) ->Right=NULL;
        }
    }
    else if(strcasecmp(Name,(Avl) ->info.Name)<0)
    {

        (Avl) ->Left=insert(Avl ->Left,Name,Gender,Date_of_admission,Date_of_birth,Illness,Address,Blood);

        if(getHeight((Avl) ->Left) - getHeight((Avl) ->Right) >= 2)
        {

            if(strcasecmp(Name, (Avl) ->Left->info.Name)<0)

                (Avl) =singleRotateRight((Avl) );

            else

                (Avl) = Rotate_Left_Right((Avl) );
        }
    }

    else if(strcasecmp(Name,(Avl)->info.Name)>0)
    {

        (Avl)->Right = insert((Avl) ->Right, Name,Gender,Date_of_admission,Date_of_birth,Illness,Address,Blood);

        if(getHeight((Avl) ->Right) - getHeight((Avl) ->Left) >= 2)
        {

            if(strcasecmp(Name, (Avl) ->Right->info.Name)>0)

                (Avl) =singleRotateLeft((Avl) );
            else

                (Avl) =Rotate_Right_left((Avl) );
        }
    }

    (Avl) ->Height = 1 + MAX(getHeight((Avl) ->Right), getHeight((Avl) ->Left));

    return (Avl) ;
}

/**
 * creates a patient from a line :
 * Patient Name#Gender#Date of admission#Date of birth#Illness#Address (City)#Blood type
 * @param Avl
 * @param Data
 * @return
 */
struct avlNode * split(struct avlNode * Avl,char Data[MAX_CHAR])
{

    char *str;

    char Name[MAX_CHAR];

    char Gender[MAX_CHAR];

    char Date_of_admission[MAX_CHAR];

    char Date_of_birth[MAX_CHAR];

    char Illness[MAX_CHAR];

    char Address[MAX_CHAR];

    char Blood[MAX_CHAR];
    str= strtok(Data,"#");
    strcpy(Name,str);
    remove_Spaces(Name);
    str= strtok(NULL,"#");
    strcpy(Gender,str);

    str= strtok(NULL,"#");
    strcpy(Date_of_admission,str);


    str= strtok(NULL,"#");
    strcpy(Date_of_birth,str);

    str= strtok(NULL,"#");
    strcpy(Illness,str);
    push(&Illness_list,str);
    str= strtok(NULL,"#");

    strcpy(Address,str);
    str= strtok(NULL,"#");
    strcpy(Blood,str);

    return  insert(Avl,Name,Gender,Date_of_admission,Date_of_birth,Illness,Address, Blood);
}
/**
 * print patient with same Illness
 * @param Avl
 * @param Illness
 */
void print(struct avlNode * Avl, char Illness[MAX_CHAR])
{

    if(Avl!= NULL)
    {

        print(Avl->Left,Illness);
        if(strcasecmp(Avl->info.Illness,Illness)==0)
        {
            printf("\nName : %s\n", Avl->info.Name);
            printf("Gender : %s\n", Avl->info.Gender);
            printf("Date of admission(ddmmyyyy) : %s\n", Avl->info.Date_of_admission);
            printf("Date of birth(ddmmyyyy)  : %s\n", Avl->info.Date_of_birth);
            printf("Address    : %s\n", Avl->info.Address);
            printf("Blood    : %s\n", Avl->info.Blood);
            printf("**********************************************\n");
        }
        print(Avl->Right,Illness);
    }
}
/**
 * insert from avl to hash table
 * @param array
 * @param Avl
 * @param flag
 */
void insert_from_avl_to_hash(struct information *array,struct avlNode * Avl,int flag)
{

    if(Avl!= NULL)
    {
        insert_from_avl_to_hash(array, Avl->Left, flag);
        if (Avl->info.Name[0]!='\0')
        {
            HashTable=insert_Hash(array, Avl->info.Name, Avl->info.Gender, Avl->info.Date_of_admission, Avl->info.Date_of_birth,
                                  Avl->info.Illness, Avl->info.Address, Avl->info.Blood, &flag);
        }
        insert_from_avl_to_hash(array, Avl->Right, flag);
    }
}
struct avlNode * insert_New_patient(struct avlNode * Avl)
{

    char Name[MAX_CHAR];

    char Gender[MAX_CHAR];

    char Date_of_admission[MAX_CHAR];

    char Date_of_birth[MAX_CHAR];

    char Illness[MAX_CHAR];

    char Address[MAX_CHAR];

    char Blood[MAX_CHAR];

    printf("Please Enter Name of patient : ");

    scanf(" %[^\n]s", Name);
    printf("\nPlease Enter Gender of patient : ");
    remove_Spaces(Name);

    scanf(" %[^\n]s", Gender);
    while (strcasecmp(Gender,"F")!=0&&strcasecmp(Gender,"M")!=0)
    {
        printf("\nPlease enter Valid Gender M of :Male or F  of  : Female : ");
        scanf(" %[^\n]s", Gender);
    }

    printf("\nplease enter the patient Date of admission (ddMMyyyy): ");

    scanf(" %[^\n]s", Date_of_admission);

    printf("\nplease enter the patient Date of birth (ddMMyyyy): ");

    scanf(" %[^\n]s", Date_of_birth);


    printf("\nplease enter the patient Illness: ");

    scanf(" %[^\n]s", Illness);
    push(&Illness_list,Illness);
    printf("\nplease enter the patient Address: ");

    scanf(" %[^\n]s", Address);

    printf("\nplease enter the patient Blood type:");

    scanf(" %[^\n]s", Blood);
    while (strcasecmp(Blood,"A+")!=0&&strcasecmp(Blood,"A-")!=0&&strcasecmp(Blood,"B+")!=0&&strcasecmp(Blood,"B-")!=0
            &&strcasecmp(Blood,"O+")!=0&&strcasecmp(Blood,"O-")!=0 &&strcasecmp(Blood,"AB+")!=0&&strcasecmp(Blood,"AB-")!=0)
    {
        printf("\nPlease enter Valid type of Blood : ");
        scanf(" %[^\n]s", Blood);
    }

    return insert(Avl,Name,Gender,Date_of_admission,Date_of_birth,Illness,Address,Blood);
}
/**
 * Search Patient depend he Name
 * @param Avl
 * @param Name
 * @return
 */
struct avlNode * find(struct avlNode *Avl,char Name[MAX_CHAR])
{

    if (strcasecmp(Name,Avl->info.Name)==0)

        return Avl;

    else if(strcasecmp(Name,Avl->info.Name)<0&&Avl->Left)

        return find(Avl->Left,Name);

    else if(strcasecmp(Name,Avl->info.Name)>0&&Avl->Right)

        return find(Avl->Right,Name);

    else
    {

        printf("\nSorry The patient %s Does not exist in the Record!\n\n",Name);

        return  NULL;
    }
}
/**
 * Delete From linked List
 * @param head_ref
 * @param key
 */
void deleteNode_list(struct Node** head_ref, char key[MAX_CHAR])
{
    // Store head node
    struct Node *temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && strcasecmp( temp->Illness, key)==0)
    {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && strcasecmp( temp->Illness, key)!=0)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}
/**
 * find The patient depend he Name and Ask of need Update information of Patient or no
 * @param Avl
 */
void Update(struct avlNode *Avl)
{

    struct avlNode *Avl1=NULL;
    printf("Please Enter Name of patient: ");
    char Data[MAX_CHAR];
    char Name1[MAX_CHAR];
    scanf(" %[^\n]s", Name1);
    remove_Spaces(Name1);
    struct avlNode*newAvl=(struct avlNode*) malloc(sizeof(struct avlNode));
    Avl1=find(Avl,Name1);
    if(Avl1!=NULL)
    {

        printf("\nThe patient exist in the  Record and This information for him : ");
        printf("\n****************************************************************\n");
        printf("Name: %s\n", Avl1->info.Name);
        printf("Gender: %s\n", Avl1->info.Gender);
        printf("Date of admission(ddmmyyyy): %s\n", Avl1->info.Date_of_admission);
        printf("Date of birth(ddmmyyyy): %s\n", Avl1->info.Date_of_birth);
        printf("Illness: %s\n", Avl1->info.Illness);
        printf("Address: %s\n", Avl1->info.Address);
        printf("Blood: %s\n", Avl1->info.Blood);
        printf("****************************************************************\n");
        printf("do you want to Update information for patient ? enter y if yes : ");
        scanf(" %[^\n]s", Data);
        if (Data[0] == 'y' || Data[0] == 'Y')
        {
            menu3();
            int select;
            printf("Please enter :");
            while (scanf("%d",&select) != 1)
            {

                printf("\nplease enter again : ");
                while(getchar() != '\n');

            }
            while (select != 8)
            {
                switch (select)
                {
                case 1:
                    strcpy(newAvl->info.Illness,Avl1->info.Illness);
                    strcpy(newAvl->info.Gender,Avl1->info.Gender);
                    strcpy(newAvl->info.Blood,Avl1->info.Blood);
                    strcpy(newAvl->info.Address,Avl1->info.Address);
                    strcpy(newAvl->info.Date_of_birth,Avl1->info.Date_of_birth);
                    strcpy(newAvl->info.Date_of_admission,Avl1->info.Date_of_admission);
                    Avl1=deleteNode(Avl,Name1);
                    printf("\nPlease Enter new Name of patient : ");
                    scanf(" %[^\n]s", Data);
                    remove_Spaces(Data);
                    strcpy(Name1,Data);
                    Avl1=insert(Avl1,Data,newAvl->info.Gender,newAvl->info.Date_of_admission,newAvl->info.Date_of_birth,newAvl->info.Illness,newAvl->info.Address,newAvl->info.Blood);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 2:
                    printf("\nPlease Enter new Gender of patient : ");
                    scanf(" %[^\n]s", Data);
                    while (strcasecmp(Data,"F")!=0&&strcasecmp(Data,"M")!=0)
                    {
                        printf("\nPlease enter Valid Gender M of :Male or F  of  : Female : ");
                        scanf(" %[^\n]s", Data);
                    }
                    strcpy(Avl1->info.Gender,Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 3:

                    printf("\nPlease Enter new Date of admission of patient (ddmmyyyy): ");
                    scanf(" %[^\n]s", Data);
                    strcpy(Avl1->info.Date_of_admission,  Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 4:
                    printf("\nPlease Enter new  Date of birth of patient (ddmmyyyy): ");

                    scanf(" %[^\n]s", Data);
                    strcpy(Avl1->info.Date_of_birth,  Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 5:
                    printf("\nPlease Enter new   Illness  of patient : ");
                    scanf(" %[^\n]s",  Data);
                    deleteNode_list(&Illness_list,Avl1->info.Illness);
                    strcpy(Avl1->info.Illness,  Data);
                    push(&Illness_list, Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 6:
                    printf("\nPlease Enter  Address of patient : ");
                    scanf(" %[^\n]s",  Data);
                    strcpy(Avl1->info.Address,  Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 7:
                    printf("\nPlease Enter new  Blood of patient : ");
                    scanf(" %[^\n]s",  Data);
                    while (strcasecmp( Data,"A+")!=0&&strcasecmp( Data,"A-")!=0&&strcasecmp( Data,"B+")!=0&&strcasecmp( Data,"B-")!=0
                            &&strcasecmp( Data,"O+")!=0&&strcasecmp( Data,"O-")!=0 &&strcasecmp( Data,"AB+")!=0&&strcasecmp( Data,"AB-")!=0)
                    {
                        printf("\nPlease enter Valid type of Blood : ");
                        scanf(" %[^\n]s", Data);
                    }
                    strcpy(Avl1->info.Blood,  Data);
                    printf("Thank you!\n");
                    printf("**********************************************\n");
                    break;
                case 8:
                    return;
                default:
                    printf("Please enter from menu!!\n");

                }
                menu3();
                printf("Please enter :");
                while (scanf("%d",&select) != 1)
                {

                    printf("\nplease enter again : ");
                    while(getchar() != '\n');

                }
            }
        }
    }
}
void print_in_order(struct avlNode * Avl)
{

    if(Avl!= NULL)
    {
        print_in_order(Avl->Left);
        printf("Name: %s\n", Avl->info.Name);
        printf("Gender: %s\n", Avl->info.Gender);
        printf("Date of admission(ddmmyyyy): %s\n", Avl->info.Date_of_admission);
        printf("Date of birth (ddmmyyyy): %s\n", Avl->info.Date_of_birth);
        printf("Illness: %s\n", Avl->info.Illness);
        printf("Address: %s\n", Avl->info.Address);
        printf("Blood: %s\n", Avl->info.Blood);
        printf("*********************************************************\n");
        print_in_order(Avl->Right);

    }
}
struct avlNode*FindMin( struct avlNode *avl )
{
    if( avl == NULL )
        return NULL;
    else if( avl->Left == NULL )
        return avl;
    else
        return FindMin( avl->Left );
}
int Max( int L, int R )
{
    return L > R ? L : R;
}
/**
 * merge two linked lists
 * @param firsthalf
 * @param secondhalf
 * @return
 */
struct Node *merge(struct Node *firsthalf, struct Node *secondhalf)
{
    if (firsthalf==NULL)
        return secondhalf;

    if (secondhalf==NULL)
        return firsthalf;

    if (strcasecmp(firsthalf->Illness,secondhalf->Illness)>0)
    {
        secondhalf->next = merge(firsthalf,secondhalf->next);
        return secondhalf;
    }
    else
    {
        firsthalf->next = merge(secondhalf,firsthalf->next);
        return firsthalf;

    }
}

/**
 *  If the head is NULL or there is only one element in the Linked List
 *  then return.
 *  Else divide the linked list into two halves.
 *  split_sort(head);
 *  Sort the two halves a and b.
 *  head = mergeSort(head);
 *  second = mergeSort(second);
 *  Merge the sorted head and second using merge()
 *  and then return linked list
 *  return merge(head,second);
 * @param head
 * @return
 */
struct Node *mergeSort(struct Node *head)
{
    if (head==NULL || head->next==NULL)
        return head;
    struct Node *second = split_sort(head);

// Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

// Merge the two sorted halves
    return merge(head,second);
}
/**
 * Split the Nodes of the given list into first half and second half
 * here if the number of Node is odd the extra Node should go in the first half
 * @param head
 * @return
 */
struct  Node*split_sort(struct Node *head)
{
    struct Node *first = head,*second = head;

    while (second->next!=NULL&& second->next->next!=NULL)
    {
        second= second->next->next;
        first = first->next;
    }
    struct Node *temp = first->next;
    first->next = NULL;
    return temp;
}
/**
 * Delet ndoe from Avl tree
 * And will have 3 ways to find Patient need Delete him
 * first if The patient in The root of tree
 * second if The name of patient larg name of root patient
 * will go right og root ,finally if The name of patient small name of root patient
 * will go left of root
 * @param root
 * @param key
 * @return
 */
struct avlNode* deleteNode(struct avlNode*root, char key[MAX_CHAR])
{
    if (root == NULL)
    {
        printf("The patient %s not found\n",key);
        return root;
    }
    if (strcasecmp(key,root->info.Name)<0)
        root->Left = deleteNode(root->Left,key);
    else if( strcasecmp(key,root->info.Name)>0 )
        root->Right = deleteNode(root->Right, key);
    else
    {
        if (root->Left && root->Right)
        {
            struct avlNode *temp = FindMin(root->Right);
            strcpy(root->info.Name, temp->info.Name);
            strcpy(root->info.Illness, temp->info.Illness);
            strcpy(root->info.Blood, temp->info.Blood);
            strcpy(root->info.Address, temp->info.Address);
            strcpy(root->info.Gender, temp->info.Gender);
            strcpy(root->info.Date_of_admission, temp->info.Date_of_admission);
            strcpy(root->info.Date_of_birth, temp->info.Date_of_birth);
            root->Right = deleteNode(root->Right, temp->info.Name);
        }
        else
        {
            if(root->Left==NULL)
            {
                struct avlNode *temp=root;
                root=root->Right;
                free(temp);
                printf("The patient %s Has been deleted  \n",key);
                counter--;
            }
            else if(root->Right==NULL)
            {
                struct avlNode *temp=root;
                root=root->Left;
                free(temp);
                counter--;
                printf("The patient %s Has been deleted  \n",key);
            }
        }
    }
    if (root == NULL)
    {

        return root;

    }
    root->Height= 1+Max(getHeight(root->Left),getHeight(root->Right));

    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->Left) >= 0)

        return singleRotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->Left) < 0)
    {

        return  Rotate_Left_Right(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->Right) <= 0)
        return singleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->Right) > 0)
    {

        return Rotate_Right_left(root);
    }
    return root;

}
/**
 * calculation Balance Factor of tree
 * @param N
 * @return
 */
int getBalanceFactor(struct avlNode*N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->Left) - getHeight(N->Right);
}
/**
 * insert in linked List
 * @param head_ref
 * @param Illness
 */
void push(struct Node** head_ref, char Illness[MAX_CHAR])
{

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));


    strcpy(new_node->Illness,Illness);


    new_node->next = (*head_ref);


    (*head_ref)    = new_node;
}
void print_hash(struct information* hash)
{
    int k = 0;
    while(k<counter)
    {
        if(hash[k].Name[0]!='\0')
        {
            printf("%d:",k+1);
            printf("\nName: %s\n", hash[k].Name);
            printf("Gender: %s\n", hash[k].Gender);
            printf("Date of admission(ddmmyyyy): %s\n", hash[k].Date_of_admission);
            printf("Date of birth (ddmmyyyy): %s\n", hash[k].Date_of_birth);
            printf("Illness: %s\n",hash[k].Illness);
            printf("Address: %s\n", hash[k].Address);
            printf("Blood: %s\n", hash[k].Blood);
            printf("*********************************************************\n");
        }
        else
        {
            printf("%d:", k+1);
            printf("EMPTY INDEX\n");
            printf("*********************************************************\n");
        }

        k++;
    }
}
void print_hash_file( FILE *out1,struct information* hash)
{
    int k = 0;
    while(k<counter)
    {
        if(hash[k].Name[0]!='\0')
        {
            fprintf(out1,"%d:",k+1);
            fprintf(out1,"\nName: %s\n", hash[k].Name);
            fprintf(out1,"Gender: %s\n", hash[k].Gender);
            fprintf(out1,"Date of admission(ddmmyyyy): %s\n", hash[k].Date_of_admission);
            fprintf(out1,"Date of birth (ddmmyyyy): %s\n", hash[k].Date_of_birth);
            fprintf(out1,"Illness: %s\n",hash[k].Illness);
            fprintf(out1,"Address: %s\n", hash[k].Address);
            fprintf(out1,"Blood: %s\n", hash[k].Blood);
            fprintf(out1,"*********************************************************\n");
        }
        else
        {
            fprintf(out1,"%d:", k+1);
            fprintf(out1,"EMPTY INDEX\n");
            fprintf(out1,"*********************************************************\n");
        }

        k++;
    }
}
struct information*split_hash(struct information*array12,char Data[MAX_CHAR],int *flag)
{

    char* str;

    char Name[MAX_CHAR];

    char Gender[MAX_CHAR];

    char Date_of_admission[MAX_CHAR];

    char Date_of_birth[MAX_CHAR];

    char Illness[MAX_CHAR];

    char Address[MAX_CHAR];

    char Blood[MAX_CHAR];

    str= strtok(Data,"#");
    strcpy(Name,str);

    str= strtok(NULL,"#");
    strcpy(Gender,str);

    str= strtok(NULL,"#");
    strcpy(Date_of_admission,str);

    str= strtok(NULL,"#");
    strcpy(Date_of_birth,str);

    str= strtok(NULL,"#");
    strcpy(Illness,str);
    push(&Illness_list,str);
    str= strtok(NULL,"#");

    strcpy(Address,str);
    str= strtok(NULL,"#");
    strcpy(Blood,str);

    return  insert_Hash(array12,Name,Gender,Date_of_admission,Date_of_birth,Illness,Address, Blood,flag);
}
struct information* insert_Hash(struct information*array1,char Name[MAX_CHAR],char Gender[MAX_CHAR],char Date_of_admission[MAX_CHAR]
                                ,char Date_of_birth[MAX_CHAR]
                                ,char Illness[MAX_CHAR]
                                ,char Address[MAX_CHAR]
                                ,char Blood[MAX_CHAR],int *flag)
{
    unsigned int key,index, i, hash12, hash22;
    key = hash(Name);
    hash12 = hash1(key);
    hash22 = hash2(key);
    for (i = 0; i < counter; i++)
    {
        index = (hash12 + i * hash22) % counter;
        if (strcasecmp(array1[index].Name, Name) == 0)
        {
            printf("Can not add this patient since he already Existing in record !\n");
            continue;
        }
    }
    for (i = 0; i < counter; i++)
    {
        index = (hash12 + i * hash22) % counter;
        if (array1[index].Name[0] == '\0')
        {
            strcpy(array1[index].Name, Name);
            strcpy(array1[index].Date_of_birth, Date_of_birth);
            strcpy(array1[index].Date_of_admission, Date_of_admission);
            strcpy(array1[index].Gender, Gender);
            strcpy(array1[index].Address, Address);
            strcpy(array1[index].Blood, Blood);
            strcpy(array1[index].Illness, Illness);
            size_table+=1;
            break;
        }

    }
    if ((0.75*counter<=size_table))
    {
        *flag=1;
    }
    return array1;
}
unsigned int hash1(unsigned int key)
{
    return (key % counter);
}

// function to calculate second hash
unsigned int hash2(unsigned int key)
{
    return (prime_size - (key % prime_size));
}
unsigned int hash(char *key )
{
    unsigned int  value=0;
    //int value=0;
    while (*key!='\0')
    {
        value+=(value<<5)+*key++;
    }
    return value;
}
int is_prime (int x)
{
    int flag = 1;
    for(int i=2; i<=x/2; i++)
    {
        if(x%i==0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
/**
 * if sel is 0 then will return the Small prime of Number x
 * another value of sel will return the first large prime of x
 * @param x
 * @param sel
 * @return
 */
int prime (int x,int sel)
{
    if (sel==0)
    {
        while(!is_prime(--x));
        return x;
    }
    else
    {
        while(!is_prime(++x));
        return x;
    }
}
/**
 * remove patient from Hash also using Hashing
 * @param array1
 * @param Name
 */
void remove_element(struct information*array1,char Name[MAX_CHAR])
{
    unsigned int key = hash(Name);
    unsigned int hash_1 = hash1(key);
    unsigned int hash_2 = hash2(key);
    unsigned int index ;

    if (counter == 0)
    {
        printf("\n Hash Table is empty \n");
        return;
    }

    /* probing through other elements */
    for (int i = 0; i < counter; ++i)
    {
        index =  (hash_1 + i * hash_2) % counter;
        if (strcasecmp(array1[index].Name, Name)==0)
        {
            printf("\n The patient %s has been removed \n", Name);
            array1[index].Name[0] = '\0';
            size_table--;
            return;
        }
        if ((unsigned int (*)(unsigned int)) index == hash1)
        {
            break;

        }
    }
    printf("\n (%s) does not exist \n",Name);

}
/**
 * Ask user to enter information of new  Patient and if patient Already found in record will not add him again
 * @param table
 * @param flag
 */
void insert_New_Hash(struct information*table,int *flag)
{

    char Name[MAX_CHAR];

    char Gender[MAX_CHAR];

    char Date_of_admission[MAX_CHAR];

    char Date_of_birth[MAX_CHAR];

    char Illness[MAX_CHAR];

    char Address[MAX_CHAR];

    char Blood[MAX_CHAR];

    printf("Please Enter Name of patient : ");

    scanf(" %[^\n]s", Name);

    printf("\nPlease Enter Gender of patient : ");

    scanf(" %[^\n]s", Gender);
    while (strcasecmp(Gender,"F")!=0&&strcasecmp(Gender,"M")!=0)
    {
        printf("\nPlease enter Valid Gender M of :Male or F  of  : Female : ");
        scanf(" %[^\n]s", Gender);
    }

    printf("\nPlease Enter Date of admission of patient (ddmmyyyy): ");

    scanf(" %[^\n]s",  Date_of_admission);

    printf("\nPlease Enter  Date of birth of patient (ddmmyyyy): ");

    scanf(" %[^\n]s",  Date_of_birth);

    printf("\nPlease Enter  Illness  of patient : ");

    scanf(" %[^\n]s",  Illness);
    push(&Illness_list,Illness);
    printf("\nPlease Enter  Address of patient : ");

    scanf(" %[^\n]s",  Address);

    printf("\nPlease Enter  Blood of patient : ");

    scanf(" %[^\n]s", Blood);
    while (strcasecmp(Blood,"A+")!=0&&strcasecmp(Blood,"A-")!=0&&strcasecmp(Blood,"B+")!=0&&strcasecmp(Blood,"B-")!=0
            &&strcasecmp(Blood,"O+")!=0&&strcasecmp(Blood,"O-")!=0 &&strcasecmp(Blood,"AB+")!=0&&strcasecmp(Blood,"AB-")!=0)
    {
        printf("\nPlease enter Valid type of Blood : ");
        scanf(" %[^\n]s", Blood);
    }
    insert_Hash(table,Name,Gender,Date_of_admission,Date_of_birth,Illness,Address,Blood,flag);
}
/**
 * Search  in Hash table And Search depend in Double Hashing
 * @param table
 * @param Name
 */
void search(struct information*table,char Name[MAX_CHAR])
{

    unsigned int key =hash(Name);
    unsigned int index1= hash1(key);
    unsigned int index2= hash2(key);
    unsigned int index;
    char Data[CHAR_MAX];
    for (int i = 0; i < counter; ++i)
    {
        index = (index1 + i * index2) % counter;
        if (strcasecmp(table[index].Name,Name)==0)
        {
            printf("\nThe patient exist in the  Record and This information for him :");
            printf("\n*********************************************************\n");
            printf("\nName: %s\n",table[index].Name);
            printf("Gender: %s\n", table[index].Gender);
            printf("Date of admission(ddmmyyyy): %s\n", table[index].Date_of_admission);
            printf("Date of birth(ddmmyyyy): %s\n", table[index].Date_of_birth);
            printf("Illness: %s\n",table[index].Illness);
            printf("Address: %s\n", table[index].Address);
            printf("Blood: %s\n", table[index].Blood);
            printf("*********************************************************\n");
            printf("do you want to Update information for patient ? enter y if yes : ");
            scanf(" %[^\n]s", Data);
            if (Data[0] == 'y' || Data[0] == 'Y')
            {
                menu3();
                int select;
                printf("Please enter :");
                while (scanf("%d",&select) != 1)
                {

                    printf("\nplease enter again : ");
                    while(getchar() != '\n');

                }
                while (select != 8)
                {
                    switch (select)
                    {
                    case 1:
                        printf("\nPlease Enter new Name of patient : ");
                        scanf(" %[^\n]s",  Data);
                        strcpy(table[index].Name, Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 2:
                        printf("\nPlease Enter new Gender of patient : ");
                        scanf(" %[^\n]s",  Data);
                        while (strcasecmp( Data,"F")!=0&&strcasecmp( Data,"M")!=0)
                        {
                            printf("\nPlease enter Valid Gender M of :Male or F  of  : Female : ");
                            scanf(" %[^\n]s",  Data);
                        }
                        strcpy(table[index].Gender, Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 3:

                        printf("\nPlease Enter new Date of admission of patient (ddmmyyyy) : ");
                        scanf(" %[^\n]s",  Data);
                        strcpy(table[index].Date_of_admission, Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 4:
                        printf("\nPlease Enter new  Date of birth of patient (ddmmyyyy) : ");

                        scanf(" %[^\n]s",  Data);
                        strcpy(table[index].Date_of_birth,  Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 5:
                        printf("\nPlease Enter new   Illness  of patient : ");
                        scanf(" %[^\n]s",  Data);
                        deleteNode_list(&Illness_list,table[index].Illness);
                        strcpy(table[index].Illness,  Data);
                        push(&Illness_list, Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 6:
                        printf("\nPlease Enter  Address of patient : ");
                        scanf(" %[^\n]s",  Data);
                        strcpy(table[index].Address,  Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 7:
                        printf("\nPlease Enter new  Blood of patient : ");
                        scanf(" %[^\n]s",  Data);
                        while (strcasecmp( Data,"A+")!=0&&strcasecmp( Data,"A-")!=0&&strcasecmp( Data,"B+")!=0&&strcasecmp( Data,"B-")!=0
                                &&strcasecmp( Data,"O+")!=0&&strcasecmp( Data,"O-")!=0 &&strcasecmp( Data,"AB+")!=0&&strcasecmp( Data,"AB-")!=0)
                        {
                            printf("\nPlease enter Valid type of Blood : ");
                            scanf(" %[^\n]s", Data);
                        }
                        strcpy(table[index].Blood,  Data);
                        printf("Thank you!\n");
                        printf("**********************************************\n");
                        break;
                    case 8:
                        return;
                    default:
                        printf("Please enter from menu!!\n");

                    }

                    menu3();
                    printf("Please enter :");
                    while (scanf("%d",&select) != 1)
                    {

                        printf("\nplease enter again : ");
                        while(getchar() != '\n');

                    }
                }
            }
            else
                return;
        }
    }
}
/**
 * re hashing Hash table if factor is 75%
 * @param Hash
 * @return
 */
struct information* re_Hashing(struct information* Hash)
{
    struct information*New_Hash;
    counter=prime(2*counter,1);
    prime_size= prime(counter,0);
    New_Hash=(struct information*) malloc(counter* sizeof(struct information));
    int initial = 0;
    while (initial < counter)
    {
        New_Hash[initial].Name[0] = '\0';
        initial++;
    }
    unsigned Hash1,Hash2,key,index;
    for (int i = 0; i < counter; ++i)
    {
        if (Hash[i].Name[0]!='\0')
        {
            key= hash(Hash[i].Name);
            Hash1= hash1(key);
            Hash2= hash2(key);
            for (int j = 0; j < counter; ++j)
            {
                index = (Hash1 + j * Hash2) % counter;
                if (New_Hash[index].Name[0]=='\0')
                {
                    strcpy(New_Hash[index].Name, Hash[i].Name);
                    strcpy(New_Hash[index].Date_of_birth, Hash[i].Date_of_birth);
                    strcpy(New_Hash[index].Date_of_admission, Hash[i].Date_of_admission);
                    strcpy(New_Hash[index].Gender, Hash[i].Gender);
                    strcpy(New_Hash[index].Address,Hash[i]. Address);
                    strcpy(New_Hash[index].Blood, Hash[i].Blood);
                    strcpy(New_Hash[index].Illness, Hash[i].Illness);
                    break;
                }

            }
            remove_element(Hash,Hash[i].Name);
        }
    }
    return New_Hash;
}
