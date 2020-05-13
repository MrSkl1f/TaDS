#include "../headerFiles/mainhead.h"
#include "../headerFiles/operationshash.h"

unsigned int hash(int key)
{
    return key % HASHTAB_SIZE;
}

void hashInit(listnode **hashTab)
{
    for (int i = 0; i < HASHTAB_SIZE; i++)
        hashTab[i] = NULL;
}

void hashTabAdd(listnode **hashTab, int key)
{
    listnode *node;
    int index = hash(key);
    node = malloc(sizeof(*node));
    node->key = key;
    node->next = hashTab[index];
    hashTab[index] = node;
}

listnode *hashTabLookUp(listnode **hashTab, int key, int *countOfCmp)
{
    int index;
    listnode *node;
    index = hash(key);
    for (node = hashTab[index]; node != NULL; node = node->next)
    {
        if (node->key == key)
            return node;
        else
           (*countOfCmp)++; 
    }
    return NULL;
}

void hashTabDelete(listnode **hashTab, int key)
{
    int index;
    listnode *p, *prev = NULL;
    index = hash(key);
    for(p = hashTab[index]; p != NULL; p = p->next)
    {
        if (p->key == key)
        {
            if (prev == NULL)
                hashTab[index] = p->next;
            else
                prev->next = p->next;
            free(p);
            return;
        }
        prev = p;
    }
}

void output(listnode **hashTab)
{
    listnode *node;
    for (int i = 0; i < HASHTAB_SIZE; i++)
    {
        if (hashTab[i] != NULL)
        {
            node = hashTab[i];
            printf("%d\t%d\t", i, (hashTab[i])->key);
            while (node->next != NULL)
            {
                node = node->next;
                printf("%d\t", node->key);
            }
            printf("\n");
        }
    }
}

void countSizeInHashTab(listnode **hashTab, int *size)
{
    listnode *node;
    for (int i = 0; i < HASHTAB_SIZE; i++)
    {
        if (hashTab[i] != NULL)
        {
            node = hashTab[i];
            (*size)++;
            while (node->next != NULL)
            {
                node = node->next;
                (*size)++;
            }
        }
    }
}

void freeHashTab(listnode **hashTab, int HASHTAB_SIZE)
{
    listnode *node, *p;
    for (int i = 0; i < HASHTAB_SIZE; i++)
    {
        if (hashTab[i] != NULL)
        {
            node = hashTab[i]->next;
            while (node != NULL)
            {
                p = node;
                node = node->next;
                free(p);
            }
            //free(node);
            free(hashTab[i]);
        }
    }
}

void createHashTable(listnode **hashTab, int *array, int size)
{
    int collis = 0;
    printf("Input count of numbers and max collisions >");
    if (scanf("%d", &HASHTAB_SIZE) == 1 && scanf("%d", &collis) == 1)
    {
        countSizeOfHashTab(size, collis);
        hashInit(hashTab);
        for (int i = 0; i < size; i++)
            hashTabAdd(hashTab, array[i]);
    }
    else
        printf("Error input\n");
}

void countSizeOfHashTab(int size, int collis)
{
    if (HASHTAB_SIZE + collis < size)
        HASHTAB_SIZE += collis;
    else if (HASHTAB_SIZE > size + collis)
        HASHTAB_SIZE = size;
}

/*
void funcHash()
{
    //hashInit(hashTab);
    hashTabAdd(hashTab, 5);
    hashTabAdd(hashTab, 1);
    hashTabAdd(hashTab, 2);
    hashTabAdd(hashTab, 3);
    hashTabAdd(hashTab, 10);
    hashTabAdd(hashTab, 1034);
    hashTabAdd(hashTab, 10);
    output(hashTab);
    freeHashTab(hashTab);
}
*/