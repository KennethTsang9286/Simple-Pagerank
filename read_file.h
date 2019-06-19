#ifndef READ_FILE_H
#define READ_FILE_H

#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "DLListStr.h"
#include "InvertedIdx.h"
#include "helper.h"
#include <ctype.h>

Graph initialize_graph(char*);

DLListStr GetCollection(char*);

Graph GetGraph(DLListStr, char*);

char **Get_URL_Arr();

Tree GetInvertedList(DLListStr, char*);

#endif