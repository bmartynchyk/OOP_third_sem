/***************************************************************************************************
* File: argz.h
* Synopsis: declarations for argz functions, types, constants
* Related files: argz.c
* Author: Bohdan Martynchyk KV-74
* Written: 06/10/2018
* Last modified: 19/11/2018
****************************************************************************************************/

#ifndef _STRMANIP_H_
#define _STRMANIP_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stddef.h> 

typedef unsigned short uint16; // 0..65535 - %hu
typedef enum { OK, ERROR } error_t;

error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len);
size_t argz_count(const char *argz, size_t arg_len);
error_t argz_add(char **argz, size_t *argz_len, const char *str);
void argz_delete(char **argz, size_t *argz_len, char *entry);
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry);
char* argz_next(char *argz, size_t argz_len, const char *entry);
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with);
void argz_print(const char *argz, size_t argz_len);

#endif _STRMANIP_H_