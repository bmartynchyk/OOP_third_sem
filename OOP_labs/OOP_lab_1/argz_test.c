#include <stdio.h>
#include <conio.h>
#include "argz.h"

#define STOP _getch()

void main() {
	int argz_len = 58;
	char *const string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz = (char*)malloc(argz_len * sizeof(char));
	int count = 0;

	STOP;
}