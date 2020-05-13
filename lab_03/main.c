#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
void test_time(int procent, int size);


struct matrix
{
    int *vector_a;
    int count;
    int *vector_ja;
    int *vector_ia;
    int count_ia;
};

struct vector
{
    int *vector_a;
    int count;
    int *vector_ja;
    int *vector_ia;
};


void create_matrix(int ***matr, int n, int m)
{
    *matr = (int **)malloc(n * sizeof(int *));
    if (*matr)
        for (int i = 0; i < n; i++)
            (*matr)[i] = (int *)malloc(m * sizeof(int));
}

void delete_matrix(int ***matr, int n)
{
    for (int i = 0; i < n; i++)
        free((*matr)[i]);
    free(*matr);
    *matr = NULL;
}

struct matrix create_vectors(struct matrix cur, int **matr, int row, int col)
{
    printf("Input count of elements no 0 > ");
    cur.count = 0;
    scanf("%d", &cur.count);
    cur.vector_a = malloc(cur.count * sizeof(int));
    cur.vector_ja = malloc(cur.count * sizeof(int));
    cur.count_ia = row + 1;
    cur.vector_ia = malloc(cur.count_ia * sizeof(int)); 
    int n, m;
    int err = 0, cur_n = 0, cur_m = -1;
    for (int i = 0; i < cur.count; i++)
    {
        err = 0;
        while (!err)
        {
            err = 0;
            printf("Input line > ");
            if (scanf("%d", &n) == 1 && n >= 0 && n < row)
            {
                if (n >= cur_n)
                {
                    printf("Input column > ");
                    if (scanf("%d", &m) == 1 && m >= 0 && m < col)
                    {
                        if (n > cur_n)
                            cur_m = -1;
                        if (m > cur_m)
                        {
                            printf("Input element > ");
                            if (scanf("%d", &(matr[n][m])) == 1)
                            {                
                                cur_m = m;
                                cur_n = n; 
                                
                                cur.vector_a[i] = matr[n][m];
                                cur.vector_ja[i] = m;
                                err = 1;
                            }
                        }
                        else
                            printf("This col should be the more than it was.\n");
                    }
                    else
                        printf("We couldn't find this col.\n");
                }
                else
                    printf("This row should be the same/more than it was.\n");
            }
            else
                printf("We couldn't find this row.\n");
            getchar();
        }
    }
    cur.vector_ia[0] = 0;
    int current = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            if (matr[i][j] != 0)
                current++;
        cur.vector_ia[i + 1] = current;
    }
    return cur;
} 

void null_matr(int **matr, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(*(matr + i) + j) = 0;
}

void fill_num(int **matr, int row, int col, int num)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matr[i][j] = num;
}

void fill_vect(int *vect, int size)
{
    for (int i = 0; i < size; i++)
        vect[i] = 0;
}

void multiply_once_c(int **matr_first, int *matr_second, int row, int col)
{
    printf("\n");
    int *calc = NULL;
    calc = malloc(col * sizeof(int));
    fill_vect(calc, row);
    //create_matrix(&calc, row, 1);
    //fill_num(calc, row, 1, 0);

    clock_t begin = clock();
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            calc[i] += matr_first[i][k] * matr_second[k];
        }
    }
    
    clock_t end = clock();
    printf("Result of multiply matr is > %.6lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Result of multiply matrix\n");
    for (int i = 0; i < row; i++)
        printf("%d ", calc[i]);
    free(calc);
    //delete_matrix(&calc, row);
}

void multiply_once_for_check(int **matr_first, int *matr_second, int row, int col)
{
    printf("\n");
    int *calc = NULL;
    //create_matrix(&calc, row, 1);
    //fill_num(calc, row, 1, 0);
    calc = malloc(col * sizeof(int));
    fill_vect(calc, row);

    clock_t begin = clock();
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < row; k++)
        {
            calc[i] += matr_first[i][k] * matr_second[k];
        }
    }
    clock_t end = clock();
    
    free(calc);
    //delete_matrix(&calc, row);
    printf("Result of multiply matr is > %.6lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

void check(struct matrix matr, struct vector vect, struct vector *res)
{
    clock_t begin = clock();
    int j = 0, sum = 0;
    int c = 0;
    int k = 0;
    for (int i = 0; i < matr.count_ia; i++)
    {
        sum = 0;
        for (; j < matr.vector_ia[i]; j++)
        {
            if (vect.vector_ia[matr.vector_ja[j] + 1] != vect.vector_ia[matr.vector_ja[j]])
            {
                sum += matr.vector_a[j] * vect.vector_a[vect.vector_ia[matr.vector_ja[j] + 1] - 1]; 
            }
        }
        if (sum != 0)
        {
            res->vector_a[k] = sum;
            k++;
        }
        res->vector_ia[i] = k;
    }
    res->count = k;
    clock_t end = clock();
    
    printf("Result of multiply struct is > %.6lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

struct vector input_vect(struct vector vect, int *vect_cur, int row)
{
    int cur = 0;
    int err = 1;
    //fill_num(vect_cur, row, 1, 0);
    fill_vect(vect_cur, row);
    int count_cur = 0;
    int check_c = -1;
    
    printf("Input count of non 0 vect > ");
    if (scanf("%d", &count_cur) == 1)
    {
        vect.count = count_cur;
        vect.vector_a = malloc(vect.count * sizeof(int));
        vect.vector_ja = malloc(vect.count * sizeof(int));
        vect.vector_ia = malloc(row * sizeof(int) + sizeof(int));
        for (int i = 0; i < vect.count; i++)
            vect.vector_a[i] = 0;
        vect.vector_ia[0] = 0;
        for (int i = 1; i < row + 1; i++)
        {
            vect.vector_ia[i] = -1;
        }
        int check_in = 0;
        int k = 0;
        for (int i = 0; i < count_cur; i++)
        {
            
            err = 1;
            while (err)
            {
                printf("Input line > ");
                if (scanf("%d", &check_in) == 1 && check_in > check_c && check_in < row)
                {
                    printf("Input elem > ");
                    if (scanf("%d", &cur) == 1 && cur != 0)
                    {
                        check_c = check_in;
                        vect_cur[check_in] = cur;
                        vect.vector_a[k] = cur;
                        k++;
                        err = 0;
                    }
                    else
                        err = 1;
                }
                else 
                    err = 1;
            }
        }
    }

   
    for (int i = 0; i < vect.count; i++)
        vect.vector_ja[i] = 0;
    int current = 0;
    for (int i = 0; i < row; i++)
    {
        if (vect_cur[i] != 0)
            current++;
        vect.vector_ia[i + 1] = current;
    }
    return vect;
}

int main()
{  
    int **matr = NULL;
    int n, m;
    int err = ERROR;
    printf("Input n > ");
    if (scanf("%d", &n) == 1 && n > 1)
    {
        printf("Input m > ");
        if (scanf("%d", &m) == 1 && m > 1)
            err = OK;
    }
    //if (n != m)
    //    err = ERROR;
    if (err)
    {
        create_matrix(&matr, n, m);
        null_matr(matr, n, m);
        int count;
        struct matrix cur;
        cur.vector_a = NULL;
        cur.vector_ia = NULL;
        cur.vector_ja = NULL;
        cur = create_vectors(cur, matr, n, m);
        printf("Matr\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                printf("%d ", matr[i][j]);
            printf("\n");
        }

        int *vect_cur = NULL;
        vect_cur = malloc(m * sizeof(int));
        //create_matrix(&vect_cur, m, 1);
        struct vector vect;
        vect.vector_a = NULL;
        vect.vector_ja = NULL;
        vect.vector_ia = NULL;
        vect.count = m;
        vect = input_vect(vect, vect_cur, m);
        printf("Vector\n");
        for (int i = 0; i < m; i++)
            printf("%d ", vect_cur[i]);
        printf("\n");
        if (1)
        {
            printf("\nMatr\n");
            for (int i = 0; i < cur.count; i++)
            {
                printf("%d ", cur.vector_a[i]);
            }
            printf("\n");
            for (int i = 0; i < cur.count; i++)
                printf("%d ", cur.vector_ja[i]);
            printf("\n");
            if (cur.count != 0)
            {
                for (int i = 0; i < cur.count_ia; i++)
                    printf("%d ", cur.vector_ia[i]);
                printf("\n");
            }
            printf("\nVect\n");
            for (int i = 0; i < vect.count; i++)
            {
                printf("%d ", vect.vector_a[i]);
            }
            printf("\n");
            for (int i = 0; i < vect.count; i++)
                printf("%d ", vect.vector_ja[i]);
            printf("\n");
            for (int i = 0; i < n + 1; i++)
                printf("%d ", vect.vector_ia[i]);
            printf("\n");
        }
        struct vector res;
        res.vector_a = NULL; res.vector_ia = NULL; res.vector_ja = NULL; res.count = n;
        res.vector_a = malloc(n * sizeof(int)); res.vector_ja = malloc(n * sizeof(int)); res.vector_ia = malloc(n * sizeof(int) + sizeof(int));
        
        
        multiply_once_c(matr, vect_cur, n, m);
        check(cur, vect, &res);
        
        printf("Res\n");
        for (int i = 0; i < res.count; i++)
            printf("%d ", res.vector_a[i]);
        printf("\n");
        for (int i = 0; i < n + 1; i++)
            printf("%d ", res.vector_ia[i]);
        printf("\n");
        
        delete_matrix(&matr, n);
        //delete_matrix(&vect_cur, n);
        free(vect_cur);
        free(res.vector_a);
        free(res.vector_ja);
        free(res.vector_ia);
        free(cur.vector_a);
        free(cur.vector_ja);
        free(cur.vector_ia);
        free(vect.vector_a);
        free(vect.vector_ja);
        free(vect.vector_ia);
        
        int ch = 1;
        while (ch)
        {
            int size_check = 0;
            int procenting_check = 0;
            printf("Input size > ");
            if (scanf("%d", &size_check) == 1)
            {
                printf("Input procenting > ");
                if (scanf("%d", &procenting_check) == 1 && procenting_check > 0 && procenting_check <= 100)
                    test_time(procenting_check, size_check);
                else
                    printf("Wrond input.\n");
            }
            else
                printf("Wrong input.\n");

            printf("If you want to continue - 1, else - 0 > ");
            if (scanf("%d", &ch) == 1)
            {   
                printf("Continue\n");
            }
            else
            {
                printf("Error input! Exit.");
                ch = 0;
            }
        }
    }
}

void test_time(int procent, int size)
{
    int need = size * size * procent / 100;
    int need_vect = size * procent / 100;
    int **matr = NULL;
    create_matrix(&matr, size, size);
    fill_num(matr, size, size, 0);
    int count_c = 0;
    int check_c = 0;
    int err = 0;
    int i = 0, j = 0;
    for (; need != 0; need--)
    {
        err = 0;
        while (!err)
        {
            i = 0 + rand() % (size);
            j = 0 + rand() % (size);
            if (matr[i][j] == 0)
            {
                matr[i][j] = 1 + rand() % 200;
                err = 1;
                count_c++;
            }
        }
    }
    /*
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            check_c = 0 + rand() % 2000;
            if (check_c != 0 && count_c < need)
            {
                matr[i][j] = check_c;
                count_c++;
            }
        }
    }
    */
    //printf("%d\n", count_c);
    if (size < 30)
    {
        printf("Matr\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                printf("%d ", matr[i][j]);
            printf("\n");
        }
    }
    struct matrix cur;
    cur.count = count_c;
    cur.vector_a = malloc(cur.count * sizeof(int));
    cur.vector_ja = malloc(cur.count * sizeof(int));
    cur.count_ia = size + 1;
    cur.vector_ia = malloc(cur.count_ia * sizeof(int)); 
    check_c = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matr[i][j] != 0)
            {
                cur.vector_a[check_c] = matr[i][j];
                cur.vector_ja[check_c] = j;
                check_c++;
            }
        }
    }

    //cur.count = check;
    cur.vector_ia[0] = 0;
    int current = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if (matr[i][j] != 0)
                current++;
        cur.vector_ia[i + 1] = current;
    }
 
 
    int *vect_cur = NULL;
    vect_cur = malloc(size * sizeof(int));
    fill_vect(vect_cur, size);
    //create_matrix(&vect_cur, size, 1);
    //fill_num(vect_cur, size, 1, 0);
    int count_s = 0;
    for (; need_vect != 0; need_vect--)
    {
        err = 0;
        while (!err)
        {
            i = 0 + rand() % (size);
            if (vect_cur[i] == 0)
            {
                vect_cur[i] = 0 + rand() % 200;
                count_s++;
                err = 1;
            }
        }
    }


    struct vector vect;
    vect.count = count_s;
    vect.vector_a = malloc(vect.count * sizeof(int));
    vect.vector_ja = malloc(vect.count * sizeof(int));
    vect.vector_ia = malloc(size * sizeof(int) + sizeof(int));
    
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        if (vect_cur[i] != 0)
        {
            vect.vector_a[k] = vect_cur[i];
            k++;
        }
    }

    for (int i = 0; i < vect.count; i++)
        vect.vector_ja[i] = 0;
    current = 0;
    vect.vector_ia[0] = 0;
    for (int i = 0; i < size; i++)
    {   
        if (vect_cur[i] != 0)
            current++;
        vect.vector_ia[i + 1] = current;
    }
    
    struct vector res;
    res.vector_a = NULL; res.vector_ia = NULL; res.vector_ja = NULL; res.count = size;
    res.vector_a = malloc(size * sizeof(int)); res.vector_ja = malloc(size * sizeof(int)); res.vector_ia = malloc(size * sizeof(int) + sizeof(int));

    multiply_once_for_check(matr, vect_cur, size, size);
    check(cur, vect, &res);
    
    /*
    printf("Size matr %ld\n", (sizeof(cur.vector_a) + sizeof(cur.vector_ja) + sizeof(cur.vector_ia)));
    printf("Size vect %ld\n", sizeof(vect.vector_a) + sizeof(vect.vector_ja) + sizeof(vect.vector_ia));

    int size_check = 0;
    for (int i = 0; i < size; i++)
        size_check += sizeof(matr[i]);

    printf("size matr full %d\n", size_check);
    
    size_check = 0;
    for (int i = 0; i < size; i++)
        size_check += sizeof(vect_cur[i]);
    printf("size vect full %d\n", size_check);
*/
    free(res.vector_a);
    free(res.vector_ja);
    free(res.vector_ia);
 
    free(vect.vector_a);
    free(vect.vector_ja);
    free(vect.vector_ia);

    free(vect_cur);
    //delete_matrix(&vect_cur, size);
   
    free(cur.vector_a);
    free(cur.vector_ja);
    free(cur.vector_ia);
    
    delete_matrix(&matr, size); 
}
