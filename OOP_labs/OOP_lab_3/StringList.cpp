
#include "StringList.h"

// Constructors
cString::cString() {
	len = 0;
	str = NULL;
}
cString::cString(const char *psz) {
	try {
		if (NULL == psz) throw "Called constructor with NULL parameter!";

		len = strlen(psz);
		str = new char[len];
		strcpy(str, psz);
	}
	catch (char *exeption) {
		printf("\nMESSAGE: %s\n", exeption);
	}
}
cString::cString(const cString& stringsrc) {
	try {
		if (stringsrc.str == NULL) throw "Called constructor with uninitialized object!";

		len = stringsrc.len;
		str = new char[len];
		strcpy(str, stringsrc.str);
	}
	catch (const char *exeption) {
		printf("\nMESSAGE: %s\n", exeption);
	}
}

// Destructors
cString::~cString() {
	delete(str);
	len = 0;
}

// Methods
int cString::Getlength() const {
	return len;
}
bool cString::Isempty() const {
	return false;
}
void cString::Empty() {

}
void cString::SetAt(int nindex, char ch) {

}
int cString::Compare(const cString& s) const {
	return 0;
}
int cString::Find(char ch) const {
	return 0;
}
int cString::Find(char *pszsub) const {
	return 0;
}
void cString::Print() {
	try {
		if (NULL == str) throw "NULL string is outputing!";

		printf("%s", str);
	}
	catch (const char *exeption) {
		printf("\nERROR: %s\n", exeption);
	}
}
cString cString::Mid(int nfirst, int ncount) const {
	cString str;

	return str;
}
cString cString::Left(int ncount) const {
	cString str;

	return str;
}
cString cString::Right(int ncount) const {
	cString str;

	return str;
}

// Operators
cString& cString::operator =(const cString& stringsrc) {
	cString str;

	return str;
}
const cString& cString::operator =(const unsigned char* psz) {
	cString str;

	return str;
}
char cString::operator [](int indx) {
	char str = '\0';

	return str;
}
cString cString::operator +(const cString& string) {
	cString str;

	return str;
}
cString& cString::operator +=(const cString& string){
	cString str;

	return str;
}