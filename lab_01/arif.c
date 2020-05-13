#include <stdio.h>
#include <string.h>

#define ELEM_COUNT 31
#define ERROR 1
#define OK 0
#define POS 1
#define NEG -1
#define ENTERED 1
#define NOT_ENTERED 0


void input_float(char *array, int *sign, int *count_num, int *point, int *point_pos, int *exp, int *err)
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
                *sign = NEG;
            else if(c == '+')
                *sign = POS;
            i--;
        }
        else if(c == '.' && *point_pos == NOT_ENTERED)
        {
            *point = ENTERED;
            *point_pos = i;
            array[i] = '.';
        }
        else if ((c <= '9') && (c >= '0'))
        {
            array[i] = c - '0';
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
        if (scanf("%d", exp) != 1)
            *err = ERROR;
    }

    if ((*exp > 99999 || *exp < -99999) && *err == OK) // NOTE error scanfing exponent
    {
        printf("Exponent should lie within [-99999, 99999]");
        *err = ERROR;
    }

    for (int i = 0;((c = getchar()) != EOF) && (c != '\n') && i == 0; i++)
    {
        printf("\nSomething wrong with exponent!");
        *err = ERROR;
    }
    *count_num = count;
}

void normalize(char *array, int count, int point_pos, int *exp)
{
    for (int i = point_pos; i < count; i++)
    {
        array[i] = array[i + 1];
        *exp -= 1;
    }
}

int zero_array(char *array, int size)
{
    for (int i = 0; i < size; i++)
        if (array[i] != '0')
            return 0;
    return 1;
}

void mirror_array(char *array, int count)
{
    int b = 0;
    for (int i = 0; i < count / 2; i++)
    {
        b = array[i];
        array[i] = array[count - i - 1];
        array[count - i - 1] = b;
    }
}

void multiplication(char *first_array, char *second_array, int first_count, int second_count, int *c, int *ind)
{
    *ind = first_count + second_count - 1;
    for (int i = 0; i < *ind; i++)
        c[i] = 0;

    for (int i = 0; i < first_count; i++)
    {
        for (int j = 0; j < second_count; j++)
            c[i + j] += first_array[i] * second_array[j];
    }
    for (int i = 0; i < *ind - 1; i++)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    printf("\n");
    for (int i = *ind - 1; i >= 0; i--)
        printf("%d ", c[i]);
    printf("\n");

}

int round_zero(int *res, int ind)
{
    while (res[0] == 0)
    {
        for(int i = 0; i < ind - 1; i++)
        {
            res[i] = res[i + 1];
        }
        ind--;
    } 
    return ind;
}

int round_arr(int *array, int count)
{
    // FIX CARRY
    if (count > 30)
    {
        while (count >= 30)
        {
            if (array[0] > 4)
                array[1]++;

            for(int i = 0; i < count - 1; i++)
            {
                array[i] = array[i + 1];
            }
            count--;
        } 

        for (int i = 0; i < count - 1; i++)
        {
            array[i + 1] += array[i] / 10;
            array[i] %= 10;
        }
    }    
    //if (array[count - 1] > 9)
    //    array[count - 1] /= 10;
   
    return count;
}

int round_exp(int *array, int count, int *exp)
{
    while (array[count - 1] == 0)
    {
        count--;
        *exp -= 1;
    }
    return count;
}

int main()
{
    int err = OK;

    char first_array[ELEM_COUNT], second_array[ELEM_COUNT];
    int first_sign = POS, second_sign = POS;
    int first_count, second_count;
    int first_point, second_point;
    int first_point_pos, second_point_pos;
    int first_exp = 0, second_exp = 0;

    int res[80] = { 0 };

    input_float(first_array, &first_sign, &first_count, &first_point, &first_point_pos, &first_exp, &err);
    if (err == OK)
    {
        if (first_point == ENTERED)
            normalize(first_array, first_count, first_point_pos, &first_exp); 


        if (zero_array(first_array, first_count))
        {
            printf("Result: 0.0e0");
            return ERROR;
        }
        else
            mirror_array(first_array, first_count);

        if (err == OK)
        {
            input_float(second_array, &second_sign, &second_count, &second_point, &second_point_pos, &second_exp, &err);
            if (err ==  OK)
            {
                if (second_point == ENTERED)
                    normalize(second_array, second_count, second_point_pos, &second_exp);
                if (zero_array(second_array, second_count))
                {
                    printf("Result: 0.0e0");
                    err = ERROR;
                }
                else
                {
                    mirror_array(second_array, second_count);

                    int res_count = 0;
                    int exp = first_exp + second_exp;
                    multiplication(first_array, second_array, first_count, second_count, res, &res_count);

                    

                    int new_count = round_arr(res, res_count);
                    new_count = round_zero(res, new_count);
                    exp += res_count;
                    new_count = round_exp(res, new_count, &exp);
                    //if (res[new_count - 1] > 9)
                    //    res[new_count - 1] /= 10;
                    if (exp <= 99999 && exp >= -99999)
                    {
                        if (res[new_count - 1] > 9)
                            exp++;
                        printf("\nResult\n");
                        printf("   1        10        20       30 e1   5\n");
                        printf("   |--------|---------|---------|--|---|\n");
                        if (first_sign * second_sign > 0)
                            printf("+0.");
                        else
                            printf("-0.");
                        for (int i = new_count - 1; i >= 0; i--)
                            printf("%d", res[i]);

                        printf("e%d\n", exp);
                    }
                    else
                    {
                        printf("Overflow");
                    }
                }
            }
        }
    }
    return err;
}