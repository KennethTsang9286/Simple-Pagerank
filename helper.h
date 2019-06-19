#ifndef HELPER_H
#define HELPER_H

#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define TEST_FOLDER "./"
#define COLLECTION_URL "./collection.txt"
#define INVERTED_PATH_DEMO "./invertedIndex.txt"
#define PAGERANK_PATH_DEMO "./pagerankList.txt"
#define MAXSTRING 1000
#define MAX_URL_LEN 100

void double_arr_to_float_arr(double *darr, float *farr, size_t n);

void long_double_arr_to_float_arr(long double *darr, float *farr, size_t n);

void show_arr_c(char **argv);

void show_arr_f(float *argv);

void show_arr_ld(long double *argv);

void show_arr_int(int *argv);

void copy_list_to_arr(float *pr, float *tmp_pr, size_t N);

void copy_darr_to_darr(double *pr, double *tmp_pr, size_t N);

void copy_ldarr_to_ldarr(long double *pr, long double *tmp_pr, size_t N);

int* get_orders_from_arr(float* arr, size_t nV);

bool is_in_arr(char* arr[], char word[], size_t size);

void RemoveSpaces(char *s);

void str_to_lower(char* str);

void struct_path(char* target, char *dir, char *filename);

void format_word(char* str);

float my_round(float f, float n);

#endif