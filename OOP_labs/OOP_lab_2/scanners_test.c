#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include "scanner.h"

#define STOP _getch()

void main() {
	create_db("Database/scanners.csv", "Database/database");
	make_index("Database/database", "year");
	reindex("Database/database");
	STOP;
}