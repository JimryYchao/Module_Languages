#include <stdio.h>
#include <string.h> // 提供 strcpy()、strlen() 的原型
#include <stdlib.h> // 提供 malloc()、free() 的原型
#define SLEN 81
struct namect
{
	char *fname; // 使用指针
	char *lname;
	int letters;
};
void getinfo(struct namect *); 		// 分配内存
void makeinfo(struct namect *);
void showinfo(const struct namect *);
void cleanup(struct namect *); 		// 调用该函数时释放内存
char *s_gets(char *st, int n);
int main(void)
{
	struct namect person;
	getinfo(&person);	// 获取标准输入并 malloc 分配空间储存字符串, 将结构中的指针指向 malloc
	makeinfo(&person);	// 计算结构的另外一个成员, 名字的长度
	showinfo(&person);	// 标准输出显示结构中的姓名信息
	cleanup(&person);	// 释放指针指向的 malloc 内存
	return 0;
}
// 为结构分配内存
void getinfo(struct namect *pst)
{
	char temp[SLEN];
	// first name
	printf("Please enter your first name.\n");
	s_gets(temp, SLEN);
	pst->fname = (char *)malloc(strlen(temp) + 1);	// 分配内存以储存名, 字符串的长度 + \0
	strcpy(pst->fname, temp);			// 把名拷贝到动态分配的内存中
	// last name
	printf("Please enter your last name.\n");
	s_gets(temp, SLEN);
	pst->lname = (char *)malloc(strlen(temp) + 1);
	strcpy(pst->lname, temp);
}
// 计算结构中 letters 的值 (name 的长度)
void makeinfo(struct namect *pst)
{
	pst->letters = strlen(pst->fname) + strlen(pst->lname);
}
void showinfo(const struct namect *pst)
{
	printf("%s %s, your name contains %d letters.\n",
		   pst->fname, pst->lname, pst->letters);
}
// 释放结构中字符指针的资源
void cleanup(struct namect *pst)
{
	free(pst->fname);
	free(pst->lname);
}

char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;
	ret_val = fgets(st, n, stdin); 	//获取标准输入
	if (ret_val)
	{
		find = strchr(st, '\n'); 	// 查找换行符
		if (find)				 	// 如果地址不是 NULL，
			*find = '\0';		 	// 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; 			// 处理输入行的剩余部分
	}
	return ret_val;
}