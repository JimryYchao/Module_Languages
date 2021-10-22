

int main(void)
{

	struct
	{
		unsigned int autfd : 1;
		unsigned int bldfc : 1;
		unsigned int undln : 1;
		unsigned int itals : 1;
	} prnt;

	// prnt 包含 4 个 1 位的字段
	// 由于每个字段恰好为 1 位，所以只能为其赋值 1 或 0
	prnt.itals = 0;
	prnt.undln = 1;

	printf("%zd", sizeof(prnt));
}

#include <stdio.h>