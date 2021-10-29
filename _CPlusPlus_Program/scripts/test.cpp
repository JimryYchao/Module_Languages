// strtype4.cpp -- line input
#include <iostream>
#include <string>  // make string class available
#include <cstring> // C-style string library
int main()
{
	using namespace std;
	char charr[20] = {};
	string str;

	cout << R"((This))) "Line" uses "\n" instead of endl._))" << '\n';
	// cin.get();
	return 0;
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