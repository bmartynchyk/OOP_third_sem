/***************************************************************************************************
* File:          scanners_test.c
* Synopsis:      project compiled & debug by using C(/TC), Visual Studio 2015. You can upload project.
Another version of this project could be different.
* Author:        Bohdan Martynchyk KV-74
* Written:       19/11/2018
* Last modified: 29/11/2018
* Source:        https://github.com/bmartynchyk/OOP_third_sem
***************************************************************************************************/

#include <stdio.h>
#include <conio.h>
#include "scanner.h"

#define STOP _getch()

void main() {
	create_db("Database/scanners.csv", "Database/database");
	print_db("Database/database");
	reindex("Database/database");
	add_scanner("Database/database", "SAMSUNG;AspireCX700;2018;1479.99;350;410");
	print_db("Database/database");
	del_scanner("Database/database", 5);
	print_db("Database/database");
	RECORD_SET *rs = select("Database/database", "model", "JetScan7");
	printf("\n\n1) select('Database/database', 'model', 'JetScan7');\n\n");
	print_rec_set(rs);
	rs = get_recs_by_index("Database/database", "Database/year");
	printf("\n\n2) get_recs_by_index('Database/database', 'Database/year');\n\n");
	print_rec_set(rs);
	STOP;
}