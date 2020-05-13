#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define AR_MAX_SIZE 20

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101

typedef struct
{
    int data[AR_MAX_SIZE];
    int size;
}arr_stack;

typedef struct list_stack
{
    int value;
    struct list_stack *next;
}l_stack;

void is_pal_a(arr_stack *stack_a, arr_stack *stack_b);
void rewrite_ar(arr_stack *stack_a, arr_stack *stack_b);
void push_ar(arr_stack *stack_a, int value);
int pop_ar(arr_stack *stack_a);
void peek_ar(arr_stack *stack_a);
void rewrite_li(l_stack **head, l_stack **head_n);
void is_pal_l(l_stack **head, l_stack **head_n);
void push_list(l_stack **head, int value, int **mas);
int pop_list(l_stack **head);
void print_list(l_stack *head);
int getSize(l_stack *head);
void out_adress(int **mas);
void out_del(int **mas);


int size_list = 0;
int c = 0;
int d = 0;

int main()
{
    arr_stack stack_a;
    arr_stack stack_b;

    stack_a.size = 0;
    stack_b.size = 0;

    l_stack *head = NULL;
    l_stack *head_n = NULL;
    l_stack *tmp;
    l_stack *tmp_n;

    int array_size;
    int var = 1;

    int *adress[AR_MAX_SIZE];
    int *del_adr[AR_MAX_SIZE];

    while (var != 0)
    {
        printf("\nMENU (choose operation):\n\t"
               "0 - Exit\n\t"
               "Array stack:\n\t"
               "1 - palindrom\n\t"
               "2 - Push to array stack\n\t"
               "3 - Pop from stack\n\t"
               "4 - Output stack\n"
               "List stack:\n\t"
               "5 - Push to stack\n\t"
               "6 - Pop from stack\n\t"
               "7 - Output stack\n\t"
               "8 - palindrom\n");

        
        printf("\nInput your choice - ");
        int check_var = scanf("%d", &var);

        if (check_var == 1)
        {
            if (var == 1)
            {
                if (stack_a.size > 0)
                {
                    rewrite_ar(&stack_a, &stack_b);
                    is_pal_a(&stack_a, &stack_b);
                }
                else
                {
                    printf("\nThe stack is empty\n");
                }
                
            }
            else if (var == 2)
            {
                int value;
                printf("Input value - ");
                int check_value = scanf("%d", &value);

                if (check_value == 1)
                {
                    push_ar(&stack_a, value);
                }
                else
                {
                    printf("\nERROR\n");
                    getchar();
                }
            }
            else if (var == 3)
            {
                int v = pop_ar(&stack_a);
                if (v != STACK_UNDERFLOW)
                    printf("\nVALUE - %d", v);
                printf("\n");
            }
            else if (var == 4)
            {
                peek_ar(&stack_a);
            }


            else if (var == 5)
            {
                int value;
                printf("Input value - ");
                int check_value = scanf("%d", &value);

                if (check_value == 1)
                {
                    push_list(&head, value, adress);
                }
                else
                {
                    printf("\nERROR\n");
                    getchar();
                }
            }
            else if (var == 6)
            {
                int v = pop_list(&head);
                if (v != -101)
                {
                    del_adr[d] = adress[c];
                    d += 1;
                    printf("\nVALUE - %d\n", v);
                }
            }
            else if (var == 7)
            {
                print_list(head);

                if (c > 0)
                {
                    printf("\nthe addresses of the existing elements - ");
                    out_adress(adress);

                    printf("\naddresses of deleted items - ");
                    out_del(del_adr);
                }
            }
            else if (var == 8)
            {
                size_list = getSize(head);
                if (size_list > 0)
                {
                    int n_size = size_list;
                    if (size_list % 2 == 0 && size_list != 0)
                    {
                        while (size_list > n_size / 2)
                        {
                            l_stack *n_tmp = malloc(sizeof(l_stack));

                            if (n_tmp != NULL)
                            {
                                n_tmp->next = head_n;
                                n_tmp->value = pop_list(&head);
                                del_adr[d] = adress[c];
                                d++;
                                head_n = n_tmp;
                            }
                        }
                    }
                    else if (size_list % 2 != 0 && size_list != 0)
                    {
                        while (size_list > n_size / 2)
                        {
                            l_stack *n_tmp = malloc(sizeof(l_stack));

                            if (n_tmp != NULL)
                            {
                                n_tmp->next = head_n;
                                n_tmp->value = pop_list(&head);
                                del_adr[d] = adress[c];
                                d++;
                                head_n = n_tmp;
                            }
                        }
                        pop_list(&head_n);
                    }

                    int count = 0;
                    int z_size = size_list;
                    int s = getSize(head);

                    int i = 0;

                    while (i < s)
                    {
                        if (pop_list(&head) == pop_list(&head_n))
                            count += 1;

                        del_adr[d] = adress[c];
                        d++;
                        i++;
                    }

                    if (s == count && count != 0)
                    {
                        printf("Is palindrome!!!");
                    }
                    else
                    {
                        printf("Is not palindrome!!!");
                    }
                }
                else
                {
                    printf("\nERROR\n");
                }
                
            }
            else if (var == 0)
            {
                return 0;
            }
            else
            {
                printf("\nthere is no such option\n");
                return 0;
            }
        }
        else
        {
            printf("\nERROR\n");
            getchar();
            return 0;
        }
    }
}

void out_adress(int **mas)
{
    for (int i = c - 1; i >= 0; i--)
        printf("%p ", mas[i]);
}

void out_del(int **mas)
{
    for (int i = d - 1; i >= 0; i--)
        printf("%p ", mas[i]);
}

void is_pal_a(arr_stack *stack_a, arr_stack *stack_b)
{
    int count = 0;
    int size = stack_a->size;

    int i = 0;
    
    while (i < size)
    {
        if (pop_ar(stack_a) == pop_ar(stack_b))
            count += 1;
        i++;
    }

    if (size == count)
    {
        printf("Is palindrome!!!");
    }
    else
    {
        printf("Is not palindrome!!!");
    }
}

void rewrite_ar(arr_stack *stack_a, arr_stack *stack_b)
{
    int size = stack_a->size;

        if (size % 2 == 0)
        {
            while (stack_a->size > size / 2)
            {
                stack_b->data[stack_b->size] = pop_ar(stack_a);
                stack_b->size++;
            }
        }
        if (size % 2 != 0)
        {
            while (stack_a->size > size / 2)
            {
                stack_b->data[stack_b->size] = pop_ar(stack_a);
                stack_b->size++;
            }
            pop_ar(stack_b);
        } 
}

void push_ar(arr_stack *stack_a, int value)
{
    if (stack_a->size >= AR_MAX_SIZE)
    {
        printf("\nStack full\n");
    }
    else
    {
        stack_a->data[stack_a->size] = value;
        stack_a->size++;
    }
}

int pop_ar(arr_stack *stack_a)
{
    if (stack_a->size == 0)
    {
        printf("\nThe stack is empty\n");
        return STACK_UNDERFLOW;
    }
    else
    {
        stack_a->size--;
        return stack_a->data[stack_a->size];
    }
}

void peek_ar(arr_stack *stack_a)
{
    if (stack_a->size <= 0)
    {
        printf("\nThe stack is empty\n");
    }
    else
    {
        int i;
        int len = stack_a->size;
        
        for (int i = 0; i < len; i++)
        {
            printf("%d", stack_a->data[i]);
            printf(" | ");
        }
        printf("\n");
    }
}

void rewrite_li(l_stack **head, l_stack **head_n)
{
    int n_size = size_list;
    if (size_list % 2 == 0 && size_list != 0)
    {
        while (size_list > n_size / 2)
        {
            l_stack *n_tmp = malloc(sizeof(l_stack));

            if (n_tmp != NULL)
            {
                n_tmp->next = *head_n;
                n_tmp->value = pop_list(head);
                *head_n = n_tmp;
            }
        }
    }
    else if (size_list % 2 != 0 && size_list != 0)
    {
        while (size_list > n_size / 2)
        {
            l_stack *n_tmp = malloc(sizeof(l_stack));

            if (n_tmp != NULL)
            {
                n_tmp->next = *head_n;
                n_tmp->value = pop_list(head);
                *head_n = n_tmp;
            }
        }
        pop_list(head_n);
    }
    else
        printf("\nERROR\n");
}

void is_pal_l(l_stack **head, l_stack **head_n)
{
    int count = 0;
    int z_size = size_list;
    int s = size_list;

    int i = 0;

    while (i < s)
    {
        printf("\nq %d\n", count);
        if (pop_list(head) == pop_list(head_n))
            count += 1;
        i++;
    }

    if (s == count && count != 0)
    {
        printf("Is palindrome!!!");
    }
    else if (count != 0)
    {
        printf("Is not palindrome!!!");
    }
}

void push_list(l_stack **head, int value, int **mas)
{
    l_stack *tmp = malloc(sizeof(l_stack));

    if (tmp != NULL)
    {
        mas[c] = (int*)tmp;
        tmp->next = *head;
        tmp->value = value;
        *head = tmp;
        size_list++;

        c += 1;
    }
}

int pop_list(l_stack **head)
{
    l_stack *out;
    int value;

    if (*head != NULL)
    {
        c -= 1;

        size_list--;
        out = *head;
        *head = (*head)->next;
        value = out->value;
        free(out);
        
        return value;
    }
    else
    {
        printf("\nERROR\n");
        return -101;
    }
}


int getSize(l_stack *head) 
{
    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

void print_list(l_stack *head)
{
    if (head)
    {
        while (head)
        {
            printf("%d", head->value);
            printf(" | ");
            head = head->next;
        }
    }
    else
    {
        printf("\nERROR!\n");
    }   
}