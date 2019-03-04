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
	for(i = 0; i < num_cases; i++){
		int num_stars, num_wormholes;
		int has_negative = 0; 

		fscanf(stdin, "%d %d", &num_stars, &num_wormholes);

		int stars[num_stars];
		Wormhole wormholes[num_wormholes]; 

		int j;
		for(j = 0; j < num_stars; j++){
			stars[j] = INT_MAX / 2; 
		}

		for(j = 0; j < num_wormholes; j++){
			int star1, star2, traveltime;
			fscanf(stdin, "%d %d %d", &star1, &star2, &traveltime);
			wormholes[j].from = star1; 
			wormholes[j].to = star2; 
			wormholes[j].years = traveltime; 
			has_negative = (has_negative | traveltime < 0); 
		}
		
		int success = 0; 
		if(has_negative){
			if(num_wormholes) stars[wormholes[0].from] = 0; /* init source to 0 */  

			int k; 
			for(j = 0; j < num_stars - 1; j++){
				for(k = 0; k < num_wormholes; k++){
					Wormhole w = wormholes[k]; 
					if(stars[w.from] + w.years < stars[w.to]) {
						stars[w.to] = stars[w.from] + w.years;
					} 
				}
			} 
	
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
