/***************************************************************************************************
* File: argz.c
* Synopsis: Definition of 'argz.h' function
* Related files: argz.h
* Author: Bohdan Martynchyk KV-74
* Written: 06/10/2018
* Last modified: 19/11/2018
***************************************************************************************************/

#include "argz.h"

/*-------------------------------------------------------------------------------------------------*
Name:         argz_create_sep
Usage:        argz_create_sep(string, sep, &argz, &argz_len);
Prototype in: argz.h
Synopsis:     separate initial string by character with number 'sep'
Return value: returns error_t value. Result 'OK'(equals 0) - everything is good, 'ERROR'(equals 1) -
one of pointers uninitialized. Main result is in variable 'argz' and argz_len.
*--------------------------------------------------------------------------------------------------*/
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {
	if (NULL == argz || NULL == string || NULL == argz_len)
		return ERROR;

	for (int i = 0; i < *argz_len; i++)
		if ((char)sep == string[i]) *(*argz + i) = '\0';
		else *(*argz + i) = string[i];

		return OK;
}

/*-------------------------------------------------------------------------------------------------*
Name:         argz_count
Usage:        argz_count(argz, arg_len);
Prototype in: argz.h
Synopsis:     counts elements in vector-string, separated by '\0.
Return value: returns number of elements in vector-string.
*--------------------------------------------------------------------------------------------------*/
size_t argz_count(const char *argz, size_t arg_len) {
	size_t count = 0;

	for (int i = 0; i < arg_len; i++)
		if (argz[i] == '\0') count++;

	return count;
}

error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	return OK;
}

void argz_delete(char **argz, size_t *argz_len, char *entry) {

}

error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {
	return OK;
}

char* argz_next(char *argz, size_t argz_len, const char *entry) {
	return NULL;
}

/*-------------------------------------------------------------------------------------------------*
Name:         argz_replace
Usage:        argz_replace(argz, arg_len, entry);
Prototype in: argz.h
Synopsis:     replaces element 'entry' of vector argz' by new element 'with'. Modifies 'argz_len'.
Return value: returns 'ERROR' in case if substring 'str' is not exist or func gets NULL-pointer. 
Returns 'OK' if substring 'str' replaced by 'with'.
*--------------------------------------------------------------------------------------------------*/
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {
	if (NULL == argz || NULL == argz_len || NULL == str || NULL == with)
		return ERROR;

	uint16 spot = 0, str_len = strlen(str),
		with_len = strlen(with);

	char *new_argz = (char*)malloc((*argz_len - str_len + with_len) * sizeof(char));

	for (int i = 0; i < *argz_len - str_len; i++) {
		for (int j = 0; j < str_len; j++, i++) {
			if (str[j] == (*argz)[i]) {
				spot = 1;
			}
			else {
				spot = 0; break;
			}
		}

		if (spot) {
			i -= str_len;

			for (int j = 0; j < i; j++) // Copy all character before str
				new_argz[j] = (*argz)[j];

			for (int j = i; j < i + with_len; j++) // Replace str by with
				new_argz[j] = with[j - i];

			*argz_len = *argz_len - str_len + with_len;

			for (int j = i + with_len; j < *argz_len; j++) // Copy all another character
				new_argz[j] = (*argz)[j + str_len - with_len];

			*argz = new_argz;

			return OK;
		}
	}

	return ERROR;
}

/*-------------------------------------------------------------------------------------------------*
Name:         argz_print
Usage:        argz_print(argz, arg_len);
Prototype in: argz.h
Synopsis:     outputs 'argz' string and length of string.
Return value: none
*--------------------------------------------------------------------------------------------------*/
void argz_print(const char *argz, size_t argz_len) {
	printf("argz_len: %d\n", argz_len);

	for (int i = 0; i < argz_len; i++)
		printf("%c", argz[i]);
}