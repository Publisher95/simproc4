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

typedef struct{
char* currentMemory;
char* referencePattern;
} pageFrames;


void printResults(){


}


pageFrames pageFrameInit(int slots, int patternLength){
	char memory[slots] ;
	char pattern[patternLength];
	pageFrames frame;

	for(int i = 0; i < slots; ++i){
		memory[i] = ' ';
	}
	for(int i = 0; i < patternLength; ++i){
		pattern[i] = ' ';
	}
	frame.currentMemory = memory;
	frame.referencePattern = pattern;
	return frame;
}


int FIFO(pageFrames frame){
return 0;

}

int LRU(pageFrames frame){
return 0;
}

int LFU(pageFrames frame){
return 0;

}

int MIN(pageFrames frame){
return 0;

}

int MRU(pageFrames frame){
return 0;

}

int RAND(pageFrames frame){
return 0;
}

int main(){

	int patternLength, uniquePages, slots, seed;
	char pageLetters[] = {"ABCDEFGHIJKLMNO"};
	pageFrames mainPage;

	printf("Enter page reference pattern length: ");
	scanf("%d", &patternLength);
	while(patternLength > 100 || patternLength < 10){
		printf("Invalid input\n");
		printf("Enter page reference pattern length: ");
		scanf("%d", &patternLength);
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
	scanf("%d", &seed);


	srand(seed);

	mainPage = pageFrameInit(slots, patternLength);

	char referencePattern[MAX];
	for (int i = 0; i < MAX; i++) {
		referencePattern[i] = 'A' + (rand() % MAX_PAGES);
	}


	FIFO(mainPage);
	
	LRU(mainPage);
	
	LFU(mainPage);
	
	MIN(mainPage);
	
	MRU(mainPage);
	
	RAND(mainPage);
	
	return 0;
}
