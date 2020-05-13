#include "../headerFiles/find.h"

void findInDDPTree(nodeDDP *root, int value)
{
    nodeDDP *tmp = NULL;
    int countOfCmp = 0;
    clock_t start = clock();
    tmp = getNodeByValue(root, value, &countOfCmp);
    clock_t end = clock();
    if (tmp != NULL)
    {
        printf("Time of searching in DDP tree > %lf | and count of comparing is > %d\n", (float)(end - start) / CLOCKS_PER_SEC, countOfCmp);
        //free(tmp);
    }
    else
        printf("We couldn't find anything in DDP tree\n");
    int size = 0;
    countSizeInDDP(root, &size);
    printf("Size of DDP Tree is > %lu\n\n", size * sizeof(struct nodeDDP));
}   

void findInAVLTree(node *root, int value)
{
    node *tmp = NULL;
    int countOfCmp = 0;
    clock_t start = clock();
    tmp = getNodeByValueAVL(root, value, &countOfCmp);
    clock_t end = clock();
    if (tmp != NULL)
    {
        printf("Time of searching in AVL tree > %lf | and count of comparing is > %d\n", (float)(end - start) / CLOCKS_PER_SEC, countOfCmp);
        //free(tmp);
    }
    else
        printf("We couldn't find anything int AVL tree\n");
    int size = 0;
    countSize(root, &size);
    printf("Size of AVL Tree is > %lu\n\n", size * sizeof(struct node));
}

void findInHashTab(listnode **hashTab, int value)
{
    listnode *tmp = NULL;
    int countOfCmp = 0;
    clock_t start = clock();
    tmp = hashTabLookUp(hashTab, value, &countOfCmp);
    clock_t end = clock();
    if (tmp != NULL)
        printf("Time of searching in Hash Table > %lf | and count of comparing is > %d\n", (float)(end - start) / CLOCKS_PER_SEC, countOfCmp); 
    else
        printf("We couldn't find anything in hash table\n");
    int size = 0;
    countSizeInHashTab(hashTab, &size);
    printf("Size of Hash Tab is > %lu\n\n", size * sizeof(struct listnode));
}

void findInFile(int value)
{
    FILE *newFile;
    //newFile = fopen("input.txt", "r");
    if ((newFile = fopen("input.txt", "r")) == NULL)
    {
        printf("Can not open the file!\n");
        getchar();
        return;
    }
    int size;
    fscanf(newFile, "%d", &size);
    int cur;
    int err = 1, countOfCmp = 0;
    clock_t start = clock();
    for (int i = 0; i < size && err; i++)
    {
        fscanf(newFile, "%d", &cur);
        if (cur == value)
            err = 0;
        else
            countOfCmp++;
    }
    clock_t end = clock();
    if (err == 0)
        printf("Time of searching in File > %lf | and count of comparing is > %d\n", (float)(end - start) / CLOCKS_PER_SEC, countOfCmp);
    else
        printf("We couldn't find anything in file\n");
    printf("Size of numbers in File is > %lu\n\n", size * sizeof(int));
    fclose(newFile);
}