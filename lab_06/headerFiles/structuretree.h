#ifndef STRUCTURETREE_H
#define STRUCTURETREE_H

#include "mainhead.h"

typedef struct node 
{
	int key;
	unsigned char height;
	struct node* left;
	struct node* right;
}node;

void func();
node* removeknot(node* p, int k);
node* removemin(node* p);
node* findmin(node* p);
node* insert(node* p, int k);
node* balance(node* p);
node* rotateleft(node* q);
node* rotateright(node* p);
void fixheight(node* p);
int bfactor(node* p);
unsigned char height(node* p);
node* getFreeNode(int value);
void createBalancedTree(node **root, int *array, int size);
void printTree(node *root, const char *dir, int level);
void freeTree(node *root);
node *getNodeByValueAVL(node *root, int value, int *countOfCmp);
void countSize(node *root, int *size) ;
void print_treeAVL(node* p, int level);
void printf_treeAVL(node* p, int level);

#endif