#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include "scanner.h"

#define STOP _getch()

void main() {
	RECORD_SET *set = NULL;

	create_db("Database/scanners.csv", "Database/database");
	make_index("Database/database", "year");
	reindex("Database/database");
	set = get_recs_by_index("Database/database", "Database/manufacturer");
	print_rec_set(set);
	print_db("Database/database");
	STOP;
}