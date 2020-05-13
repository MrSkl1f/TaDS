#ifndef OPERATIONSHASH_H
#define OPERATIONSHASH_H

typedef struct listnode 
{
    int key;
    int index;
    struct listnode *next;
} listnode;

unsigned int hash(int key);
void hashInit(listnode **hashTab);
void hashTabAdd(listnode **hashTab, int key);
listnode *hashTabLookUp(listnode **hashTab, int key, int *countOfCmp);
void hashTabDelete(listnode **hashTab, int key);
void output(listnode **hashTab);
void freeHashTab(listnode **hashTab, int HASHTAB_SIZE);
void funcHash();
void createHashTable(listnode **hashTab, int *array, int size);
void countSizeInHashTab(listnode **hashTab, int *size);
void countSizeOfHashTab(int size, int collis);

#endif