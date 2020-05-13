#ifndef MAIN_H
#define MAIN_H



int input_float(int *m_m, int *size, int *sign, int *exponent);
void move_digits(int *arr_, int size, int poryadok);
void normalize_float(int *arr, int *size, int dot, int *exponent);
void output_res(int *arr, int size, int exp, int sign);
void multiplication(int *arr_first, int *arr_second, int *res, int size_f, int size_s);
void print_array(const int *array, int size);
void rounding(int *arr, int size, int last_digit);
int zero_array(int *array, int size);
void clean(int *array, int size);
#endif // MAIN_H