
#include <iostream>
#include "StringList.h"
#include <conio.h>

using namespace std;

#define STOP _getch()
#define ENDL std::cout<<std::endl

void main() {
	
	cString *s1 = NULL;
	cString *s2;

	s1 = new cString("123");
	cout << "s1 = new cString('123'); = "; s1->Print();

	s1->SetAt(s1->Getlength() - 2, '&');
	cout << "\ns1->SetAt(s1->Getlength() - 2, '&'); = "; s1->Print();

	s2 = new cString(*s1);
	cout << "\ns2 = new cString(*s1); = "; s2->Print(); ENDL;
	s2->Empty(); s1->Empty();

	cString s3("142"), s4("0123456789");

	cout << "\n\ncString s3('142'); = "; s3.Print();
	cout << "\ncString s4('0123456789'); = "; s4.Print(); ENDL;
	cout << "\ns3.Compare(*s1); = " << s3.Compare(*s1);
	
	s3.SetAt(2, 's');
	cout << "\ns3.SetAt(2, 's'); = "; s3.Print();

	cout << "\n\ns4 = "; s4.Print();
	cString s;

	s = s4.Left(3);
	cout << "\n\ns = s4.Left(3) = "; s.Print();
	if (s == s4.Left(3)) cout << "\n(s == s4.Left(3))? - true";
	else cout << "\n(s == s4.Left(3))? - false";

	s = s4.Right(5);
	cout << "\n\ns = s4.Right(5) = "; s.Print();
	if (s == s4.Right(3)) cout << "\n(s == s4.Right(3))? - true";
	else cout << "\n(s == s4.Right(3))? - false";

	STOP;
}