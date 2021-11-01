// strtype4.cpp -- line input
#include <iostream>
#include <string>  // make string class available
#include <cstring> // C-style string library
int main()
{
	using namespace std;
	int Arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int* pArr = Arr;

	int counter = -1;
	// 1. 数组模式访问元素
	while(++counter < 10){
		cout << "ARR: " << Arr[counter] << endl;
		cout << "pARR: " << *(pArr + counter) << endl;
	}
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