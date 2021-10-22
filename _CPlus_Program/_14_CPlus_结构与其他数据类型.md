# C Plus 结构与其他数据类型

- 关键字：struct、union、enum、typedef
- 运算符：" . " " -> "
- 结构与结构变量，访问结构成员, 匿名结构
- 联合, 枚举和指向函数的指针

---
- [C Plus 结构与其他数据类型](#c-plus-结构与其他数据类型)
	- [1. 复合数据结构](#1-复合数据结构)
	- [2. 结构 struct](#2-结构-struct)
		- [2.1 结构声明](#21-结构声明)
		- [2.2 定义结构变量](#22-定义结构变量)
	- [3. 结构数组](#3-结构数组)
	- [4. 指向结构的指针](#4-指向结构的指针)
	- [5. 结构应用](#5-结构应用)
		- [5.1 向函数传递结构的信息](#51-向函数传递结构的信息)
		- [5.2 其他结构的特征](#52-其他结构的特征)
		- [5.3 结构中的字符数组和字符指针](#53-结构中的字符数组和字符指针)
		- [5.4 结构, 指针和 malloc 函数](#54-结构-指针和-malloc-函数)
		- [5.5 复合字面量和结构 (C99)](#55-复合字面量和结构-c99)
		- [5.6 伸缩型数组成员 (C99)](#56-伸缩型数组成员-c99)
		- [5.7 匿名结构 (C11)](#57-匿名结构-c11)
	- [6. 把结构内容保存在文件中](#6-把结构内容保存在文件中)
	- [7. 链式结构](#7-链式结构)
	- [8. 联合 union](#8-联合-union)
		- [8.1 联合应用](#81-联合应用)
		- [8.2 匿名联合 (C11)](#82-匿名联合-c11)
	- [9. 枚举 enum](#9-枚举-enum)
		- [9.1 枚举常量](#91-枚举常量)
		- [9.2 枚举特性](#92-枚举特性)
	- [10. 共享名称空间 (关于结构, 联合, 枚举标记)](#10-共享名称空间-关于结构-联合-枚举标记)
	- [11. typedef 关键字](#11-typedef-关键字)
		- [11.1 typedef 工作原理](#111-typedef-工作原理)
	- [12. 一些复杂的声明](#12-一些复杂的声明)
	- [13. 函数与指针](#13-函数与指针)

---
## 1. 复合数据结构

- 单一变量表示数据的方式在大多数情况中形容对象的特征表现的很单一，例如要打印一份图书目录，想打印每本书的各种信息：书名、作者、出版社、版权日期、页数、册数和价格

- 用 7 个不同的数组分别记录每一项比较繁琐，尤其是若想创建多份列表：一份按书名排序、一份按作者排序、一份按价格排序等

- 因此需要一种即能包含字符串又能包含数字的数据形式，而且还要保持各信息的独立
  
---
## 2. 结构 struct

### 2.1 结构声明

- 结构声明（structure declaration）描述了一个结构的组织布局

- 结构的标记名是可选的。但是以程序示例中的方式建立结构时（在一处定义结构布局，在另一处定义实际的结构变量），必须使用标记。

- 如果打算多次使用结构模板，就要使用带标记的形式；或者，使用 typedef。

> 标识声明

```c
	#define MAXTITL 41 /* 书名的最大长度 + 1 */
	#define MAXAUTL 31 /* 作者姓名的最大长度 + 1*/
	
	struct book { 				/* 结构模版：标记是 book */
		char title[MAXTITL];
		char author[MAXAUTL];
		float value;
	};	// 需要分号表示结构的布局定义结束

	struct {					/* 无结构标记 */
		int Num;
	} NUM;	// 未声明标记的结构变量
```

- 该声明描述了一个由两个字符数组和一个float类型变量组成的结构

* 该声明并未创建实际的数据对象，只描述了该对象由什么组成：
  - book 表示为该结构模板的标记名称
  - 结构块中表示由什么类型复合组成，不能包含函数

> 声明结构变量

```c
	struct book lib;
```

> 结构中可以包含的内容

- 可以包含任意一种 C 的数据结构

- 可以是其他结构变量, 但要求包含的该结构的布局定义在该结构之前声明

- 组合其他结构时, 会将内部结构布局的变量组合映射到外层结构的布局定义中

- 指向自身的指针对象, 指向其他结构的指针

```c
	struct A{
		int A_num;
	}

	struct B{
		int B_num;
		struct A a;
	};

	struct B b;
	/* b 本质在声明时的布局 {
			int B_num;
			int	A.A_num;  <<< struct A a
	  }; */
```

> 可以不声明标识直接指定变量

```c
	struct {
		// 复合结构布局
	} s_myStruct;

	struct{	
		int num1;
		int num2;
	} NUMs = {1,2};
```

> 声明的位置

- 可以是文件作用域, 或其他块中, 或某个函数的内部, 它的标记仅供该作用域内部使用 (包括内部块)

> 结构的嵌套

- 嵌套存在几种情况, 一种是嵌套外部结构, 一种是内部声明结构的布局 (内部结构的变量)

---
### 2.2 定义结构变量

* 结构有两层含义 
  - 一是 "结构布局": 结构布局告诉编译器如何表示数据，但是它并未让编译器为数据分配空间
  - 二是 "结构变量": 创建一个结构变量, 并为其分配空间, 根据布局成员的顺序分配连续的空间

- 结构布局的内部不允许初始化成员, 仅存在声明

- 声明结构变量时, 编译器使用该结构的布局为该变量分配空间

> 初始化结构

```c
#include<stdio.h>
int main(void){
	struct book{
		const char * Name;
		int cost;
	};

	// 1. 外部声明
	struct book myBook;
	myBook.Name = "Ychao";
	myBook.cost = 99;

	// 2. 块初始化
	struct book myBook2 = {
		"Ychao",99,
	};

	// 3. 指定初始化器
	struct book mBook3 ={
		.Name = "Ychao",
		.cost = 99,
	};

	// 4. 无标识符结构变量
	struct{
		const char * Name;
		int cost;
	} MBook = {
		.Name = "Ychao",
		.cost = 99,
	};
}
```

> 访问结构成员

- '.' 访问结构中的成员, '.' 的优先级高于 ( )

> 结构的初始化器

- 在结构的初始化中同时使用了指定初始化器与普通初始化器, 与数组声明方式相似

---
## 3. 结构数组

> 结构与内存

- 创建了一个内含 100 个结构变量的数组。由于该数组是自动存储类别的对象，其中的信息被储存在栈（stack）中。

- 如此大的数组可能会需要很大一块内存, 可能会存在栈溢出, 可以使用编译器选项设置栈大小为 10000，以容纳这个结构数组

- 或者将数组声明为静态或者外部数组 

> 声明结构数组

```c
	#define size 10
	struct book{
		int cost;
	};

	struct book lib[size];	// lib 是一个数组名, 每个元素是一个结构变量

	>>> 等价于 struct book *plib[size]

	// 调用
	lib[0].cost = 99;
```

---
## 4. 指向结构的指针

> 结构指针的特点

- 像指向数组的指针比数组本身更容易操控(如, 排序问题), 指向结构的指针通常比结构本身更容易操控

- 在一些早期的 C 实现中，结构不能作为参数传递给函数，但是可以传递指向结构的指针

- 传递结构指针比传递结构本身效率更高

- 一些用于表示数据的结构中包含指向其他结构的指针

> 结构指针的声明

```c
	struct book{
		int cost;
	} bp;

	struct book * pbook = &bp;
```

> 用指针访问成员

- 第一种方式(常用) : 使用 -> 运算符

```c
	struct book{
		const char * name;
		int cost;
	} lib;

	struct book *pbook;
	pbook == &lib;  
	pbook -> cost = 99;	// 等价于 lib.cost
```

- 第二种方式: 解指针方式访问成员

```c
	(*pbook).cost = 99;
```

---
## 5. 结构应用

### 5.1 向函数传递结构的信息

> 传递结构成员

```c
	// 传递结构的成员
	printf("Name: %s, Cost: %d", pbook -> name, pbook -> cost);
	printf("Name: %s, Cost: %d", lib.name, lib.cost");

	// 在函数中修改结构变量的值
	modify(&lib.cost);
	modify(&(pbook->cost));
```

> 传递结构的地址

```c
	// 传递指针 pbook 进入 modity 函数, 修改 cost 的值
	struct book * pbook = &lib;
	modity(pbook);

	modity(struct book * ptr){
		ptr -> cost = 99;
	}
```

> 传递结构

```c
	// 传递结构 lib 进入 modity 函数, 修改 cost 的值
	struct book lib;
	modity(lib);

	modity(struct book mbook){
		mbook.cost = 99;
	}
```

---
### 5.2 其他结构的特征

> 结构赋值

- 两个结构变量的类型相同, 可以将一个结构赋值给另一个结构 (与简单数据结构相同的行为, 数组不可以)

> 结构与结构指针的选择

- 向函数传递参数时可以传递结构本身或结构指针

- 使用指针作为参数, 传递参数的速度比传递整个结构要快, 但是无法保证数据是否被修改, 但函数的执行速度会很快

- 把结构传递给参数, 函数处理的是结构原始数据的副本, 保护了原始数据, 但占用了一定的内存资源

- 一般地, 仅处理结构的一小部分或追求效率时可以传递结构指针, 防止被修改可以 const 限定; 按值传递结构是处理小型结构常用的方法

---
### 5.3 结构中的字符数组和字符指针

```c
	// 1. 字符串数组作为成员
	struct name{
		char first[LEN];
		char last[LEN];
	}

	// 2. 字符指针作为成员
	struct pname{
		char * first;
		char * last;
	}

	struct names veep = {"Talia", "Summers"};
	struct pnames treas = {"Brad", "Fallingjaw"};
```

- name 结构将两个固定大小的数组用于储存姓名, 字符串储存在结构内部

- pname 结构保存了两个指针变量, 它使用的是储存在别处的字符串(字符串常量或数组中的字符串)

> 使用 pname 时的潜在危险

- 由于 pname 中的指针是未初始化的变量, 因此地址可以是任何值, 为其赋值可能会修改掉原有的程序数据, 直接赋值操作可能会导致程序的崩溃

- 因此，如果要用结构储存字符串，用字符数组作为成员比较保险。用指向 char 的指针也行，但是误用会导致严重的问题。
  
---
### 5.4 结构, 指针和 malloc 函数

- 如果使用 malloc 分配内存并使用指针储存该地址, 在结构中使用指针处理字符串就比较合理

- 声明的字符串储存在 malloc 分配的空间, 不会失误覆写修改程序中的数据, 结构中储存声明的字符串的地址, 字符串并未储存在结构中, 因此处理字符串的函数直接使用结构传递的指针即可

- 需要成对使用 malloc 与 free (或 calloc 与 free)

```c
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
```

---
### 5.5 复合字面量和结构 (C99)

- C99 的复合字面量特性可用于结构与数组，可以使用复合字面量创建一个数组作为函数的参数或赋给另一个结构

```c
	struct book lib2;
	lib2 = (struct book){{"The Idiot", 6.99};

	method(struct book _book){}
	method((struct book){"The Idiot", 6.99});

	function(struct book* _pbook){}
	function(&(struct book){"The Idiot", 6.99});
```

---
### 5.6 伸缩型数组成员 (C99)

- C99 新增了一个特性： 伸缩型数组成员（ flexible array member），该数组最后一个成员具有一些特性

- 该数组不会立即存在，使用这个伸缩型数组成员可以编写合适的代码，就好像它确实存在并具有所需数目的元素一样

> 声明

```c
	struct flex{
		int count;
		double average;
		double scores[];	// 伸缩型数组成员, 要求不声明大小, 必须是最后一个, 结构中至少有一个非伸缩成员
	}
```

- 声明一个 struct flex 类型的结构变量时，不能用 scores 做任何事，因为没有给这个数组预留存储空间

- C99 意图声明一个指向 struct flex 的指针, 然后用 malloc 类分配足够的空间, 以存储 struct flex 结构的常规内容与伸缩型数组成员所需的额外空间

```c
	struct flex * pf;
	pf = malloc(sizeof(struct flex) + 5 * sizeof(double));	
	// 分配一个内含 5 个 double类型的数组的 flex
```

> 伸缩型数组成员案例

```c
#include <stdio.h>
#include <stdlib.h>
struct flex
{
	size_t count;
	double average;
	double scores[]; // 伸缩型数组成员
};
void showFlex(const struct flex *p);	// 打印 scores
int main(void)
{
	struct flex *pf1, *pf2;
	int n = 5;
	int i;
	int tot = 0;
	// 1. 为结构和数组分配存储空间
	pf1 = malloc(sizeof(struct flex) + n * sizeof(double));
	pf1->count = n;	// 数组的长度
	for (i = 0; i < n; i++)
	{
		pf1->scores[i] = 20.0 - i;
		tot += pf1->scores[i];
	}
	pf1->average = tot / n;
	showFlex(pf1);
	free(pf1);
	return 0;
}
void showFlex(const struct flex *p)
{
	int i;
	printf("Scores : ");
	for (i = 0; i < p->count; i++)
		printf("%g ", p->scores[i]);
	printf("\nAverage: %g\n", p->average);
}
/*
	Scores : 20 19 18 17 16 
	Average: 18
*/
```

> 使用带伸缩型数组的结构应注意

- 不能用结构进行赋值或拷贝

```c
	struct flex * pf1, *pf2; 	// *pf1 和*pf2 都是结构
	*pf2 = *pf1; 	// 不要这样做, 因为只能拷贝除伸缩型数组成员以外的其他成员
```

- 不要以按值方式把这种结构传递给结构 (行为与赋值类似)

- 不要使用带伸缩型数组成员的结构作为数组成员或另一个结构的成员。

---
### 5.7 匿名结构 (C11)

> 常规嵌套

```c
	struct names{
		char first[20];
		char last[20];
	};
	struct person{
		int id;
		struct names name;
	};

	struct person pSir = {1,{"Jimry","Ychao"}};
	struct person pMiss = {2,"Lily","Who"};
	struct person pMrs = {.id = 3,.name.first = "Mary","White"};
/*
	pSir.name.first = "Jimry";
	pSir.name.last = "Ychao";
	pSir.id = 1;
*/
```

> 匿名结构作为成员存在于其他结构

```c
	// 1. 无标识匿名
	struct person{
		int id;
		struct{
			char first[20];		>>>>>   person 直接访问
			char last[20];
		};
	};
	// 2. 带标识匿名
	struct person{
		int id;
		struct names{
			char first[20];		>>>>>   person 直接访问, names 标识在内部使用
			char last[20];
		};
	};
	// 3. 带标识匿名声明, 内部声明该标识变量
	struct person{
		int id;
		struct names{
			char first[20];		>>>>>   person 直接访问, name 使用 names 标识
			char last[20];			    并作为成员嵌入到 person
		};
		struct names name;
	};
	// 4. 内部声明匿名结构的标识与变量
		struct person{
		int id;
		struct names{
			char first[20];		>>>>>   需要通过 name 访问, names 标识在内部使用
			char last[20];
		} name;
	};
	// 5. 内部声明无标识的匿名结构变量
		struct person{
		int id;
		struct{
			char first[20];		>>>>>   需要通过 name 访问
			char last[20];
		} name;
	};
```

---
## 6. 把结构内容保存在文件中

- 由于结构可以储存不同类型的信息，所以它是构建数据库的重要工具

- 数据库文件可以包含任意数量的此类数据对象。储存在一个结构中的整套信息被称为记录（record），单独的项被称为字段（field）。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 10 /* 最大书籍数量 */
char *s_gets(char *st, int n);
struct book /* 建立 book 模板 */
{
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};
int main(void)
{
	struct book library[MAXBKS]; /* 结构数组 */
	int count = 0;
	int index, filecount;
	FILE *pbooks;
	int size = sizeof(struct book);

	// 1. fopen 二进制读写 a 模式
	if ((pbooks = fopen("book.dat", "a+b")) == NULL)
	{
		fputs("Can't open book.dat file\n", stderr);
		exit(1);
	}
	// 2. 定位到文件开始
	rewind(pbooks);
	// 3. 预先 fread 读取 book.dat 中的二进制数据 (library: 并输出)
	while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
	{
		// 读取 book 并赋值给 library 数组中的结构体
		if (count == 0)
			puts("Current contents of book.dat:");	// 打印当前 book 中的数据
		printf("%s by %s: $%.2f\n", library[count].title,
			   library[count].author, library[count].value);
		count++;
	}
	filecount = count;
	if (count == MAXBKS)	// 验证当前 book 容量是否满
	{
		fputs("The book.dat file is full.", stderr);
		exit(2);
	}
	// 4. 输入数据并保存在 book.dat 中
	puts("Please add new book titles.");
	puts("Press [enter] at the start of a line to stop.");
	while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
	{
		puts("Now enter the author.");
		s_gets(library[count].author, MAXAUTL);
		puts("Now enter the value.");
		scanf("%f", &library[count++].value);
		while (getchar() != '\n')
			continue; /* 清理输入行 */
		if (count < MAXBKS)
			puts("Enter the next title.");
	}
	// 5. 输入结束输出 book.dat 内容
	if (count > 0)
	{
		puts("Here is the list of your books:");
		for (index = 0; index < count; index++)
			printf("%s by %s: $%.2f\n", library[index].title,
				   library[index].author, library[index].value);
		fwrite(&library[filecount], size, count - filecount,
			   pbooks);
	}
	else
		puts("No books? Too bad.\n");
	puts("Bye.\n");
	fclose(pbooks);
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
				continue; 		 // 清理输入行
	}
	return ret_val;
}
```

---
## 7. 链式结构

- 一些特定的形式如队列、二叉树、堆、哈希表和图表等都由链式结构 (linked structure) 组成

- 每个结构都包含一两个数据项可一两个指向其他同类型结构的指针, 这些指针将一个结构与另一个结构链接起来

> 二叉树结构

```
# 第一级 ----------------------->> {Struct * pL, pR} <<-------------------
						 ____________________|   |__________
						|									|
# 第二级 --------->> {struct * pL, pR}				     {struct * pL, pR} ....
						 ______|   |____________
						|						|
# 第三级 --------->> {struct * pL, pR}		 {struct * pL, pR} ....
							   |   |
							{.........}		
```

- 考虑一个有 10 级节点的树的情况。它有 2<sup>10</sup>−1（或 1023）个节点，可以储存 1023 个单词。

- 如果这些单词以某种规则排列，那么可以从最顶层开始，逐级向下移动查找单词，最多只需移动 9 次便可找到任意单词

- 若是在一个数组中, 则最多需要查找 1023 个元素

---
## 8. 联合 union
 
- 联合（union）是一种数据类型，它能在同一个内存空间中储存不同的数据类型（不是同时储存）

> 典型用法

- 设计一种表以储存既无规律、事先也不知道顺序的混合类型。使用联合类型的数组，其中的联合都大小相等，每个联合可以储存各种数据类型。

> 联合的声明与模板声明和结构相同

```c
	union container{
		int digit;
		double bigfl;
		char letter;
	};
```

- 该 container 联合只能储存它包含的数据内容

```c
	union container fit;		// container 类型的联合
	union container arr[5]; 	// container 联合数组
	union container * pC;		// container 联合指针
```

- 声明的联合变量 fit, 编译器分配足够的空间以便它能储存联合声明中占用最大字节的类型 double, 该变量占有 8 个字节

- arr 占有 8 * 5 = 40 个字节

> 联合的初始化

- 联合的初始化, 联合只能储存一个值 (与结构不同的地方)

```c
	// 初始化联合的第一个元素
	union container digit = {99};
	// 用另一个联合初始化
	union container digit2 = digit;
	// 指定初始化器
	union container val = {.digit = 100};
```

- 多次初始化联合的不同成员, 仅最后一次的数值有效, 访问其他成员时将丢失数据, 联合只能储存它包含类型的其中一个值, 它的大小以最大的类型为准

---
### 8.1 联合应用

> 利用联合指针访问联合的元素

```c
	union container pC = &digit;
	pC -> digit = 99;
	(*pC).digit = 100;
```

> 在结构中储存与其成员有从属关系的信息

- 假设用一个结构表示一辆汽车。如果汽车属于驾驶者，就要用一个结构成员来描述这个所有者。如果汽车被租赁，那么需要一个成员来描述其租赁公司

```c
	struct owner {
		char socsecurity[12];
	};
	struct leasecompany {
		char name[40];
		char headquarters[40];
	};
	union date {
		struct owner owncar;
		struct leasecompany leasecar;
	};

	struct car_date{
		char make[15];
		int status; /* 私有为0，租赁为1 */
		union data ownerinfo;
	};
	//  status 为 0, 程序将使用 .ownerinfo.owncar.socsecurity
	//  status 为 1, 程序将使用 .ownerinfo.leasecar.name
```

---
### 8.2 匿名联合 (C11)

```c
	union F{
		union{
			int a;
			int b[2];
		} F1;
		union{
			double a;
			double b[2];
		}F2;
	};
	printf("%zd", sizeof (union F)); // 16
```

- 匿名联合的声明与用法与结构相似, 可以声明在联合或结构中

---
## 9. 枚举 enum

- 可以用枚举类型（enumerated type）声明符号名称来表示整型常量

```c
	enum spectrum{
		red, orange, yellow, green
	};
	enum spectrum color;

	if(color == yellow){
		color = red;
	}
	
	for(color = red;color <= green;color++){
		printf("%d",color);
	}
```

- 枚举符（enumerator）是 int 类型, 但枚举变量可以是任意整数类型

- C 的枚举特性与 C++ 有些不同, C 允许使用递增递减, C++ 标准中不允许

---
### 9.1 枚举常量

- 枚举声明时的成员为枚举符, 其标识符是一个有名称的常量, 声明数组大小时可以使用直接使用枚举常量 (red, yellow ...)

- switch 语句中可以把枚举常量作为标签

---
### 9.2 枚举特性

> 默认值

- 默认从 0 开始, 后面的成员依次递增

- 可以指定整数值, 后面的成员不指定时继承前面的值递增

- 枚举类型的目的是为了提高程序的可读性和可维护性

```c
	enum levels{
		low = 100,
		medium = 500,
		high = 2000,
		high_s,	// 2001
	};
```

---
## 10. 共享名称空间 (关于结构, 联合, 枚举标记)

- C 语言使用名称空间（namespace）标识程序中的各部分，即通过名称来识别

- 作用域是名称空间概念的一部分：两个不同作用域的同名变量不冲突；两个相同作用域的同名变量冲突

- 在特定作用域中的结构标记、联合标记和枚举标记都共享相同的名称空间，该名称空间与普通变量使用的空间不同

- 意味着在相同作用域中, 变量与标记的名称可以相同, 但变量之间, 标记之间不一颗重名

---
## 11. typedef 关键字

- typedef 工具是一个高级数据特性，利用 typedef 可以为某一类型自定义名称

- 与 define 不同的是, typedef 创建的符号只受限于类型, 不能作用于值

- typedef 由编译器解释, 非预处理器

- typedef 并没有创建任何新类型，它只是为某个已存在的类型增加了一个方便使用的标签

---
### 11.1 typedef 工作原理

- 定义的类型只作用于它所在的作用域

```c
	typedef unsigned char BYTE;
	BYTE x,y[10],*z;
```

- 为现有类型创建一个名称, 使用 typedef 还能提高程序的可移植性

- time_t 在一个系统中是 unsigned long，在另一个系统中可以是 unsigned long long。只要包含 time.h 头文件，程序就能访问合适的定义，也可以在代码中声明 time_t 类型的变量

> typedef 的一些特性与 #define 的功能重合

```c
	#define BYTE unsigned char
	// 功能相似
	typedef unsigned char BYTE;
```

- typedef 定义的标识是类型

- #define 是预处理 BYTE 替换 unsigned char

```c
	typedef char * STRING;
	STRING name, sign;
	// 相当于：
	char * name, * sign;
	//但是，如果这样假设：
	#define STRING char *
	//然后，下面的声明：
	STRING name, sign;
	//将被翻译成：
	char * name, sign;
```

> 替换结构标识

```c
	struct book{
		char* name[10];
		int cost;
	};
	typedef BOOK struct book;
	BOOK* pbook;
	BOOK mbook={"YCHAO",99};
```

---
## 12. 一些复杂的声明

> 对于运算符 ( ), [ ], *

```c
// 声明一个内含 int 数组的数组
int board[8][8]; 	

// 声明一个指向指针的指针，被指向的指针指向 int
int ** ptr; 		

// 声明一个内含 10 个元素的数组，每个元素都是一个指向 int 的指针
int * risks[10];	

// 声明一个指向数组的指针，该数组内含 10 个 int 类型的值
int (* rusks)[10]; 	

// 声明一个 3×4 的二维数组，每个元素都是指向 int 的指针
int * oof[3][4]; 	

// 声明一个指向 3×4 二维数组的指针，该数组中内含 int 类型值
int (* uuf)[3][4]; 

// 声明一个内含 3 个指针元素的数组，其中每个指针都指向一个内含 4 个 int 类型元素的数组
int (* uof[3])[4]; 
```

- 数组名后面的 [ ] 和函数名后面的 ( ) 具有相同的优先级

- \[ ] 和 ( ) 的优先级相同，由于都是从左往右结合

- \[ ] 和 ( ) 都是从左往右结合

```c
	// 返回字符指针的函数
	char * fump(int);

	// 指向函数的指针，该函数的返回类型为 char
	char (* frump)(int); 

	// 内含 3 个指针的数组，每个指针都指向返回类型为 char 的函数
	char (* flump[3])(int); 
```

---
## 13. 函数与指针

- 通常，函数指针常用作另一个函数的参数，告诉该函数要使用哪一个函数

- 声明一个数据指针时，必须声明指针所指向的数据类型。声明一个函数指针时，必须声明指针指向的函数类型。为了指明函数类型，要指明函数签名，即函数的返回类型和形参类型。

```c
	void TpUpper(char *);  // 函数原型

	void (*pf)(char*);	   // pf 指向一个函数
```

> 声明了函数指针后，可以把类型匹配的函数地址赋给它

```c
	void ToUpper(char *);
	void ToLower(char *);
	int round(double);
	
	void (*pFun)(char *);
	pFun = ToUpper;
	pFun = ToLower;
	pFun = round; 		// ERR, 类型不一致
	pFun = ToUpper();	// ERR, ToUpper() 不是地址, 返回 void

	pFun("UPPER"); // = ToLower("UPPER");
	(*pFUN)("UPPER");
```

> 函数指针作为参数

```c
	void show(void (* fp)(char *), char * str);
```

---