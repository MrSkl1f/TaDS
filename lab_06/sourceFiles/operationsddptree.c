#include "../headerFiles/mainhead.h"
#include "../headerFiles/operationsddptree.h"

nodeDDP* getFreeNodeDDP(int value, nodeDDP *parent) 
{
    nodeDDP* tmp = (nodeDDP*) malloc(sizeof(nodeDDP));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void createDDPtree(nodeDDP **root, int *array, int size)
{
	for (int i = 0; i < size; i++)
    {
		insertDDP(root, array[i]);
    }
}

void printTreeDDP(nodeDDP *root, const char *dir, int level) 
{
    if (root) 
	{
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTreeDDP(root->left, "left", level+1);
        printTreeDDP(root->right, "right", level+1);
    }
}

void print_treeDDP(nodeDDP* p, int level)
{
    if(p)
    {
        print_treeDDP(p->left, level + 1);
        for(int i = 0; i < level; i++) 
            printf("   ");

        printf("%d\n", p->data);
        print_treeDDP(p->right,level + 1);
    }
}

void printf_treeDDP(nodeDDP* p, int level)
{
    if (p)
    {
        printf("--------------------------------\n");
        printf("LEFT UP AND RIGHT DOWN\n");
        //printf("            DOWN");
        printf("\nROOT--------------------------->\n");

        print_treeDDP(p, 0);

        printf("\nROOT--------------------------->\n");
        printf("LEFT UP AND RIGHT DOWN\n");
        //printf("            DOWN\n");
        printf("--------------------------------\n");
    }
    else
        printf("\n\nE M P T Y \n\n");
}

void freeTreeDDP(nodeDDP *root)
{
	if (root)
	{
		if (root->left != NULL)
			freeTreeDDP(root->left);
		if (root->right != NULL)
			freeTreeDDP(root->right);
		free(root);
	}
}

void insertDDP(nodeDDP **head, int value) 
{
    nodeDDP *tmp = NULL;
    if (*head == NULL) 
    {
        *head = getFreeNodeDDP(value, NULL);
        return;
    }
     
    tmp = *head;
    while (tmp) 
    {
        if (CMP_GT(value, tmp->data)) 
        {
            if (tmp->right) 
            {
                tmp = tmp->right;
                continue;
            } 
            else 
            {
                tmp->right = getFreeNodeDDP(value, tmp);
                return;
            }
        } 
        else if (CMP_LT(value, tmp->data)) 
        {
            if (tmp->left) 
            {
                tmp = tmp->left;
                continue;
            } 
            else 
            {
                tmp->left = getFreeNodeDDP(value, tmp);
                return;
            }
        } 
        else 
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else 
            {
                tmp->left = getFreeNodeDDP(value, tmp);
                return;
            }
        }
    }
}

nodeDDP* getMinNode(nodeDDP *root) 
{
    while (root->left)
        root = root->left;
    return root;
}

nodeDDP* getMaxNode(nodeDDP *root) 
{
    while (root->right) 
        root = root->right;
    return root;
}

nodeDDP *getNodeByValue(nodeDDP *root, int value, int *countOfCMP) 
{
    while (root) 
    {
        if (CMP_GT(root->data, value)) 
        {
            (*countOfCMP)++;
            root = root->left;
            continue;
        } 
        else if (CMP_LT(root->data, value)) 
        {
            (*countOfCMP)++;
            root = root->right;
            continue;
        } 
        else 
            return root;
    }
    return NULL;
}

void countSizeInDDP(nodeDDP *root, int *size) 
{
    if (root) 
	{
		(*size)++;
        countSizeInDDP(root->left, size);
        countSizeInDDP(root->right, size);
    }
}

void removeNodeByPtr(nodeDDP *target) 
{
    if (target->left && target->right) 
    {
        nodeDDP *localMax = getMaxNode(target->left);
        target->data = localMax->data;
        removeNodeByPtr(localMax);
        return;
    } 
    else if (target->left) 
    {
        if (target == target->parent->left) 
            target->parent->left = target->left;
        else 
            target->parent->right = target->left;
    } 
    else if (target->right) 
    {
        if (target == target->parent->right) 
            target->parent->right = target->right;
        else 
            target->parent->left = target->right;
    } 
    else 
    {
        if (target == target->parent->left)
            target->parent->left = NULL;
        else 
            target->parent->right = NULL;
    }
    free(target);
}

void deleteValue(nodeDDP *root, int value) 
{
    int check = 0;
    nodeDDP *target = getNodeByValue(root, value, &check);
    removeNodeByPtr(target);
}

