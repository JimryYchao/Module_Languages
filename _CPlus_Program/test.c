#include <stdio.h>
#include <stdlib.h> /* 提供malloc()原型 */
#include <string.h> /* 提供strcpy()原型 */
#define TSIZE 45	/* 储存片名的数组大小 */
struct film
{
	char title[TSIZE];
	int rating;
	struct film *next; /* 指向链表中的下一个结构 */
};
char *s_gets(char *st, int n); // 处理字符串

int main(void)
{
	struct film *head = NULL;	 	// 创建头指针置空
	struct film *prev, *current; 	// 用来串联链表
	char input[TSIZE];
	/* 1. 收集并储存信息 */
	puts("Enter first movie title:");
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		// 为当前输入的结构动态分配空间
		current = (struct film *)malloc(sizeof(struct film));
		if (head == NULL) 				/* 第 1 个结构 */
			head = current; 			// 头指针
		else 							/* 后续的结构 */
			prev->next = current;		
		current->next = NULL;
		strcpy(current->title, input);
		puts("Enter your rating <0-10>:");
		scanf("%d", &current->rating);
		while (getchar() != '\n')
			continue;
		puts("Enter next movie title (empty line to stop) : ");
		prev = current;
	}
	/* 显示电影列表 */
	if (head == NULL)
		printf("No data entered. ");
	else
		printf("Here is the movie list:\n");
	current = head;
	while (current != NULL)
	{
		printf("Movie: %s Rating: %d\n",
			   current->title, current->rating);
		current = current->next;
	}
	/* 完成任务，释放已分配的内存 */
	current = head;
	while (current != NULL)
	{
		current = head;
		head = current->next;
		free(current);
	}
	printf("Bye!\n");
	return 0;
}
char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); // 查找换行符
		if (find)				 // 如果地址不是 NULL，
			*find = '\0';		 // 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; // 处理剩余输入行
	}
	return ret_val;
}