// Name: Arpit Jasapara, UID: 504742401

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
	if (argc != 3)
	{
		fprintf(stderr, "Error: Wrong Number of Arguments!\n");
		exit(1);
	}

	if (strlen(argv[1]) != strlen(argv[2]))
	{
		fprintf(stderr, "Error: Strings Do Not Have Same Length!\n");
		exit (1);
	}

	int len = strlen(argv[1]);
	char translate[256] = {0};
	int i, j;
	for(i = 0; i < len; i++) {
		for (j = i+1; j < len; j++)
			if(argv[1][i] == argv[1][j]) {
				fprintf(stderr, "Error: First String Contains Duplicate Bytes!\n");
				exit (1);
			}
		translate[argv[1][i]] = argv[2][i];
	}

	char c = getchar();
	while (c != EOF) {
		if (translate[c] == 0)
			putchar(c);
		else
			putchar(translate[c]);
		c = getchar();
	}
}