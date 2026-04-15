/*
 * Names:
 * Michael Gavina
 * Blake Carbon
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>












int main(){

	int pageSize, pages, slots, rand;


	printf("Enter page reference pattern length: ");
	scanf("%d", &pageSize);
	while(pageSize > 100 || pageSize < 10){
		printf("Invalid input\n");
		printf("Enter page reference pattern length: ");
		scanf("%d", &pageSize);
	}

	printf("Enter number of unique pages: ");
	scanf("%d", &pages);
	while(pages > 15 || pages < 2){
		printf("Invalid input\n");
		printf("Enter number of unique pages: ");
		scanf("%d", &pages);
	}

	printf("Enter number of slots: ");
	scanf("%d", &slots);
	while(slots < 2 || slots > 10){
		printf("Invalid input\n");
		printf("Enter number of slots: ");
		scanf("%d", &slots);
	}

	printf("Enter a seed: ");
	scanf("%d", &rand);






	return 0;
}








