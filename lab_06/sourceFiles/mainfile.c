#include "../headerFiles/mainhead.h"
#include "../headerFiles/structuretree.h"
#include "../headerFiles/mainfile.h"
#include "../headerFiles/input.h"
#include "../headerFiles/operationshash.h"
#include "../headerFiles/operationsddptree.h"
#include "../headerFiles/find.h"

int main()
{
    int input = 100;

    int *array = NULL;
    int size = 0;
    
    nodeDDP *ddpTree = NULL;
    node *balancedTree = NULL;

     
    int HASHTAB_SIZE = 0;
    int *arrayHash = NULL;
    int sizeHash = 0;

    while (input != 0)
    {
        menu();
        if (scanf("%d", &input) == 1)
        {
            printf("-------------------------------------\n");
            switch (input)
            {
                case 0:
                {
                    printf("Goodbuy!\n");
                    if (array != NULL)
                        free(array);
                    if (arrayHash != NULL)
                        free(arrayHash);
                    freeTreeDDP(ddpTree);
                    freeTree(balancedTree);
                    freeHashTab(hashTab);
                    exit(0);
                }
                case 1:
                {
                    inputFromFile(&array, &size);
                    printf("Done!\n");
                    break;
                }
                case 2:
                {
                    if (array != NULL)
                    {
                        freeTreeDDP(ddpTree); ddpTree = NULL;
                        createDDPtree(&ddpTree, array, size);
                        //printTreeDDP(ddpTree, "DDP Tree", 0);
                    }
                    else
                        printf("You didn't input data from file!\n");
                    break;
                }
                case 3:
                {
                    if (array != NULL)
                    {
                        freeTree(balancedTree); balancedTree = NULL;
                        createBalancedTree(&balancedTree, array, size);
                        //printTree(balancedTree, "DDP Tree", 0);
                    }
                    else
                        printf("You didn't input data from file!\n");
                    break;
                }
                case 4:
                {
                    if (array != NULL)
                    {
                        int cur;
                        printf("Input value > ");
                        if (scanf("%d", &cur) == 1)
                        {
                            deleteValue(ddpTree, cur);
                        }
                        else
                            printf("Error input\n");
                    }
                    else
                        printf("You didn't input from file.\n");
                    break;
                }
                case 5:
                {
                    if (array != NULL)
                    {
                        int cur;
                        printf("Input value > ");
                        if (scanf("%d", &cur) == 1)
                        {
                            balancedTree = removeknot(balancedTree, cur);
                        }
                        else
                            printf("Error input\n");
                    }
                    else
                        printf("You didn't input from file.\n");
                    break;
                }
                case 6:
                {
                    if (ddpTree != NULL && balancedTree != NULL)
                    {
                        printf("\n\n");
                        printf_treeDDP(ddpTree, 0);
                        printf("\n\n");
                        printf_treeAVL(balancedTree, 0);
                    }
                    else
                        printf("You didn't create DDP or AVL tree!\n");
                    break;
                }
                case 7:
                {
                    freeHashTab(hashTab, HASHTAB_SIZE);
                    inputFromFile(&arrayHash, &sizeHash);
                    createHashTable(hashTab, arrayHash, sizeHash);
                    printf("Done!\n");
                    break;
                }
                case 8:
                {
                    if (arrayHash != NULL)
                        output(hashTab);
                    break;
                }
                case 9:
                {
                    int cur;
                    printf("Input value > ");
                    if (scanf("%d", &cur) == 1)
                        hashTabDelete(hashTab, cur);
                    break;
                }
                case 10:
                {
                    int cur;
                    printf("\nInput value > ");
                    if (scanf("%d", &cur) == 1)
                    {
                        findInDDPTree(ddpTree, cur);
                        findInAVLTree(balancedTree, cur);
                        findInHashTab(hashTab, cur);
                        findInFile(cur);
                    }
                    else
                        printf("Error input!\n");
                    break;
                }
                default:
                    printf("Error input!\n");
            }
        }
        else
            printf("Error input\n");
        getchar();
    }

    return 0;
}

void menu()
{
    printf("\n-------------------------------------\n"
            "Menu:\n"
            "\t0 - Exit\n"
            "\t1 - Input from file\n"
            "Operations with tree:\n"
            "\t2 - Create main tree (DDP)\n"
            "\t3 - Create balanced tree (AVL)\n"
            "\t4 - Delete knot from DDP tree\n"
            "\t5 - Delete knot from AVL tree\n"
            "\t6 - Print trees\n"
            "Operations with hash table:\n"
            "\t7 - Create hash table\n"
            "\t8 - Print hash table\n"
            "\t9 - Remove from hash table\n"
            "Other operations:\n"
            "\t10 - Check time/memory\n"
            "\tInput > ");
}