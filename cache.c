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

// Global data
typedef enum {
	FIFO,
	LRU,
	LFU,
	MIN,
	MRU,
	RAND
} Algorithm;

char pageLetters[] = "ABCDEFGHIJKLMNO";
int patternLength, uniquePages, slotCount, seed;
char *referencePattern, *hitBuffer;

int checkHit(char pageID, char* slots) {
	// Returns -1 if not found
	int i = 0;
	while (slots[i] != '\0') {
		if (slots[i] == pageID) {
			return i;
		}
		i++;
	}
	return -1;
}

char* runAlgorithm(Algorithm algo) {
	int pageIndex = -1;
	char *slots = (char *)malloc(patternLength*sizeof(char));
	char *hits = (char *)malloc(patternLength*sizeof(char));
	if (hits == NULL || slots == NULL) {
		printf("Memory allocation error.");
		return NULL;
	}
	int fill = 0;
	// Algo specific setup:
	switch (algo) {
		case FIFO:
			fill = 0;
			break;
		case LRU:
			break;
		case LFU:
			break;
		case MIN:
			break;
		case MRU:
			break;
		case RAND:
			break;
	}
	for (int i = 0; i < patternLength; i++) {
		printf("%s\n",referencePattern);
		printf("%s\n",hits);
		printf("SLOTS: %s\n",slots);
		pageIndex = checkHit(referencePattern[i],slots);
		switch (algo) {
			case FIFO:
				if (pageIndex == -1) {
					hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// FIFO Shift array
						// 12345
						// 23451
						for (int is = 0; is < (slotCount-1); is++) {
							slots[is] = slots[is+1];
						}
						// Set last element to missing page
						slots[slotCount-1] = referencePattern[i];
					}
				} else {
					hits[i] = '+';
				}
				break;
			case LRU:
				break;
			case LFU:
				break;
			case MIN:
				break;
			case MRU:
				break;
			case RAND:
				break;
		}
	}
	free(slots);
	return hits;
}

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
	referencePattern = (char *)malloc(patternLength*sizeof(char));
	if (referencePattern == NULL) {
		printf("Memory allocation error.");
		return 1;
	}

	for (int i = 0; i < patternLength; i++) {
		referencePattern[i] = 'A' + (rand() % uniquePages);
	}


	hitBuffer = runAlgorithm(FIFO);
	printf("%s\n",referencePattern);
	printf("%s\n",hitBuffer);
	//hitBuffer = runAlgorithm(LRU);
	//hitBuffer = runAlgorithm(LFU);
	//hitBuffer = runAlgorithm(MIN);
	//hitBuffer = runAlgorithm(MRU);
	//hitBuffer = runAlgorithm(RAND);

	free(referencePattern);
	free(hitBuffer);

	return 0;
}
