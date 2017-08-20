// Name: Arpit Jasapara, UID: 504742401

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int frobcmp(const void* a, const void* b)
{
	char const * achar = *(char const **) a;
	char const * bchar = *(char const **) b;
	while (100 < 101) { // keeps loop running until value returned
		char froba = *achar ^ 42;
		char frobb = *bchar ^ 42;
		if (*achar == ' ' && *bchar == ' ') { 
			return 0;
		}
		else if (*achar == ' ' || froba < frobb) { 
			return -1; 
		}
		else if (*bchar == ' ' || froba > frobb) { 
			return 1; 
		}
		achar++;
		bchar++;
	}
}

int frobcapcmp(const void* a, const void* b)
{
	char const * achar = *(char const **) a;
	char const * bchar = *(char const **) b;
	while (100 < 101) { // keeps loop running until value returned
		char froba = toupper((unsigned char)(*achar ^ 42));
		char frobb = toupper((unsigned char)(*bchar ^ 42));
		if (*achar == ' ' && *bchar == ' ') { 
			return 0;
		}
		else if (*achar == ' ' || froba < frobb) { 
			return -1; 
		}
		else if (*bchar == ' ' || froba > frobb) { 
			return 1; 
		}
		achar++;
		bchar++;
	}
}

void inputError(){
	fprintf(stderr, "Input Error!");
	exit(1);
}

void memoryError(){
	fprintf(stderr, "Memory Allocation Error!");
	exit(1);
}

int main (int argc, char **argv) {
	int flag = 0;
	if (getopt(argc, argv, "f") == 102)
		flag = 1;
	int fileSize = sizeof(char*);
	struct stat fileStat;
	if (fstat(0, &fileStat) < 0)
		inputError();
	if (S_ISREG(fileStat.st_mode))
		fileSize = fileStat.st_size+1;

	char* currFile = (char*) malloc (fileSize * sizeof(char)); // current word
	if (currFile == NULL)
		memoryError();

	char** arr;
	int arrSize = 1;
	int currCount = 0;
	char p, c;

	while(read(0, &c, sizeof(char)) > 0) {
		if (c == ' ') {
			if (p == ' ')
				continue;
			arrSize++;
		}

		currFile[currCount] = c;
		currCount++;
		p = c;

		if (currCount >= fileSize-1) {
			fileSize *= 2;
			char* temp = realloc(currFile, sizeof(char) * fileSize);
			if (temp == NULL)
				memoryError();
			currFile = temp;
		}
	}

	if (p != ' ')
		currFile[currCount] = ' ';

	arr = (char**) malloc (arrSize * sizeof(char*)); // array of words
	if (arr == NULL)
		memoryError();

	char* word = currFile;
	int i;
	for (i = 0; i < arrSize; i++, word++) {
		arr[i] = word;
		while(*word != ' ')
			word++;
	}
	if (flag)
		qsort(arr, arrSize, sizeof(char*), frobcapcmp);
	else
		qsort(arr, arrSize, sizeof(char*), frobcmp);

	int j;
	for (i = 0; i < arrSize; i++){
		for (j = 0; arr[i][j] != ' '; j++)
			write(1, &arr[i][j], sizeof(char));
		write(1, &arr[i][j], sizeof(char));
	}
	free(currFile);
	free(arr);
	return 0;
}