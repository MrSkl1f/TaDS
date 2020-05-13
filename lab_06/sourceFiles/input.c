#include "../headerFiles/mainhead.h"
#include "../headerFiles/input.h"

void inputFromFile(int **array, int *size)
{
    *size = 1;
    *array = malloc(*size * sizeof(int));
    FILE *newFile;
    //newFile = fopen("input.txt", "r");
    if ((newFile = fopen("input.txt", "r")) == NULL)
    {
        printf("Can not open the file!\n");
        getchar();
        return;
    }
    fscanf(newFile, "%d", size);
    *array = realloc(*array, *size * sizeof(int));
    int cur;
    for (int i = 0; i < *size; i++)
    {
        fscanf(newFile, "%d", &cur);
        (*array)[i] = cur;
    }
    fclose(newFile);
}

void deleteValueFromFile(int **array, int *size, int key)
{
    int index = -1;
    for (int i = 0; i < *size; i++)
    {
        if ((*array)[i] == key)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        for (int i = index; i < *size - 1; i++)
            (*array)[i] = (*array)[i + 1];
        (*size)--;
        *array = realloc(*array, *size * sizeof(int));
        inputInFile(*array, *size);
    }
    else
        printf("Couldn't find anything!\n");
}

void inputInFile(int *array, int size)
{
    FILE *newFile;
    if ((newFile = fopen("input.txt", "w")) == NULL)
    {
        printf("Can not open the file!\n");
        getchar();
        return;
    }
    fprintf(newFile, "%d ", size);
    for (int i = 0; i < size; i++)
        fprintf(newFile, "%d ", array[i]);
    fclose(newFile);
}