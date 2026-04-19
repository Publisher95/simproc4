/*
 * Names:
 * Michael Gavina
 * Blake Carbon
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>



typedef struct{
char* currentMemory;
char* referencePattern;
} pageFrames;

pageFrames pageFramesInit(int slots, int patternLength){
	char[slots] memory;
	char[patternLength] pattern;
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


int[] FIFO(pageFrames Frame){

}

int[] LRU(pageFrames Frame){

}

int[] LFU(pageFrames Frame){

}

int[] MIN(pageFrames Frame){

}

int[] MRU(pageFrames Frame){

}

int[] RAND(pageFrames Frame){

}

int main(){

	int pageLength, uniquePages, slots, rand;
	char[] pageLetters = {"ABCDEFGHIJKLMNO"};
	pageFrames mainPage;

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

	srand(rand);

	mainPage = pageFramesInit();
	
	FIFO();
	
	LRU();

	LFU();

	MIN();

	MRU();

	RAND();


	return 0;
}
