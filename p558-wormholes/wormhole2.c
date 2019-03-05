/******************************************************************************
 * Solution for UVa problem #558 - Wormholes 
 * Written by Alex Grejuc & Jonah Siekmann 
 * March 4 2019 
 * ***************************************************************************/ 

#include <stdio.h>
#include <limits.h> 

typedef struct e{
	int from; 
	int to;
	int years;  
} Wormhole; 

int main(){
	int num_cases;
	fscanf(stdin, "%d", &num_cases);

	int i;
	/* read in all cases */ 
	for(i = 0; i < num_cases; i++){
		int num_stars, num_wormholes;
		int min = INT_MAX; /* wupdated as minimums are found */ 

		fscanf(stdin, "%d %d", &num_stars, &num_wormholes);

		int stars[num_stars];
		Wormhole wormholes[num_wormholes]; 

		int j;
		/* init vertex distances to a max val for proper relaxation */ 
		for(j = 0; j < num_stars; j++){
			stars[j] = INT_MAX / 2; /* divide to avoid overflow later */ 
		}

		/* read in and set all edges */ 
		for(j = 0; j < num_wormholes; j++){
			fscanf(stdin, "%d %d %d", &wormholes[j].from, &wormholes[j].to, &wormholes[j].years);
			if(wormholes[j].years < min) min = wormholes[j].years; /* update min */
		}
		
		int success = 0; /* successful if a negative cycle is found */ 

		if(min < 0){
			if(num_wormholes) stars[wormholes[0].from] = 0; /* init source to 0 */  

			int k;
			
			/* try to relax all edges in graph |V| - 1 times */  
			for(j = 0; j < num_stars - 1; j++){
				for(k = 0; k < num_wormholes; k++){
					Wormhole w = wormholes[k]; 
					if(stars[w.from] + w.years < stars[w.to]) {
						stars[w.to] = stars[w.from] + w.years;
					} 
				}
			} 

			/* All distances should be fully relaxed unless a negative cycle exists */
			/* Because earth can reach all other star systems a negative cycle
			*  anywhere implies a possible solution */  
			for(k = 0; k < num_wormholes; k++){
				Wormhole w = wormholes[k];
				
				if(stars[w.from] + w.years < stars[w.to]) {
					success = 1;
					break;  
				}
			}
		}
		if(success) printf("possible\n");
		else printf("not possible\n");
	}
	return 0;
}
