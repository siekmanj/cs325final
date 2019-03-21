#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 60

/*
 * Does in-place recursive mergesort
 */
static void recursive_mergesort(char **arr, size_t len){
	
	/* Subdivide the list into half */
	if(len > 1){
		recursive_mergesort(arr, len/2);
		recursive_mergesort(&arr[len/2], len-(len/2)); /* len-(len/2) catches the corner case of len being odd */
	}
	else return; /* If we've subdivided the arr into subarrays of size 1, we should go back */

	char *tmp[len];
	char **sub1 = arr; /* left subarray */
	char **sub2 = &arr[len/2]; /* right subarray */
	int x = 0; /* index of current element in left subarray */
	int y = 0; /* index of current element in right subarray */

	/* merge sorted subarrays */
	int i;
	for(i = 0; i < len; i++){
		if(x >= len/2) 
			tmp[i] = sub2[y++];
		else if(y >= len-(len/2)) 
			tmp[i] = sub1[x++];
		else if(strcmp(sub1[x], sub2[y]) >= 0)
			tmp[i] = sub2[y++];
		else 
			tmp[i] = sub1[x++];
	}
	for(i = 0; i < len; i++){
		arr[i] = tmp[i];
	}
	return;
}

int main(){
	while(1){
		int num_files;
		if(fscanf(stdin, "%d", &num_files) == EOF)
			exit(0);
		
		char *files[num_files];
		size_t longest_filename = 0;
		int i;
		for(i = 0; i < num_files; i++){
			files[i] = (char*)malloc(sizeof(char) * MAX_LEN);

			fscanf(stdin, "%s", files[i]);
			int filelen = strlen(files[i]);
			if(filelen > longest_filename){
				longest_filename = filelen;
			}
		}
		size_t columns = 1 + (MAX_LEN - longest_filename) / (longest_filename + 2);
		size_t rows;
		if(num_files % columns == 0)
			rows = num_files / columns;
		else
			rows = num_files / columns + 1;

		recursive_mergesort(files, num_files);
		for(i = 0; i < MAX_LEN; i++)
			printf("-");
		printf("\n");
		for(i = 0; i < rows; i++){
			int j;
			for(j = 0; j < columns; j++){
				int idx = i + j * rows;
				if(idx < num_files){
					if(!j)
						printf("%s", files[idx]);
					else
						printf("  %s", files[idx]);

					int offset;
					offset = longest_filename - strlen(files[idx]);
					int k;
					for(k = 0; k < offset; k++)
						printf(" ");
				}
			}
			printf("\n");
		}
		for(i = 0; i < num_files; i++)
			free(files[i]);
	}
}
