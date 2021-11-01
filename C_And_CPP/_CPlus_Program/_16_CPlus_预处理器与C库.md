# C Plus 预处理器与 C 库

- 预处理指令：#define、#include、#ifdef、#else、#endif、#ifndef 、#if 、#elif 、#line 、#error 、#pragma 
- 关键字：_Generic、_Noreturn、_Static_assert
- 函数/ 宏： sqrt() 、atan() 、atan2() 、exit() 、atexit() 、assert() 、memcpy() 、memmove() 、va_start() 、va_arg() 、
va_copy()、va_end() 
- C 预处理器的其他功能
- 通用选择表达式
- 内联函数
- C 库概述和一些特殊用途的方便函数

---
- [C Plus 预处理器与 C 库](#c-plus-预处理器与-c-库)
	- [1. 编译源文件的第一步(翻译)](#1-编译源文件的第一步翻译)
	- [2. #define 明示常量](#2-define-明示常量)
		- [2.1 记号](#21-记号)
		- [2.2 重定义常量](#22-重定义常量)
	- [3. 在 define 中使用参数](#3-在-define-中使用参数)
		- [3.1 宏参数创建字符串 # 运算符](#31-宏参数创建字符串--运算符)
		- [3.2 预处理器黏合剂: ## 运算符](#32-预处理器黏合剂--运算符)
		- [3.3 变参宏: ... 和 \_\_VA\_ARGS\_\_](#33-变参宏--和-__va_args__)
	- [4. 宏和函数的选择](#4-宏和函数的选择)
	- [5. #include 文件包含](#5-include-文件包含)
		- [5.1 头文件](#51-头文件)
	- [6. 其他指令](#6-其他指令)
		- [6.1 #undef 取消宏定义](#61-undef-取消宏定义)
		- [6.2 条件编译 ifdef 与 ifndef](#62-条件编译-ifdef-与-ifndef)
		- [6.3 条件编译 if 与 elif](#63-条件编译-if-与-elif)
		- [6.4 预定义宏](#64-预定义宏)
		- [6.5 #line 与 #error](#65-line-与-error)
		- [6.6 #pragma 编译支持 C9X](#66-pragma-编译支持-c9x)
		- [6.7 泛型选择 (C11)](#67-泛型选择-c11)
	- [7. 内联函数 (C99)](#7-内联函数-c99)
	- [8. _Noreturn 函数 (C11)](#8-_noreturn-函数-c11)
	- [9. C 库](#9-c-库)
		- [9.1 数学库 (math.h)](#91-数学库-mathh)
		- [9.2 tgmath.h 泛型类型宏数学库](#92-tgmathh-泛型类型宏数学库)
	- [10. 通用工具库 (stdlib.h)](#10-通用工具库-stdlibh)
		- [10.1 exit 与 atexit 函数](#101-exit-与-atexit-函数)
		- [10.2 qsort 快速排序函数](#102-qsort-快速排序函数)
	- [11. 断言库](#11-断言库)
		- [11.1 assert](#111-assert)
		- [11.2 _Static_assert (C11) 静态断言](#112-_static_assert-c11-静态断言)
	- [12. memcpy 与 memmove (string.h)](#12-memcpy-与-memmove-stringh)
	- [13. 可变参数 stdarg.h](#13-可变参数-stdargh)

---
## 1. 编译源文件的第一步(翻译)

> 在预处理之前, 编译器会对该程序进行一下翻译处理:
  
- 首先，编译器把源代码中出现的字符映射到源字符集 (处理多字节字符与三字符序列, 字符扩展)
  
- 第二，编译器定位每个反斜杠后面跟着换行符的实例，并删除它们(换行符指通过按下 Enter 键在源代码文件中换行所生成的字符，而不是指符号表征 \n)

```c
	//把下面两个物理行（physical line）：
	printf("That's wond\
	erful!\n");
	//转换成一个逻辑行（logical line）：
	printf("That's wonderful\n!");
	//由于预处理表达式的长度必须是一个逻辑行, 一个逻辑行可以是多个物理行
```

- 第三，编译器把文本划分成预处理记号序列、空白序列和注释序列（记号是由空格、制表符或换行符分隔的项）

```c
	//编译器将用一个空格字符替换每一条注释
	int/* 这看起来并不像一个空格*/fox;
	//将变成：
	int fox;
	//而且，实现可以用一个空格替换所有的空白字符序列（不包括换行符）
```

- 最后，程序已经准备好进入预处理阶段，预处理器查找一行中以#号开始的预处理指令。

---
## 2. #define 明示常量

- #define 指令来定义明示常量（manifest constant）（也叫做符号常量）

```c
	#define SIZE 10;
	// #define  指令
	// SIZE     宏, 选定的缩写
	// 10 		替换列表或替换体
```

- 预处理器在程序中找到宏表示的实例后，就会用替换体代替该宏。从宏变成最终替换文本的过程称为宏展开（macro expansion）

```c
#include <stdio.h>
#define TWO 2
#define PX printf("X is %d.\n",x)

int main(void)
{
	int x = TWO;
	PX; // 预处理时用 "printf("X is %d.\n",x)" 替换 PX
}
```

> 宏展开过程

- 由于编译器在编译期对所有的常量表达式（只包含常量的表达式）求值，所以预处理器不会进行实际的乘法运算，这一过程在编译时进行。
  
- 预处理器不做计算，不对表达式求值，它只进行替换。

---
### 2.1 记号

- 从技术角度来看，可以把宏的替换体看作是记号（token）型字符串，而不是字符型字符串

- 由于编译器理解 C 语言的规则，所以不要求代码中用空格来分隔记号

- C 编译器可以把 2\*2 直接视为 3 个记号，因为它可以识别 2 是常量，\* 是运算符。

---
### 2.2 重定义常量

- 定义相同, 替换体发生改变

---
## 3. 在 define 中使用参数

- 在 #define 中使用参数可以创建外形和作用与函数类似的类函数宏

```c
	#define FUN(X,Y) (((X)+(Y))/2)
	// X, Y   宏参数
	//FUN()	  宏函数

	#define SQUARE(X) X*X
	//在程序中可以这样用：
	z = SQUARE(2);   // 2*2 = 4;
	Z = SQUARE(z+1); // z+1*z+1 = 4+4+1 = 9;
	// 宏函数与标准函数的区别在于, 宏仅仅是在预处理阶段将替换体替换掉宏标识, 并不参与计算
```

- 可以使用足够多的圆括号来确保宏函数正确的结合顺序

---
### 3.1 宏参数创建字符串 # 运算符

- C 允许在字符串中包含宏参数。在类函数宏的替换体中，# 号作为一个预处理运算符，可以把记号转换成字符串

- 如果 x 是一个宏形参，那么 #x 就是转换为字符串 "x" 的形参名。这个过程称为字符串化（stringizing）

- 格式要求: 在字符串外使用【 "str1" #x "str2" 】，在字符串内使用没有替换功能

```c
	#define PSQR(x) printf("The square of " #x " is %d.\n",\
	((x)*(x))) int main(void)

	int y = 5;
	PSQR(y);
	PSQR(2 + 4);

	// The square of y is 25.
	// The square of 2 + 4 is 36.
```

---
### 3.2 预处理器黏合剂: ## 运算符

- \#\# 运算符可用于类函数宏的替换部分。而且，\#\# 还可用于对象宏的替换部分。\#\# 运算符把两个记号组合成一个记号。

```c
#include <stdio.h>
#define XNAME(n) x ## n   // 表示将 x 与 n 组合成一个记号
#define PRINT_XN(n) printf("x" #n " = %d\n", x ## n);

int main(void)
{
	int XNAME(1) = 14; 	// 变成 int x1 = 14;
	int XNAME(2) = 20; 	// 变成 int x2 = 20;
	int x3 = 30;	
	
	PRINT_XN(1); // 变成 printf("x1 = %d\n", x1);
	PRINT_XN(2); // 变成 printf("x2 = %d\n", x2);
	PRINT_XN(3); // 变成 printf("x3 = %d\n", x3);
	return 0;
}
```

- PRINT_XN() 宏用 # 运算符组合字符串

- \#\# 运算符把记号组合为一个新的标识符。

---
### 3.3 变参宏: ... 和 \_\_VA\_ARGS\_\_

- 预定义宏实现宏参数的可变, 通过把宏参数列表中最后的参数写成省略号（即...）来实现这一功能

- 预定义宏 【 \_\_VA\_ARGS\_\_ 】 可用在替换部分中，表明省略号代表什么

```c
	#define PR(...) printf(__VA_ARGS__)

	PR("Holiday");  // 第 1 次调用 __VA_ARGS__ 展开一个参数
	PR("weight = %d, shipping = $%.2f\n", wt, sp);  // 展开三个参数
```

> 变参宏与 # 运算符

```c
include <stdio.h>
include <math.h>
#define PR(X, ...) printf("Message " #X ": " __VA_ARGS__)
int main(void)
{
	double x = 48;
	double y;
	y = sqrt(x);
	PR(1, "x = %g\n", x);
	PR(2, "x = %.2f, y = %.4f\n", x, y);
	return 0;
}
// 预处理阶段 --- 替换 
// printf(("Message ""1"": ""x = %g\n", x);
// printf("Message ""2"": ""x = %.2f, y = %.4f\n", x, y);
```

---
## 4. 宏和函数的选择

- 一些编程任务可以是用带参数的宏完成, 也可以是函数完成

- 宏与函数的主要区别, 宏的实现比普通函数复杂一些, 宏产生内联代码 (在程序中生成语句), 调用 N 次宏就替换 N 次代码, 函数调用 N 次, 但函数的副本只有一份, 节省了空间

- 函数的调用需要跳转到函数内, 随后返回主调函数, 这要比内联代码花费更多的时间

- 宏的声明中, 无需担心变量类型, 宏处理的是字符串, 实际替换过程中不会涉及到计算

- 一些简单的函数, 可以使用宏会更有效率和简单化

---
## 5. #include 文件包含

- 当预处理器发现 #include 指令时，会查看后面的文件名并把文件的内容包含到当前文件中，即替换源文件中的 #include 指令。
  
- 这相当于把被包含文件的全部内容输入到源文件 #include 指令所在的位置。

> #include 有两种形式

```c
	#include <stdio.h>
	#include "myClass.h"
```

- 在 UNIX 系统中, \< \> 表示预处理器在标准系统目录下查找该文件, " " 表示预处理器首先在当前目录下查找, 或在文件名中指定的其他目录, 未找到则再查找标准系统目录



```c
	// 查找系统目录
	#include <stdio.h> 			
	// 查找当前工作目录
	#include "hot.h" 	
	// 查找/usr/biff目录	
	#include "/usr/biff/p.h" 	
```

---
### 5.1 头文件

- C 语言中 *.h 表示头文件, 这些文件包含需要放在程序顶部的信息, 其中包含一些预处理器指令

> names_st.h 头文件示意

```c
#include <string.h>
#define SLEN 32
// 结构声明
struct names_st
{
	char first[SLEN];
	char last[SLEN];
};
// 类型定义
typedef struct names_st names;
// 函数原型
void get_names(names *);
void show_names(const names *);
char * s_gets(char * st, int n);
```

- 该头文件包含了一些头文件中常见的内容：#define 指令、结构声明、typedef 和函数原型。这些内容是编译器在创建可执行代码时所需的信息，而不是可执行代码

- 可执行代码通常在源代码文件中，而不是在头文件中

> 头文件中包含的基本信息

```c
#define EOF 0    			// 明示常量

#define Function(x) x * x	// 宏函数

void method(void);	// 函数原型声明

struct book{		// 结构模板声明
	int cost;
}

typedef size_t  long long int;	// 类型定义

int status = 0;   // 外部变量
```

---
## 6. 其他指令

### 6.1 #undef 取消宏定义

- \#undef 用于取消已定义的 \#define 指令, 无论之前该宏是否被定义, 取消宏定义仍然有效

```c
	#define LIMIT 10
	//...
	#undef LIMIT
	// 取消 LIMIT 的定义
```

- #define 宏的作用域从它在文件中的声明处开始，直到用 #undef 指令取消宏为止，或延伸至文件尾（以二者中先满足的条件作为宏作用域的结束）

- 如果宏通过头文件引入，那么 #define 在文件中的位置取决于 #include 指令的位置。

- \_\_DATE\_\_ 和 \_\_FILE\_\_ , 这些宏是已定义的, 且不能取消定义

---
### 6.2 条件编译 ifdef 与 ifndef

- 可以使用其他指令创建条件编译（conditinal compilation）。可以使用这些指令告诉编译器根据编译时的条件执行或忽略信息（或代码）块

- 条件编译 ifdef 检查宏, 若当前宏已定义, 则编译当前分支的指令

> #ifdef, else, endif

```c
#ifdef UNITY
	#include "unity.h"
	#define LEVEL 1
#else
	#include "unreal.h"
	#define LEVEL 2
#endif
```

> 条件编译案例

```c
#include <stdio.h>
#define JUST_CHECKING
#define LIMIT 4
int main(void)
{
	int i;
	int total = 0;
	for (i = 1; i <= LIMIT; i++)
	{
		total += 2 * i*i + 1;
#ifdef JUST_CHECKING
		printf("i=%d, running total = %d\n", i, total);
#endif
	}
	printf("Grand total = %d\n", total);
	return 0;
}
```

> #ifndef 

- 条件编译 ifndef 检查宏, 当前宏未定义时, 将编译当前分支下的指令

```c
#ifndef SIZE
	#define SIZE 100
#endif
```

- 当包含多个头文件时, 可以使用 ifndef 指令防止相同的宏被重复定义

> ifndef 防止多次包含一个文件

- #ifndef 指令通常用于防止多次包含一个文件, 当引用多个头文件时, 可能无法检查到哪个头文件被多次引用, 可以使用类似这种设置, 防止头文件中的内容重复定义

```c
/* things.h */
#ifndef THINGS_H_
	#define THINGS_H_

	/*
		该头文件中的其他成员
	*/
#endif

//--------------
/* exam.c */
#include "things.h"

#include "things.h" // 重复引用, 预定义 ifndef 防止头文件成员重复声明
```

---
### 6.3 条件编译 if 与 elif

- \#if 跟整型表达式, 表达式结果为非零, 表达式输出真, 可以再指令中使用 C 的关系运算符与逻辑运算符

```c
#if LEVEL == 1
	#include "unity.h"
#elif LEVEL == 2
	#include "unreal.h"
#else
	#include "cryengine.h"
#endif
```

---
### 6.4 预定义宏

> C 标准的预定义宏

```c
	__DATE__	// 预处理的日期(Mmm dd yyyy 形式的字符串字面量, Oct 25 2021)
	__FILE__	// 表示当前源代码文件名的字符串字面量
	__LINE__ 	// 表示当前源代码文件中行号的整型常量
	__STDC__	// 设置为 1 时, 表明实现遵循 C 标准
	__STDC_HOSTED__		// 本机环境设置为 1; 否则为 0
	__STDC_VERSION__	// 支持 C99 标准, 设置为 199901L; 支持 C11 标准, 设置为 201112L
	__TIME__	// 翻译代码的时间, 格式为 "hh:mm:ss"
```

> C99 预定义标识符

- C99 提供 \_\_func\_\_ 的预定义标识符, 表示展开为一个代表函数名的字符串 (该函数包含该标识符), func 必须具有函数作用域, 它是 C 的预定义标识符, 而不是预定义宏

> 预定义宏和预定义标识符

```c
#include <stdio.h>
void why_me();

int main()
{
	printf("The file is %s.\n", __FILE__);
	printf("The date is %s.\n", __DATE__);
	printf("The time is %s.\n", __TIME__);
	printf("The version is %ld.\n", __STDC_VERSION__);
	printf("This is line %d.\n", __LINE__);
	printf("This function is %s\n", __func__);
	why_me();
	return 0;
}
void why_me()
{
	printf("This function is %s\n", __func__);
	printf("This is line %d.\n", __LINE__);
}
/*
	The file is d:\_JC_Workbook\_Languages_Programme\_CPlus_Program\test.c.
	The date is Oct 25 2021.
	The time is 10:42:41.
	The version is 201112.
	This is line 10.
	This function is main
	This function is why_me
	This is line 18.
*/
```

---
### 6.5 #line 与 #error

> #line 重置行数

- #line 指令重置 \_\_LINE\_\_ 和 \_\_FILE\_\_ 宏报告的行号与文件名

```c
	#line 1000   // 将当前行重置为 1000 行
	#line 10 "cool.c"	// 把行号重置为 10, 把文件名重置
```

> #error 错误指令

- \#error 指令让预处理器发出一条错误消息，该消息包含指令中的文本, 编译过程会被中断

```c
#if _ _STDC_VERSION_ _ != 201112L
	#error Not C11
#endif
//-------------------
$ gcc newish.c
newish.c:14:2: error: #error Not C11
$ gcc -std=c11 newish.c
// 编译器支持 C11 标准时将成功编译
```

---
### 6.6 #pragma 编译支持 C9X

- 使用 #pragma 表示编译器支持 C9X

```c
	#pragma c9x on
```

- 一般而言编译器都有自己的编译指示集, 用于控制分配给自动变量的内存量, 或者设置错误检查的严格程度, 或者启用非标准语言特性等

- C99 提供 _Pragma() 预处理器运算符, 该运算符把字符串转换成普通的编译指示

```c
	_Pragma("nonstandardtreatmenttypeB on");
// 等价于
	#pragma nonstandardtreatmenttypeB on
```

- _Pragma() 运算符不使用 # 符号, 可以用于宏展开的一部分

```c
	#define PRAGMA(X) _Pragma(#X);  // #X 字符串替换
	#define LIMRG(X) PRAGMA(STDC CX_LIMITED_RANGE X)

	LIMRG(ON)

// 使用 PRAGMA(STDC CX_LIMITED_RANGE X)
// 而不是 _Pragma(STDC CX_LIMITED_RANGE #X)  <依赖字符串的串联功能>

// 预处理 PRAGMA 结束后, 转入到 _Pragma() 传入 X

// _Pragma 运算符完成“解字符串”（destringizing）的工作，即把字符串中的转义序列转换成它所代表的字符

	_Pragma("use_bool \"true \"false")
	//变成了：
	#pragma use_bool "true "false
```

---
### 6.7 泛型选择 (C11)

- 在程序设计中，泛型编程（generic programming）指那些没有特定类型，但是一旦指定一种类型，就可以转换成指定类型的代码

- C++ 在模板中可以创建泛型算法，然后编译器根据指定的类型自动使用实例化代码; C 没有这种功能

- C11 新增了泛型选择表达式 (generic selection expression), 根据表达式的类型选择一个值, 泛型表达式常用于 define 宏定义的一部分

```c
	// 泛型表达式
 	_Generic(x, int: 0, float: 1, double: 2, default: 3)	
```

- x 表示一个表达式, 该表达式匹配哪个标签, 就返回哪个标签后面的值, 与 switch 语句相似

> 泛型表达式与 define 组合

```c
	#define MYTYPE(X) _Generic((X),\
						int: "int",\
						float : "float",\
						double: "double",\
						default: "other")
```

> 演示

```c
#include <stdio.h>
#define MYTYPE(X) _Generic((X),\
		int: "int",\
		float : "float",\
		double: "double",\
		default: "other"\
		)
int main(void)
{
	int d = 5;
	printf("%s\n", MYTYPE(d)); // d 是int类型
	printf("%s\n", MYTYPE(2.0*d)); // 2.0 * d 是double类型
	printf("%s\n", MYTYPE(3L)); // 3L 是long类型
	printf("%s\n", MYTYPE(&d)); // &d 的类型是 int *
	return 0;
}
/*
	int
	double
	other
	other
*/
```

- 可以使用更多类型标签来扩展宏的能力

---
## 7. 内联函数 (C99)

- 函数调用都有一定的开销, 函数调用过程包括建立调用、传递参数、跳转到函数代码并返回

- 使用宏使代码内联， 可以避免这样的开销

- C99 提供了内联函数（inline function）的概念，把函数变成内联函数建议尽可能快地调用该函数，其具体效果由实现定义

- 把函数变成内联函数，编译器可能会用内联代码替换函数调用，并（或）执行一些其他的优化，但是也可能不起作用

- 内部链接（static）的函数可以成为内联函数，使用函数说明符 inline 和存储类别说明符 static，内联函数也相当于函数原型

```c
inline static void eatline(){
	while(getchar() != '\n')
		continue;
}

int main(void){
	//...
	eatline();
	//...
}
```

- 一般无法获取内联函数的地址，内联函数的设计应该比较短小，较长的函数变成内联并不会节约太多的时间，执行函数体的时间总会比调用函数的时间长得多

- 内联函数定义与调用必须在同一个文件，如果程序有多个文件都要使用某个内联函数，这些文件中都必须包含该内联函数的定义

- 可以将内联函数定义放在头文件中，使用该函数时包含该头文件即可

```c
#ifndef EATLINE_H_
	#define EATLINE_H_
	inline static void eatline(){
		while(getchar() != '\n')
			continue;
	}
#endif
```

- 与 C++ 不同的是，C 允许混合使用内部函数定义和外部函数定义（具有外部链接）

```c
inline static void fun();   // 静态内联函数定义，内部链接
void fun();   // 外部链接函数定义
inline void fun()   // 既充当内部内联函数, 又具有外部链接
// 该 inline 定义被视为可替换的外部定义
```

## 8. _Noreturn 函数 (C11)

- C11 新增的函数说明符 _Noreturn, 表明调用完成后函数不返回主调函数

- exit() 函数是 _Noreturn 函数的一个示例

- _Noreturn 的目的是告诉用户和编译器，这个特殊的函数不会把控制返回主调程序。告诉用户以免滥用该函数，通知编译器可优化一些代码。

```c
#include<stdlib.h>
#include <stdnoreturn.h>

_Noreturn void Fun(void){
	//...
	exit(3);
}

noreturn void FUN(int x){
	//...
	exit(x);
}
```

---
## 9. C 库

* 访问 C 库取决于实现, 根据系统的不同, 可以在多个不同的位置找到库函数
  - 自动访问: 使用函数前必须先声明函数的类型, 通过包含合适的头文件即可
  - 文件包含: 函数被定义成宏, 可以通过 include 指令包含该定义的文件
  - 库包含: 一些编译的某些阶段, 可能需要指定库选项, 必须通过编译时选项显式指定这些库

---
### 9.1 数学库 (math.h)

```c
double acos(double x);			  	// 余弦值为 x 的角度(0 ~ PI 弧度)  
double asin(double x);			  	// 正弦值为 x 的角度(-PI/2 ~ PI/2, 弧度)
double atan(double x);			  	// 正切值为 x 的角度(-PI/2 ~ PI/2, 弧度)
double atan2(double x, double y); 	// 正弦值为 y/x 的角度 (-PI ~ PI, 弧度)
double cos(double x);			  	// x 的余弦值
double sin(double x);			  	// x 的正弦值
double tan(double x);			  	// x 的正切值
double exp(double x);			  	// x 的指数函数的值(e^x)
double log(double x);			  	// x 的自然对数值
double log10(double x);			  	// x 的以 10 为底的对数值
double pow(double x, double y);	  	// x 的 y 次幂
double sqrt(double x);			  	// x 的平方值
double cbrt(double x);			  	// x 的立方值
double ceil(double x);			  	// 不小于 x 的最小整数值
double fabs(double x);			  	// x 的绝对值
double floor(double x);			  	// 不大于 x 的最大整数值
```

> 把直角坐标转换为极坐标

```c
#include <stdio.h>
#include <math.h>
#define RAD_TO_DEG (180 / (4 * atan(1))) // 弧度转角度
typedef struct polar_v					 // 极坐标结构
{
	double magnitude;
	double angle;
} Polar_V;
typedef struct rect_v // 直角系结构
{
	double x;
	double y;
} Rect_V;

Polar_V rect_to_polar(Rect_V); // 转换函数原型

int main(void)
{
	Rect_V input;
	Polar_V result;
	puts("Enter x and y coordinates; enter q to quit:");
	while (scanf("%lf %lf", &input.x, &input.y) == 2)
	{
		result = rect_to_polar(input);
		printf("magnitude = %0.2f, angle = %0.2f\n",
			   result.magnitude, result.angle);
	}
	puts("Bye.");
	return 0;
}

// 转换函数 rect -> polar
Polar_V rect_to_polar(Rect_V rv)
{
	Polar_V pv;
	pv.magnitude = sqrt(rv.x * rv.x + rv.y * rv.y);
	if (pv.magnitude == 0)
		pv.angle = 0.0;
	else
		pv.angle = RAD_TO_DEG * atan2(rv.y, rv.x);
	return pv;
}
```

- 若编译器出现【 Undefined: _sqrt 】或【'sqrt': unresolved external】，表明编译器链接器没有找到数学库

```powershell
  $ gcc rect_pol.c -lm
```

> 数学库类型变体

- 基本的浮点型数学函数接受 double 类型的参数，并返回 double 类型的值

- 传入其他类型可能出现精度丢失的问题，C 标准专门为 float 类型和 long double 类型提供了标准函数，即在原函数名前加上 f 或 l 前缀

- 可以利用 C11 泛型选择表达式定义一个泛型宏

```c
// 泛型平方根
#define RAD_TO_DEG (180/(4 * atanl(1)))

#define SQRT(X) _Generic((X), long double: sqrtl, default: sqrt, float: sqrtf)(X)
// 泛型正弦函数
#define SIN(X) _Generic((X),long double: sinl((X)/RAD_TO_DEG),\
							default: sin((X)/RAD_TO_DEG),\
							float: sinf((X)/RAD_TO_DEG))

```

- _Generic 表达式的值是一个特定的函数调用， 如 sinf((X)/RAD_TO_DEG)，用传入 SIN() 的参数替换 X。

---
### 9.2 tgmath.h 泛型类型宏数学库

- tgmath.h 文件创建一个泛型类型宏，与原来 double 版本的函数名同名, 定义 sqrt()宏展开为 sqrtf()、sqrt()或 sqrtl() 函数。

- 若编译器支持复数运算, 也会支持 complex.h 头文件, 其中声明了与复数相关的函数

- 声明有 csqrtf()、csqrt() 和 csqrtl()，这些函数分别返回 float complex、double complex和
long double complex 类型的复数平方根, 同时 tgmath.h 也能展开为相应的复数平方根函数

> 调用 math 函数而非宏函数时

- 若调用 sqrt 函数而非 sqrt 宏, 可以将函数标识符括起来

```c
	#include <tgmath.h>
	float x = 44.0f;
	double y = sqrt(x);	// 调用宏, 泛型选择为 sqrtf(x)
	y = (sqrt)(x); 		// 调用函数 sqrt()
```

---
## 10. 通用工具库 (stdlib.h)

- 通用工具库包含各种函数，包括随机数生成器、查找和排序函数、转换函数和内存管理函数

---
### 10.1 exit 与 atexit 函数

- exit 调用时不返回主调函数, 在 main 返回系统时会自动(隐式)调用 exit(int) 函数

- atexit(void*) 传递函数地址, 并注册函数列表中的函数, 在 exit(int) 调用时执行这些函数, 这个函数列表至少可以放 32 个函数, 执行顺序与注册顺序相反, 最后添加的函数最先执行

- atexit() 注册的函数应该是不带任何参数且返回 void, 该函数一般会执行一些清理任务, 更新监视程序的文件或重置环境变量

- 未主动调用 exit 时, 也会在 main 结束时隐式调用 exit

- 一般清理工作包括：刷新所有输出流、关闭所有打开的流和关闭由标准 I/O 函数 tmpfile() 创建的临时文件, 然后将控制权返回主机环境 (可能报告终止状态), UNIX 程序使用 0 (EXIT_SUCCESS) 表示成功终止, 非 0 (EXIT_FAILURE,1) 值表示终止失败

---
### 10.2 qsort 快速排序函数

- 快速排序算法在 C 实现中的名称是 qsort()。qsort() 函数排序数组的数据对象

```c
void qsort(void *base, size_t nmemb, size_t size, 
		int (*compar)(const void *, const void *));
/*>>> base    指向待排序数组的首元素, 可以引用任何类型的数组
	  nmemb   待排序项的数量, 
	  size    显式指明待排序数组中每个元素的大小
	  compar  指针指向的比较函数用于确定排序的顺序
  >>> 比较函数: 如果第 1 项的值大于第 2 项，比较函数则返回正数；
  			   如果两项相同，则返回 0；
			   如果第 1 项的值小于第 2 项，则返回负数	  
*/


> 排序浮点值数组

```c
#include <stdio.h>
#include <stdlib.h>
#define NUM 40
void fillarray(double ar[], int n);
void showarray(const double ar[], int n);
int mycomp(const void *p1, const void *p2); // 比较函数原型
int main(void)
{
	double vals[NUM];
	fillarray(vals, NUM);
	puts("Random list:");
	showarray(vals, NUM);
	qsort(vals, NUM, sizeof(double), mycomp); // qsort 排序
	puts("\nSorted list:");
	showarray(vals, NUM);
	return 0;
}
// 随机数填充数组
void fillarray(double ar[], int n)
{
	int index;
	for (index = 0; index < n; index++)
		ar[index] = (double)rand() / ((double)rand() + 0.1);
}
void showarray(const double ar[], int n)
{
	int index;
	for (index = 0; index < n; index++)
	{
		printf("%9.4f ", ar[index]);
		if (index % 6 == 5)
			putchar('\n');
	}
	if (index % 6 != 0)
		putchar('\n');
}
/* 按从小到大的顺序排序 */ // 可自定义排序规则, 对复合结构
int mycomp(const void *p1, const void *p2)
{
	/* 要使用指向 double 的指针来访问这两个值 */
	const double *a1 = (const double *)p1;
	const double *a2 = (const double *)p2;
	if (*a1 < *a2)
		return -1;
	else if (*a1 == *a2)
		return 0;
	else
		return 1;
}
```

> C 与 C++ void* 通用型指针

- C++ 要求在把 void* 指针赋给任何类型的指针时必须进行强制类型转换

- C 没有这样的要求

---
## 11. 断言库

- assert.h 头文件支持的断言库是一个用于辅助调试程序的小型库

- assert.h 由 assert() 宏组成，接受一个整型表达式作为参数。如果表达式求值为假（非零），assert() 宏就在标准错误流（stderr）中写入一条错误信息，并调用 abort() 函数终止程序（abort()函数的原型在stdlib.h头文件中）

- assert() 宏是为了标识出程序中某些条件为真的关键位置，如果其中的一个具体条件为假，就用 assert()语句终止程序

- assert() 的参数是一个条件表达式或逻辑表达式。如果 assert() 中止了程序，它首先会显示失败的测试、包含测试的文件名和行号。

---
### 11.1 assert 

- assert 能够自动标识文件和问题的行号

- 还有一种无需更改代码就能开启或关闭 assert() 的机制。如果认为已经排除了程序的 bug，在包含 assert.h 的位置前面：【 #define NDEBUG 】, 编译器就会禁用文件中的所有 assert() 语句。

```c
#include <stdio.h>
#include <math.h>
#include <assert.h>
int main()
{
	double x, y, z;
	puts("Enter a pair of numbers (0 0 to quit): ");
	while (scanf("%lf%lf", &x, &y) == 2 && (x != 0 || y != 0))
	{
		z = x * x - y * y; /* 应该用 + */
		assert(z >= 0);
		printf("answer is %f\n", sqrt(z));
		puts("Next pair of numbers: ");
	}
	puts("Done");
	return 0;
}
/*
	Enter a pair of numbers (0 0 to quit):
	1 2
	Assertion failed: z >= 0, file .\test.c, line 11
*/
```

---
### 11.2 _Static_assert (C11) 静态断言

- assert() 表达式是在运行时进行检查

- C11 新增了一个特性：_Static_assert 声明，可以在编译时检查 assert() 表达式

- assert() 可以导致正在运行的程序中止，而 _Static_assert() 可以导致
程序无法通过编译。

```c
	_Static_assert(exp, const char*);
	/*>>>>>>>
		exp   整型常量表达式
	*/
```

---
## 12. memcpy 与 memmove (string.h)

- 一般时不能将数组赋给另一个数组, 可以通过循环把数组中的每个元素赋给另一个数组相应的元素, 或使用 strcpy 与 strncpy 处理字符串

- memcpy 与 memmove 函数提供类似的方法处理任意类型的数组

```c
	void *memcpy(void * restrict s1, const void * restrict s2,size_t n);
	void *memmove(void *s1, const void *s2, size_t n);

	/*
		都是 s2 指向拷贝 n 字节到 s1 指向的位置, 并返回 s1 的值
		>>> memcpy 若两个参数的内存区域之间没有重叠, 拷贝可能会成功, 
				但假设重叠, 则可能出现数据被修改的风险
		>>> memmove 的拷贝过程会将所有字节拷贝到临时缓冲区, 然后再拷贝到目的地, 整个过程相对内存安全

		size n 要指明待拷贝的字节数
	*/
```

---
## 13. 可变参数 stdarg.h

> 使用步骤

1. 提供一个使用省略号的函数原型；
2. 在函数定义中创建一个 va_list 类型的变量；
3. 用宏把该变量初始化为一个参数列表；
4. 用宏访问参数列表；
5. 用宏完成清理工作。

```c
	// 有效	
	void f1(int n, ...);
	int f2(const char * s, int k, ...); 	
	// 无效
	char f3(char c1, ..., char c2);	// 省略号不在最后
	double f3(...); 				// 没有形参

	// 宏使用可变参数列表
	double sum(int lim,...)
	{
		// 设 lim 表明变参列表中参数的数量

		// 1. 声明一个储存参数的对象 
		va_list ap; 		
		// 2. 把 ap 初始化为参数列表, lim 为参数数目
		va_start(ap, lim);  

		// 3. 访问参数列表的内容 
		va_arg(ap, 类型名)
		/*
			double tic = va_arg(ap, double); // 检索第 1 个参数
			int toc = va_arg(ap, int); 		 // 检索第 2 个参数
		*//* 传入的参数类型必须与宏参数的类型相匹配 */
		
		// 4. 宏完成清理工作
		va_end(ap); 	// 清理工作
		/* 释放动态分配用于储存参数的内存 */
	}
```

- 调用 va_end(ap) 后，只有用 va_start 重新初始化 ap 后，才能使用变量 ap。

- va_arg() 并不提供退回之前参数的方法，所以有必要保存 va_list 类型变量的副本。

- 可以使用 (C99) va_copy(va_list1, va_list2),  把 list2 传递给第一个参数

> 示例

```c
#include <stdio.h>
#include <stdarg.h>
double sum(int, ...);
int main(void)
{
	double s, t;
	s = sum(3, 1.1, 2.5, 13.3);
	t = sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	printf("return value for "
		   "sum(3, 1.1, 2.5, 13.3): %g\n",
		   s);
	printf("return value for "
		   "sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): %g\n",
		   t);
	return 0;
}
double sum(int lim, ...)
{
	va_list ap; // 声明一个对象储存参数
	double tot = 0;
	int i;
	va_start(ap, lim); // 把ap初始化为参数列表
	for (i = 0; i < lim; i++)
		tot += va_arg(ap, double); // 访问参数列表中的每一项
	va_end(ap);					   // 清理工作
	return tot;
}
/*
	return value for sum(3, 1.1, 2.5, 13.3): 16.9
	return value for sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): 31.6
*/
```

---