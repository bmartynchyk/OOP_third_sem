/***************************************************************************************************
* File:          StringList.h
* Synopsis:      declaration of methods, constructors, destructors and overloaded operators of class 
* cString. Forms module with file StringList.cpp.
* Related files: StringList.cpp
* Author:        Bohdan Martynchyk KV-74
* Written:       01/12/2018
* Last modified: 02/12/2018
* Source:        https://github.com/bmartynchyk/OOP_third_sem
***************************************************************************************************/

#ifndef DEBUG
#define DEBUG

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>

class cString {
public:
	// Constructors
	cString();
	cString(const char *psz);
	cString(const cString& stringsrc);

	// Destructors
	~cString();

	// Methods
	int Getlength() const;
	bool Isempty()const;
	void Empty();
	void SetAt(int nindex, char ch);
	int Compare(const cString& s) const;
	int Find(char ch) const;
	int Find(char *pszsub) const;
	void Print();
	cString Mid(int nfirst, int ncount = -1) const;
	cString Left(int ncount) const;
	cString Right(int ncount) const;

	// Operators
	cString& operator =(const cString& stringsrc);
	const cString& operator =(const unsigned char* psz);
	bool operator ==(const cString& stringsrc);
	char operator [](int indx);
	cString operator +(const cString& string);
	cString& operator +=(const cString& string);

private:
	char *str; // String-value
	int len; // Len of string
};

#endif DEBUG