#include <stdio.h>
#include <conio.h>
#include "argz.h"

#define STOP _getch()

void main() {
	size_t argz_len = 58;
	char *const string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz = (char*)malloc(argz_len * sizeof(char));
	int count = 0;

	printf("Test 1) 'argz_create_sep':\n");
	argz_create_sep(string, 58, &argz, &argz_len);
	argz_print(argz, argz_len);
	STOP;

	printf("\n\nTest 2) 'argz_count':\n");
	count = argz_count(argz, argz_len);
	printf("count = %d\n", count);
	STOP;
}