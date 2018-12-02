
#include <iostream>
#include "StringList.h"
#include <conio.h>

using namespace std;

#define STOP _getch()
#define ENDL std::cout<<std::endl

void main() {
	cString *s1 = NULL;
	cString *s2;

	s1 = new cString("123"); // Tested: cString(const char *);
	cout << "s1 = new cString('123'); => "; s1->Print(); // Tested: void Print();

	s1->SetAt(s1->Getlength() - 2, '&'); // Tested: void SetAt(int, char); int Getlength();
	cout << "\ns1->SetAt(s1->Getlength() - 2, '&'); => "; s1->Print();

	s2 = new cString(*s1); // Tested: cString(cString&);
	cout << "\ns2 = new cString(*s1); => "; s2->Print(); ENDL;
	s2->Empty(); s1->Empty(); // Tested: void Empty();

	cString s3("142"), s4("0123456789");

	cout << "\n\ncString s3('142'); => "; s3.Print();
	cout << "\ncString s4('0123456789'); => "; s4.Print(); ENDL;
	cout << "\ns3.Compare(*s1); => " << s3.Compare(*s1); // Tested: int Compare(cString&);
	
	s3.SetAt(2, 's');
	cout << "\ns3.SetAt(2, 's'); => "; s3.Print();

	cout << "\n\ns4 = "; s4.Print();
	cString s;

	s = s4.Left(3); // Tested: cString operator =(cString&); cString Left(int);
	cout << "\n\ns = s4.Left(3); => "; s.Print();
	if (s == s4.Left(3)) cout << "\n(s == s4.Left(3))? => true"; // Tested: bool operator ==(cString&);
	else cout << "\n(s == s4.Left(3))? => false";

	s = s4.Right(5); //Tested: cString Right(int);
	cout << "\n\ns = s4.Right(5); => "; s.Print();
	if (s == s4.Right(3)) cout << "\n(s == s4.Right(3))? => true";
	else cout << "\n(s == s4.Right(3))? => false";

	// Tested: int Find(char); int Find(char *);
	cout << "\n\ns4.Find('6'); => " << s4.Find('6');
	cout << "\ns4.Find('599'); => " << s4.Find("599");
	cout << "\ns4.Find('5678'); => " << s4.Find("5678"); ENDL;

	cout << "\ns4[-1] = " << s4[-1]; // Tested: char operator[] (int);
	cout << "\ns4[3] = " << s4[3];
	cout << "\ns4[13] = " << s4[13];

	s = s4.Mid(4, 3); // Tested: cString Mid(int, int)
	cout << "\n\ns = s4.Mid(4, 3); => "; s.Print();
	s = s4.Mid(2);
	cout << "\ns = s4.Mid(2); => "; s.Print();

	cString ss(" + cString");
	s = "new cString"; // Tested: cString operator =(const unsigned char*);
	cout << "\n\ns = 'new cString'; => "; s.Print();
	cout << "\nss(' + cString'); => "; ss.Print();

	s += ss; // Tested: cString operator +=(const cString&);
	cout << "\ns += ss; => "; s.Print();

	cString sss;

	sss = s + ss; // Tested: cString operator +(const cString&);
	cout << "\nsss = s + ss; => "; sss.Print();
	STOP;
}