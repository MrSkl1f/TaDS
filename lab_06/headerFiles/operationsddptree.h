#ifndef OPERATIONSDDPTREE_H
#define OPERATIONSDDPTREE_H

typedef struct nodeDDP 
{
    int data;
    struct nodeDDP *left;
    struct nodeDDP *right;
    struct nodeDDP *parent;
} nodeDDP;

nodeDDP* getFreeNodeDDP(int value, nodeDDP *parent);
void insertDDP(nodeDDP **head, int value);
nodeDDP* getMinNode(nodeDDP *root);
nodeDDP* getMaxNode(nodeDDP *root);
nodeDDP *getNodeByValue(nodeDDP *root, int value, int *countOfCMP);
void removeNodeByPtr(nodeDDP *target);
void deleteValue(nodeDDP *root, int value);
void createDDPtree(nodeDDP **root, int *array, int size);
void freeTreeDDP(nodeDDP *root);
void printTreeDDP(nodeDDP *root, const char *dir, int level);
void countSizeInDDP(nodeDDP *root, int *size);
void print_treeDDP(nodeDDP* p, int level);
void printf_treeDDP(nodeDDP* p, int level);

#endif