#include "main.h"

typedef struct config_t
{
    int LogStep;
    int EntranceFirstMin;
    int EntranceFirstMax;
    int ProcessFirstMaxInOA;
    int ProcessFirstMinInOA;
    int EntranceSecondMin;
    int EntranceSecondMax;
    int ProcessSecondMaxInOA;
    int ProcessSEcondMinInOA;
    int MaxNumProcess;
} config_t;

void SimulateResultArray(config_t config);
void SimulatingServiceProcess(config_t config, struct QueueForArray *QueueArrayFirst, struct QueueForArray *QueueArraySecond);
//void SimulatingServiceProcessForList(config_t config, struct QuereForList *QueueListFirst, struct QuereForList *QueueListSecond);
void SimulateResultList(config_t config);
int FindAverage(struct Table *CurTable, int Count, int flag);
void ChangeConfig(config_t *config);

int main()
{
    srand(time(NULL));
    config_t config;
    config.LogStep = 100;

    config.EntranceFirstMin = 1;
    config.EntranceFirstMax = 5;
    
    config.ProcessFirstMinInOA = 0;
    config.ProcessFirstMaxInOA = 3;
    
    config.EntranceSecondMin = 0;
    config.EntranceSecondMax = 4;
    
    config.ProcessSEcondMinInOA = 0;
    config.ProcessSecondMaxInOA = 1;
    
    config.MaxNumProcess = 1000;
    srand(time(NULL));
    int Check = 5;
    while (Check != 4)
    {
        printf("Choose > \n"
            "\t1 - Simulate Array Queue\n"
            "\t2 - Simulate List Queue\n"
            "\t3 - Change config\n"
            "\t4 - Exit\n"
            "Input > ");
        
        if (scanf("%d", &Check) == 1)
        {
            if (Check == 1)
                SimulateResultArray(config);
            else if (Check == 2)
                SimulateResultList(config);
            else if (Check == 3)
                ChangeConfig(&config);
            else if (Check == 4)
                getchar();
        }
        else
        {
            printf("Error\n");
            Check = 5;
        }
        getchar();
        getchar();
    }

    //SimulateResultArray(config);
    //SimulateResultList(config);
    return 0;
}

void ChangeConfig(config_t *config)
{
    printf("Input EntranceFirstMin and EntranceFirstMax > ");
    if (scanf("%d %d", &(config->EntranceFirstMin), &(config->EntranceFirstMax)) == 2)
    {
        printf("Input ProcessFirstMinInOA and ProcessFirstMaxInOA > ");
        if (scanf("%d %d", &(config->ProcessFirstMinInOA), &(config->ProcessFirstMaxInOA)) == 2)
        {
            printf("Input EntranceSecondMin and EntranceSecondMax > ");
            if (scanf("%d %d", &(config->EntranceSecondMin), &(config->EntranceSecondMax)) == 2)
            {
                printf("Input ProcessSEcondMinInOA and ProcessSEcondMaxInOA > ");
                if (scanf("%d %d", &(config->ProcessSEcondMinInOA), &(config->ProcessSecondMaxInOA)) == 2)
                {
                    printf("Input MaxNumProcess > ");
                    scanf("%d", &(config->MaxNumProcess));
                }
            }
        }
    }
}

void SimulateResultArray(config_t config)
{
    printf("Simulating with queue implemented by array\n");
    struct QueueForArray QueueArrayFirst, QueueArraySecond;
    InitForArray(&QueueArrayFirst);
    InitForArray(&QueueArraySecond);
    printf("%lu\n", sizeof(QueueArrayFirst) + sizeof(QueueArraySecond));
    SimulatingServiceProcess(config, &QueueArrayFirst, &QueueArraySecond);
}

void SimulatingServiceProcessForList(config_t config, struct QueueForList *QueueListFirst, struct QueueForList *QueueListSecond)
{
    struct Table *CurTable = malloc(sizeof(struct Table));
    int i = 1;
    int j = 0;
    int IsProcessFirst = 0, IsProcessSecond = 0;
    float TimeNextAppFirst = 0, TimeNextAppSecond = 0, TimeEndProcess = 0;
    int NumOfProcess = 0;
    int LenFirst = 0, LenSecond = 0;
    int count1 = 0, count2 = 0;
    TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
    TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
    
    float TimeRewind = 0;
    
    int CountInFirst = 0, CountOutFirst = 0, CountInSecond = 0, CountOutSecond = 0;

    if (TimeNextAppFirst < TimeNextAppSecond)
        TimeRewind = TimeNextAppFirst;
    else
        TimeRewind = TimeNextAppSecond;

    float TimeVirtual = 0;
    int Previous = 0;
    float TimeVirtualOfWork = 0;
    clock_t start = clock();
    int Check = 0;

    while (NumOfProcess <= config.MaxNumProcess)
    {
        TimeNextAppFirst -= TimeRewind;
        TimeNextAppSecond -= TimeRewind;
        TimeVirtual += TimeRewind;

        if (TimeNextAppFirst <= 0)
        {
            CountInFirst++;
            PushList(QueueListFirst, 1);
            LenFirst += 1;
            TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
        }

        if (TimeNextAppSecond <= 1.3)
        {
            CountInSecond++;
            PushList(QueueListSecond, 2);
            LenSecond += 1;
            TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
        }

        if (IsProcessFirst)
        {   
            
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 0)
            {
                IsProcessFirst = 0;
                NumOfProcess += 1;
            }
        }
        else if (IsProcessSecond)
        {   
            
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 0)
            {
                IsProcessSecond = 0;
            }
        }
        if (!IsProcessFirst && !IsProcessSecond && LenFirst)
        {
            CountOutFirst++;
            PopList(QueueListFirst);
            LenFirst -= 1;
            TimeEndProcess = RandTime(config.ProcessFirstMinInOA, config.ProcessFirstMaxInOA);
            IsProcessFirst = 1;
            TimeVirtualOfWork += TimeEndProcess;
        }
        if (!IsProcessFirst && !IsProcessFirst && !LenFirst && LenSecond)
        {
            CountOutSecond++;
            PopList(QueueListSecond);
            LenSecond -= 1;
            TimeEndProcess = RandTime(config.ProcessSEcondMinInOA, config.ProcessSecondMaxInOA);
            IsProcessSecond = 1;
            TimeVirtualOfWork += TimeEndProcess;
        }
        
        if ((TimeEndProcess < TimeNextAppFirst && IsProcessFirst) || (TimeEndProcess < TimeNextAppSecond && IsProcessSecond))
            TimeRewind = TimeEndProcess;
        else if (TimeNextAppFirst < TimeNextAppSecond) 
            TimeRewind = TimeNextAppFirst;
        else
            TimeRewind = TimeNextAppSecond;

        if (NumOfProcess % 100 == 0 && NumOfProcess != Previous && NumOfProcess > 0)
        {
            CurTable[j].CurLenFirst = LenFirst;
            CurTable[j].CurLenSecond = LenSecond;
            
            CurTable[j].CountInFirst = CountInFirst;
            CurTable[j].CountOutFirst = CountOutFirst;
            
            CurTable[j].CountInSecond = CountInSecond;
            CurTable[j].CountOutSecond = CountOutSecond;
            j++;
            i++;
            Previous = NumOfProcess;
            //CountInFirst = 0, CountInSecond = 0, CountOutFirst = 0, CountOutSecond = 0;
            CurTable = realloc(CurTable, i * sizeof(struct Table));
        }
    }
    clock_t end = clock();
    printf("Time of Simulating list is %lf and virtual %lf ", (float)(end - start) / CLOCKS_PER_SEC, (TimeVirtual));
    if (TimeVirtual - TimeVirtualOfWork < 0)
        TimeVirtualOfWork = 0;
    else
        TimeVirtualOfWork = TimeVirtual - TimeVirtualOfWork;
    printf("and no work %f\n", TimeVirtualOfWork);
    i--;
    printf("| Num   | Cur 1 | Cur 2 | Avr 1 | Avr 2 | In 1  | In 2  | Out 1 | Out 2 |\n");
    for (int j = 0; j < i; j++)
    {
        printf("| %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d |", (j + 1) * 100, CurTable[j].CurLenFirst, CurTable[j].CurLenSecond, FindAverage(CurTable, j + 1, 1), FindAverage(CurTable, j + 1, 0), 
            CurTable[j].CountInFirst, CurTable[j].CountInSecond, CurTable[j].CountOutFirst, CurTable[j].CountOutSecond);
        printf("\n");
    }

    printf("size of list is %lu\n", sizeof(struct QueueForList));

    printf("\n");
    int MaxInFirst = 0, MaxOutFirst = 0, MaxInSecond = 0, MaxOutSecond = 0;
    for (int j = 0; j < i; j++)
    {
        MaxInFirst += CurTable[j].CountInFirst;
        MaxInSecond += CurTable[j].CountInSecond;
        MaxOutFirst += CurTable[j].CountOutFirst;
        MaxOutSecond += CurTable[j].CountOutSecond;
    }
    printf("Max in %d and out %d first.\n", MaxInFirst, MaxOutFirst);
    printf("Max in %d and out %d second.\n", MaxInSecond, MaxOutSecond);
    free(CurTable);
}

int FindAverage(struct Table *CurTable, int Count, int flag)
{
    int sum = 0;
    for (int i = 0; i < Count; i++)
    {
        if (flag)
            sum += CurTable[i].CurLenFirst;
        else
            sum += CurTable[i].CurLenSecond;
    }
    return sum / Count;
}

void SimulateResultList(config_t config)
{
    
    printf("Simulating with queue implemented by list\n");
    struct QueueForList QueueArrayFirst, QueueArraySecond;
    InitForList(&QueueArrayFirst);
    InitForList(&QueueArraySecond);
    SimulatingServiceProcessForList(config, &QueueArrayFirst, &QueueArraySecond);
    FreeList(&QueueArrayFirst);
    FreeList(&QueueArraySecond);
}

void SimulatingServiceProcess(config_t config, struct QueueForArray *QueueArrayFirst, struct QueueForArray *QueueArraySecond)
{
    struct Table *CurTable = malloc(sizeof(struct Table));
    int i = 1;
    int j = 0;
    int IsProcessFirst = 0, IsProcessSecond = 0;
    float TimeNextAppFirst = 0, TimeNextAppSecond = 0, TimeEndProcess = 0;
    int NumOfProcess = 0;
    int LenFirst = 0, LenSecond = 0;
    int count1 = 0, count2 = 0;
    TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
    TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
    
    float TimeRewind = 0;
    
    int CountInFirst = 0, CountOutFirst = 0, CountInSecond = 0, CountOutSecond = 0;

    if (TimeNextAppFirst < TimeNextAppSecond)
        TimeRewind = TimeNextAppFirst;
    else
        TimeRewind = TimeNextAppSecond;

    float TimeVirtual = 0;
    float TimeVirtualOfWork = 0;
    int Previous = 0;
    int err = 0;
    clock_t start = clock();
    int Check = 0;

    while (NumOfProcess <= config.MaxNumProcess)
    {
        TimeNextAppFirst -= TimeRewind;
        TimeNextAppSecond -= TimeRewind;
        TimeVirtual += TimeRewind;

        if (TimeNextAppFirst <= 0)
        {
            CountInFirst++;
            InsertForArray(QueueArrayFirst, 1, &err);
            if (err)
                break;
            LenFirst += 1;
            TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
        }

        if (TimeNextAppSecond <= 1.3)
        {
            CountInSecond++;
            InsertForArray(QueueArraySecond, 2, &err);
            if (err)
                break;
            LenSecond += 1;
            TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
        }

        if (IsProcessFirst)
        {   
            
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 0)
            {
                IsProcessFirst = 0;
                NumOfProcess += 1;
            }
        }
        if (IsProcessSecond)
        {   
            
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 0)
            {
                IsProcessSecond = 0;
            }
        }
        if (!IsProcessFirst && !IsProcessSecond && LenFirst)
        {
            CountOutFirst++;
            RemoveElementxForArray(QueueArrayFirst);
            LenFirst -= 1;
            TimeEndProcess = RandTime(config.ProcessFirstMinInOA, config.ProcessFirstMaxInOA);
            IsProcessFirst = 1;
            TimeVirtualOfWork += TimeEndProcess;
        }
        if (!IsProcessFirst && !IsProcessFirst && !LenFirst && LenSecond)
        {
            CountOutSecond++;
            RemoveElementxForArray(QueueArraySecond);
            LenSecond -= 1;
            TimeEndProcess = RandTime(config.ProcessSEcondMinInOA, config.ProcessSecondMaxInOA);
            IsProcessSecond = 1;
            TimeVirtualOfWork += TimeEndProcess;
        }
        
        if ((TimeEndProcess < TimeNextAppFirst && IsProcessFirst) || (TimeEndProcess < TimeNextAppSecond && IsProcessSecond))
            TimeRewind = TimeEndProcess;
        else if (TimeNextAppFirst < TimeNextAppSecond) 
            TimeRewind = TimeNextAppFirst;
        else
            TimeRewind = TimeNextAppSecond;
        //printf("Rewind%f\n", TimeRewind);
        if (NumOfProcess % 100 == 0 && NumOfProcess != Previous && NumOfProcess > 0)
        {
            CurTable[j].CurLenFirst = LenFirst;
            CurTable[j].CurLenSecond = LenSecond;
            
            CurTable[j].CountInFirst = CountInFirst;
            CurTable[j].CountOutFirst = CountOutFirst;
            
            CurTable[j].CountInSecond = CountInSecond;
            CurTable[j].CountOutSecond = CountOutSecond;
            j++;
            i++;
            Previous = NumOfProcess;
            //CountInFirst = 0, CountInSecond = 0, CountOutFirst = 0, CountOutSecond = 0;
            CurTable = realloc(CurTable, i * sizeof(struct Table));
        }
    }
    clock_t end = clock();

    printf("Time of Simulating list is %lf and virtual %lf ", (float)(end - start) / CLOCKS_PER_SEC, (TimeVirtual));
    if (TimeVirtual - TimeVirtualOfWork < 0)
        TimeVirtualOfWork = 0;
    else
        TimeVirtualOfWork = TimeVirtual - TimeVirtualOfWork;
    printf("and no work %f\n", TimeVirtualOfWork);
    i--;
    printf("| Num   | Cur 1 | Cur 2 | Avr 1 | Avr 2 | In 1  | In 2  | Out 1 | Out 2 |\n");
    for (int j = 0; j < i; j++)
    {
       // printf("| %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d |", (j + 1) * 100, CurTable[j].CurLenFirst, CurTable[j].CurLenSecond, FindAverage(CurTable, j + 1, 1), FindAverage(CurTable, j + 1, 0), 
        ////    CurTable[j].CountInFirst, CurTable[j].CountInSecond, CurTable[j].CountOutFirst, CurTable[j].CountOutSecond);
      //  printf("\n");
    }
    printf("\n");
    int MaxInFirst = 0, MaxOutFirst = 0, MaxInSecond = 0, MaxOutSecond = 0;
    for (int j = 0; j < i; j++)
    {
        MaxInFirst += CurTable[j].CountInFirst;
        MaxInSecond += CurTable[j].CountInSecond;
        MaxOutFirst += CurTable[j].CountOutFirst;
        MaxOutSecond += CurTable[j].CountOutSecond;
    }
    printf("Max in %d and out %d first.\n", MaxInFirst, MaxOutFirst);
    printf("Max in %d and out %d second.\n", MaxInSecond, MaxOutSecond);
    free(CurTable);
}


float RandTime(int min, int max)
{
    //printf("%lf\n",  min + (max - min) * ((float) rand() / RAND_MAX));
    return min + (max - min) * ((float) rand() / RAND_MAX);
}




/*
void SimulatingServiceProcess(config_t config, struct QueueForArray *QueueArrayFirst, struct QueueForArray *QueueArraySecond)
{
    int IsProcessFirst = 0, IsProcessSecond = 0;
    float TimeNextAppFirst = 0, TimeNextAppSecond = 0, TimeEndProcess = 0;
    //int NumOfEntranceAppFirst = 0;
    int NumOfProcess = 0;
    int LenFirst = 0, LenSecond = 0;
    int count1 = 0, count2 = 0;
    TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
    TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
    
    float TimeRewind = 0;
    
    if (TimeNextAppFirst < TimeNextAppSecond)
        TimeRewind = TimeNextAppFirst;
    else
        TimeRewind = TimeNextAppSecond;
    float TimeVirtual = 0;
    clock_t start = clock();

    while (NumOfProcess < 1000)
    {
        TimeNextAppFirst -= TimeRewind;
        TimeNextAppSecond -= TimeRewind;
        TimeVirtual += TimeRewind;
        if (TimeNextAppFirst <= 1E-5)
        {
            InsertForArray(QueueArrayFirst, 1);
            LenFirst += 1;
            TimeNextAppFirst = RandTime(config.EntranceFirstMin, config.EntranceFirstMax);
        }

        if (TimeNextAppSecond <= 1E-5)
        {
            InsertForArray(QueueArraySecond, 2);
            LenSecond += 1;
            TimeNextAppSecond = RandTime(config.EntranceSecondMin, config.EntranceSecondMax);
        }

        if (IsProcessFirst)
        {   
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 1E-5)
            {
                IsProcessFirst = 0;
                NumOfProcess += 1;
            }
        }
        else if (IsProcessSecond)
        {   
            TimeEndProcess -= TimeRewind;
            if (TimeEndProcess <= 1E-5)
            {
                IsProcessSecond = 0;
                NumOfProcess += 1;
            }
        }
        if (!IsProcessFirst && !IsProcessSecond && LenFirst)
        {
            RemoveElementxForArray(QueueArrayFirst);
            LenFirst -= 1;
            TimeEndProcess = RandTime(config.ProcessFirstMinInOA, config.ProcessFirstMaxInOA);
            IsProcessFirst = 1;
        }
        else if (!IsProcessFirst && !IsProcessFirst && !LenFirst && LenSecond)
        {
            RemoveElementxForArray(QueueArraySecond);
            LenSecond -= 1;
            TimeEndProcess = RandTime(config.ProcessSEcondMinInOA, config.ProcessSecondMaxInOA);
            IsProcessSecond = 1;
        }

        if ((TimeEndProcess < TimeNextAppFirst && IsProcessFirst) || (TimeEndProcess < TimeNextAppSecond && IsProcessSecond))
            TimeRewind = TimeEndProcess;
        else if (TimeNextAppFirst < TimeNextAppSecond) 
            TimeRewind = TimeNextAppFirst;
        else
            TimeRewind = TimeNextAppSecond;
    }
    clock_t end = clock();
    printf("Time of Simulating array is %lf and virtual %lf\n", (float)(end - start) / CLOCKS_PER_SEC, (TimeVirtual));
}
*/