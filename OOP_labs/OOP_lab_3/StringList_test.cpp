
#include <iostream>
#include "StringList.h"
#include <conio.h>

using namespace std;

#define STOP _getch()

void main() {
	cString *str1 = NULL, str2(NULL), str3;
	cString s4(str3);

	str1 = new cString("123");
	str1->Print();
	str3 = str2;


	STOP;
}