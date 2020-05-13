/*
При реализации стека массивом располагать два
стека в одном массиве. Один стек располагается
в начале массива и растет к концу, а другой
располагается в конце массива и растет к началу.
Заполнять и освобождать стеки произвольным
образом с экрана. Элементами стека являются
вещественные числа. Списком реализовать один
стек.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define AR_MAX_SIZE 5
#define AR_MAX_SIZE_CHECK 10

#define AR_MAX_FOR_CHECK 10000

#define STACK_OVERFLOW -100.0
#define STACK_UNDERFLOW -101.0

typedef struct
{
    float data[AR_MAX_SIZE];
    int size_head;
    int size_bot;
}arr_stack;

typedef struct
{
    float data[AR_MAX_FOR_CHECK];
    int size_head;
    int size_bot;
}arr_stack_for_check;

typedef struct list_stack
{
    float value;
    struct list_stack *next;
}l_stack;

// Push and Pop for head
void push_arr_head(arr_stack *main_stack);
void pop_arr_head(arr_stack *main_stack);

// Push and Pop for botton
void push_arr_bot(arr_stack *main_stack);
void pop_arr_bot(arr_stack *main_stack);

// Seeout for mass stack
void output_stack(arr_stack main_stack);

// Operations with list stack
void push_list(l_stack **head, int **mas);
void pop_list(l_stack **head, int **mas_adr, int **mas_del);
void print_list(l_stack *head, int **mas_adr, int **mas_del);
void out_adress(int **mas);
void out_del(int **mas);
void free_list(l_stack **head);

// Check time
void check_time();
void push_arr_head_for_check(arr_stack_for_check *main_stack, float value);
void push_arr_bot_for_check(arr_stack_for_check *main_stack, float value);
void pop_arr_bot_for_check(arr_stack_for_check *main_stack);
void pop_arr_head_for_check(arr_stack_for_check *main_stack);
void push_list_for_check(l_stack **head, float value);
void pop_list_for_check(l_stack **head);
void output_stack_for_check(arr_stack_for_check main_stack);


int size_list = 0;
int adr_list = 0;
int del_list = 0;
int size_list_check = 0;

int main()
{
    arr_stack main_stack;
    main_stack.size_head = 0;
    main_stack.size_bot = 0;

    l_stack *head = NULL;
    l_stack *tmp;

    int *adress[AR_MAX_SIZE];
    int *del_adr[AR_MAX_SIZE];

    int var = -1;

    while (var != 0)
    {
        printf("\nMENU (choose operation):\n"
               "0 - Exit\n\n"
               "Array stack head:\n"
               "1 - Push to array stack\n"
               "2 - Pop from stack\n\n"
               "Array stack bottom\n"
               "3 - Push to array stack\n"
               "4 - Pop from stack\n\n"
               "Operations with array stack\n"
               "5 - Output stack\n\n"
               "List stack:\n"
               "6 - Push to stack\n"
               "7 - Pop from stack\n"
               "8 - Output stack\n\n"
               "Check time for arr and list\n"
               "9 - Check time\n");

        printf("\nInput your choice - ");
        int check_var = scanf("%d", &var);
        if (check_var = 1)
        {
            if (var == 1)
                push_arr_head(&main_stack);
            else if (var == 2)
                pop_arr_head(&main_stack);
            else if (var == 3)
                push_arr_bot(&main_stack);
            else if (var == 4)
                pop_arr_bot(&main_stack);
            else if (var == 5)
                output_stack(main_stack);
            else if (var == 6)
                push_list(&head, adress);
            else if (var == 7)
                pop_list(&head, adress, del_adr);
            else if (var == 8)
                print_list(head, adress, del_adr);
            else if (var == 9)
                check_time();
            else
                printf("Wrong number!\n");
        }
        printf("\n\n\n");
        getchar();
    }
    free_list(&head);
    return 0;
}

void check_time()
{
    arr_stack_for_check main_stack;
    main_stack.size_head = 0;
    main_stack.size_bot = 0;
    l_stack *head = NULL;
    l_stack *tmp;

    clock_t begin = clock();
    for (int i = 0; i < AR_MAX_FOR_CHECK; i++)
    {
        if (i % 2)
            push_arr_head_for_check(&main_stack, (0 + rand() % 50));
        else
            push_arr_bot_for_check(&main_stack, (0 + rand() % 50));
    } 
    
    for (int i = 0; i < AR_MAX_FOR_CHECK; i++)
    {
        if (i % 2)
            pop_arr_head_for_check(&main_stack);
        else
            pop_arr_bot_for_check(&main_stack);
          
    }  
    clock_t end = clock();
    printf("Result of arr stack is > %.6lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    begin = clock();
    for (int i = 0; i < AR_MAX_FOR_CHECK; i++)
        push_list_for_check(&head, (0 + rand() % 50));
    for (int i = 0; i < AR_MAX_FOR_CHECK; i++)
        pop_list_for_check(&head); 
    end = clock();
    printf("Result of list stack is > %.6lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
}

void push_list_for_check(l_stack **head, float value)
{
    if (size_list_check < AR_MAX_FOR_CHECK)
    {
        l_stack *tmp = malloc(sizeof(l_stack));

        tmp->next = *head;
        tmp->value = value;
        *head = tmp;
        size_list_check++;
    }
}

void pop_list_for_check(l_stack **head)
{
    l_stack *out;

    if (*head != NULL)
    {
        size_list_check--;
        out = *head;
        *head = (*head)->next;
        free(out);
    }
}

void push_arr_head_for_check(arr_stack_for_check *main_stack, float value)
{
    if (main_stack->size_head == AR_MAX_FOR_CHECK - main_stack->size_bot)
        printf("The stack is full!\n");
    else
    {
        main_stack->data[main_stack->size_head] = value;
        main_stack->size_head++;
    }

}

void push_arr_bot_for_check(arr_stack_for_check *main_stack, float value)
{
    if (main_stack->size_head == AR_MAX_FOR_CHECK - main_stack->size_bot)
        printf("The stack is full!\n");
    else
    {
        main_stack->data[AR_MAX_FOR_CHECK - main_stack->size_bot - 1] = value;
        main_stack->size_bot++;
    }
}

void pop_arr_bot_for_check(arr_stack_for_check *main_stack)
{
    if (main_stack->size_bot != 0)
        main_stack->size_bot--;
}

void pop_arr_head_for_check(arr_stack_for_check *main_stack)
{
    if (main_stack->size_head != 0)
        main_stack->size_head--;
    
}

void push_arr_head(arr_stack *main_stack)
{
    printf("\nInput in head stack!\n");
    if (main_stack->size_head == AR_MAX_SIZE - main_stack->size_bot)
        printf("The stack is full!\n");
    else
    {
        float value;
        printf("Input value > ");
        if (scanf("%f", &value) == 1)
        {
            main_stack->data[main_stack->size_head] = value;
            main_stack->size_head++;
        }
        else
            printf("Wrong input!\n");
    }
}

void push_arr_bot(arr_stack *main_stack)
{
    printf("\nInput in bottom stack!\n");
    if (main_stack->size_head == AR_MAX_SIZE - main_stack->size_bot)
        printf("The stack is full!\n");
    else
    {
        float value;
        printf("Input value > ");
        if (scanf("%f", &value) == 1)
        {
            main_stack->data[AR_MAX_SIZE - main_stack->size_bot - 1] = value;
            main_stack->size_bot++;
        }
        else
            printf("Wrong input!\n");
    }
}

void pop_arr_bot(arr_stack *main_stack)
{
    printf("\nPop from stack bottom!\n");
    if (main_stack->size_bot == 0)
        printf("STACK UNDERFLOW!\n");
    else
    {
        main_stack->size_bot--;
        printf("Value > %f\n", main_stack->data[AR_MAX_SIZE - main_stack->size_bot - 1]);
    }
}

void pop_arr_head(arr_stack *main_stack)
{
    printf("\nPop from stack head!\n");
    if (main_stack->size_head == 0)
        printf("STACK UNDERFLOW!\n");
    else
    {
        main_stack->size_head--;
        printf("Value > %f\n", main_stack->data[main_stack->size_head]);
    }
}

void output_stack(arr_stack main_stack)
{
    if (main_stack.size_head > 0)
    {
        printf("Your stack in head > | ");
        for (int i = 0; i < main_stack.size_head; i++)
            printf("%.4f | ", main_stack.data[i]);
        printf("\n");
    }
    else
        printf("Empty stack in head!\n");
    if (main_stack.size_bot > 0)
    {
        printf("Your stack in bottom > | ");
        for (int i = AR_MAX_SIZE - 1; i >= AR_MAX_SIZE - main_stack.size_bot; i--)
            printf("%.4f | ", main_stack.data[i]);
        printf("\n");
    }
    else
        printf("Empty stack in bottom!\n");
}

void output_stack_for_check(arr_stack_for_check main_stack)
{
    if (main_stack.size_head > 0)
    {
        printf("Your stack in head > | ");
        for (int i = 0; i < main_stack.size_head; i++)
            printf("%.4f | ", main_stack.data[i]);
        printf("\n");
    }
    else
        printf("Empty stack in head!\n");
    if (main_stack.size_bot > 0)
    {
        printf("Your stack in bottom > | ");
        for (int i = 300 - 1; i >= 300 - main_stack.size_bot; i--)
            printf("%.4f | ", main_stack.data[i]);
        printf("\n");
    }
    else
        printf("Empty stack in bottom!\n");
}

void push_list(l_stack **head, int **mas)
{
    if (size_list < 5)
    {
        l_stack *tmp = malloc(sizeof(l_stack));
        printf("Input value > ");
        float value = 0;
        if (tmp && scanf("%f", &value) == 1)
        {
            mas[adr_list] = (int*)tmp;
            tmp->next = *head;
            tmp->value = value;
            *head = tmp;
            size_list++;
            adr_list += 1;
        }
    }
    else
        printf("The stack is full!\n");
}

void pop_list(l_stack **head, int **mas_adr, int **mas_del)
{
    l_stack *out;
    float value;

    if (*head != NULL)
    {
        adr_list -= 1;
        size_list--;

        out = *head;
        *head = (*head)->next;
        value = out->value;
        free(out);

        mas_del[del_list] = mas_adr[adr_list];
        del_list++;
        printf("Your value > %f\n", value);
    }
    else
        printf("\nERROR\n");
}

void print_list(l_stack *head, int **mas_adr, int **mas_del)
{
    
    if (head)
    {
        printf("\nYour list > | ");
        while (head)
        {
            printf("%f", head->value);
            printf(" | ");
            head = head->next;
        }
        printf("\n");
        if (adr_list > 0)
        {
            printf("The adress of existing elements > ");
            out_adress(mas_adr);
            printf("\n");
        }
        else
            printf("We couldn't find anything in adress list!\n");
            
    }
    else
    {
        printf("\nThe list is empty!\n");
    }   
    if (del_list > 0)
    {
        printf("The adress of deleted elements > ");
        out_del(mas_del);
    }
    else
        printf("We couldn't find anything in delete list!\n");
}

void out_adress(int **mas)
{
    for (int i = adr_list - 1; i >= 0; i--)
        printf("%p ", mas[i]);
}

void out_del(int **mas)
{
    for (int i = del_list - 1; i >= 0; i--)
        printf("%p ", mas[i]);
}

void free_list(l_stack **head)
{
    l_stack *out;
    while (*head != NULL)
    {
        out = *head;
        *head = (*head)->next;
        free(out);
    }
}

