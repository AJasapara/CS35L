// Name: Arpit Jasapara, UID: 504742401

#include<stdio.h>
#include<stdlib.h>

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

void inputError(){
	fprintf(stderr, "Input Error!");
	exit(1);
}

void memoryError(){
	fprintf(stderr, "Memory Allocation Error!");
	exit(1);
}

int main (void) {
	char* curr = (char*) malloc (sizeof(char)); // current word
	char** arr = (char**) malloc (sizeof(char*)); // array of words
	int currSize = 1;
	int arrSize = 1;
	int currCount = 0;
	int arrCount = 0;
	char c, n;
	c = getchar(); // gets first/current character
	if (ferror(stdin))
		inputError();

	while(c != EOF) {	
		n = getchar(); // gets next character to check for repeating spaces/EOF
		if (ferror(stdin))
			inputError();

		if (currCount >= currSize-1){ // reallocates current word if more space is needed
			currSize *= 2;
			char* temp = realloc(curr, sizeof(char) * currSize);
			if (temp == NULL)
				memoryError();
			curr = temp;
		}
		curr[currCount] = c; // puts current character in current word

		if (c == ' ') { // puts curr in arr if end of word (space)
			if (arrCount >= arrSize-1) { // reallocates arr if more space is needed
				arrSize *= 2;
				char** tempArr = realloc(arr, sizeof(char*) * arrSize);
				if (tempArr == NULL)
					memoryError();
				arr = tempArr;
			}
			arr[arrCount] = curr;
			arrCount++;
			curr = (char*) malloc (sizeof(char)); // starts over current word and stats
			currSize = 1;
			currCount = -1;
		}

		if (c == ' ' && n == ' ') { // if repeating spaces are encountered
			while (c == ' ') {
				c = getchar();
				if (ferror(stdin))
					inputError();
			}
			n = c;
		}
		else if (n == EOF && c != ' '){ // if last character is not a space
			curr[++currCount] = ' ';
			arr[arrCount] = curr;
			arrCount++;
		}

		c = n;
		currCount++;
	}

	qsort(arr, arrCount, sizeof(char*), frobcmp);

	int i;
	for (i = 0; i < arrCount; i++){
		int j;
		for (j = 0; arr[i][j] != ' '; j++)
			putchar(arr[i][j]);
		free(arr[i]);
		putchar(' ');
	}
	free(arr);
	return 0;
}