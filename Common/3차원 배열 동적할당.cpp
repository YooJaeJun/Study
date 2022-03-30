#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Turboc.h"

void main()
{
	int l = 5, n = 3, m = 4;
	char ***p;

	p = (char***)malloc(l * sizeof(char**));

	for (int i = 0; i != l; i++) {
		p[i] = (char**)malloc(n * sizeof(char*));

		for (int j = 0; j != n; j++) {
			p[i][j] = (char*)malloc(m * sizeof(char));
		}
	}


	strcpy(p[0][0], "dog");
	strcpy(p[1][1], "cow");
	strcpy(p[2][0], "cat");

	for (int i = 0; i != l; i++) {
		for (int j = 0; j != n; j++) {
			puts(p[i][j]);
		}
	}

	for (int i = 0; i != l; i++) {
		for (int j = 0; j != n; j++) {
			free(p[i][j]);
		}
		free(p[i]);
	}
	free(p);

}