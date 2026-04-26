/*
 * Names:
 * Michael Gavina
 * Blake Karbon
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_PAGES 15
#define MAX_SLOTS 12

char pageLetters[] = "ABCDEFGHIJKLMNO";
int patternLength, uniquePages, slotCount, seed;
char *referencePattern, *hitBuffer;

//int clearHitBuffer

int main() {
	
	printf("Enter page reference pattern length: ");
	scanf("%d", &patternLength);
	while(patternLength > MAX || patternLength < 10){
		printf("Invalid input\n");
		printf("Enter page reference pattern length: ");
		scanf("%d", &patternLength);
	}

	printf("Enter number of unique pages: ");
	scanf("%d", &uniquePages);
	while(uniquePages > MAX_PAGES || uniquePages < 2){
		printf("Invalid input\n");
		printf("Enter number of unique pages: ");
		scanf("%d", &uniquePages);
	}

	printf("Enter number of slotCount: ");
	scanf("%d", &slotCount);
	while(slotCount < 2 || slotCount > MAX_SLOTS){
		printf("Invalid input\n");
		printf("Enter number of slotCount: ");
		scanf("%d", &slotCount);
	}

	printf("Enter a seed: ");
	scanf("%d", &seed);

	srand(seed);
	referencePattern = (char*)malloc(patternLength*sizeof(char));
	hitBuffer = (char*)malloc(patternLength*sizeof(char));
	if (referencePattern == NULL || hitBuffer == NULL) {
		printf("Memory allocation error.");
		return -1;
	}

	for (int i = 0; i < MAX; i++) {
		referencePattern[i] = 'A' + (rand() % uniquePages);
	}

	

	free(referencePattern);
	free(hitBuffer);

	return 0;
}
