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

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// As per assignment requirements we need to manage line wrap of slotCount + 1 lines so we need terminal width...
int getTerminalWidth() {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	return 80; // fallback
#else
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		return w.ws_col;
	}
	return 80; // fallback
#endif
}

// Global data
typedef enum {
	FIFO,
	LRU,
	LFU,
	MIN,
	MRU,
	RAND
} Algorithm;

typedef struct {
	char *hits;
	char **slotHistory;
} runBuffer;

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


int indexMIN(char* slots, int startIndex){
	int patternSize = sizeof(referencePattern)/sizeof(referencePattern[0]);

	int slotCounter[slotCount];
	for (int i = startIndex; i < patternSize; i++) {
		for (int si = 0; si < slotCount; si++) {
			if (slots[si] == referencePattern[i]) {
				slotCounter[si]++;
			}
		}
	}
	// this is ok because we guarantee arrays more than 3 min 
	int returnIndex = 0 ;
	for(int i = 1; i < slotCount; i++){
		if(slotCounter[returnIndex] > slotCounter[i]){
			returnIndex = i;
		}
	}
	return returnIndex;
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

runBuffer runAlgorithm(Algorithm algo) {
	int pageIndex = -1;
	char *slots = (char *)malloc(slotCount*sizeof(char));
	int *useTicks = (int *)malloc(slotCount*sizeof(int));
	runBuffer algoData;
	algoData.hits = (char *)malloc(patternLength*sizeof(char));
	algoData.slotHistory = malloc(patternLength*sizeof(char*));
	if (algoData.hits == NULL || algoData.slotHistory == NULL || slots == NULL || useTicks == NULL) {
		printf("Memory allocation error.");
	}
	for (int i = 0; i < patternLength; i++) {
		algoData.slotHistory[i] = (char *)malloc(slotCount*sizeof(char));
		algoData.hits[i] = '\0';
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
					algoData.hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// FIFO Shift array
						for (int is = 0; is < (slotCount-1); is++) {
							slots[is] = slots[is+1];
						}
						// Set last element to missing page
						slots[slotCount-1] = referencePattern[i];
					}
				} else {
					algoData.hits[i] = '+';
				}
				break;
			case LFU:
				if (pageIndex == -1) {
					algoData.hits[i] = '-';
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
					algoData.hits[i] = '+';
					useTicks[pageIndex]++;
				}
				break;
			case LRU:
				if (pageIndex == -1) {
					algoData.hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// Replace
						slots[indexLRU(slots,i)] = referencePattern[i];
					}
				} else {
					algoData.hits[i] = '+';
				}
				break;
			case MIN:
				if(pageIndex == -1){
					algoData.hits[i] = '-';
					if(fill < slotCount){
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						slots[indexMIN(slots, i)] = referencePattern[i];
					}
				}else {
					algoData.hits[i] = '+';
				}
				break;
			case MRU:
				if (pageIndex == -1) {
					algoData.hits[i] = '-';
					//manage / replace
					if (fill < slotCount) {
						slots[fill] = referencePattern[i];
						fill++;
					} else {
						// Replace
						slots[indexMRU(slots,i)] = referencePattern[i];
					}
				} else {
					algoData.hits[i] = '+';
				}
				break;
			case RAND:
				if(pageIndex == -1){
					algoData.hits[i] = '-';
					if(fill < slotCount){
						slots[fill] = referencePattern[i];
						fill++;
					} else { 
						slots[(rand() % slotCount)] = referencePattern[i];
					}
				} else { 
					algoData.hits[i] = '+';
				}
				break;
		}
		for (int sci = 0; sci < slotCount; sci++) {
			algoData.slotHistory[i][sci] = slots[sci];
		}
	}
	free(slots);
	return algoData;
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

	printf("Enter number of slots: ");
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

	runBuffer dataFIFO = runAlgorithm(FIFO);
	runBuffer dataLRU = runAlgorithm(LRU);
	runBuffer dataLFU = runAlgorithm(LFU);
	runBuffer dataMRU = runAlgorithm(MRU);
	runBuffer dataMIN = runAlgorithm(MIN);
	runBuffer dataRAND = runAlgorithm(RAND);
	
	int terminalWidth = getTerminalWidth() - 10; // Subtract space for names?
	int sectionCount = (patternLength + ((10+(terminalWidth))/2) - 1) / ((10+(terminalWidth))/2);
	for (int x = 0; x < sectionCount; x++) {
		printf("Page Wrap %d:\n",x);
		printf("%10s","Ref Str:  ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = referencePattern[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");

		for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "FIFO", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataFIFO.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataFIFO.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");
		
		for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "LRU", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataLRU.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataLRU.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");


        for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "LFU", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataLFU.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataLFU.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");
		
		for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "MRU", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataMRU.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataMRU.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");
		
		for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "MIN", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataMIN.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataMIN.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");
		
		for (int i = 0; i < slotCount; i++) {
			printf("%5s %2d: ", "RAND", i);
			for (int y = 0; y < (terminalWidth/2); y++) {
				if (((x*(terminalWidth/2))+y) < patternLength) {
					char current = dataRAND.slotHistory[(x*(terminalWidth/2))+y][i];
					if (current == '\0') {
						current = ' ';
					}
					printf("%c ",current);
				}
			}
			printf("\n");
		}
		printf("%9s","          ");
		for (int y = 0; y < (terminalWidth/2); y++) {
			if (((x*(terminalWidth/2))+y) < patternLength) {
				char current = dataRAND.hits[(x*(terminalWidth/2))+y];
				if (current == '\0') {
					current = ' ';
				}
				printf("%c ",current);
			}
		}
		printf("\n\n");
	}

	free(referencePattern);
	free(hitBuffer);

	return 0;
}
