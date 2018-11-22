
#include "scanner.h"
#include <stdlib.h>

#define FIELDS_AMOUNT 7
#define FILE_PATH_BUFF 128
#define STRUCT_BIT_SIZE 276
#define FILE_READ_BUFF 128

// 's1' - points to begin of extracting element, 's2' - points to the end of this one
#define MOVE_NEXT(s1, s2) s1 = s2 + 1; s2 = strstr(s1, ";")
// Extracts value into 'dest'
#define EXTRAXT_STR(dest, s1, s2) strncpy(dest, s1, s2 - s1); dest[s2 - s1] = '\0';

// Safely open file 'fname' with mode 'fmode', abort if failed
#define SAFE_OPEN_FILE(file, fname, fmode) if (!(file = fopen(fname, fmode))) { \
printf("ERROR: Could not open file '%s'!\n\n", fname); \
return; \
}

/*-------------------------------------------------------------------------------------------------*
Name:         cmp_<fieldname>
Usage:        cmp_<fieldname>(&scan1, &scan2);
Synopsis:     set of functions which compare spesific structure field.
Return value: returns 1 if 's1' more then 's2' otherwise - returns 0.
*--------------------------------------------------------------------------------------------------*/
int cmp_manuf(SCAN_INFO *s1, SCAN_INFO *s2) {
	int tmp = strcmp(s1->manufacturer, s2->manufacturer);
	return tmp > 0 ? 1 : 0;
}
int cmp_model(SCAN_INFO *s1, SCAN_INFO *s2) {
	int tmp = strcmp(s1->model, s2->model);
	return tmp > 0 ? 1 : 0;
}
int cmp_year(SCAN_INFO *s1, SCAN_INFO *s2) {
	return s1->year > s2->year;
}
int cmp_price(SCAN_INFO *s1, SCAN_INFO *s2) {
	return s1->price > s2->price;
}
int cmp_x_size(SCAN_INFO *s1, SCAN_INFO *s2) {
	return s1->x_size > s2->x_size;
}
int cmp_y_size(SCAN_INFO *s1, SCAN_INFO *s2) {
	return s1->y_size > s2->y_size;
}
int cmp_id(SCAN_INFO *s1, SCAN_INFO *s2) {
	return s1->id > s2->id;
}


typedef int(*Comparator)(SCAN_INFO *s1, SCAN_INFO *s2); // Prototype for comparison funcs

const char *fields[FIELDS_AMOUNT] = { "manufacturer", "model", 
	"year", "price", "x_size", "y_size", "id" };
const Comparator funcs[FIELDS_AMOUNT] = { &cmp_manuf, &cmp_model,
&cmp_year, &cmp_price, &cmp_x_size, &cmp_y_size, &cmp_id };


/*-------------------------------------------------------------------------------------------------*
Name:         free_2d_array
Usage:        free_2d_array(arr, size);
Synopsis:     empty space after using two-dimensional array 'arr'. Result - cleared pointer 'arr'.
Return value: none.
*--------------------------------------------------------------------------------------------------*/
void free_2d_array(void **arr, int size)
{
	for (int i = 0; i < size; i++) free(arr[i]);
	free(arr);
}

// Temp function
void out_one_scan(SCAN_INFO * const scan) {
	printf("Id: %d\n", scan->id);
	printf("Manufacturer: %s\n", scan->manufacturer);
	printf("Model: %s\n", scan->model);
	printf("Year: %d\n", scan->year);
	printf("Price: %f\n", scan->price);
	printf("X-size: %d\n", scan->x_size);
	printf("Y-size: %d\n", scan->y_size);
}

// Temp function
void out_scans_info(SCAN_INFO * const scans, int amount) {
	for (int i = 0; i < amount; i++) {
		printf("\n###[%d]###\n", i);
		out_one_scan(scans + i);
	}
}

/*-------------------------------------------------------------------------------------------------*
Name:         qsort_scans
Usage:        qsort_scans(rec_set, func_criterion);
Synopsis:     quicksort function which sorts incoming 'set' structures by 'criterion' func.
Return value: none.
*--------------------------------------------------------------------------------------------------*/
void qsort_scans(SCAN_INFO *set, int left, int right, Comparator criterion) {
	int l = left, r = right;
	SCAN_INFO temp, pivot = set[(l + r) / 2];

	do { // Criterion returns 0 if in second value will be more then first
		while (criterion(&pivot, set + l)) l++;
		while (criterion(set + r, &pivot)) r--;

		if (l <= r) {
			temp = set[l];
			set[l] = set[r];
			set[r] = temp;

			l++; r--;
		}
	} while (l < r);

	if (left < r) qsort_scans(set, left, r, criterion);
	if (l < right) qsort_scans(set, l, right, criterion);
}

/*-------------------------------------------------------------------------------------------------*
Name:         create_db
Usage:        create_db("f1/f2/data.csv", "f3/database");
Prototype in: sacnner.h
Synopsis:     extracts record from 'csv' file. Separates records by values. Removes dublicate records.
Fills structures 'SCAN_INFO' with values of records(each record is 1 structure) and pushes them into 
binary database file. Result is new binary file 'db' with unique values from file 'csv'.
Return value: none.
*--------------------------------------------------------------------------------------------------*/
void create_db(const char *csv, const char *db) {
	int count = 0, i = 0,
		left = 0, right = 0, midd = 0; // For binary search
	FILE *csv_file = NULL, *db_file = NULL;
	char buff[STRUCT_BIT_SIZE],
		*substr1 = NULL, *substr2 = NULL, //For extracting elements into struct
		**str_hive = NULL;
	SCAN_INFO scan;

	SAFE_OPEN_FILE(csv_file, csv, "r");

	while (NULL == feof(csv_file)) { //Getting strings form '*.csv' file, checking on buffer overloading
		if (STRUCT_BIT_SIZE <= strlen(fgets(buff, STRUCT_BIT_SIZE, csv_file))) {
			printf("\nERROR: Buffer overloaded! Records should be less 300 characters!\n");
			return;
		}
		count++;
	}

	str_hive = (char**)malloc(count * sizeof(char*));
	fseek(csv_file, 0, SEEK_SET);

	i = 0;
	while (NULL == feof(csv_file)) {
		if (NULL == fgets(buff, STRUCT_BIT_SIZE, csv_file)) {
			printf("\nERROR: Reading failure string='%s' from file='%s'!\n", buff, csv);
			return;
		}

		str_hive[i] = (char*)malloc(STRUCT_BIT_SIZE * sizeof(char));
		strcpy(str_hive[i], buff);
		i++;
	}

	fclose(csv_file);
	
	SAFE_OPEN_FILE(db_file, db, "wb");
	if (!db_file) {
		free_2d_array(str_hive, count);
		return;
	}

	// The last string may be differ from previous ones. We compare full string and it have 
	//character '\n'. Last string may have this character or no. Function 'strstr' return
	//different results for strings "111\n\0" and "111\0". So to escape this, performs backward 
	//search. It escapes cases with skipping last string if it equal to another one.
	for (int i = count - 1; i > 0; i--) {
		if (NULL == str_hive[i]) continue;

		for (int j = i - 1; j >= 0; j--) // Deleting the same values
			if (NULL != str_hive[j] && strstr(str_hive[j], str_hive[i])) {
				free(str_hive[j]);
				str_hive[j] = NULL;
				count--;
			}
	}

	fwrite(&count, sizeof(count), 1, db_file);

	// Latest id for scanner will be less than number of scanners on 1. Use this feature for cycle.
	for (int i = 0, id = 0; id < count; i++) {
		if (NULL == str_hive[i]) continue;

		char dest[20]; // Destination string variable
		substr1 = str_hive[i], substr2 = strstr(substr1, ";");

		// Subtracting 2 because of adding 'id' field and the way of last string conversion for field 'y_sze'
		for (int j = 0; j < FIELDS_AMOUNT - 2; j++) {
			EXTRAXT_STR(dest, substr1, substr2); // Extracting current value for specific field
			MOVE_NEXT(substr1, substr2);

			switch (j) {
			case 0: strcpy(scan.manufacturer, dest); break;
			case 1: strcpy(scan.model, dest); break;
			case 2: scan.year = atoi(dest); break;
			case 3: scan.price = atof(dest); break;
			case 4: scan.x_size = atoi(dest); break;
			}
		}

		scan.y_size = atoi(substr1);
		scan.id = id++; // Firstly assignes 'id' then it increments

		fwrite(&scan, sizeof(SCAN_INFO), 1, db_file);
	}

	fclose(db_file);
	free_2d_array(str_hive, count);
}

/*-------------------------------------------------------------------------------------------------*
Name:         make_index
Usage:        make_index("f1/f2/database", "field_name");
Prototype in: sacnner.h
Synopsis:     makes an index-file(with extension '.idx') in which has ids of structures. This ids is
set's of structures ids which sorted by increase by specific field.
Return value: returns 1 in case if all performed without mistakes else returns 0.
*--------------------------------------------------------------------------------------------------*/
int make_index(const char *db, const char *field_name) {
	FILE *db_file = NULL, *res_file = NULL;
	int fld_num = 0, // Number of structure's field
		scans_num = 0; // Amount structures in file
	char filename[64];
	SCAN_INFO *set;

	SAFE_OPEN_FILE(db_file, db, "rb");

	fread(&scans_num, sizeof(int), 1, db_file);
	set = (SCAN_INFO*)malloc(scans_num * sizeof(SCAN_INFO));
	fread(set, sizeof(SCAN_INFO), scans_num, db_file);
	fclose(db_file);

	while (FIELDS_AMOUNT > fld_num && strcmp(fields[fld_num], field_name))
		fld_num++; // Detect number of field

	if (FIELDS_AMOUNT <= fld_num) {
		printf("ERROR: Invalid field name, correct it and try again!");
		return 0;
	}

	strcpy(filename, "Database/"); // Creating file name with extension
	strcat(filename, fields[fld_num]);
	strcat(filename, ".idx");

	qsort_scans(set, 0, scans_num - 1, funcs[fld_num]);

	SAFE_OPEN_FILE(res_file, filename, "w");

	for (int i = 0; i < scans_num; i++)
		fprintf(res_file, "%d ", set[i].id);

	fclose(res_file);
	free(set);

	return 1;
}

/*-------------------------------------------------------------------------------------------------*
Name:         reindex
Usage:        reindex();
Prototype in: sacnner.h
Synopsis:    creates an index file (with the extension “.idx”) in which there are identifiers of 
structures for all fields. These identifiers are the identifiers of the structures, which are sorted 
by increase of according field.
Return value: none.
*--------------------------------------------------------------------------------------------------*/
void reindex(const char *db) {
	for (int i = 0; i < FIELDS_AMOUNT; i++)
		if (0 == make_index(db, fields[i])) {
			printf("ERROR: Failed creating index file '%s.idx' for database '%s'!\n", fields[i], db);
			return;
		}
}

/*-------------------------------------------------------------------------------------------------*
Name:         get_recs_by_index
Usage:        get_recs_by_index("Database/db1", "Database/year");
Prototype in: sacnner.h
Synopsis:     reads the order of scanners from 'idx_filed + .idx' file. And forms result variable by
according to this order.
Return value: RECORD_SET* variable, which contains the array of scanners and size of it's array. In
another uncorrect case returns NULL.
*--------------------------------------------------------------------------------------------------*/
RECORD_SET* get_recs_by_index(const char *db, char *idx_field) {
	FILE *idx_file = NULL, *db_file = NULL;
	SCAN_INFO *scans = NULL;
	char file_name[FILE_PATH_BUFF]; // Target file's name
	int *ids = NULL; // Array of ids stored in 'idx_filed' file
	RECORD_SET *set = (RECORD_SET*)malloc(sizeof(RECORD_SET)); // The number of scanners
	//for this func stored in field of 'set' structure(set->rec_nmb)

	if (strlen(idx_field) + 4 > FILE_PATH_BUFF) { // Checking buffer overflow for 'file_name'
		printf("ERROR: Overloaded buffer for file path/name! It should be less then 128!");
		return NULL;
	}
	strcpy(file_name, idx_field); // Creating file name with extension
	strcat(file_name, ".idx");

	SAFE_OPEN_FILE(db_file, db, "rb");

	fread(&(set->rec_nmb), sizeof(int), 1, db_file);
	scans = (SCAN_INFO*)malloc(set->rec_nmb * sizeof(SCAN_INFO));
	ids = (int*)malloc(set->rec_nmb * sizeof(int));
	set->recs = (SCAN_INFO*)malloc(set->rec_nmb * sizeof(SCAN_INFO));
	fread(scans, sizeof(SCAN_INFO), set->rec_nmb, db_file);

	fclose(db_file);

	SAFE_OPEN_FILE(idx_file, file_name, "r");

	for (int  i = 0; i<set->rec_nmb; i++)
		fscanf(idx_file, "%d", (ids + i));

	fclose(idx_file);

	for (int i = 0; i < set->rec_nmb; i++)
		set->recs[i] = scans[ids[i]];

	free(scans); free(ids);

	return set;
}

void del_scanner(const char *db, int id) {

}

void add_scanner(const char *db, const char* scanner_str) {

}

void print_db(const char *db) {

}

RECORD_SET* select(const char *db, const char *field, const char *value) {
	return NULL;
}

void print_rec_set(RECORD_SET *rs) {

}