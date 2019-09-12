void insert_in_place(double *array, int count_of_numbers, int need_position, double result)
{
    for (int i = count_of_numbers - 1; i >= need_position; i--)
        swap((array + i), (array + i - 1));
    *(array + need_position - 1) = result;
}

void swap(double *first, double *second)
{
    double temp = *first;
    *first = *second;
    *second = temp;
}

void see_out(double *array, int count_of_numbers)
{
    for (int i = 0; i < count_of_numbers; i++)
        printf("%lf ", *(array + i));
    printf("\n");
}

void insert(double *array, int count_of_numbers, double result, int position)
{
    insert_in_place(array, count_of_numbers + 1, position, result);
    insert_in_place(array, count_of_numbers + 2, 1, result);
    *(array + count_of_numbers + INSERT_INDEX - 1) = result;
}

void check_insert_in_place()
{
	double array[6] = {1., 2., 3., 4., 5., 0.}
	double result = 10.;
	insert_in_place(array, 6, 3, result);
	double check_array[6] = {1., 2., result, 3., 4., 5.};
	int count = 0;
	for (int i = 0; i < 6; i++)
		if (array[i] == check_array[i])
			count++;
	if (count == 6)
		printf("Correct work of inster in place\n";
	
	

}
