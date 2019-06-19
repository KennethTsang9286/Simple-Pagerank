#ifndef TRIPLE_H
#define TRIPLE_H

#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

typedef struct Triple {
   char url[100];
   int count;
   float score;	
} Triple;

typedef struct TripleH{
	Triple* ts;
	int total_number;
} TripleH;

TripleH* create_tripleh(size_t max_number_triple);

Triple create_triple(TripleH* th, char url[]);

int find_triple(TripleH* th, char url[]);

void show_triples(TripleH* th);

void show_triple(Triple t);

void increase_count_with_index(TripleH* th, int index);

void increase_count(TripleH* th, char url[]);

void update_score(TripleH* th, char url[], float score);

void update_score_with_index(TripleH* th, int index, float score);

void free_tripleh(TripleH* th);

#endif