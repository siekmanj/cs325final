#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORMS 2000
#define UNDISCOVERED 0
#define DISCOVERED 1
#define ROOT 2

int debug = 0;

typedef struct v {
	struct v *wormholes[MAX_WORMS];
	int years[MAX_WORMS];
	int num_wormholes;
	int state;
	int idx;
} Star;


int search(Star *s, int dist, int isrootcall){
	if(debug) printf("search():init star %d, dist %d\n", s->idx, dist);
	if(s->state == ROOT && dist < 0){
		if(debug) printf("search():	returning 1 because possible\n");
		return 1;
	}
	if(s->state == ROOT && dist >= 0 && !isrootcall){
		if(debug) printf("search():	returning 0 because cycle found but sum positive\n");
		return 0;
	}
	if(s->state == DISCOVERED && dist < 0){
		return 0;
	}
	if(s->state == DISCOVERED && dist >= 0){
		if(debug) printf("search():	returning 0 because cycle found but sum positive\n");
		return 0;
	}

	if(s->state != ROOT) s->state = DISCOVERED;
	int i;
	for(i = 0; i < s->num_wormholes; i++){
		if(debug) printf("search():	doing wormhole %d to star %d from star %d\n", i, s->wormholes[i]->idx, s->idx);
		if(search(s->wormholes[i], dist + s->years[i], 0)){
			if(debug) printf("search():	returning 1 because recursive call returned 1\n");
			return 1;
		}
	}

	s->state = UNDISCOVERED;
	if(debug) printf("search(): returning 0 because end of scope\n");
	return 0;
}

int main(){
	int num_cases;
	fscanf(stdin, "%d", &num_cases);

	int i;
	for(i = 0; i < num_cases; i++){
		int num_stars, num_wormholes;
		fscanf(stdin, "%d %d", &num_stars, &num_wormholes);
		if(debug) printf("case %d, got %d %d\n", i, num_stars, num_wormholes);

		Star stars[num_stars];

		int j;
		for(j = 0; j < num_stars; j++){
			stars[j].num_wormholes = 0;
			stars[j].state = UNDISCOVERED;
			stars[j].idx = j;
		}

		for(j = 0; j < num_wormholes; j++){
			int star1, star2, traveltime;
			fscanf(stdin, "%d %d %d", &star1, &star2, &traveltime);

			Star *s = &stars[star1];
			int idx = s->num_wormholes;
			s->wormholes[idx] = &stars[star2];
			s->years[idx] = traveltime;
			s->num_wormholes++;

			if(debug) printf("got %d %d %d\n", star1, star2, traveltime);
		}
		int success = 0;
		for(j = 0; j < num_stars; j++){
			Star *s1 = &stars[j];
			int k;
			for(k = 0; k < stars[j].num_wormholes; k++){
				if(stars[j].years[k] < 0){
					stars[j].state = ROOT;
					success = search(&stars[j], 0, 1);
					stars[j].state = UNDISCOVERED;
					if(success) goto done;
				}
			}
		}
		done:
		if(success)
			printf("possible\n");
		else
			printf("not possible\n");
	}
	return 0;
}
