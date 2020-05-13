#ifndef FIND_H
#define FIND_H

#include "../headerFiles/mainhead.h"
#include "../headerFiles/structuretree.h"
#include "../headerFiles/input.h"
#include "../headerFiles/operationshash.h"
#include "../headerFiles/operationsddptree.h"
#include <time.h>

void findInDDPTree(nodeDDP *root, int value);
void findInAVLTree(node *root, int value);
void findInHashTab(listnode **hashTab, int value);
void findInFile(int value);

#endif