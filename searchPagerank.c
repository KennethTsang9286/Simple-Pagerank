#include "searchPagerank.h"

#define INVERTED_PATH_DEMO "./invertedIndex.txt"
#define PAGERANK_PATH_DEMO "./pagerankList.txt"
#define MAX_NUMBER_TRIPLE 100
#define MAXSTRING 1000

#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(int argc, char* argv[]);
void findMatchedUrls(TripleH* th, char inverted_path[], char* queryWords[], int size);
void findPagerank(TripleH* th, char pagerank_path[]);
void show_triples_for_ass(TripleH* th);
void _findMatchedUrls(TripleH* th, char* token);
void order_with_pagerank(TripleH* th);
int _order_with_pagerank(const void* a, const void* b);

int main(int argc, char* argv[])
{
	if( argc <= 1) {
		printf("Please enter word(s)\n");
		return 0;
	}
	TripleH* th = create_tripleh(MAX_NUMBER_TRIPLE);
	findMatchedUrls(th, INVERTED_PATH_DEMO, argv + 1, argc - 1);
	findPagerank(th, PAGERANK_PATH_DEMO);
	show_triples_for_ass(th);
	free_tripleh(th);
}

void findMatchedUrls(TripleH* th, char inverted_path[], char* queryWords[], int size)
{
	char delim[2] = " ";
	char* token;
	char line[MAXSTRING] ;
	FILE* f;
	if ((f = fopen (inverted_path, "r")) == NULL) {
		printf("Error!\n");
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL)  {
		int is_target;
		token = strtok(line, delim);
		RemoveSpaces(token);
		is_target = is_in_arr(queryWords, token, size);
		token = strtok(NULL, delim);
		while( token != NULL ) {
			if(is_target) {
				_findMatchedUrls(th, token);
			}
			token = strtok(NULL, delim);
		}
	}
}

void _findMatchedUrls(TripleH* th, char* token)
{
	RemoveSpaces(token);
	if(token != NULL) {
		int index = find_triple(th, token);
		if(index == -1) {
			create_triple(th, token);
		}
		else {
			increase_count_with_index(th, index);
		}
	}
}

void findPagerank(TripleH* th, char pagerank_path[])
{
	char delim[2] = ", ";
	char* token;
	char line[MAXSTRING] ;
	FILE* f;
	if ((f = fopen (pagerank_path, "r")) == NULL) {
		printf("Error!\n");
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL)  {
		token = strtok(line, delim);
		int index = find_triple(th, token);
		if (index != -1) {
			token = strtok(NULL, delim);
			token = strtok(NULL, delim);
			update_score_with_index(th, index, atof(token));
		}
	}
	order_with_pagerank(th);
}

void show_triples_for_ass(TripleH* th)
{
	for(int i = 0; i < min(th->total_number, 30); i++) {
		Triple t = (th->ts)[i];
		printf("%s\n", t.url);
	}
}

void order_with_pagerank(TripleH* th)
{
	qsort(th->ts, th->total_number, sizeof(Triple), _order_with_pagerank);
}

int _order_with_pagerank(const void* a, const void* b)
{
	Triple* bb = (Triple*)b;
	Triple* aa = (Triple*)a;
	int tmp = ( bb->count - aa->count );
	if(tmp != 0) {
		return tmp;
	}
	else {
		tmp = ( bb->score > aa->score );
		return tmp;
	}
}