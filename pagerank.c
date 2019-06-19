#include "pagerank.h"

#define TEST_FOLDER "./"
#define COLLECTION_URL "./collection.txt"

int main(int argc, char* argv[]);
long double* calculatePageRank(Graph g, float damping, float diffPR, int maxIterations);
void show_pagerank(char** arr_of_urls, float* scores, int* order, Graph g);
void save_pagerank(char** arr_of_urls, float* scores, int* order, Graph g);

int main(int argc, char* argv[])
{
	if(argc != 4) {
		printf("The arguement should be damping, diffPR and maxIterations\n");
		return 0;
	}
	DLListStr list_of_urls = GetCollection(COLLECTION_URL);
	Graph g = GetGraph(list_of_urls, TEST_FOLDER);
	float* scores = calloc(g->nV, sizeof(float));
	long_double_arr_to_float_arr(calculatePageRank(g, atof(argv[1]), atof(argv[2]), atoi(argv[3])), scores, g->nV);
	int* order = get_orders_from_arr(scores, g->nV);
	save_pagerank(Get_URL_Arr(), scores, order, g);
	freeDLListStr(list_of_urls);
	freeGraph(g);
	free(scores);
	free(order);
	return 0;
}

long double* calculatePageRank(Graph g, float damping, float diffPR, int maxIterations)
{
	int nV = g->nV;
	damping = (long double) damping;
	diffPR = (long double) diffPR;
	long double* pr = calloc(nV, sizeof(long double));
	if(pr == NULL) {
		exit(1);
	}
	long double tmp_pr[nV];
	for(int i = 0; i < nV; i++) {
		pr[i] = 1.0 / nV;
		tmp_pr[i] = 1.0 / nV;
	}
	int iteration = 0;
	long double diff = diffPR;
	while (iteration < maxIterations && diff >= diffPR) {
		iteration++;
		for(Vertex i = 0; i < nV; i++) {
			pr[i] = (1.0 - damping) / (nV);
			Vertex* incomers = find_incomer(g, i);
			int incomer_index = 0;
			while(incomers[incomer_index] != -1) {
				Vertex incomer = incomers[incomer_index];
				pr[i] += damping * tmp_pr[incomer] / get_out_degree(g, incomer);
				incomer_index += 1;
			}
		}
		diff = 0.0;
		for(int i = 0; i < nV; i++) {
			diff += fabsl(pr[i] - tmp_pr[i]);
		}
		copy_ldarr_to_ldarr(pr, tmp_pr, nV);
	}
	return pr;
}

void show_pagerank(char** arr_of_urls, float* scores, int* order, Graph g)
{
	for(int i = 0; i < (g->nV); i++) {
		int index = order[i];
		printf("%s, %d, %f\n", arr_of_urls[index], get_out_degree(g, index), scores[index]);
	}
}

void save_pagerank(char** arr_of_urls, float* scores, int* order, Graph g)
{
	FILE* f = fopen("./pagerankList.txt", "w");
	for(int i = 0; i < (g->nV); i++) {
		int index = order[i];
		fprintf(f, "%s, %d, %.7f\n", arr_of_urls[index], get_out_degree(g, index), scores[index]);
	}
	fclose(f);
}