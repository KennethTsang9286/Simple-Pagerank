/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "DLListStr.h"

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);

        strcpy(new->value, val);  // for int, new->value = it;
	
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLListStr
DLListStr newDLListStr()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}


/* 
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(DLListStr L, char *val){

	/* 
	   implement this function to
	   insert val in L  (in order), no duplicates (set)

	*/

	DLListNode *newNode = newDLListNode(val);

	if( L->first == NULL){
		L->first = newNode;
		L->last = newNode;
		L->curr = newNode;
		L->nitems = 1;
		return;
	}

	DLListNode *node = L->first;
	while(strcmp(node->value, val) < 0 && node->next != NULL){
		node = node->next;
	}

	//printf("vallue: %s, val: %s\n", node->value, val);
	//printf("strcmp(node->value, val): %d\n", strcmp(node->value, val));
	//showDLListStr(L);

	if(node->next == NULL){
		node->next = newNode;
		newNode->prev = node;
		L->last = newNode;
	}else if(strcmp(node->value, val) >= 1 && node == L->first){
		node->prev = newNode;
		newNode->next = node;
		L->first = newNode;
		
	}else if(strcmp(node->value, val) >= 1){
		node->prev->next = newNode;
		newNode->prev = node->prev;
		node->prev = newNode;
		newNode->next = node;
	}

	L->nitems++;
	return;
}



// display items from a DLListStr, comma separated
void showDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		count++;
		if(count > 1) {
			fprintf(stdout,", ");
		}
		fprintf(stdout,"%s",curr->value);
	}
	fprintf(stdout,"\n");
}

int findDLListStr(DLListStr L, char* input){
	int count = 0;
	if (L->nitems == 0){
		return -1;
	}
	DLListNode *node = L->first;
	while(node != NULL && strncmp(node->value, input, 7)){
		count++;		
		node = node->next;
	}
	if(node == NULL){
		return -1;
	}else{
		return 0;
	}
}


// free up all space associated with list
void freeDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

void insertDLListStr(DLListStr L, char* input){
	DLListNode *newNode = newDLListNode(input);

	if(L->first == NULL){
		L->first = newNode;
		L->last = newNode;
		L->curr = newNode;
		L->nitems = 1;
		return;
	}else{
		DLListNode *last = L->last;
		last->next = newNode;
		newNode->prev = last;
		L->last = newNode;
		L->nitems += 1;
	}
}

int getOrderDLListStr(DLListStr list, char *word){
	DLListNode *node = list->first;
	int	count = 0;
	while( strcmp(node->value,  word) != 0 && node->next != NULL){
		count++;
		node = node->next;
	}
	if(!strcmp(node->value, word)){
		return count;
	}else{
		printf("get_order_from_list Error\n");
		return -1;
	}
}


