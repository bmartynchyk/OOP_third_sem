
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
	cString Mid(int nfirst, int ncount) const;
	cString Left(int ncount) const;
	cString Right(int ncount) const;

	// Operators
	cString& operator =(const cString& stringsrc);
	const cString& operator =(const unsigned char* psz);
	char operator [](int indx);
	cString operator +(const cString& string);
	cString& operator +=(const cString& string);

private:
	char *str; // String-value
	int len; // Len of string
};

#endif DEBUG