#include <stdio.h>
#include <string.h>

#define ELEM_COUNT 31
#define ERROR 1
#define OK 0
#define POS 1
#define NEG -1
#define ENTERED 1
#define NOT_ENTERED 0

typedef struct {
    char num[ELEM_COUNT];
    int num_sign;
    int num_count;
    int dot;
    int dot_pos;
    int ord;
} Float_L;



void float_reading(Float_L *a, int *err)
{
    printf("\nInput float:\n");
    printf("Correct input: -1e0, 0.5e-7, +.5e1\n\n");
    printf("1        10        20       30 e1   5\n");
    printf("|--------|---------|---------|--|---|\n");

	char c;
    int i;
    int count = 0;
	for(i = 0; (i <= 31) && scanf("%c", &c) && (c != EOF) && (c != '\n') && (c != 'E') && (c != 'e'); i++)
    {
        if(i == 0 && (c == '-' || c == '+'))
        {
            if(c == '-')
                a->num_sign = NEG;
            else if(c == '+')
                a->num_sign = POS;
            i--;
        }
        else if(c == '.' && a->dot_pos == NOT_ENTERED)
        {
            a->dot = ENTERED;
            a->dot_pos = i;
            a->num[i] = '.';
        }
        else if ((c <= '9') && (c >= '0'))
        {
            a->num[i] = c - '0';
            count++;
        }
        else
        {
            *err = ERROR;
            printf("Wrong input! Please enter only [0-9], +, -, E, e, . --- once");
        }
    }

    if (i == 0 && *err == OK)
    {
        printf("Empty input!");
        *err = ERROR;
    }

    if (count > 30 && *err == OK)
    {
        printf("Too many digits");
        *err = ERROR;
    }

    if ((c == 'E') || (c == 'e'))
    {
        if (scanf("%d", &a->ord) != 1)
            *err = ERROR;
    }

    if ((a->ord > 99999 || a->ord < -99999) && *err == OK) // NOTE error scanfing exponent
    {
        printf("Exponent should lie within [-99999, 99999]");
        *err = ERROR;
    }

    for (int i = 0;((c = getchar()) != EOF) && (c != '\n') && i == 0; i++)
    {
        printf("\nSomething wrong with exponent!");
        *err = ERROR;
    }
    a->num_count = count;
}

void normalize(Float_L *a)
{
    for (int i = a->dot_pos; i < a->num_count; i++)
    {
        a->num[i] = a->num[i + 1];
        a->ord--;
    }
}

void turn_over_arr(Float_L *a)
{
    int b = 0;
    for (int i = 0; i < a->num_count / 2; i++)
    {
        b = a->num[i];
        a->num[i] = a->num[a->num_count - i - 1];
        a->num[a->num_count - i - 1] = b;
    }

}

void multiplication(Float_L *a, Float_L *b, int *c, int *ind)
{
    int i, j, carry;
    for ( i = 0; i < a->num_count; i++)
        for ( j = 0, carry = 0; j < b->num_count || carry; j++)
        {
            int cur = c[i + j] + a->num[i] * 10 * (j < b->num_count ? b->num[j] : 0) + carry;
            c[i + j] = (int)(cur % 10);
            carry = (int)(cur / 10);
        }

    *ind = i + j;
}

int main()
{
    int err = OK;
    Float_L x = { .num = { 0 }, .num_sign = POS, .dot_pos = NOT_ENTERED, .ord = 0};
    Float_L y = { .num = { 0 }, .num_sign = POS, .dot_pos = NOT_ENTERED, .ord = 0};
    int res[80] = { 0 };

    float_reading(&x, &err);
    if (err == OK)
    {
        if (x.dot == ENTERED)
            normalize(&x);
        turn_over_arr(&x);
        if (err == OK)
        {
            float_reading(&y, &err);
            if (err ==  OK)
            {
                if (y.dot == ENTERED)
                    normalize(&y);
                turn_over_arr(&y);


                int ind = 0;
                multiplication(&x, &y, res, &ind);

                printf("\nResult\n");
                if (x.num_sign * y.num_sign > 0)
                    printf("+0.");
                else
                    printf("-0.");
                for (int i = ind - 2, count = 0; i > 0 && count < 30; i--, count++)
                    printf("%d", res[i]);
                printf("e%d", x.ord + y.ord + ind - 2);
            }
        }
    }
}