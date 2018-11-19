/***************************************************************************************************
* File:          argz_test.c
* Synopsis:      project compiled by using C(/TC), VS 2015
* Author:        Bohdan Martynchyk KV-74
* Written:       06/10/2018
* Last modified: 19/11/2018
***************************************************************************************************/

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

	printf("\n\nTest 2) 'argz_replace':\n");
	argz_replace(&argz, &argz_len, "PWD=/bin/monty", "PWD=~/billy");
	argz_print(argz, argz_len);
	STOP;

	printf("\n\nTest 3) 'argz_add':\n");
	argz_add(&argz, &argz_len, "SHELL=/cryptoKeys");
	argz_print(argz, argz_len);
	STOP;

	printf("\n\nTest 4) 'argz_count':\n");
	count = argz_count(argz, argz_len);
	printf("count = %d", count);
	STOP;

	printf("\n\nTest 5) 'argz_delete':\n");
	argz_delete(&argz, &argz_len, "SHELL=/bin/bash");
	argz_print(argz, argz_len);
	STOP;

	printf("\n\nTest 6) 'argz_insert':\n");
	argz_insert(&argz, &argz_len, "PWD=~/billy", "SHELL=/bin/bash");
	argz_print(argz, argz_len);
	STOP;

	printf("\n\nTest 7) 'argz_next':\n");
	for (char *entry = 0; entry = argz_next(argz, argz_len, entry);) printf("%s\n", entry);
	system("pause");
}