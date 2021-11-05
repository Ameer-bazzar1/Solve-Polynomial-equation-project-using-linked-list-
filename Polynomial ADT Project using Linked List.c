#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAX_CHAR 100
char *INPUTDATA="equations.txt";
char *OUTDATA="results.txt";
struct Node{
    double coefficient;
    int  power;
    struct Node *next;
    struct Node *prev;
};

struct Node *inputData[1000];

FILE *input;
FILE *output;

int count=0;

struct Node *sum_sub(struct Node *head2,struct Node *head1,char sign [1]);

int  readFile();

int split(struct Node *list,char Data[MAX_CHAR]);

int number_of_X(char *str);

void remove_Spaces(char *str);

void fill(struct Node *list, char *cof, char *pow, char sign[1]);

struct Node *split_sort(struct Node *head);

struct Node *merge(struct Node *firsthalf, struct Node *secondhalf);

struct Node *mergeSort(struct Node *head);

void print(struct Node *head);

void insert(struct Node** head, double x,  int y);

struct Node *mul(struct Node *head2,struct Node *head1);

void Substitute(struct Node*result1);

void Preform_operations();

void Display_menu();

struct Node*case4();

struct Node *final_result(struct Node *head);

void print_in_File();

struct Node* case5();

struct Node* case3();

struct Node*mul_constant(struct Node*head1,double value,int *check);

struct Node*Add_constant(struct Node*head1,double value,int *check);

void start();

int main() {
    start();
}
/**
 * this function to print the menu and ask user to enter anything from menu
 */
void start(){
    int counter,select,value,ins,check;
    char Data[MAX_CHAR],Data1[MAX_CHAR];
    int num,i=0;
    struct Node*result;
    readFile();
    //this is to show what the menu contain
    Display_menu();
    /**
     *   this while to handle errors from user example if him enter 'a'
     *    its error because must enter integer and make sure he read a file Firstly
     */
    while (scanf("%d",&select) != 1||(select<0 || select>4)){

        printf("please enter again : ");
        while(getchar() != '\n');

    }
    while (1) {

        switch (select) {

            case 0 :
                exit(0);
            case 1:
                counter=0;
                while (counter<count) {
                    printf("\nequation %d : ",counter+1);
                    print(inputData[counter]);
                    ++counter;
                }
                printf("\n");

                break;

            case 2:
                Preform_operations();
                while(( scanf("%d",&select)!=1 )||(select<0 || select>5))
                {
                    printf("Please enter an integer: ");
                    while(getchar() != '\n');
                }

                while (select!=0) {
                    switch (select) {
                        case 1:
                            result=case3();
                            printf("\nThe sum of the equations is : ");
                            print(result);
                            printf("do you want to substitute the x value ? enter y if yes : ");
                            scanf(" %[^\n]s", Data);
                            if (strcasecmp(Data,"y")==0) {
                                Substitute(result);
                                result=NULL;
                                break;
                            } else {
                                result = NULL;
                                break;
                            }
                        case 2:
                            result=case4();
                            printf("\nThe subtraction of the equations is : ");
                            print(result);
                            printf("do you want to substitute the x value ? enter y if yes : ");
                            scanf(" %[^\n]s", Data);
                            if (strcasecmp(Data,"y")==0) {
                                Substitute(result);
                                result=NULL;
                                break;
                            } else {
                                result = NULL;
                                break;
                            }
                        case 3:
                            result=case5();
                            printf("\n The multiplication is : ");
                            print(result);
                            printf("do you want to substitute the x value ? enter y if yes : ");
                            scanf(" %[^\n]s", Data);
                            if (strcasecmp(Data,"y")==0) {
                                Substitute(result);
                                result=NULL;
                                break;
                            } else {
                                result = NULL;
                                break;
                            }
                        case 4:
                            printf("please choose one equation:");
                            while (scanf("%d",&value) != 1){
                                printf("please enter again : ");
                                while(getchar() != '\n');
                            }
                            printf("please enter the value : ");
                            while (scanf(" %d", &ins)!= 1){
                                printf("please enter again : ");
                                while(getchar() != '\n');
                            }
                            check=1;
                            inputData[value-1]=mul_constant(inputData[value-1],ins,&check);
                            if (check==0){
                                break;
                            } else {
                                printf("\n Result  is : ");
                                print(inputData[value-1]);
                                printf("do you want to substitute the x value ? enter y if yes : ");
                                scanf(" %[^\n]s", Data);
                                if (strcasecmp(Data,"y")==0) {
                                    Substitute(inputData[value-1]);
                                    result = NULL;
                                    break;
                                } else {
                                    result = NULL;
                                    break;
                                }
                            }
                        case 5:
                            printf("please choose one equation:");
                            while (scanf("%d",&value) != 1){
                                printf("please enter again : ");
                                while(getchar() != '\n');
                            }
                            printf("please enter the value : ");
                            while (scanf(" %d", &ins)!= 1){
                                printf("please enter again : ");
                                while(getchar() != '\n');
                            }
                            check=1;
                            inputData[value-1]=Add_constant(inputData[value-1],ins,&check);
                            if (check==0){
                                break;
                            } else {
                                printf("\n Result  is : ");
                                print(inputData[value-1]);
                                printf("do you want to substitute the x value ? enter y if yes : ");
                                scanf(" %[^\n]s", Data);
                                if (strcasecmp(Data,"y")==0) {
                                    Substitute(inputData[value-1]);
                                    result = NULL;
                                    break;
                                } else {
                                    result = NULL;
                                    break;
                                }
                            }
                    }
                    Preform_operations();
                    while(( scanf("%d",&select)!=1 )||(select<0 || select>5))
                    {
                        printf("Please enter an integer: ");
                        while(getchar() != '\n');
                    }
                }
                break;
            case 3:
                printf("How many equations do you want to add : ");
                while (scanf("%d",&num) != 1){
                    printf("please enter integer .");
                    printf("\n enter again : ");
                    while(getchar() != '\n');
                }
                while (num > 0) {

                    printf("Enter Equation %d: ",i+1);

                    scanf(" %[^\n]s", Data);
                    if (Data[0] == '\n') {
                        continue;
                    }
                    //This to remove spaces from every equation
                    remove_Spaces(Data);
                    strcpy(Data1,Data);
                    //create new doubly linked to store him the equation
                    inputData[count] = (struct Node *) malloc(sizeof(struct Node));

                    inputData[count]->next = NULL;

                    //if the value return from the function split not equal 0 then the equation not Polynomial
                    if (split(inputData[count], Data) != 0) {
                        input = fopen(INPUTDATA, "a");
                        fputs("\n",input);
                        fputs(Data1,input);
                        inputData[count] = mergeSort(inputData[count]->next);
                        count++;
                        fclose(input);
                    } else {
                        printf("you are enter a not valid equation of polynomial in equation number %d  ", count + 1);
                        exit(0);
                    }
                    num--;
                    i++;
                }
                printf("All equation are loaded to the file equations.txt Thank you!");
                break;

            case 4:
                print_in_File();
                break;
        }

        Display_menu();

        while(( scanf("%d",&select)!=1 )||(select<0 || select>4))
        {
            printf("Please enter an integer: ");
            while(getchar() != '\n');
        }
    }

}
/**
 * this function is contain the menu
 */
void Display_menu(){

    printf("\nMain options:\n"
           "*************************************************\n"
           "*  1- Print The Equations On The Screen.        *\n"
           "*  2- Preform operations.                       *\n"
           "*  3- insert new Equation.                      *\n"
           "*  4- set output of all operation in The File.  *\n"
           "*  0- Exit.                                     *\n"
           "*************************************************"
           "\nPlease select the option from menu : ");

}
void Preform_operations(){
    printf("Preform operations :\n"
           "*************************************************\n"
           "*  1- Find The Addition Of The Equations.        *\n"
           "*  2- Find The Subtraction Of The Equations.     *\n"
           "*  3- Find The Multiplication Of The Equations.  *\n"
           "*  4- it multiplies an equation with a constant. *\n"
           "*  5- addition of equation with a constant.      *\n"
           "*  0- Close.                                     *\n"
           "*************************************************\n"
           "Please select the option from menu : ");
}
/**
 * Multiplication any equation with a constant
 * time complicity is o(n)
 * @param head1
 * @param value
 * @return
 */
struct Node*mul_constant(struct Node*head1,double value,int *check){
    struct Node*temp=NULL;
    double z;
    *check=1;
    struct Node*temp1=head1;
    if (head1!=NULL) {
        while (temp1 != NULL) {
            z = temp1->coefficient *value;
            insert(&temp, z, temp1->power);
            temp1=temp1->next;
        }
    } else{
        printf("you enter invalid number of equation\n");
        *check=0;
        return NULL;
    }
    printf("\n please Be Careful equation have been saved in the main list");
    temp= mergeSort(temp);
    return temp;
}
/**
 * Addition any equation with a constant
 * time complicity is o(n)
 * @param head1
 * @param value
 * @return
 */
struct Node*Add_constant(struct Node*head1,double value,int *check) {
    struct Node *temp = NULL;
    double z;
    *check=1;
    struct Node *temp1 = head1;
    if(head1 != NULL) {
        while (temp1!=NULL) {
            if (temp1->power == 0) {
                //sum  coefficient
                z = temp1->coefficient + value;
                //insert the result of the sum in the list
                insert(&temp, z, temp1->power);
            } else {
                insert(&temp, temp1->coefficient, temp1->power);
            }
            temp1 = temp1->next;
        }
    }else {
        printf("you enter invalid number of equation\n");
        *check=0;
        return NULL;
    }
    printf("\n please Be Careful equation have been saved in the main list");
    temp = mergeSort(temp);
    return temp;
}
/**
 * this function to find sum all equation
 * and iam using mergesort to sort border equation Descending depending on a power
 * and the function final_result to sum all border with the same power
 * and must the equation is sorted  to get a correct answer
 * this reason to sort border and i make him for every loop since i need
 * reduce the number of border of equation
 * and the time complicity is O(n^2) i know can less him but i need different ideas
 * the best case is (n log n);
 * @return result_sum
 */
struct Node* case3(){

    struct Node *result_sum=NULL;

    for (int i = 0; i < count; i=i+1) {
        result_sum=sum_sub(inputData[i], result_sum,"+");
        result_sum=mergeSort(result_sum);
        result_sum= final_result(result_sum);
    }
    return result_sum;
}
/**
 * this function to find subtraction all equation
 * and iam using mergesort to sort border equation Descending depending on a power
 * and the function final_result to sum all border with the same power
 * and must the equation is sorted  to get a correct answer
 * this reason to sort border and i make him for every loop since i need
 * reduce the number of border of equation
 * and the time complicity is O(n^2)
 * the best case is (n log n);
 * @return result_sub
 */
struct Node* case4(){

    struct Node *result_sub=NULL;
    for (int i = 0; i < count; i=i+1) {
        result_sub =sum_sub(result_sub,inputData[i] ,"-");
        result_sub =mergeSort(result_sub);
        result_sub =  final_result(result_sub);
    }

    return result_sub;
}
/**
 * this function to find multiplication all equation
 * and iam using mergesort to sort border equation Descending depending on a power
 * and the function final_result to sum all border with the same power
 * and must the equation is sorted  to get a correct answer
 * this reason to sort border and i make him for every loop since i need
 * reduce the number of border of equation
 * and the time complicity is O(n^2)
 * the best case is (n log n);
 * @return result_mul
 */
struct Node* case5(){

    struct Node *result_mul=NULL;

    for (int i = 0; i < count; i=i+1) {
        result_mul=mul(result_mul,inputData[i]);
        result_mul=mergeSort(result_mul);
        result_mul=final_result(result_mul);

    }
    result_mul=mergeSort(result_mul);
    result_mul=final_result(result_mul);
    return result_mul;
}
/**
 * this function to insert new Node to doubly linked list
 * and the insert in the beginning and i have reason for this the reason is
 * when i need for example multiplication 500 equation maybe can from multiplication 499 equation have 1000
 * borders when i need multiplication with the equation number 500 and i need add now Node i must
 * move through 1000 Node to insert new Node and this take mush time so i add in the beginning with
 * time complicity O(1)
 * @param head
 * @param cof
 * @param power
 */
void insert(struct Node** head, double cof,  int power)
{
    //create new Node
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //check if the Node is null then the memory is full
    if (temp==NULL)
        printf("out of memory");


    //put the data in Node
    temp->coefficient= cof;

    temp->power=power;

    // set next of new Node as head and previous as NULL //
    temp->next = (*head);
    temp->prev = NULL;

    // change prev of head Node to new Node
    if ((*head) != NULL)
        (*head)->prev = temp;

    // move the head to point to the new Node
    (*head) = temp;
}
/**
 * this function to read the Data from file and
 * split him to store the Data in Doubly linked List
 * and if the function return 0 then we have error in the equation its not  polynomial equation
 * @return
 */
int  readFile() {

    input = fopen(INPUTDATA, "r");

    char Data[MAX_CHAR];

    int count1 = 0;

    //Check if the file is Null this meaning the file not found then exit from program
    if (input == NULL) {

        printf("Error! opening file");

        exit(1);
    }
    else {
        while (!feof(input)) {

            //read line from File
            fgets(Data, MAX_CHAR, input);
            //if found new line then not store him in linked list
            if(Data[0]=='\n'){
                continue;
            }

            //This to remove spaces from every equation
            remove_Spaces(Data);

            //create new doubly linked to store him the equation
            inputData[count] = (struct Node *) malloc(sizeof(struct Node));

            inputData[count]->next = NULL;

            //if the value return from the function split not equal 0 then the equation not Polynomial
            if (split(inputData[count], Data) != 0) {
                count++;
            } else {
                printf("you are enter a not valid equation of polynomial in equation number %d  ",count+1);
                return 0;
            }
        }

    }
    //this to sort all equation read from file  Descending depending on a power
    while (count1 < count) {

        inputData[count1] = mergeSort(inputData[count1]->next);
        ++count1;
    }

    fclose(input);
    return 1;
}
/**
 * This function will remove all space in the equation
 * @param str
 */
void remove_Spaces(char *str) {
    /*
     * keep counter  incremented until found space
     * If current character
     * is not space then place it at index counter
     * If the character encountered is an empty space, skip the character.
     */
    int counter1 = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' '){
            str[counter1] = str[i];
            counter1++;
        }
    str[counter1] = '\0';
}
/**
 * this function to split every  equation  read from file
 * to power and coefficient and sent him to function fill to fill him in doubly linked list
 * and the function will return 1 if the equation is Polynomial and zero For others
 * @param list
 * @param Data
 * @return
 */
int split(struct Node *list,char Data[MAX_CHAR]){

    char *str;

    char str2[MAX_CHAR];

    int x;

    int y;

    //set the str2 with same string of Data
    strcpy(str2,Data);

    int flag=-1;
    /*
     * This to check if the first coefficient from the equation is negative or not
     * if is negative set the flag is equal 1 and set y 1
     * */
    if (str2[0]=='-') {

        y = 1;

        flag=1;
    }
    /*
     * this to check if the first coefficient from the equation not negative
     * set the flag equal 1
     * */
    if ((str2[0]!='+'||str2[0]=='+')&&str2[0]!='-') {
        flag=2;
    }
    //here iam split every equation depends the "+-"
    str=strtok(Data,"+-");

    while (str!=NULL){

        char cof[10]={ '\0' };

        char pow[10]={ '\0' };

        char  equ[10]={ '\0' };

        //every string splitting set him in equ
        strcpy(equ,str);

        // this function return the index of 'x' or 'X'
        x=number_of_X(equ);

        //here iam copy from equ number of char x and this will give the Polynomial and store him in cof
        strncpy(cof,equ,x);

        //and here str[x+2] will give me the power  and store him in pow
        strcpy(pow,&str[x+2]);

        /*
         * here i check if the equation is  Polynomial  or Not i mean
         *  for example if we have the following equation 2x+x^-1
         *  this is not Polynomial equation since the power its negative
         *  and this can not in Polynomial equation
         *
         * */
        if (str[x+1]=='^'&&!isdigit(str[x+2])){
            return 0;
        }

        /*
         * here if x is zero so no coefficient in another words the first is 'x'
         * and this its meaning the coefficient its 1
         * */
        if(x==0)
            strcpy(cof,"1");
        /*
         * check if we not have the symbolic '^' then the power its one and set 1 in pow
         */
        if (str[x+1]!='^')
            strcpy(pow, "1");
        /*
         * check if not found the symbolic 'x' or 'X' then the power its zero and set 0 in pow
         */
        if(str[x]!='x'&&str[x]!='X')
            strcpy(pow, "0");

        //  if the flag is 2 the meaning the first coefficient in the equation its positive
        if (flag==2)
            //here i send the first border with sign of coefficient
            fill(list,cof,pow,"+");

            //if the flag is 1 then the  first coefficient in the equation is negative
        else if (flag==1)
            //here i send the first border with sign of coefficient
            fill(list,cof,pow,"-");
            /*
             * check the sign  coefficient for other borders through a
             * get the length for every border and sum him
             * */
        else if (str2[y-1]=='+')
            //sent the border to fill him in doubly linked list
            fill(list,cof,pow,"+");
        else
            fill(list,cof,pow,"-");

        //sum the length for every border are split
        y = y + (strlen(str)) + 1;

        str=strtok(NULL,"+-");

        flag=-1;
    }
    return 1;
}
/**
 * this function will return the index of x in the border
 * @param str
 * @return Y
 */
int number_of_X(char *str){

    int x=0,y=0;

    while (x<strlen(str)){

        if(str[x]!='x'&&str[x]!='X')
            ++y;
        else
            break;
        ++x;
    }
    return y;
}
/**
 * store the equation to double linked list
 */
void fill(struct Node *list, char *cof, char *pow, char sign[1]) {

    //convert the coefficient  from the string to number
    double x=atoi(cof);

    //convert the power  from the string to number
    int y=atoi(pow);

    //check if the sign is '-' then the coefficient  is negative
    if ( strcmp(sign ,"-")==0)
        x=x*-1;

    //create new Node to insert the border to th linked list
    struct Node*temp=(struct Node*)malloc(sizeof(struct Node));

    //if Node is Null then the memory is full!
    if (temp==NULL)
        printf("out of space ! \n");

    temp->coefficient=x;

    temp->power=y;

    //insert in the last of list
    while (list->next!=NULL)
        list=list->next;

    temp->prev=list;

    list->next=temp;

    temp->next=NULL;
}
/**
 * this function will found the summation and subtraction between two equation
 * depends the sign  and will return the result of this
 * equation but this function will sum the borders with the same power just
 * and with the same number
 * of borders and from the function final_result will give the final result
 * time complicity is O(n)
 * @param head2
 * @param head1
 * @param sign
 * @return temp
 */
struct Node *sum_sub(struct Node *head1,struct Node *head2,char sign [1]){
    struct Node*temp=NULL;
    double z;

    while (head1 != NULL && head2 != NULL) {

        //if sign is '+' then will summation for equations

        if (strcmp(sign ,"+")==0) {

            //if the power is equal for two borders will go to summation
            if (head1->power == head2->power) {

                //sum two coefficient for two borders and store result in z
                z = head1->coefficient + head2->coefficient;

                //insert the result of two borders in the list
                insert(&temp, z, head1->power);
            }
            else  {

                //now since two borders not same power will insert him to list
                insert(&temp, head1->coefficient, head1->power);
                insert(&temp, head2->coefficient, head2->power);
            }

            //move the equation one and second equation to next borders
            head1 = head1->next;
            head2 = head2->next;
        }

            //since the sign is '-' will go to subtraction
        else if (strcmp(sign ,"-")==0){

            //if the power is equal for two borders will go to subtraction
            if (head1->power == head2->power) {

                //subtraction two coefficient for two borders and store result in z
                z = head1->coefficient - head2->coefficient;

                //insert the result of two borders in the list
                insert(&temp,z,head1->power);
            }
            else{
                /*
                 * now since two borders not same power will insert him to list
                 * and must set the coefficient of second border a negative since the
                 * he  represent second equation and we know the first equation - second equation
                 * to make subtraction
                 * */
                z=(head2->coefficient);
                z=z*-1;
                insert(&temp,(head1->coefficient),head1->power);
                insert(&temp,z,head2->power);
            }
            //move the equation one and second equation to next borders
            head1= head1->next;
            head2 = head2->next;
        }
    }
    /*
     * here will check if any of two equation  is null and second not will add him to list
     * this for if the number of borders of any equation more than other will insert the
     * borders direct to list
     * */
    while (head1 || head2) {
        if (head1 != NULL) {
            insert(&temp,head1->coefficient,head1->power);
            head1 = head1->next;
        } else {
            insert(&temp, head2->coefficient, head2->power);
            head2 = head2->next;
        }
    }
    return temp;
}
/**
 * this function will found the time complicity is O(n) between two equation
 * and the multiplication will the multiplication of borders
 * and here will the number of borders Will decrease through a function final_result its
 * summation the borders with  the same power
 * time complicity is O(n^2)
 * @param head2
 * @param head1
 * @return temp
 */
struct Node *mul(struct Node *head2,struct Node *head1){
    struct Node*temp=NULL;
    int pow;
    double z;
    struct Node*temp1=head1;
    struct Node*temp2=head2;

    //check if two list are not Null
    if (head1!=NULL&&head2!=NULL) {

        //now will multiplication the every border of equation 1 with the all borders of equation 2
        while (temp1 != NULL) {
            while (temp2 != NULL) {

                //will found the multiplication of coefficient of two equation and store the result in z
                z = temp1->coefficient * temp2->coefficient;

                //since this operation is multiplication  and multiplication  in  polynomial will add the power
                pow = temp1->power + temp2->power;

                //insert every border in list
                insert(&temp, z, pow);

                //move the border of equation number 2 to next border
                temp2 = temp2->next;
            }
            //since head2 here is NUll since in before will arrive the last border i will return he to equation number 2
            temp2=head2;
            //move the border of first equation to  next border
            temp1=temp1->next;
        }
    } else {
        /*
        * here will check if any of two equation  is null and second not will add him to list
        * this for if the number of borders of any equation more than other will insert the
        * borders direct to list
        * */
        while (head1 || head2) {
            if (head1 != NULL) {
                insert(&temp, head1->coefficient, head1->power);
                head1 = head1->next;
            } else {
                insert(&temp, head2->coefficient, head2->power);
                head2 = head2->next;
            }
        }
    }
    return temp;
}

/**
 * this function to provide a choice for a user to Substitute value
 * after operation Addition or Subtraction or Multiplication
 */
void Substitute(struct Node*result1){
    double x;
    double c=0;
    //here if choice 1 so he need Substitute value after  Addition

    printf("Please enter a Value : ");
    while((scanf("%lf",&x)!=1 ))
    {
        printf("Please enter an integer: ");
        while(getchar() != '\n');
    }
    while (result1!=NULL){

        //here i will Substitute value for every border
        c=c+(pow(x,result1->power))*(result1->coefficient);

        result1=result1->next;
    }

    printf("\nThe result after Substitute is  : %0.1lf\n",c);

}



/**
 * this function to grouping boundaries with same power
 * @param head
 * @return
 */
struct Node *final_result(struct Node *head) {

    struct Node *list = (struct Node *) malloc(sizeof(struct Node));

    list->prev = NULL;
    int flag=0;
    struct Node* tempzero=NULL;
    struct Node *temphead = head;

    struct Node *templist = list;

    while (temphead != NULL) {

        templist->coefficient = 0;

        templist->power = temphead->power;
        if (temphead->coefficient==0){
            temphead = temphead->next;
            continue;
        }
        while (temphead != NULL && templist->power == temphead->power) {
            flag=1;
            templist->coefficient += temphead->coefficient;

            temphead = temphead->next;
        }

        if (templist->coefficient != 0) {
            templist->next = (struct Node *) malloc(sizeof(struct Node));
            templist->next->prev = templist;
            templist = templist->next;
        }
    }

    templist = templist->prev;
    if (flag==0) {
        insert(&tempzero,0,0);
        return tempzero;
    } else {
        free(templist->next);
        templist->next = NULL;
    }
    return list;
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

    if (firsthalf->power < secondhalf->power)
    {
        secondhalf->next = merge(firsthalf,secondhalf->next);
        secondhalf->next->prev = secondhalf;
        secondhalf->prev = NULL;
        return secondhalf;
    }
    else
    {
        firsthalf->next = merge(secondhalf,firsthalf->next);
        firsthalf->next->prev = firsthalf;
        firsthalf->prev = NULL;
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
void print(struct Node *head)
{
    int flag=1;
    while (head) {
        if (head->power != 0 && head->power != 1) {
            if (head->coefficient == 1) {
                printf("X^%d", head->power);
                flag = 0;
            } else if (head->coefficient != 0)  {
                printf("%.6gX^%d", head->coefficient, head->power);
                flag = 0;
            }
        } else if (head->power == 1) {
            if (head->coefficient == 1) {
                flag = 0;
                printf("X");
            } else if (head->coefficient != 0){
                flag = 0;
                printf("%.6gX", head->coefficient);
            }
        }
        else if (head->coefficient != 0) {
            flag = 0;
            printf("%.6g", head->coefficient);
        }
        head = head->next;
        if (head != NULL&&flag==0)
            printf(" + ");
    }
    if (flag==1){
        printf("0");
    }
    printf("\n");
}

void print_in_File()
{
    output=fopen(OUTDATA,"w");

    if (output == NULL) {

        printf("Error! opening file");

        exit(1);
    }
    fprintf(output,"The sum of the equations is : \n");
    int flag=1;
    struct Node * result=case3();
    while (result){
        if (result->power != 0 && result->power != 1) {
            if (result->coefficient == 1){
                fprintf(output, "X^%d", result->power);
                flag = 0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX^%d", result->coefficient, result->power);
            }
        } else if (result->power == 1) {
            if (result->coefficient == 1) {
                fprintf(output, "X");
                flag=0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX", result->coefficient);
            }
        }  else if (result->coefficient != 0) {
            flag = 0;
            fprintf(output,"%.6g", result->coefficient);
        }
        result= result->next;
        if(result != NULL&&flag==0)
            fprintf(output," + ");
    }
    if (flag==1)
        fprintf(output,"0\n");

    flag=1;
    result=NULL;
    result=case4();
    fprintf(output,"\nThe subtraction of the equations is : \n");
    while (result){
        if (result->power != 0 && result->power != 1) {
            if (result->coefficient == 1){
                fprintf(output, "X^%d", result->power);
                flag = 0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX^%d", result->coefficient, result->power);
            }
        } else if (result->power == 1) {
            if (result->coefficient == 1) {
                fprintf(output, "X");
                flag=0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX", result->coefficient);
            }
        }  else if (result->coefficient != 0) {
            flag = 0;
            fprintf(output,"%.6g", result->coefficient);
        }
        result= result->next;
        if(result != NULL&&flag==0)
            fprintf(output," + ");
    }
    if (flag==1)
        fprintf(output,"0\n");

    flag=1;
    result=NULL;
    result=case5();
    fprintf(output,"\nThe multiplication is : \n");
    while (result){
        if (result->power != 0 && result->power != 1) {
            if (result->coefficient == 1){
                fprintf(output, "X^%d", result->power);
                flag = 0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX^%d", result->coefficient, result->power);
            }
        } else if (result->power == 1) {
            if (result->coefficient == 1) {
                fprintf(output, "X");
                flag=0;
            }
            else if (result->coefficient != 0){
                flag = 0;
                fprintf(output,"%.6gX", result->coefficient);
            }
        }  else if (result->coefficient != 0) {
            flag = 0;
            fprintf(output,"%.6g", result->coefficient);
        }
        result= result->next;
        if(result != NULL&&flag==0)
            fprintf(output," + ");
    }
    if (flag==1)
        fprintf(output,"0\n");

    printf("Thank you all result now in the File !\n");
    fclose(output);
}
