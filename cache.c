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

typedef struct{
char* currentMemory;
char* referencePattern;
} pageFrames;

pageFrames pageFramesInit(int slots, int patternLength){
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

void patternInit(pageFrames *frame, char bank[]){
	int size = sizeof(frame->referencePattern)/sizeof(frame->referencePattern[0]);
	
	for(int i = 0; i < size; ++i){
		int k = (rand() % size);
		frame->referencePattern[i] = bank[k];
	}
}

char* bankReturn(char letters[], int uniquePages){
	char *bank = malloc(sizeof(char)*uniquePages);
	for(int i = 0; i < uniquePages; ++i){
		bank[i] = letters[i];
	}
	return bank;
}

int FIFO(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);
	char *line1, *line2, *line3;

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}
	

}

int LRU(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}



}

int LFU(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}
	printf("\n");

	


}

int MIN(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}


}

int MRU(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}


}

int RAND(pageFrames frame){
	int size = sizeof(frame.referencePattern)/sizeof(frame.referencePattern[0]);

	printf("Ref Str: ");
	for(int i = 0; i < size; ++i){
		printf("%c ", frame.referencePattern[i]);
	}


}

int main(){

	int patternLength, uniquePages, slots, rand;
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
	scanf("%d", &rand);

	char *useableLetters = bankReturn(pageLetters, uniquePages);

	srand(rand);

	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);

	FIFO(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);
	
	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);
	
	LRU(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);

	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);
	
	LFU(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);

	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);
	
	MIN(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);

	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);
	
	MRU(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);

	mainPage = pageFramesInit(slots, patternLength);
	patternInit(&mainPage, useableLetters);
	
	RAND(mainPage);
	
	free(mainPage.currentMemory);
    free(mainPage.referencePattern);

	free(useableLetters);
	return 0;
}
