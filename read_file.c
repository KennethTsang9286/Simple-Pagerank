#include "read_file.h"

#define MAXSTRING 1000

char** NAME_URLS;

char** Get_URL_Arr();

DLListStr reader(char* url, void (*func)(char*, DLListStr));

DLListStr GetCollection(char* collection_url);

Graph GetGraph(DLListStr list_of_urls, char* folder_url);

Tree GetInvertedList(DLListStr list_of_urls, char* folder_url);

void List_Helper(DLListStr tmp_list);

void GetCollection_F(char* token, DLListStr list);

void GetGraph_F(char* token, DLListStr list);

void GetInvertedList_F(char* token, DLListStr list);

char** Get_URL_Arr()
{
	return NAME_URLS;
}

DLListStr reader(char* url, void (*func)(char*, DLListStr))
{
	DLListStr list_of_urls = newDLListStr();
	char delim[2] = " ";
	char* token;
	char line[MAXSTRING] ;
	FILE* f;
	if ((f = fopen (url, "r")) == NULL) {
		printf("Error!\n");
		return (0);
	}
	while(fgets(line, MAXSTRING, f) != NULL)  {
		token = strtok(line, delim);
		while( token != NULL ) {
			(*func)(token, list_of_urls);
			token = strtok(NULL, delim);
		}
	}
	return list_of_urls;
}

DLListStr GetCollection(char* collection_url)
{
	DLListStr output = reader(collection_url, GetCollection_F);
	NAME_URLS = calloc(output->nitems, MAX_URL_LEN * sizeof(char));
	DLListNode* node = output->first;
	int count = 0;
	while(node != NULL) {
		NAME_URLS[count] = node->value;
		count++;
		node = node->next;
	}
	return output;
}

void GetCollection_F(char* token, DLListStr list)
{
	RemoveSpaces(token);
	if(strlen(token) > 0) {
		insertSetOrd(list, token);
	}
}

Graph GetGraph(DLListStr list_of_urls, char* folder_url)
{
	Graph g = newGraph(list_of_urls->nitems);
	DLListNode* node = list_of_urls->first;
	int count = 0;
	char path[MAX_URL_LEN];
	while(node != NULL) {
		struct_path(path, folder_url, node->value);
		DLListStr tmp_list = reader(path, GetGraph_F);
		List_Helper(tmp_list);
		if(tmp_list->nitems != 0) {
			DLListNode* tmp_node = tmp_list->first;
			while(tmp_node != NULL) {
				int order = getOrderDLListStr(list_of_urls, tmp_node->value);
				Edge e;
				e.v = count;
				e.w = order;
				insertEdge(g, e);
				tmp_node = tmp_node->next;
			}
		}
		freeDLListStr(tmp_list);
		node = node->next;
		count++;
	}
	return g;
}

void GetGraph_F(char* token, DLListStr list)
{
	RemoveSpaces(token);
	if(strcmp(token, "\0")) {
		if(!strcmp(token, "Section-1") && list->first == NULL) {
			insertDLListStr(list, token);
		}
		else if(list->first != NULL && token != NULL && strcmp(list->last->value, "#end") != 0) {
			insertDLListStr(list, token);
		}
	}
}

Tree GetInvertedList(DLListStr list_of_urls, char* folder_url)
{
	Tree t = newTree();
	DLListNode* node = list_of_urls->first;
	char path[MAX_URL_LEN];
	while(node != NULL) {
		struct_path(path, folder_url, node->value);
		DLListStr tmp_list = reader(path, GetInvertedList_F);
		List_Helper(tmp_list);
		if(tmp_list->nitems != 0) {
			DLListNode* tmp_node = tmp_list->first;
			while(tmp_node != NULL) {
				Tree ts = TreeSearch(t, tmp_node->value);
				if(ts != NULL) {
					if(findDLListStr(ts->list, node->value) == -1) {
						insertSetOrd(ts->list, node->value);
					}
				}
				else {
					t = TreeInsert(t, tmp_node->value);
					ts = TreeSearch(t, tmp_node->value);
					insertSetOrd(ts->list,  node->value);
				}
				tmp_node = tmp_node->next;
			}
			freeDLListStr(tmp_list);
		}
		node = node->next;
	}
	return t;
}

void GetInvertedList_F(char* token, DLListStr list)
{
	RemoveSpaces(token);
	if(strcmp(token, "\0")) {
		if(strcmp(token, "Section-2") == 0 && list->first == NULL) {
			format_word(token);
			insertDLListStr(list, token);
		}
		else if(list->first != NULL && strcmp(list->last->value, "#end") != 0) {
			format_word(token);
			insertDLListStr(list, token);
		}
	}
}


void List_Helper(DLListStr tmp_list)
{
	if(tmp_list->nitems < 3) {
		tmp_list->nitems = 0;
	}
	else {
		DLListNode* new_first = tmp_list->first->next;
		DLListNode* new_last = tmp_list->last->prev;
		free(tmp_list->first);
		tmp_list->first = new_first;
		new_first->prev = NULL;
		new_last->next = NULL;
		free(tmp_list->last);
		tmp_list->last = new_last;
		tmp_list->nitems -= 2;
	}
}



