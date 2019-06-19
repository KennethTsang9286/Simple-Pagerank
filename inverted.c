#include "inverted.h"

int main();
void get_words(Tree t, DLListStr words);
void terminal_show_inverted(DLListStr words, Tree t);
void save_inverted(DLListStr words, Tree t);

int main(){
	DLListStr list_of_urls = GetCollection(COLLECTION_URL);
	Tree t = GetInvertedList(list_of_urls, TEST_FOLDER);
	DLListStr words = newDLListStr();
	get_words(t, words);
	save_inverted(words, t);
	freeDLListStr(words);
	freeDLListStr(list_of_urls);
	freeTree(t);
}

void get_words(Tree t, DLListStr words){
	if(t->right != NULL){
		get_words(t->right, words);
	}
	insertSetOrd(words, t->data);
	if(t->left != NULL){
		get_words(t->left, words);
	}
}

void terminal_show_inverted(DLListStr words, Tree t){
	DLListNode *node = words->first;
	while(node != NULL){
		Tree search_t = TreeSearch(t, node->value);
		DLListNode *tmp_node = search_t->list->first;
		printf("%s", node->value);
		while(tmp_node != NULL){
			printf(" %s", tmp_node->value);
			tmp_node = tmp_node->next;
		}
		printf("\n");
		node = node->next;
	}
}

void save_inverted(DLListStr words, Tree t){
	FILE *f = fopen("./invertedIndex.txt", "w");
	DLListNode *node = words->first;
	while(node != NULL){
		Tree search_t = TreeSearch(t, node->value);
		DLListNode *tmp_node = search_t->list->first;
		fprintf(f, "%s", node->value);
		while(tmp_node != NULL){
			fprintf(f, " %s", tmp_node->value);
			tmp_node = tmp_node->next;
		}
		fprintf(f, "\n");
		node = node->next;
	}
	fclose(f);
}