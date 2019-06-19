#include "Triple.h"

TripleH* create_tripleh(size_t max_number_triple){
	TripleH *th = calloc(1, sizeof(TripleH));
	th->ts = calloc(max_number_triple, sizeof(Triple));
	th->total_number = 0;
	return th;
}

Triple create_triple(TripleH* th, char url[]){
	Triple tmp_t;
	strcpy(tmp_t.url, url);
	tmp_t.count = 1;
	tmp_t.score = 0;
	th->ts[th->total_number] = tmp_t;
	th->total_number++;
	return tmp_t;
}

int find_triple(TripleH* th, char url[]){
	int count = 0;
	Triple* ts = th->ts;
	while(count < th->total_number){
		if(strcmp(ts[count].url, url ) == 0){
			return count;
		}
		count++;
	}
	return -1;
}

void show_triples(TripleH* th){
	for(int i = 0; i < th->total_number; i++){
		Triple t = (th->ts)[i];
		printf("url: %s, count: %d, score: %f\n", t.url, t.count, t.score);
	}
}

void show_triple(Triple t){
	printf("url: %s, count: %d, score: %f\n", t.url, t.count, t.score);
}

void increase_count_with_index(TripleH* th, int index){
	if(th->total_number < index){
		printf("Error increase_count_with_index\n");
		return;
	}
	(th->ts)[index].count++;
}

void increase_count(TripleH* th, char url[]){
	for(int i = 0; i < th->total_number; i++){
		if(strcmp((th->ts)[i].url, url) == 0){
			(th->ts)[i].count++;
		}
	}
}

void update_score(TripleH* th, char url[], float score){
	for(int i = 0; i < th->total_number; i++){
		if(strcmp((th->ts)[i].url, url) == 0){
			(th->ts)[i].score = score;
		}
	}
}

void update_score_with_index(TripleH* th, int index, float score){
	if(th->total_number < index){
		printf("Error increase_count_with_index\n");
		return;
	}
	(th->ts)[index].score = score;
}

void free_tripleh(TripleH* th){
	free(th->ts);
	free(th);
}