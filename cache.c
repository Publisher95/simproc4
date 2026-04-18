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

	int pageLength, uniquePages, slots, rand;
	char* pageLetters = {"ABCDEFGHIJKLMNO"};

	printf("Enter page reference pattern length: ");
	scanf("%d", &pageLength);
	while(pageLength > 100 || pageLength < 10){
		printf("Invalid input\n");
		printf("Enter page reference pattern length: ");
		scanf("%d", &pageLength);
	}

	printf("Enter number of unique pages: ");
	scanf("%d", &uniquePages);
	while(uniquePages > 15 || uniquePages < 2){
		printf("Invalid input\n");
		printf("Enter number of unique pages: ");
		scanf("%d", &uniquePages);
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








