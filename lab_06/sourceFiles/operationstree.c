#include "../headerFiles/mainhead.h"
#include "../headerFiles/structuretree.h"

node* getFreeNode(int value) 
{
    node* tmp = (node*) malloc(sizeof(node));
    tmp->left = tmp->right = NULL;
    tmp->key = value; tmp->height = 1;
    return tmp;
}

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
		{
			p->right = rotateright(p->right);
		}
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
		{
			p->left = rotateleft(p->left);
		}
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node *getNodeByValueAVL(node *root, int value, int *countOfCmp) 
{
    while (root) 
    {
        if (root->key > value) 
        {
			(*countOfCmp)++;
            root = root->left;
            continue;
        } 
        else if (root->key < value) 
        {
			(*countOfCmp)++;
            root = root->right;
            continue;
        } 
        else 
            return root;
    }
    return NULL;
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return  getFreeNode(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* removeknot(node* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = removeknot(p->left,k);
	else if( k > p->key )
		p->right = removeknot(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		free(p);
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void freeTree(node *root)
{
	if (root)
	{
		if (root->left != NULL)
			freeTree(root->left);
		if (root->right != NULL)
			freeTree(root->right);
		free(root);
	}
}

void print_treeAVL(node* p, int level)
{
    if(p)
    {
        print_treeAVL(p->left, level + 1);
        for(int i = 0; i < level; i++) 
            printf("   ");

        printf("%d\n", p->key);
        print_treeAVL(p->right,level + 1);
    }
}

void printf_treeAVL(node* p, int level)
{
    if (p)
    {
        printf("--------------------------------\n");
        printf("LEFT UP AND RIGHT DOWN\n");
        //printf("            DOWN");
        printf("\nROOT--------------------------->\n");

        print_treeAVL(p, 0);

        printf("\nROOT--------------------------->\n");
        printf("LEFT UP AND RIGHT DOWN\n");
        //printf("            DOWN\n");
        printf("--------------------------------\n");
    }
    else
        printf("\n\nE M P T Y \n\n");
}

void printTree(node *root, const char *dir, int level) 
{
    if (root) 
	{
        printf("lvl %d %s = %d\n", level, dir, root->key);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}

void countSize(node *root, int *size) 
{
    if (root) 
	{
		(*size)++;
        countSize(root->left, size);
        countSize(root->right, size);
    }
}

void createBalancedTree(node **root, int *array, int size)
{
	for (int i = 0; i < size; i++)
		*root = insert(*root, array[i]);
}


