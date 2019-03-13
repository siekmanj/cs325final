#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_set>
#include <limits.h>
#include <cmath>

using namespace std;

int main(){
	while(1){
		/* Get user input */
		int books;
		if(fscanf(stdin, "%d", &books) == EOF)
			exit(0);
		int bookprices[books];
		memset(bookprices, '\0', books);
		for(int i = 0; i < books; i++)
			int err = fscanf(stdin, "%d", &bookprices[i]);
		int money;
		int err = fscanf(stdin, "%d", &money);

		/* Get books */
		int book1, book2, best_diff;

		best_diff = INT_MAX;

		unordered_set<int> set;
		for(int i = 0; i < books; i++){
			if(set.find(money - bookprices[i]) != set.end()){
				//printf("found pair %d and %d - is %d less than best diff %d?\n", money - bookprices[i], bookprices[i], abs(money - bookprices[i] - bookprices[i]), best_diff);
				if(abs(money - bookprices[i] - bookprices[i]) < best_diff){
					best_diff = abs(money - bookprices[i] - bookprices[i]);
					book1 = money - bookprices[i];
					book2 = bookprices[i];
				}
			}
			else
				set.insert(bookprices[i]);
		}

		if(book1 < book2)
			printf("Peter should buy books whose prices are %d and %d.\n", book1, book2);
		else
			printf("Peter should buy books whose prices are %d and %d.\n", book2, book1);


		/* Dispose of the newline */
		printf("%c", fgetc(stdin));
	}

}
