
#ifndef _HEADER_H_
#define _HEADER_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct { // Total size: 276 bits
	char manufacturer[128]; // 128
	char model[128]; // 128
	int year; // 4 
	float price; // 4
	int x_size; // 4
	int y_size; // 4
	int id; // 4
} SCAN_INFO;
typedef struct {
	int rec_nmb;// Number of records
	SCAN_INFO *recs;// Records 
} RECORD_SET;

typedef unsigned int uint32;

void create_db(const char *csv, const char *db);
int make_index(const char *db, const char *field_name);
void reindex(const char *db);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
void print_db(const char *db);
RECORD_SET* select(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);

#endif