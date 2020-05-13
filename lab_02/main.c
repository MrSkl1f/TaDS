/*
Ввести список стран, содержащий название страны, количество
жителей, столицу, материк, 

основной вид туризма (экскурсионный - количество объектов, основной вид (природа, история, искусство);
пляжный – основной сезон, температура воздуха и воды, время полета до страны; 
спортивный – вид спорта (горные лыжи, серфинг, восхождения), минимальная стоимость отдыха). 

Вывести список стран на выбранном материке, где можно заняться указанным видом отдыха.
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Tourism
{
    char country[20];
    char continent[20];
    char city_center[20];
    long int population;
    char flag[20];
    union 
    {
        struct excursion_tourism 
        {
            long int count_of_objects;
            char main_type[20];
        } excursion_tourism;

        struct beach_tourism
        {
            char season[20];
            long int temperature_air;
            long int temperature_water;
            long int hours_in_flight;
        } beach_tourism;

        struct sports_tourism
        {
            char sports_type[20];
            long int min_price;
        } sports_tourism;
    } tourism_type;
} Tourism;

struct KeyTable
{
    int index;
    int population;
} KeyTable;

long int read_file(char *filename, struct Tourism *new, long int count);
void display_table(struct Tourism *tourists, long int count);
void add_record(long int *count, struct Tourism *new);
void delete_record(struct Tourism *tourists, long int *count);
void sort_tourism_table(struct Tourism *tourists, long int count);
void create_key_table(struct Tourism *tourists, struct KeyTable *keys, long int count);
void show_key_table(struct KeyTable *keys, long int count);
void sort_key_table(struct KeyTable *keys, long int count);
void display_countries(struct Tourism *tourists, int count);
void save_file(struct Tourism *tourists, int count);
void check_soutring(struct Tourism *tourists, struct KeyTable *keys, long int count);
void sort_table_buble(struct Tourism *keys, long int count);
void sort_keys_qsort(struct KeyTable *keys, long int count);
int comp_key(const void *a, const void *b);
void display_table_by_keys(struct Tourism *tourists, struct KeyTable *keys, long int count);
int check_keys_dimention(struct KeyTable *keys, long int count);
int check_table_dimention(struct Tourism *tourists, long int count);

int flag_sort = 0;

long int menu(struct Tourism *tourists, struct KeyTable *keys, long int *count, int *flag)
{
    long int operation = 1;
    getchar();
    printf("Press Enter\n");
    printf("\nMENU (choose operation):\n"
           "1 - Display table\n" // Вывести таблицу
           "2 - Add record\n" // Добавить запись
           "3 - Delete record\n" // Удалить запись
           "4 - Display countries on the specified continent\n" // Вывести по материку
           "5 - Sort table\n"
           "6 - Create key table\n" 
           "7 - Show key table\n" // Проверка эффективности
           "8 - Sort key table\n" // Сравнение методов
           "9 - Save file\n"
           "10 - Check sorting\n"
           "11 - Display table by keys\n"
           "12 - Load file\n"
           "0 - Exit\n");
    printf("Input operation > ");
    if (scanf("%ld", &operation) == 1)
    {
        if (operation == 0)
        {
            printf("Exit\n");
            return 0;
        }
        else if (operation == 1)
        {
            //printf("You should input max 20 symbols of words and 212 147 483 64 is max population\n");
            printf("Display table\n");
            display_table(tourists, *count);
        }
        else if (operation == 2)
        {
            printf("Add record\n");
            printf("You should input max 20 symbols of words and 212 147 483 64 is max population\n");
            if (*count <= 50)
            {
                add_record(count, tourists);
                create_key_table(tourists, keys, *count);
                *flag = 0;
            }
            else
            {
                printf("Over 50 records!\n");
            }
            
        }   
        else if (operation == 3)
        {            
            printf("You should input max 20 symbols of words and 212 147 483 64 is max population\n");
            printf("Delete record\n");
            delete_record(tourists, count);
            create_key_table(tourists, keys, *count);
            *flag = 0;
        }
        else if (operation == 4)
        {
            printf("You should input max 20 symbols of words and 212 147 483 64 is max population\n");
            display_countries(tourists, *count);
        }
        else if (operation == 5)
        {
            sort_tourism_table(tourists, *count);
            printf("Table sorted!\n");
            flag_sort = 1;
        }
        else if (operation == 6)
        {
            printf("Create key table\n");
            create_key_table(tourists, keys, *count);
            *flag = 1;
        }
        else if (operation == 7)
        {
            printf("Show key table\n");
            if (*flag)
                show_key_table(keys, *count);
            else
                printf("You should create key table!\n");
        }
        else if (operation == 8)
        {
            printf("Sort key table\n");
            if (*flag)
                sort_key_table(keys, *count);
            else
                printf("You should create key table!\n");
        }
        else if (operation == 9)
        {
            printf("Save into file\n");
            save_file(tourists, *count);
        }
        else if (operation == 10)
        {
            if (*flag)
                check_soutring(tourists, keys, *count);
            else
                printf("You must create new Key Table!\n");
        }
        else if (operation == 11)
        {
            if (*flag)
                if (flag_sort == 0)
                    display_table_by_keys(tourists, keys, *count);
                else
                    printf("You already sorted the table\n");
            else
                printf("You must create new Key Table!\n");
        }
        else if (operation == 12)
        {
            read_file("table.txt", tourists, *count);
            printf("Loaded!\n");
            *flag = 0;
            flag_sort = 0;
        }
        else
        {
            printf("Invalid input.\n");
            getchar();
        }
    }
    else
    {
        printf("\nInvalid input.\n");
        getchar();
    }
    return -1;
}

int check_table_dimention(struct Tourism *tourists, long int count)
{
    int dimention = 0;
    for (int i = 0; i < count; i++)
        dimention += sizeof(tourists[i]);
    return dimention;
}

int check_keys_dimention(struct KeyTable *keys, long int count)
{
    int dimention = 0;
    for (int i = 0; i < count; i++)
        dimention += sizeof(keys[i]);
    return dimention;
}

void display_table_by_keys(struct Tourism *tourists, struct KeyTable *keys, long int count)
{
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    for (long int i = 0; i < count; i++)
    {
        printf("[Student %ld]\n", i + 1);
        printf("Index in key table > %ld\n", keys[i].index);
        printf("Country > %s\n", tourists[keys[i].index].country);
        printf("Continent > %s\n", tourists[keys[i].index].continent);
        printf("City center > %s\n", tourists[keys[i].index].city_center);
        printf("Population > %ld\n", tourists[keys[i].index].population);
        printf("Tourism type > %s\n", tourists[keys[i].index].flag);
        if (!strcmp(tourists[keys[i].index].flag, check1))
        {
            printf("Count of objects > %ld\n", tourists[keys[i].index].tourism_type.excursion_tourism.count_of_objects);
            printf("Type of excursion > %s", tourists[keys[i].index].tourism_type.excursion_tourism.main_type);
        }
        else if (!strcmp(tourists[keys[i].index].flag, check2))
        {
            printf("Season > %s\n", tourists[keys[i].index].tourism_type.beach_tourism.season);
            printf("Temperature of air > %ld\n", tourists[keys[i].index].tourism_type.beach_tourism.temperature_air);
            printf("Temperature of water > %ld\n", tourists[keys[i].index].tourism_type.beach_tourism.temperature_water);
            printf("Hours in flight > %ld\n", tourists[keys[i].index].tourism_type.beach_tourism.hours_in_flight);
        }
        else if (!strcmp(tourists[keys[i].index].flag, check3))
        {
            printf("%s\n", tourists[keys[i].index].tourism_type.sports_tourism.sports_type);
            printf("%ld\n", tourists[keys[i].index].tourism_type.sports_tourism.min_price);
        }       
        printf("\n\n");






/*
        for (long int i = 0; i < 167; i++)
            printf("-");
        printf("\n");
        if (!strcmp(tourists[keys[i].index].flag, check1))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s \n", "Country", "Continent", "City Center", "Population", "Tourism type", "Count objects", "Type of Excursion");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[keys[i].index]).country, tourists[i].continent, tourists[keys[i].index].city_center, tourists[keys[i].index].population, tourists[keys[i].index].flag);
            printf("%-18d %-18s\n", tourists[keys[i].index].tourism_type.excursion_tourism.count_of_objects, tourists[keys[i].index].tourism_type.excursion_tourism.main_type);
        }
        if (!strcmp(tourists[keys[i].index].flag, check2))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s %-18s %-18s\n", "Country", "Continent", "City Center", "Population", "Tourism type", "Season", "Temprature of air", "Temperature water", "Hours in flight");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[keys[i].index]).country, tourists[keys[i].index].continent, tourists[keys[i].index].city_center, tourists[keys[i].index].population, tourists[keys[i].index].flag);
            printf("%-18s %-18d %-18d %-18d\n", tourists[keys[i].index].tourism_type.beach_tourism.season, tourists[keys[i].index].tourism_type.beach_tourism.temperature_air, tourists[keys[i].index].tourism_type.beach_tourism.temperature_water, tourists[keys[i].index].tourism_type.beach_tourism.hours_in_flight);
        }
        if (!strcmp(tourists[keys[i].index].flag, check3))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s\n", "Country", "Continent", "City Center", "Population", "Tourism type", "Sports type", "Min price");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[keys[i].index]).country, tourists[keys[i].index].continent, tourists[keys[i].index].city_center, tourists[keys[i].index].population, tourists[keys[i].index].flag);
            printf("%-18s %-18d\n", tourists[keys[i].index].tourism_type.sports_tourism.sports_type, tourists[keys[i].index].tourism_type.sports_tourism.min_price);
        }
        */
    }
}

void check_soutring(struct Tourism *tourists, struct KeyTable *keys, long int count)
{
    save_file(tourists, count);
    double check_time = 0;
    double time_spent;
    for (int i = 0; i < 2000; i++)
    {
        read_file("table.txt", tourists, count);
        clock_t begin = clock();
        sort_tourism_table(tourists, count);
        clock_t end = clock();
        time_spent = (double)(end - begin);
        check_time += time_spent;
    }
    check_time = (check_time);
    printf("Result of sorting table with qsort is > %.6lf\n", check_time);
    
    check_time = 0;
    read_file("table.txt", tourists, count);
    for (int i = 0; i < 2000; i++)
    {
        read_file("table.txt", tourists, count);
        clock_t begin = clock();
        sort_table_buble(tourists, count);
        clock_t end = clock();
        time_spent = (double)(end - begin);
        check_time += time_spent;
    }
    check_time = (check_time);
    printf("Result of sorting table with buble is > %.6lf\n", check_time);

    check_time = 0;
    read_file("table.txt", tourists, count);
    for (int i = 0; i < 2000; i++)
    {
        create_key_table(tourists, keys, count);
        clock_t begin = clock();
        sort_keys_qsort(keys, count);
        clock_t end = clock();
        time_spent = (double)(end - begin);
        check_time += time_spent;
    }
    check_time = (check_time);
    printf("Result of sorting key table with qsort is > %.6lf\n", check_time);

    check_time = 0;
    read_file("table.txt", tourists, count);
    for (int i = 0; i < 2000; i++)
    {
        create_key_table(tourists, keys, count);
        clock_t begin = clock();
        sort_key_table(keys, count);
        clock_t end = clock();
        time_spent = (double)(end - begin);
        check_time += time_spent;
    }
    check_time = (check_time);
    printf("Result of sorting key table with buble is > %.6lf\n", check_time);
    double dimention = (double)check_table_dimention(tourists, count) / (double)check_keys_dimention(keys, count);
    printf("Procenting dimention %lf\n", dimention);
    printf("Dimention of structs > %ld %ld\n", check_table_dimention(tourists, count), check_keys_dimention(keys, count));
}

void save_file(struct Tourism *tourists, int count)
{
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    FILE *file = fopen("table.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n%s\n%s\n%ld\n%s\n", tourists[i].country, tourists[i].continent, tourists[i].city_center, tourists[i].population, tourists[i].flag);
        if (!strcmp(tourists[i].flag, check1))
            fprintf(file, "%ld\n%s\n", tourists[i].tourism_type.excursion_tourism.count_of_objects, tourists[i].tourism_type.excursion_tourism.main_type);
        else if (!strcmp(tourists[i].flag, check2))
            fprintf(file, "%s\n%ld\n%ld\n%ld\n", tourists[i].tourism_type.beach_tourism.season, tourists[i].tourism_type.beach_tourism.temperature_air, tourists[i].tourism_type.beach_tourism.temperature_water, tourists[i].tourism_type.beach_tourism.hours_in_flight);
        else if (!strcmp(tourists[i].flag, check3))
            fprintf(file, "%s\n%ld\n", tourists[i].tourism_type.sports_tourism.sports_type, tourists[i].tourism_type.sports_tourism.min_price);
    }
    fclose(file);
}

void display_countries(struct Tourism *tourists, int count)
{
    printf("Input your continent and type of sports > ");

    char cur[20];
    char cur_sport[20];
    if (scanf("%s", cur) == 1 && scanf("%s", cur_sport))
    {
        int check = 0;
        printf("We are starting searching it...\n\n");
        for (int i = 0; i < count; i++)
        {
            if (!strcmp(tourists[i].continent, cur))
            {
                if (!strcmp(tourists[i].flag, "Sport") && (!strcmp(tourists[i].tourism_type.sports_tourism.sports_type, cur_sport)))
                {
                    printf("> %s\n", tourists[i].country);
                    check++;
                }
            }
        }
        if (check == 0)
            printf("We couldn't find any countries\n\n");
        else
            printf("\nWe could find %ld countries\n", check);
    }
    else
    {
        printf("Error Input\n");
    }
    
}

void sort_key_table(struct KeyTable *keys, long int count)
{
    int cur = 1;
    while (cur < count)
    {
        for (int i = 0; i < (count - cur); i++)
        {
            if (keys[i].population > keys[i + 1].population)
            {
                struct KeyTable cur_table = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = cur_table;
            }
        }
        cur++;
    }
}

void sort_table_buble(struct Tourism *keys, long int count)
{
    int cur = 1;
    while (cur < count)
    {
        for (int i = 0; i < (count - cur); i++)
        {
            if (keys[i].population > keys[i + 1].population)
            {
                struct Tourism cur_table = keys[i];
                keys[i] = keys[i + 1];
                keys[i + 1] = cur_table;
            }
        }
        cur++;
    }
}

void show_key_table(struct KeyTable *keys, long int count)
{
    for (int i = 0; i < count; i++)
        printf("%-3ld %ld\n", keys[i].index, keys[i].population);
}

void create_key_table(struct Tourism *tourists, struct KeyTable *keys, long int count)
{
    for (int i = 0; i < count; i++)
    {
        keys[i].index = i;
        keys[i].population = tourists[i].population;
    }
}

int comp(const void *a, const void *b)
{
    return ((struct Tourism*) a)->population - ((struct Tourism*) b)->population;
}

int comp_key(const void *a, const void *b)
{
    return ((struct KeyTable*) a)->population - ((struct KeyTable*) b)->population;
}

void sort_keys_qsort(struct KeyTable *keys, long int count)
{
    qsort(keys, count, sizeof(struct KeyTable), comp_key);
}

void sort_tourism_table(struct Tourism *tourists, long int count)
{
    qsort(tourists, count, sizeof(struct Tourism), comp);
}

void display_table(struct Tourism *tourists, long int count)
{
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    for (long int i = 0; i < count; i++)
    {
        printf("[Student %ld]\n", i + 1);
        printf("Country > %s\n", tourists[i].country);
        printf("Continent > %s\n", tourists[i].continent);
        printf("City center > %s\n", tourists[i].city_center);
        printf("Population > %ld\n", tourists[i].population);
        printf("Tourism type > %s\n", tourists[i].flag);
        if (!strcmp(tourists[i].flag, check1))
        {
            printf("Count of objects > %ld\n", tourists[i].tourism_type.excursion_tourism.count_of_objects);
            printf("Type of excursion > %s", tourists[i].tourism_type.excursion_tourism.main_type);
        }
        else if (!strcmp(tourists[i].flag, check2))
        {
            printf("Season > %s\n", tourists[i].tourism_type.beach_tourism.season);
            printf("Temperature of air > %ld\n", tourists[i].tourism_type.beach_tourism.temperature_air);
            printf("Temperature of water > %ld\n", tourists[i].tourism_type.beach_tourism.temperature_water);
            printf("Hours in flight > %ld\n", tourists[i].tourism_type.beach_tourism.hours_in_flight);
        }
        else if (!strcmp(tourists[i].flag, check3))
        {
            printf("%s\n", tourists[i].tourism_type.sports_tourism.sports_type);
            printf("%ld\n", tourists[i].tourism_type.sports_tourism.min_price);
        }       
        printf("\n\n");
        /*
        printf("\n");
        if (!strcmp(tourists[i].flag, check1))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s \n", "Country", "Continent", "City Center", "Population", "Tourism type", "Count objects", "Type of Excursion");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[i]).country, tourists[i].continent, tourists[i].city_center, tourists[i].population, tourists[i].flag);
            printf("%-18d %-18s\n", tourists[i].tourism_type.excursion_tourism.count_of_objects, tourists[i].tourism_type.excursion_tourism.main_type);
        }
        if (!strcmp(tourists[i].flag, check2))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s %-18s %-18s\n", "Country", "Continent", "City Center", "Population", "Tourism type", "Season", "Temprature of air", "Temperature water", "Hours in flight");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[i]).country, tourists[i].continent, tourists[i].city_center, tourists[i].population, tourists[i].flag);
            printf("%-18s %-18d %-18d %-18d\n", tourists[i].tourism_type.beach_tourism.season, tourists[i].tourism_type.beach_tourism.temperature_air, tourists[i].tourism_type.beach_tourism.temperature_water, tourists[i].tourism_type.beach_tourism.hours_in_flight);
        }
        if (!strcmp(tourists[i].flag, check3))
        {
            printf("%-18s %-18s %-18s %-18s %-18s %-18s %-18s\n", "Country", "Continent", "City Center", "Population", "Tourism type", "Sports type", "Min price");
            printf("%-18s %-18s %-18s %-18d %-18s ", (tourists[i]).country, tourists[i].continent, tourists[i].city_center, tourists[i].population, tourists[i].flag);
            printf("%-18s %-18d\n", tourists[i].tourism_type.sports_tourism.sports_type, tourists[i].tourism_type.sports_tourism.min_price);
        }
        */
    }
}

long int read_file(char *filename, struct Tourism *new, long int count)
{
    long int err = 0;
    FILE *file = fopen(filename, "r");
    count = 0;
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    while (err == 0)
    {
        if (fscanf(file, "%s", new[count].country) == 1)
        {
            if (fscanf(file, "%s", new[count].continent) == 1)
            {
                if (fscanf(file, "%s", new[count].city_center) == 1)
                {
                    if (fscanf(file, "%ld", &new[count].population) == 1)
                    {
                        if (fscanf(file, "%s", new[count].flag) == 1)
                        {
                            if (!strcmp(new[count].flag, check1))
                            {
                                if (fscanf(file, "%ld", &(new[count].tourism_type.excursion_tourism.count_of_objects)) == 1)
                                    if (fscanf(file, "%s", (new[count].tourism_type.excursion_tourism.main_type)) == 1)
                                        err = 0;
                                    else
                                        err = 1;
                                else
                                    err = 1;
                            }
                            else if (!strcmp(new[count].flag, check2))
                            {
                                if (fscanf(file, "%s", new[count].tourism_type.beach_tourism.season) == 1)
                                    if (fscanf(file, "%ld", &(new[count].tourism_type.beach_tourism.temperature_air)) == 1)
                                        if (fscanf(file, "%ld", &(new[count].tourism_type.beach_tourism.temperature_water)) == 1)
                                            if (fscanf(file, "%ld", &(new[count].tourism_type.beach_tourism.hours_in_flight)) == 1)
                                                err = 0;
                                            else
                                                err = 1;
                                        else
                                            err = 1;
                                    else 
                                        err = 1;
                                else
                                    err = 1;
                            }   
                            else if (!strcmp(new[count].flag, check3))
                            {
                                if (fscanf(file, "%s", new[count].tourism_type.sports_tourism.sports_type) == 1)
                                    if (fscanf(file, "%ld", &new[count].tourism_type.sports_tourism.min_price) == 1)
                                        err = 0;
                                    else
                                        err = 1;
                                else
                                    err = 1;
                            }
                            else
                                err = 1;
                        }
                        else
                            err = 1;
                    }
                    else
                        err = 1;
                }
                else
                    err = 1;
            }
            else
                err = 1;
        }
        else
            err = 1;
        if (err == 0)
            count++;
        else
            break;
    }
    fclose(file);
    if (err == 1 && count == 0)
        return 0;
    else
        return count;
}

void add_record(long int *count, struct Tourism *new)
{
    char filename[] = "table.txt";
    long int err = 0;
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    FILE *file = fopen(filename, "a");
    printf("Input country > ");
    if (scanf("%s", new[*count].country) == 1)
    {    
        printf("Input continent > ");
        if (scanf("%s", new[*count].continent) == 1)
        {       
            printf("Input city center > ");
            if (scanf("%s", new[*count].city_center) == 1)
            {
                printf("Input population > ");
                if (scanf("%ld", &new[*count].population) == 1)
                {
                    printf("Input type of tourism (Tourism, Beach, Sport) > ");
                    if (scanf("%s", new[*count].flag) == 1)
                    {
                        if (!strcmp(new[*count].flag, check1))
                        {
                            printf("Input count of objects > ");
                            if (scanf("%ld", &(new[*count].tourism_type.excursion_tourism.count_of_objects)) == 1)
                            {
                                printf("Input type of excursion > ");
                                if (scanf("%s", (new[*count].tourism_type.excursion_tourism.main_type)) == 1)
                                    err = 0;
                                else
                                    err = 1;
                            }
                            else
                                err = 1;
                        }
                        else if (!strcmp(new[*count].flag, check2))
                        {
                            printf("Input season > ");
                            if (scanf("%s", new[*count].tourism_type.beach_tourism.season) == 1)
                            {
                                printf("Input temperature of air > ");
                                if (scanf("%ld", &(new[*count].tourism_type.beach_tourism.temperature_air)) == 1)
                                {
                                    printf("Input temperature of water > ");
                                    if (scanf("%ld", &(new[*count].tourism_type.beach_tourism.temperature_water)) == 1)
                                    {
                                        printf("Input hours in flight > ");
                                        if (scanf("%ld", &(new[*count].tourism_type.beach_tourism.hours_in_flight)) == 1)
                                            err = 0;
                                        else
                                            err = 1;
                                    }
                                    else
                                        err = 1;
                                }
                                else 
                                    err = 1;
                            }
                            else
                                err = 1;
                        }   
                        else if (!strcmp(new[*count].flag, check3))
                        {
                            printf("Input type of sport > ");
                            if (scanf("%s", new[*count].tourism_type.sports_tourism.sports_type) == 1)
                            {    
                                printf("Input min price > ");
                                if (scanf("%ld", &new[*count].tourism_type.sports_tourism.min_price) == 1)
                                    err = 0;
                                else
                                    err = 1;
                            }
                            else
                                err = 1;
                        }
                        else
                            err = 1; 
                    }
                    else
                        err = 1;
                }
                else
                    err = 1;
            }
            else
                err = 1;
        }
        else
            err = 1;
    }
    else
        err = 1;
    if (err == 1)
        printf("Wong input\n");
    else
    {
        fprintf(file, "%s\n%s\n%s\n%ld\n%s\n", (new[*count]).country, new[*count].continent, new[*count].city_center, new[*count].population, new[*count].flag);
        if (!strcmp(new[*count].flag, check1))
        {
            fprintf(file, "%ld\n%s\n", new[*count].tourism_type.excursion_tourism.count_of_objects, new[*count].tourism_type.excursion_tourism.main_type);
        }
        else if (!strcmp(new[*count].flag, check2))
        {
            fprintf(file, "%s\n%ld\n%ld\n%ld\n", new[*count].tourism_type.beach_tourism.season, new[*count].tourism_type.beach_tourism.temperature_air, new[*count].tourism_type.beach_tourism.temperature_water, new[*count].tourism_type.beach_tourism.hours_in_flight);
        }
        else if (!strcmp(new[*count].flag, check3))
        {
            fprintf(file, "%s\n%ld\n", new[*count].tourism_type.sports_tourism.sports_type, new[*count].tourism_type.sports_tourism.min_price);         
        }
        *count += 1;
    }
    fclose(file);
}

void delete_record(struct Tourism *tourists, long int *count)
{
    struct Tourism cur;
    long int index = -1;
    long int err = 0;
    char check1[] = "Tourism";
    char check2[] = "Beach";
    char check3[] = "Sport";
    printf("Input country, continent, city center, population, type of tourism (Tourism, Beach, Sport) > ");
    if (scanf("%s %s %s %ld %s", cur.country, cur.continent, cur.city_center, &cur.population, cur.flag) == 5)
    {
        if (!strcmp(cur.flag, check1))
        {
            printf("Input count of objects, type of tourism > ");
            if (scanf("%ld %s", &cur.tourism_type.excursion_tourism.count_of_objects, cur.tourism_type.excursion_tourism.main_type) == 2)
            {
                err = 1;
            }
        }
        else if (!strcmp(cur.flag, check2))
        {
            printf("Input season, temperature of air, water, hours in flight > ");
            if (scanf("%s %ld %ld %ld", cur.tourism_type.beach_tourism.season, &cur.tourism_type.beach_tourism.temperature_air, &cur.tourism_type.beach_tourism.temperature_water, &cur.tourism_type.beach_tourism.hours_in_flight) == 4)
            {
                printf("Yes\n");
                err = 1;
            }
        }
        else if (!strcmp(cur.flag, check3))
        {
            printf("Input sports type, min price > ");
            if (scanf("%s %ld", cur.tourism_type.sports_tourism.sports_type, &cur.tourism_type.sports_tourism.min_price))
            {
                printf("Yes\n");
                err = 1;
            }
        }
        else
            printf("Wrong input\n");
    }
    else
        printf("Wrong input\n");

    if (err)
    {
        for (long int i = 0; i < *count; i++)
        {
            if (!strcmp(cur.country, tourists[i].country) && !strcmp(cur.continent, tourists[i].continent) && !strcmp(cur.city_center, tourists[i].city_center) && (cur.population == tourists[i].population))
            {
                if (!strcmp(cur.flag, check1) && !strcmp(cur.flag, tourists[i].flag))
                {
                    if (cur.tourism_type.excursion_tourism.count_of_objects == tourists[i].tourism_type.excursion_tourism.count_of_objects && !strcmp(cur.tourism_type.excursion_tourism.main_type, tourists[i].tourism_type.excursion_tourism.main_type))
                    {
                        index = i;
                        break;
                    }
                }
                else if (!strcmp(cur.flag, check2) && !strcmp(cur.flag, tourists[i].flag))
                {
                    if (!strcmp(cur.tourism_type.beach_tourism.season, tourists[i].tourism_type.beach_tourism.season) && cur.tourism_type.beach_tourism.temperature_air == tourists[i].tourism_type.beach_tourism.temperature_air)
                    {
                        if (cur.tourism_type.beach_tourism.temperature_water == tourists[i].tourism_type.beach_tourism.temperature_water && cur.tourism_type.beach_tourism.hours_in_flight == tourists[i].tourism_type.beach_tourism.hours_in_flight)
                        {
                            index = i;
                            break;
                        }
                    }
                }
                else if (!strcmp(cur.flag, check3) && !strcmp(cur.flag, tourists[i].flag))
                {
                    if (!strcmp(cur.tourism_type.sports_tourism.sports_type,  tourists[i].tourism_type.sports_tourism.sports_type) && tourists[i].tourism_type.sports_tourism.min_price == cur.tourism_type.sports_tourism.min_price)
                    {
                        index = i;
                        break;
                    }
                }
            }
            
        }
        if (index == -1)
            printf("We couldn't find anything\n");
        else
        {
            for (long int i = index; i < *count - 1; i++)
                tourists[i] = tourists[i + 1];
            *count -= 1;
            printf("Done!\n");
        }
    }
    
}

long int main(void)
{
    printf("Press Enter\n");
    int check_flag = 0;
    char filename[] = "table.txt";
    struct Tourism tourists[50];
    struct KeyTable keys[50]; 
    long int count = 0;
    count = read_file(filename, tourists, count);
    printf("Press Enter\n");
    while (menu(tourists, keys, &count, &check_flag) == -1);
    return 0;
}