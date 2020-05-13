#include "main.h"

void InitForArray(struct QueueForArray *q) 
{
    q->frnt = 1;
    q->rear = 0;
    return;
}

void InsertForArray(struct QueueForArray *q, int x, int *err) 
{
    if(q->rear < QMAX-1) 
    {
        q->rear++;
        q->qu[q->rear]=x;
    }
    else
    {
        printf("Full QueueForArray!\n");
        *err = 1;
    }
}

int IsEmptyForArray(struct QueueForArray *q)   
{
    if(q->rear < q->frnt)    
        return(1);
    else  
        return(0);
}
/*
void PrintForArray(struct QueueForArray *q) 
{
    int h;
    if(IsEmptyForArray(q)==1) 
    {
        printf("Empty QueueForArray!\n");
        return;
    }
    for(h = q->frnt; h<= q->rear; h++)
        printf("%d ", q->qu[h]);
}
*/
void RemoveElementForArray(struct QueueForArray *q) 
{
    int x;
    //if(IsEmptyForArray(q)==1) 
    //{
        //printf("Empty QueueForArray!\n");
        //return(0);
    //}
    x = q->qu[q->frnt];
    q->frnt++;
    //return(x);
}

void RemoveElementxForArray(struct QueueForArray *q) 
{
    int x, h;
    if(IsEmptyForArray(q)==1) 
    {
        printf("Empty QueueForArray!\n");
    }
    x = q->qu[q->frnt];
    for(h = q->frnt; h < q->rear; h++) 
    {
        q->qu[h] = q->qu[h+1];
    }
    q->rear -= 1;
}

/*
int main()
{
    struct QueueForArray *UpperQueueForArray, *UnderQueueForArray;
    UpperQueueForArray = malloc(sizeof(struct QueueForArray));
    UnderQueueForArray = malloc(sizeof(struct QueueForArray));
    InitForArray(UpperQueueForArray); InitForArray(UnderQueueForArray);

    int check = 4;
    while (check)
    {
        PrintForArrayf("Main menu:\n"
        "\t1 - Start working with QueueForArrays (array)\n"
        "Input choice > ");
        scanf("%d", &check);
        if (check == 1)
        {

        }
    }



return 0;
}
*/