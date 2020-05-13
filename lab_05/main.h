#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#define QMAX 1000

struct QueueForArray 
{
    int qu[QMAX];
    int rear, frnt;
};

struct node_t
{
    struct node_t *last;
    int value;
};

struct QueueForList
{
    struct node_t *ptr_push;
    struct node_t *ptr_pop;
    int len;
};

struct Table
{
    int CurLenFirst;
    int CurLenSecond;
    int AverLenFirst;
    int AverLenSecond;
    int CountInFirst;
    int CountInSecond;
    int CountOutFirst;
    int CountOutSecond;
};

int QueueForArrayArr();
float RandTime(int min, int max);
void RemoveElementxForArray(struct QueueForArray *q);
void RemoveElementForArray(struct QueueForArray *q);
void PrintForArray(struct QueueForArray *q);
int IsEmptyForArray(struct QueueForArray *q);
void InsertForArray(struct QueueForArray *q, int x, int *err);
void InitForArray(struct QueueForArray *q);

void QueueForListCheck();

void InitForList(struct QueueForList *queue);
void FreeList(struct QueueForList *queue);
int PushList(struct QueueForList *queue, int elem);
void PopList(struct QueueForList *queue);

