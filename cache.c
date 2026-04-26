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

int indexLRU(char* slots, int startIndex) {
	for (int i = 0; i < startIndex; i++) {
		for (int si = 0; si < slotCount; si++) {
			if (slots[si] == referencePattern[i]) {
				return si;
			}
		}
	}
	// This should never happen.
	return 0;
}

int indexMRU(char* slots, int startIndex) {
	for (int i = startIndex-1; i >= 0; i++) {
		for (int si = 0; si < slotCount; si++) {
			if (slots[si] == referencePattern[i]) {
				return si;
			}
		}
	}
	// This should never happen.
	return 0;
}

char* runAlgorithm(Algorithm algo) {
	int pageIndex = -1;
	char *slots = (char *)malloc(slotCount*sizeof(char));
	int *useTicks = (int *)malloc(slotCount*sizeof(int));
	char *hits = (char *)malloc(patternLength*sizeof(char));
	if (hits == NULL || slots == NULL || useTicks == NULL) {
		printf("Memory allocation error.");
		return NULL;
	}
	for (int i = 0; i < patternLength; i++) {
		hits[i] = '\0';
	}
	int fill = 0;
	for (int i = 0; i < slotCount; i++) {
		slots[i] = '\0'; // Make sure to clear
		useTicks[i] = 0;
	}
	for (int i = 0; i < patternLength; i++) {
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
			case LFU:
				if (pageIndex == -1) {
					hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						useTicks[fill] = 1;
						fill++;
					} else {
						// 12345
						int lowest = patternLength; // Theoretical max if every single char was a reference.
						char *slotsCopy = (char *)malloc(slotCount*sizeof(char));
						for (int fi = 0; fi < fill; fi++) {
							slotsCopy[fi] = '\0';
							if(useTicks[fi] < lowest) {
								lowest = useTicks[fi];
							}
						}
						for (int fi = 0; fi < fill; fi++) {
							if(useTicks[fi] = lowest) {
								slotsCopy[fi] = slots[fi];
							}
						}
						int replaceIndex = indexLRU(slotsCopy, i); // Break ties using LRU
						slots[replaceIndex] = referencePattern[i];
						useTicks[replaceIndex] = 1;
						// One horrid way to do this would be to run indexLRU but with a custom slot array containing ONLY the ties, This is what we think we have done.

						free(slotsCopy);
					}
				} else {
					hits[i] = '+';
					useTicks[pageIndex]++;
				}
				break;
			case LRU:
				if (pageIndex == -1) {
					hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// Replace
						slots[indexLRU(slots,i)] = referencePattern[i];
					}
				} else {
					hits[i] = '+';
				}
				break;
			case MIN:
				break;
			case MRU:
				if (pageIndex == -1) {
					hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// Replace
						slots[indexMRU(slots,i)] = referencePattern[i];
					}
				} else {
					hits[i] = '+';
				}
				break;
			case RAND:
				if(pageIndex == -1){
					hits[i] = '-';
					if(fill < slotCount){
						slots[fill] = referencePattern[i];
						fill++;
					} else { 
						slots[(rand() % slotCount)] = referencePattern[i];
					}
				} else { 
					hits[i] = '+';
				}
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
		printf("Enter number of slots: ");
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
	hitBuffer = runAlgorithm(LRU);
	hitBuffer = runAlgorithm(LFU);
	hitBuffer = runAlgorithm(MRU);
	//hitBuffer = runAlgorithm(MIN);
	hitBuffer = runAlgorithm(RAND);

	free(referencePattern);
	free(hitBuffer);

	return 0;
}
