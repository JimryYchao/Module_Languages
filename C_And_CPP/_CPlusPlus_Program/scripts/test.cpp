// strtype4.cpp -- line input
#include <iostream>
#include <string>  // make string class available
#include <cstring> // C-style string library

typedef void (*PF)(int);
using namespace std;
void fun(int);
int &fun(int &n, int &&m);

extern "C" void spiff(int);	  // use C protocol
extern void spoff(int);		  // use C++ protocol
extern "C++" void spaff(int); // use C++ protocol

template <typename T>
void Swap(T, T);

int main()
{
	int *pa = new int[3]{1, 2, 3};
	cout << pa << endl;
	cout << &pa[2] << endl;
	const int *p = &pa[2];
	delete [] pa;
	cout << pa << endl;
	cout << *p << endl;

	PF pf = fun;
	pf(10);

	PF Pspiff = spiff;
	Pspiff(11);

	PF Pspoff = spoff;
	Pspiff(12);

	PF Pspaff = spaff;
	Pspiff(13);
}

void spiff(int x)
{
	fun(x);
}
void spoff(int x)
{
	fun(x);
}
void spaff(int x)
{
	fun(x);
}

void fun(int n)
{
	using namespace std;
	cout << n;
}
/*
	Length of string in charr before input: 0
	Length of string in str before input: 0
	Enter a line of text:
	Hello
	You entered: Hello
	Enter another line of text:
	World
	You entered: World
	Length of string in charr after input: 5
	Length of string in str after input: 5
*/