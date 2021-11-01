# C Plus 函数

- 函数与函数递归
- 指针与地址运算符

---
- [C Plus 函数](#c-plus-函数)
  - [1. C 语言函数结构](#1-c-语言函数结构)
  - [2. ANSI C 函数原型](#2-ansi-c-函数原型)
    - [2.1 无参数与未指定参数](#21-无参数与未指定参数)
    - [2.2 函数原型的优点](#22-函数原型的优点)
  - [3. 函数递归](#3-函数递归)
    - [3.1 递归演示](#31-递归演示)
    - [3.2 递归的基本原理](#32-递归的基本原理)
    - [3.3 递归的优缺点](#33-递归的优缺点)
  - [4. 编译多源代码文件的程序](#4-编译多源代码文件的程序)
    - [4.1 UNIX](#41-unix)
    - [4.2 Linux](#42-linux)
    - [4.3 DOS 命令行编译器](#43-dos-命令行编译器)
    - [4.4 Windows 和 Mac IDE 编译器](#44-windows-和-mac-ide-编译器)
    - [4.5 使用头文件](#45-使用头文件)
  - [5. 查找地址 & 运算符](#5-查找地址--运算符)
  - [6. 指针简介](#6-指针简介)
    - [6.1 间接运算符 *](#61-间接运算符-)
    - [6.2 指针声明](#62-指针声明)
    - [6.3 使用指针在函数间通信](#63-使用指针在函数间通信)

---
## 1. C 语言函数结构

- 函数（function）是完成特定任务的独立程序代码单元

* 程序在 3 处使用定义函数的标识符
  - 函数原型 (function prototype) 告诉编译器函数的类型
  - 函数调用 (function call) 告诉在此处执行函数
  - 函数定义 (function definition) 指定函数要做什么

- 函数和变量一样，有多种类型。因此在任何程序在使用函数之前都必须要声明该函数的原型, 需要在 main() 函数定义前面出现, 函数原型指明了函数的返回值类型和函数接受的参数类型

```c
void FuncA(void);   // 函数原型

int main(void){
    FuncA();        // 函数调用
}
void FuncA(void){
    printf("Function start");
}
```

- 函数也可以放在另外的文件中, 调用方需要引用该函数所在的头文件 (#include)

---
## 2. ANSI C 函数原型

- 在 ANSI C 标准之前, 声明函数原型只需要声明函数的类型, 不用声明任何参数( int imin(); )

- 函数原型需要在任何调用函数的前方声明, 保持函数原型的位置在 main() 之前

- 函数原型表示函数的类型与返回类型, 主调函数把它的参数储存在被称为栈 (stack) 的临时存储区, 被调函数根据函数调用中的实际参数决定传递的类型, 而被调函数根据它的形式参数读取值

- C 语言函数是不支持函数重载的

```c
#include <stdio.h>
int imax(); /* 旧式函数声明 */
int main(void)
{
    printf("The maximum of %d and %d is %d.\n", 3, 5, imax(3));
    printf("The maximum of %d and %d is %d.\n", 3, 5, imax(3.0, 5.0));
    return 0;
}
int imax(n, m) 
int n, m;
{
    return (n > m ? n : m);
}
/*
  The maximum of 3 and 5 is 1606416656.
  The maximum of 3 and 5 is 3886.
*/
```
- 第 1 次调用 printf() 时省略了 imax() 的一个参数， 第 2 次调用 printf() 时用两个浮点参数而不是整数参数

- 函数调用 imax(3) 把一个整数放在栈中, 当 func() 函数开始执行时, 它从栈中读取两个整数, 实际上栈中只存放了一个带读取的整数, 第 2 个值当时恰好在栈中的其他值

> 标准 ANSI C 函数原型

- 针对参数不匹配的问题，ANSI C 标准要求在函数声明时还要声明变量的类型，即使用函数原型（function prototype）来声明函数的返回类型、参数的数量和每个参数的类型。

```c
  int imax(int,int);    // 或
  int imax(int a, int b);
```

- 以 imax() 为例，如果两个参数都是数字，但是类型不匹配，编译器会把实际参数的类型转换成形式参数的类型，imax(3.0, 5.0) 会被转换成 imax(3, 5)。

- 但是编译器仍会给出警告: double 转换成 int 可能会导致丢失数据

---
### 2.1 无参数与未指定参数

- 无参数声明: void Func(void), 支持 ANSI C 的编译器解释为 Func() 不接受任何参数。然后在调用该函数时，编译器会检查以确保没有使用参数。
  
- 形参数目不确定: 例如 printf 与 scanf 的参数列表, printf() 的原型函数可以是 int printf(const char*,...), 【...】变长参数

---
### 2.2 函数原型的优点

- 函数原型是 C 语言的一个强有力的工具，它让编译器捕获在使用函数时可能出现的许多错误或疏漏

- 一种方法可以省略函数原型, 之所以使用函数原型，是为了让编译器在第 1 次执行到该函数之前就知道如何使用它。因此，把整个函数定义放在第1次调用该函数之前，也有相同的效果。此时，函数定义也相当于函数原型。

---
## 3. 函数递归

- 外部调用函数: 第 1 级递归

- 内部调用依次: 第 2 级递归, 第 3 级递归.....

---
### 3.1 递归演示

```c
#include <stdio.h>
void up_and_down(int);

int main(void)
{
	up_and_down(1);
	return 0;
}

void up_and_down(int n)
{
	printf("Level %d: n location %p\n", n, &n); // #1
	if (n < 4)
		up_and_down(n + 1);
	printf("LEVEL %d: n location %p\n", n, &n); // #2
}
/*
	Level 1: n location 009BFC18
	Level 2: n location 009BFB40
	Level 3: n location 009BFA68
	Level 4: n location 009BF990
	LEVEL 4: n location 009BF990
	LEVEL 3: n location 009BFA68
	LEVEL 2: n location 009BFB40
	LEVEL 1: n location 009BFC18
*/
```

* 可以假设有一条函数调用链 —— fun1() 调用fun2()、fun2()调用 fun3()、fun3() 调用 fun4()。
  - 当 fun4() 结束时，控制传回 fun3()；
  - 当 fun3() 结束时，控制传回 fun2()；
  - 当 fun2() 结束时，控制传回 fun1()。

---
### 3.2 递归的基本原理

1. 每级函数调用都有自己的变量。

2. 每次函数调用都会返回一次。当函数执行完毕后，控制权将被传回上一级递归。程序必须按顺序逐级返回递归。

3. 递归函数中位于递归调用之前的语句，均按被调函数的顺序执行。

4. 递归函数中位于递归调用之后的语句，均按被调函数相反的顺序执行。

5. 虽然每级递归都有自己的变量，但是并没有拷贝函数的代码。（类似于循环）

6. 递归函数必须包含能让递归调用停止的语句。通常，递归函数都使用if或其他等价的测试条件在函数形参等于某特定值时终止递归。

---
### 3.3 递归的优缺点

- 优点是递归为某些编程问题提供了最简单的解决方案。

- 缺点是一些递归算法会快速消耗计算机的内存资源。另外，递归不方便阅读和维护

---
## 4. 编译多源代码文件的程序

### 4.1 UNIX

- 假定在 UNIX 系统中安装了 UNIX C 编译器（gcc 或 clang编译器），对 file1.c 与 file2.c 内含 C 函数的文件，使用以下命令编译并生成 a.out 的可执行文件，同时会生成 file1.o 和 file2.o

```powershell
  cc file1.c file2.c
```

- 修改其中一个文件，重新编译并与另外一个文件合并(修改 file1.c)

```powershell
  cc file1.c file2.o
```

---
### 4.2 Linux

- 假定 Linux 系统安装了 GNU C 编译器 GCC

```shell
  gcc file1.c file2.c 编译
  gcc file1.c file2.o 重编译合并
```

---
### 4.3 DOS 命令行编译器
 
- 绝大多数 DOS 命令行编译器的工作原理和 UNIX 的 cc 命令类似，只不过使用不同的名称而已

- file.c 编译之后的对象文件扩展名是 *.obj 而不是 *.o

```shell
  cc file1.c file2.obj
```

---
### 4.4 Windows 和 Mac IDE 编译器

- Windows 和 Macintosh 系统使用的集成开发环境中的编译器是面向项目的，资源包括源代码文件

- IDE 中的编译器要创建项目来运行单文件程序。对于多文件程序，要使用相应的菜单命令，把源代码文件加入一个项目中。

- 要确保所有的源代码文件都在项目列表中列出。许多 IDE 都不用在项目列表中列出头文件（即扩展名为 .h 的文件），因为项目只管理使用的源代码文件，源代码文件中的 #include 指令管理该文件中使用的头文件

- Xcode 要在项目中添加头文件。

---
### 4.5 使用头文件

- 可以将函数原型放在同一个头文件中，在外部调用方法时，只需要引用头文件，无需在调用位置前声明函数原型，例如 I/O 函数原型在 stdio.c 与数学函数原型 math.h 等。

- 预处理器定义符号常量，头文件只存储 #define 指令的文件，用于保存 #define 定义的值。
 
---
## 5. 查找地址 & 运算符

- 一元 & 运算符给出变量的存储地址。

```c
  printf("%p", &value);  // 打印变量的地址, %p 表示输出地址的转换说明
```

> 形式参数与实际参数地址

```c
#include <stdio.h>
void mikado(int); /* 函数原型 */
int main(void)
{
	int pooh = 2, bah = 5; /* main()的局部变量 */
	printf("In main(), pooh = %d and &pooh = %p\n", pooh, &pooh);
	printf("In main(), bah = %d	and &bah = %p\n", bah, &bah);

	mikado(pooh);
	return 0;
}
void mikado(int bah) /* 定义函数 */
{
	int pooh = 10; /* mikado()的局部变量 */
	printf("In mikado(), pooh = %d and &pooh = %p\n", pooh, &pooh);
	printf("In mikado(), bah = %d and &bah = %p\n", bah, &bah); 
}
/*
	In main(), pooh = 2 and &pooh = 005BF8FC
	In main(), bah = 5      and &bah = 005BF8F0
	In mikado(), pooh = 10 and &pooh = 005BF808
	In mikado(), bah = 2 and &bah = 005BF81C
*/
```

---
## 6. 指针简介

- 从根本上看，指针（pointer）是一个值为内存地址的变量（或数据对象）。

```c
  ptr = &ptrName;
  // ptr 和 &ptrName 的区别是, ptr 是变量, &ptrName 是常量, ptrName 表示变量, ptr 表示变量 ptrName 的地址
```

---
### 6.1 间接运算符 *

- 已知 ptr = &bah 

- 使用间接运算符 * (indirection operator) 或解引用运算符 (dereferencing operator), 找出储存在 bah 中的值

- 即 val = *ptr 

---
### 6.2 指针声明

- 指针类型与变量类型保持一致

- 实际上，指针式一个新类型，不是整数类型，有专门的 %p 格式转换说明

```c
  int I = 1;
  int* pI = &I;
  // I = *pI

  float F = 1.0;
  float* pF = &F;
  // F = *pF

  void Func(void);
  void* pFunc = &Func;
  // Func = *pFunc
```

---
### 6.3 使用指针在函数间通信

> 使用指针解决交换函数的问题

```c
#include <stdio.h>
void interchange(int* u, int* v);
int main(void)
{
	int x = 5, y = 10;
	printf("Originally x = %d and y = %d.\n", x, y);
	interchange(&x, &y); // 把地址发送给函数
	printf("Now x = %d and y = %d.\n", x, y);
	return 0;
}
void interchange(int* u, int* v)
{
	int temp;
	temp = *u; // temp获得 u 所指向对象的值
	*u = *v;
	*v = temp;
}
// interchange() 表示传入两个参数的地址, 交换他们的值
```

> 按字节寻址系统(如 PC)

- 变量的名称、地址和变量的值之间关系密切，指针获取变量的机器码地址，变量保存数据的类型，数据的类型决定了值在内存中的字节大小，在该内存位置保存变量的值。

- 普通变量把值作为基本量，把地址作为通过 & 运算符获得的派生量；

- 而指针变量把地址作为基本量，把值作为通过 * 运算符获得的派生量。

---