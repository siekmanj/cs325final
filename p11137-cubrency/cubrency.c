#include <stdio.h>
#include <stdlib.h>

#define MAX_COIN 21

//cubic coins
//0^3 ==> 21^3
//denominations of 1, 8, 27, ...
//how many ways to pay given an amount

//10 =  2 * 1^3 + 1 * 2^3
//     10 * 1^3 + 0 * 2^3

//21 = 21 * 1^3 + 0 * 2^3 + 0 * 3^3
//      5 * 1^3 + 2 * 2^3 + 0 * 3^3

//

int dp[MAX_COIN];

int denominations[MAX_COIN];

int cubecount(int target){
  return 0;  
}

int main(){
  for(int i = 0; i < MAX_COIN; i++)
    denominations[i] = i*i*i;
  
  while(1){
    int target;
    int ret = fscanf(stdin, "%d", &target);
    if(ret == EOF) exit(0);
    printf("got %d as target\n", target);
    printf("%d\n", cubecount(target));
  }
  

  return 0;
}
