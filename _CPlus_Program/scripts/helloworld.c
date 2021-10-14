#include <stdio.h>
#include<text.h>
int imax(int,...); 

#include <stdio.h>

void Func(int size, int Arr[size]);
void Func(int row, int col, int Arr[row][col]);
void Func(int size, int(*pr)[size]);

#define MONTHS 12
int main(void)
{
	int days[MONTHS] = { 31, 28, [4] = 31,30, 31,[1] = 29 };
	int i;
	for (i = 0; i < MONTHS; i++)
		printf("%2d %d\n", i + 1, days[i]);
	return 0;
}
