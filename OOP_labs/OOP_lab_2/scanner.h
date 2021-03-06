/***************************************************************************************************
* File:          scanner.h
* Synopsis:      declarations for file 'scanner.c' functions and structures.
* Related files: scanner.c
* Author:        Bohdan Martynchyk KV-74
* Written:       19/11/2018
* Last modified: 29/11/2018
* Source:        https://github.com/bmartynchyk/OOP_third_sem
****************************************************************************************************/

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

void create_db(const char *csv, const char *db);
int make_index(const char *db, const char *field_name);
void reindex(const char *db);
RECORD_SET * get_recs_by_index(const char *db, char *idx_field);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
void print_db(const char *db);
RECORD_SET* select(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);

#endif