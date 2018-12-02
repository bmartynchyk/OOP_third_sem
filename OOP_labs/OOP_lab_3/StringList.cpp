
#include "StringList.h"
#include <iostream>

// Constructors
cString::cString() : len(0), str(NULL) { }
cString::cString(const char *psz) {
	try {
		if (NULL == psz) throw "Called constructor with NULL parameter!";

		len = strlen(psz);
		str = new char[len + 1]; // Always +1 for NULL-terminated string 
		strcpy(str, psz);		// not to occur error when deleting
	}
	catch (char *exeption) {
		std::cerr << "\nERROR: " << exeption << "\n";
	}
}
cString::cString(const cString& stringsrc) {
	try {
		if (&stringsrc == NULL) throw "Called constructor with NULL reference on cString!";
		if (stringsrc.str == NULL) throw "Called constructor with uninitialized/empty cString object!";

		len = stringsrc.len;
		str = new char[len + 1];
		strcpy(str, stringsrc.str);
	}
	catch (const char *exeption) {
		std::cerr << "\nERROR: " << exeption << "\n";
	}
}

// Destructors
cString::~cString() {
	delete[] str;
	str = NULL;
	len = 0;
}

// Methods
int cString::Getlength() const {
	return len;
}
bool cString::Isempty() const {
	return len;
}
void cString::Empty() {
	try {
		if (NULL == str) throw "cString is already empty!";
		
		delete[] str;
		str = NULL;
		len = 0;
	}
	catch (char *exeption) {
		std::cerr << "\nERROR: " << exeption << "\n";
	}
}
void cString::SetAt(int nindex, char ch) {
	try {
		if (NULL == str) throw 1;
		if (nindex >= len) throw 2;

		str[nindex] = ch;
	}
	catch (const int exeption) {
		switch (exeption) {
		case 1: std::cerr << "\nERROR: Insertion in uninitialized cString!\n"; break;
		case 2: std::cerr << "\nERROR: Out of range of string(length = 0.." << len - 1 << ")!\n"; break;
		}
	}
}
int cString::Compare(const cString& s) const {
	int res = 1; // Default result of comparison with uninitialized/empty cString object 's'

	try {
		if (NULL == s.str) throw "Uninitialized/empty cString comparison - returns 1 by default!";

		res = strcmp(str, s.str);
	}
	catch (const char *exception) {
		std::clog << "\nWARNING: " << exception << "\n";
	}

	return res;
}
int cString::Find(char ch) const {
	int i = 0;

	for (i = 0; i < len; i++) 
		if (str[i] == ch) break;
	
	if (len <= i) i = -1;

	return i;
}
int cString::Find(char *pszsub) const {
	char *temp = strstr(str, pszsub);

	if (NULL == temp) return -1;

	return temp - str;
}
void cString::Print() {
	try {
		if (NULL == str) throw "NULL-string outputing!";

		std::cout << str;
	}
	catch (const char *exeption) {
		std::cerr << "\nERROR: " << exeption << "\n";
	}
}
cString cString::Mid(int nfirst, int ncount) const {
	cString *res = new cString(); // By default returns empty cString

	// If 'ncount' missed, copying from 'nfirst' to the end by default
	if (-1 == ncount) ncount = len - nfirst;

	try {
		if (ncount == 0) throw 1;
		if (nfirst + ncount > len) throw 2;

		res->len = ncount; // Extracting to the result string
		res->str = new char[ncount + 1];
		strncpy(res->str, str + nfirst, ncount);
		res->str[ncount] = '\0';
	}
	catch (const int exception) {
		switch (exception) {
		case 1: std::clog << "\nWARNING: cString is empty!\n"; break;
		case 2: std::cerr << "\nERROR: Out of range of copying!\n"; break;
		}
	}

	return *res;
}
cString cString::Left(int ncount) const {
	cString res;

	if (ncount > len) {
		ncount = len;
		std::clog << "\nWARNING: Out of range! Returning full string!\n";
	}
	if (0 > ncount) {
		std::clog << "\nWARNING: Out of range! Returning empty string!\n";
		return res;
	}

	res.len = ncount;
	res.str = new char[ncount + 1];
	strncpy(res.str, str, ncount);
	res.str[ncount] = '\0';

	return res;
}
cString cString::Right(int ncount) const {
	cString res; // Default result - empty string

	if (ncount > len) {
		ncount = len;
		std::clog << "\nWARNING: Out of range! Returning full string!\n";
	}
	if (0 > ncount) {
		std::clog << "\nWARNING: Out of range! Returning empty string!\n";
		return res;
	}

	res.len = ncount;
	res.str = new char[ncount + 1];
	strncpy(res.str, str + len - ncount, ncount);
	res.str[ncount] = '\0';

	return res;
}

// Operators
cString& cString::operator =(const cString& stringsrc) {
	delete[] this->str;
	len = 0;

	try {
		if (NULL == &stringsrc) throw "Equating to NULL-reference on cString object!";
		if (NULL == stringsrc.str) throw "Equating to empty cSting object!";

		this->len = stringsrc.len;
		this->str = new char[len + 1];
		strcpy(str, stringsrc.str);
		this->str[len] = '\0';
	}
	catch (const char *exception) {
		std::cerr << "\nERROR: " << exception << "\n";
	}

	return *this;
}
const cString& cString::operator =(const unsigned char* psz) {
	delete[] this->str; // Returns empty cString if detected 
	this->len = 0; // NULL-reference on const unsigned char *

	try {
		if (NULL == psz) throw "";

		len = strlen((const char*)psz);
		str = new char[len + 1];
		strcpy(str, (const char*)psz);
		str[len] = '\0';
	}
	catch (const char *exeption) {
		std::cerr << "\nWARNING: " << exeption << "\n";
	}

	return *this;
}
bool cString::operator ==(const cString& stringsrc) {
	int res = 1;

	try {
		if (NULL == &stringsrc) throw "Comparison with NULL-reference on cString object!";
		if (NULL == stringsrc.str) throw "Comparison with uninitialized/empty cString object!";

		res = strcmp(stringsrc.str, str);
	}
	catch (const char *exception) {
		std::cerr << "\nERROR: " << exception << "\n";
	}

	return !res;
}
char cString::operator [](int indx) {
	if (indx >= len) {
		std::cerr << "\nERROR: Out of range for operator[]! Assigned last character!\n";
		indx = len - 1;
	}
	if (indx < 0) {
		std::cerr << "\nERROR: Out of range for operator[]! Assigned first character!\n";
		indx = 0;
	}

	return str[indx];
}
cString cString::operator +(const cString& string) {
	cString res; // Result object of adding

	res.len = this->len;
	
	if (NULL == &string) std::cerr << "\nERROR: Right operand for + is NULL-reference on cString object!\n";
	if (NULL == string.str) std::cerr << "\nWARNING: Right operand for + is uninitialize/empty!\n";
	else res.len += string.len;

	res.str = new char[res.len + 1];

	if (NULL == this->str) std::cerr << "\nWARNING: Left operand for + is uninitialize/empty!\n";
	else strcpy(res.str, this->str);

	if (res.len != this->len)
		strcat(res.str, string.str);
	res.str[res.len] = '\0';

	return res;
}
cString& cString::operator +=(const cString& string) {
	char *buff = new char[len + 1]; // Buffer for temporary copying 'str' variable

	try {
		if (NULL == &string) throw "\nERROR: Adding NULL-reference on cString object!\n";
		if (NULL == string.str) throw "\nWARNING: Adding uninitialized/empty cString object!\n";

		strcpy(buff, str); 
		delete[] str;

		len += string.len; // Creating new string
		str = new char[len + 1];

		strcpy(str, buff); // Copying into destination string
		strcat(str, string.str);
		str[len] = '\0';
	}
	catch(const char *exception){
		std::cerr << exception;
	}

	delete[] buff;

	return *this;
}