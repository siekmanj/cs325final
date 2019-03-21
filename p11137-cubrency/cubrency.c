#include <stdio.h>
#include <stdlib.h>

#define MAX_COIN 25
#define MAX_TARGET 50000
long long dp[MAX_COIN+1][MAX_TARGET+1];

int denominations[MAX_COIN];

long long coinchange(size_t numcoins, int *denominations, int target){
	if(dp[numcoins][target] != -1)
		return dp[numcoins][target];
	
	int coins, t;
	for(coins = 1; coins <= numcoins; coins++){
		for(t = 1; t <= target; t++){
			if(dp[coins][t] == -1){
				long long one = dp[coins-1][t];
				long long two;
				if(t - denominations[coins-1] < 0)
					two = 0;
				else
					two = dp[coins][t - denominations[coins-1]];
				

				dp[coins][t] = one + two;
			}
		}
	}
	return dp[numcoins][target];
}

int main(){
	int i, j;
	for(i = 0; i < MAX_COIN+1; i++){
		for(j = 0; j < MAX_TARGET+1; j++){
			if (!j)
				dp[i][j] = 1;

			else if(!i)
				dp[i][j] = 0;

			else
				dp[i][j] = -1;
		}
	}
  for(i = 1; i <= MAX_COIN; i++)
    denominations[i-1] = i*i*i;

  
  while(1){
    int target;
    int ret = fscanf(stdin, "%d", &target);
    if(ret == EOF)
			exit(0);
		long long val = coinchange(MAX_COIN, denominations, target);
		printf("%lld\n", val);
  }
  

  return 0;
}
