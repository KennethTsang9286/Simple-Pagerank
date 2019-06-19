#include "helper.h"

void double_arr_to_float_arr(double* darr, float* farr, size_t n)
{
	for(int i = 0;  i < n; i++) {
		farr[i] = (float) darr[i];
	}
}

void long_double_arr_to_float_arr(long double* darr, float* farr, size_t n)
{
	for(int i = 0;  i < n; i++) {
		farr[i] = (float) darr[i];
	}
}

void show_arr_c(char** argv)
{
	int count = 0;
	while(argv[count] != NULL) {
		printf("%s\n", argv[count]);
		count++;
	}
}

void show_arr_f(float* argv)
{
	int MAX = 7;
	int count = 0;
	while( count < MAX  && argv[count] != '\0') {
		printf("%f\n", argv[count]);
		count++;
	}
}

void show_arr_ld(long double* argv)
{
	int MAX = 7;
	int count = 0;
	while( count < MAX  && argv[count] != '\0') {
		printf("%.10Lf\n", argv[count]);
		count++;
	}
}

void show_arr_int(int* argv)
{
	int MAX = 7;
	int count = 0;
	while( count < MAX ) {
		printf("%d\n", argv[count]);
		count++;
	}
}

void copy_list_to_arr(float* pr, float* tmp_pr, size_t N)
{
	for(int i = 0; i < N; i++) {
		tmp_pr[i] = pr[i];
	}
}

void copy_darr_to_darr(double* pr, double* tmp_pr, size_t N)
{
	for(int i = 0; i < N; i++) {
		tmp_pr[i] = pr[i];
	}
}

void copy_ldarr_to_ldarr(long double* pr, long double* tmp_pr, size_t N)
{
	for(int i = 0; i < N; i++) {
		tmp_pr[i] = pr[i];
	}
}

int _get_order_from_arr(const void* a, const void* b)
{
	return ( ((float*)a)[1] < ((float*)b)[1] );
}

int* get_orders_from_arr(float* arr, size_t nV)
{
	float pairs[nV][2];
	for (int i = 0; i < nV; i++) {
		pairs[i][0] = (float) i;
		pairs[i][1] = arr[i];
	}
	qsort(pairs, nV, sizeof(float) * 2, _get_order_from_arr);
	int* output = malloc(sizeof(int) * nV);
	for(int i = 0; i < nV; i++) {
		output[i] = (int) pairs[i][0];
	}
	return output;
}

bool is_in_arr(char* arr[], char word[], size_t size)
{
	for (int i = 0; i < size; i++) {
		if(strcmp(arr[i], word) == 0) {
			return true;
		}
	}
	return false;
}

//https://stackoverflow.com/questions/1515195/how-to-remove-n-or-t-from-a-given-string-in-c
void RemoveSpaces(char* s)
{
	char* p2 = s;
	while(*s != '\0') {
		if(*s != '\t' && *s != '\n' && *s != ' ' && *s != '\r' && *s != '\f') {
			*p2++ = *s++;
		}
		else {
			++s;
		}
	}
	*p2 = '\0';
}

void str_to_lower(char* str)
{
	for(int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

void struct_path(char* target, char* dir, char* filename)
{
	strcpy(target, dir);
	strcat(target, filename);
	strcat(target, ".txt");
}

void format_word(char* s)
{
	str_to_lower(s);
	char* p2 = s;
	while(*s != '\0') {
		if(*s != '\t' && *s != '\n' && *s != ' ' && *s != '\r' && *s != '\f' && *s != '.' && *s != ',' && *s != '?' && *s != ' ') {
			*p2++ = *s++;
		}
		else {
			++s;
		}
	}
	*p2 = '\0';
}

float my_round(float f, float n)
{
	return (round(f * pow(10, n) + 0.05) / pow(10, n));
}