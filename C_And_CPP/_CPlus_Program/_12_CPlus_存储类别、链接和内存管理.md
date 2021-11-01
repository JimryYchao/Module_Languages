# C PLus  存储类别\链接与内存管理

- 关键字：auto、extern、static、register、const、volatile、restricted、_Thread_local、_Atomic 
- 函数：rand()、srand()、time()、malloc()、calloc()、free()
- 变量的作用域（可见的范围）和生命期

---
- [C PLus  存储类别\链接与内存管理](#c-plus--存储类别链接与内存管理)
	- [1. 存储类别](#1-存储类别)
		- [1.1 作用域 scope](#11-作用域-scope)
		- [1.2 链接](#12-链接)
		- [1.3 存储期](#13-存储期)
		- [1.4 自动变量](#14-自动变量)
		- [1.5 寄存器变量](#15-寄存器变量)
		- [1.6 块作用域的静态变量](#16-块作用域的静态变量)
		- [1.7 外部链接的静态变量](#17-外部链接的静态变量)
		- [1.8 内部链接的静态变量](#18-内部链接的静态变量)
		- [1.9 多文件](#19-多文件)
		- [1.10 存储类别说明符](#110-存储类别说明符)
		- [1.11 存储类别与函数](#111-存储类别与函数)
	- [2. 随机数函数和静态变量](#2-随机数函数和静态变量)
		- [2.1 掷骰子](#21-掷骰子)
	- [3. 分配内存 malloc() 与 free()](#3-分配内存-malloc-与-free)
		- [3.1 malloc](#31-malloc)
		- [3.2 free](#32-free)
		- [3.3 free 的重要性](#33-free-的重要性)
		- [3.4 calloc](#34-calloc)
		- [3.5 动态内存分配和变长数组](#35-动态内存分配和变长数组)
		- [3.6 存储类别与动态内存分配](#36-存储类别与动态内存分配)
	- [4. 类型限定符](#4-类型限定符)
		- [4.1 const](#41-const)
		- [4.2 volatile](#42-volatile)
		- [4.3 restrict](#43-restrict)
		- [4.4 _Atomic](#44-_atomic)
		- [4.5 旧关键字的新位置 (C99)](#45-旧关键字的新位置-c99)

---
## 1. 存储类别

> 对象 object

- 数据都储存在内存：从硬件方面来看，被储存的每个值都占用一定的物理内存，C 语言把这样的一块内存称为对象（object）（面向对象编程中的对象表示为类对象）。

- 对象可以储存一个或多个值。一个对象可能并未储存实际的值，但是它在储存适当的值时一定具有相应的大小

- 标识符 entity 即是软件（即 C 程序）指定硬件内存中的对象的方式，标识符可以用来指定（designate）特定对象的内容

- 在 C 语言中，变量名不是指定对象的唯一途径，例如指针结构与数组

> 左值 lvalue

- 指定对象的表达式被称为左值

```c
	int num = 10;               // 可修改左值
	const int num2 = 11;        // 不可修改左值
	char str[] = "Hello";
	const char* ptr = str;     // ptr 可修改左值, *ptr 不可修改左值
	ptr = "World";
	char* const ptr2 = str;    // ptr2 不可修改左值 *ptr2 可修改
	ptr2[0] = 'h';
    const char* const ptr3 = str;  // ptr3 与 *ptr3 均是不可修改左值
```

> 存储期  storage duration

- 存储期是指对象在内存中保留了多长时间。

- 标识符用于访问对象，可以用作用域（scope）和链接（linkage）描述标识符，标识符的作用域和链接表明了程序的哪些部分可以使用它

- 对象可存在于程序的执行期，也可以仅存在于它所在函数的执行期

- 对于并发编程，对象可以在特定线程的执行期存在。
  
- 可以通过函数调用的方式显式分配和释放内存。

---
### 1.1 作用域 scope

- 作用域描述程序中可访问标识符的区域，作用域可以是块作用域，函数作用域、函数原型作用域、文件作用域

- 块作用域（block scope）块作用域变量的可见范围是从定义处到包含该定义的块的末尾（块是用一对花括号括起来的代码区域）

- 函数作用域（function scope）仅用于 goto 语句的标签：一个标签首次出现在函数的内层块中，它的作用域也延伸至整个函数

- 函数原型作用域（function prototype scope）用于函数原型中的形参名（变量名），编译器在处理函数原型中的形参时只关心它的类型，而形参名（如果有的话）通常无关紧要，只有在变长数组中，形参名才有用

- 变量的定义在函数的外面，具有文件作用域（file scope），具有文件作用域的变量，从它的定义处到该定义所在文件的末尾均可见（全局变量 global variable）

```c
#include <stdio.h>

int Number = 10; // 文件作用域/全局变量

void Function(int max, char *arr[max]); // 函数原型作用域

int main(void)
{ // 块作用域
    if (Number == 10)
    { // 块作用域
        Function(Number, arr[Number]);
    }
}
void Function(int max, char *arr[max])
{
label:
    printf("%d", max); // 函数作用域

    if (arr[0] == NULL)
    {
        goto label;
    }
}
```

> 翻译单元与文件

- 通常在源代码（.c 扩展名）中包含一个或多个头文件（.h 扩展名）

- 头文件会依次包含其他头文件，所以会包含多个单独的物理文件
 
- C 预处理实际上是用包含的头文件内容替换 #include 指令，编译器源代码文件和所有的头文件都看成是一个包含信息的单独文件。这个文件被称为翻译单元（translation unit）。

- 描述一个具有文件作用域的变量时，它的实际可见范围是整个翻译单元

---
### 1.2 链接

- C 变量有 3 中链接属性：外部链接、内部链接、无链接

- 局部变量都是无链接变量，仅包含在当前作用域私有

- 具有文件作用域的变量可以是外部或内部链接，外部可在多文件程序中使用，内部仅只能在一个翻译单元中使用

> 内部与外部链接

- C 标准用 “内部链接的文件作用域” 描述仅限于一个翻译单元（即一个源代码文件和它所包含的头文件）的作用域，用 “外部链接的文件作用域” 描述可延伸至其他翻译单元的作用域

```c
int giants = 5;         // 外部链接的文件作用域
static int size = 10;   // 内部链接的文件作用域
```

---
### 1.3 存储期

* 作用域和链接描述了标识符的可见性。存储期描述了通过这些标识符访问的对象的生存期
  - 静态存储期：在程序的执行期间一直存在（文件作用域变量具有静态存储期，static 表示变量的内部链接属性）
  - 线程存储期：用于并发程序设计，程序执行可被分为多个线程（线程存储期的对象，从被声明时到线程结束一直存在，关键字 _Thread_local 声明一个对象时，每个线程都获得该变量的私有备份）
  - 自动存储期：块作用域的变量通常都具有自动存储期（进入块时，为这些变量分配内存；离开块区域时，这些局部变量会被释放，static 表示块变量拥有静态存储期，从程序被载入到程序结束期间都存在。其他函数可以通过该存储区的地址间接访问该对象）
  - 动态分配存储期

> 5 种存储类别(不包括并发程序设计)

|**存储类别**|**存储期**|**作用域**|**链接**|**声明方式**|
|:----|:----|:----|:----|:----|
|自动|自动|块|无|块内|
|寄存器|自动|块|无|块内, register 声明|
|静态外部链接|静态|文件|外部|所有函数外|
|静态内部链接|静态|文件|内部|所有函数外, static 声明|
|静态无链接|静态|块|无|块内, static 声明|

---
### 1.4 自动变量

- 属于自动存储类别的变量具有自动存储期、块作用域且无链接

- 显式使用 auto：表明有意覆盖一个外部变量定义，或者强调不要把该变量改为其他存储类别

- 关键字 auto 是存储类别说明符（storage-class specifier）。（在 C++ 用法不同）

- 内存与外层有相同的变量名，在内部变量会覆盖外层定义，离开内层之后，恢复外层同名定义

- 自动变量不会初始化, 变量的值可能是之前占用分配给该变量空间中的任意值因此声明后需要初始化, 才能确保使用的程序的正确性

```c
int num = 1;
int main(void){
    auto int num = 2;   // 显式覆盖一个外部定义
}
```

> 举例

```c
int main()
{
	int x = 30;			// 原始的 x
	printf("x in outer block: %d at %p\n", x, &x);
	{
		int x = 77;		// 新的 x，隐藏了原始的 x
		printf("x in inner block: %d at %p\n", x,&x);
	}
	printf("x in outer block: %d at %p\n", x, &x);
	while (x++ < 33)	// 原始的 x, 每次循环使用的都是原始 x
	{
		int x = 100;	// 新的 x，隐藏了原始的 x
		x++;
		printf("x in while loop: %d at %p\n", x,
			&x);
	}
	printf("x in outer block: %d at %p\n", x, &x);
	return 0;
}
/*
	x in outer block: 30 at 0093FD00
	x in inner block: 77 at 0093FCF4
	x in outer block: 30 at 0093FD00
	x in while loop: 101 at 0093FCE8
	x in while loop: 101 at 0093FCE8
	x in while loop: 101 at 0093FCE8
	x in outer block: 34 at 0093FD00
*/
```

---
### 1.5 寄存器变量

- 变量通常储存在计算机内存中, 寄存器变量储存在 CPU 的寄存器中, 访问速度要比内存中的变量更快

- 寄存器变量无法获取到值的地址, 和自动变量一样, 寄存器变量是块作用域、无链接、自动存储期

- 使用 register 声明寄存器变量，类似于向编译器发起请求，根据寄存器或最快可用内存的数量来衡量存储请求，被忽略时就会编程普通变量
  
- 寄存器变量储存在寄存器而非内存中，所以无法获取寄存器变量的地址，即使成为普通变量也不可以使用地址运算符

- 可声明为register的数据类型有限

```c
int main(void){
    register int num = 1;       //  指定该变量储存在 CPU 寄存器中 
}
void Fun(register int num);     // 指定形参储存方式
```

---
### 1.6 块作用域的静态变量

- 静态变量（static variable）表示该变量在内存中的位置不变, 值可以发生改变

- 文件作用域变量均具有静态变量的特性, 块静态变量 (也叫内部静态存储类别) 同样具有 static 属性, 计算机在多次函数调用之间会记录它们的值

```c
void Function(void); // 函数原型
int main(void)
{
    for (size_t i = 0; i < 3; i++)
        Function();
}

void Function(void)
{
    static int recoder = 0;
    recoder++;
    printf("%d    %p\n", recoder, &recoder);
}
/*
    1    00407020
    2    00407020
    3    00407020
*/
```

---
### 1.7 外部链接的静态变量

- 外部链接的静态变量具有文件作用域、外部链接和静态存储期。也叫外部存储类别

- 变量的定义声明在函数的外部，函数中使用外部变量，可以在函数中 extern 再次声明（可选），文件域中使用另一个源代码文件的外部变量，必须在该文件中 extern 声明该变量

```c
extern char* HELLO; // 外部
extern char* WORLD; // 外部
int num = 1;
char Str[10];

int main(void)
{
    extern int num;     // 可选
    extern char Str[];  // 可选, 大小不需要再次声明   
}
```

> 外部变量初始化

- 外部变量声明时会被自动初始化为 0, 因此可以对外部变量采用显式初始化或只做声明 (内部变量需要初始化之后才可正确调用)

- 初始化外部变量只能使用常量表达式

> 外部名称

- C99 和 C11 标准都要求编译器识别局部标识符的前 63 个字符和外部标识符的前 31 个字符

> 声明与定义

```c
    int tern = 1;           // 定义式声明
    main(){
        extern int tern;    // 使用别处定义, 即引用式声明
    } 
```

---
###  1.8 内部链接的静态变量

- 内部静态变量存储类别的变量具有静态存储期、文件作用域和内部链接

- static 修饰外部变量, 表示该变量只能用于同一个文件中的函数

---
### 1.9 多文件

- 只有当程序由多个翻译单元组成时，才体现区别内部链接和外部链接的重要性

- 复杂的 C 程序通常由多个单独的源代码文件组成，C 通过在一个文件中进行定义式声明，然后在其他文件中进行引用式声明来实现共享。

- 调用其他文件的外部变量，要使用 extern 关键字

---
### 1.10 存储类别说明符

- auto 表明变量是自动存储期，只能用于块作用域的变量声明中

- register 用于块作用域的变量，它把变量归为寄存器存储类别，请求最快速度访问该变

- static 创建的对象具有静态存储期，载入程序时创建对象，当程序结束时对象消失。该变量仅作用于所用于当前作用域或嵌套作用域

- extern 表明声明的变量定义在别处。包含 extern 的声明具有文件作用域，则引用的变量必须具有外部链接

- _Thread_local 线程存储期，可以与 static 与 extern 一起使用吗，表明变量在并发线程中为各个线程私有

- typedef 关键字与任何内存存储无关，也不能用多个存储类别说明符作为 typedef 的一部分

---
### 1.11 存储类别与函数

- 函数存在存储类别，可以是外部函数（默认）或静态函数，C99 新增内联函数

```c
    double Func(void);      // 默认外部函数
    static int func(void);  // 静态函数, 内部存储期
    extern double delta(void);  // 引用外部文件的外部函数
```

---
## 2. 随机数函数和静态变量

- 随机数函数: ANSI C 提供了 rand() 函数生成随机数(伪随机数生成器), 每次生成的随机数需要一个特定的种子, 该函数使用该种子生成新的数, 这个数又成为了新的种子......方案需要一个静态变量作为种子迭代

> 可移植伪随机数函数 rand0: 

```c
static unsigned long int next = 1; /* 种子 */
unsigned int rand0(void)
{
    /* 生成伪随机数的魔术公式 */
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}
```

- 函数是用于返回一个0～32767之间的值

- 但每次重新启动返回的结果顺序都相同, 源于每次程序启动的起始种子总是 1

> 设置种子刷新机制

```c
static unsigned long int next = 1; /* 种子 */
int rand1(void)
{
    /*生成伪随机数的魔术公式*/
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}
void srand1(unsigned int seed)  // 外部调用函数重置随机数种子
{
    next = seed;
}
``` 

- 可以使用 C 访问一些可变的量(时钟系统), 使用 time() 函数返回系统时间 time_t, 和系统有关

- srand1((unsigned int) time(0)), time(ptr) 一般接受的参数是一个 time_t 类型的指针, 时间值存储在该地址上, 传入空指针只能通过返回值获取

---
### 2.1 掷骰子

* 一个 6 面的骰子, 需要获得 1 ~ 6 之间的随机数, rand() 生成的随机数在 0 ~ Rand_MAX(= INT_MAX) 之间, 实现方法
  - 随机数求取模 6, 获得的整数在 0 ~ 5 之间
  - 结果加 1, 保持新值在 1 ~ 6 之间
  - 把第 1 步中的数字 6 替换成骰子面数(方便拓展, 骰子也存在更多的面数)

```c
#include <stdio.h>
#include <stdlib.h> /* 为库函数 srand() 提供原型 */
#include <time.h>

static int roll_count = 0;
static int roll(int);
int roll_n_dice(int, int);

int main(void)
{
    int dice, roll;
    int sides;
    int status;
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0)
    {
        printf("How many dice?\n");
        if ((status = scanf("%d", &dice)) != 1)
        {
            if (status == EOF)
                break;           /* 退出循环 */
            else
            {
                printf("You should have entered an integer.");
                printf(" Let's begin again.\n");
                while (getchar() != '\n')
                    continue;   /* 处理错误的输入 */
                printf("How many sides? Enter 0 to stop.\n");
                continue;       /* 进入循环的下一轮迭代 */
            }
        }
        roll = roll_n_dice(dice, sides);
        printf("You have rolled a %d using %d %dsided dice.\n ", roll, dice, sides);
        printf("How many sides? Enter 0 to stop.\n");
    }
    printf("The rollem() function was called %d times.\n ", roll_count);
    printf("GOOD FORTUNE TO YOU!\n");
    return 0;
}
int roll(int sides)
{   
    srand((unsigned int)time(0)); /* 随机种子, 与 rand()混合使用 */
    int roll;
    roll = rand() % sides + 1;
    roll_count++;
    return roll;
}
int roll_n_dice(int dice, int sides)
{
    int d, total = 0;
    if (sides < 2)
    {
        puts("Need at least 2 sides");
        return -2;
    }
    if (dice < 1)
    {
        puts("Need at least 1 die");
        return -1;
    }
    for (d = 0; d < dice; d++)
        total += roll(sides);
    return total;
}
```

---
## 3. 分配内存 malloc() 与 free() 

- 一般 C 数据声明时, 程序使用的内存大多数是自动分配的(#include stdlib.h)

---
### 3.1 malloc

- 可以使用 malloc 函数在程序运行时分配更多的内存, 接受一个参数表示所需要的内存字节数, 该函数会找到合适的匿名空闲内存块, 返回值为动态分配内存的首字节地址(返回一个指针对象, 指向 void 的指针); 分配内存失败时, 将返回空指针

- 可以把指向 void 通用指针赋给任意类型的指针, 不用考虑类型匹配的问题(可以强制转换成匹配的类型)

> 为 30 个 double 类型的值请求内存空间, ptd 指向该位置

```c
    double * ptd;
    ptd = (double*)malloc(30* sizeof(double));
```

- ptd 指向一个 double 类型, 但不是指向内含 30 个 double 类型值的块, ptd 指向了该内存的首元素, 可以像数组那样 ptd[n] 访问该区域的元素变量

> 动态数组

- 数组的声明, 可以是常量表示维度自动分配内存创建, 也可以声明变长数组, 在函数块中的自动内存中创建, 或者是声明一个指针, 调用 malloc 函数创建

- 利用变长数组的特征与分配内存函数可以创建动态数组, 可以在程序运行时选择数组的大小和分配内存

> exit()

- 如果内存分配失败，可以调用 exit() 函数结束程序

- 标准提供了两个返回值以保证在所有操作系统中都能正常工作：EXIT_SUCCESS（或者，相当于 0）表示普通的程序结束，EXIT_FAILURE 表示程序异常中止

```c
    ptd = (double *) malloc(n * sizeof(double));
```

---
### 3.2 free

- free() 要与 malloc() 函数搭配使用, free 函数的参数是 malloc 返回的地址, 表示释放之前 malloc 分配的内存, 不能使用 free 释放其他方式分配的内存

- 被 free 释放掉的内存区域, 访问数据时, 数据以丢失

- 一般将 free 函数位于程序的末尾

> malloc, free, exit 动态分配数组

```c
#include <stdio.h>
#include <stdlib.h> /* 为 malloc()、free()提供原型 */
int main(void)
{
	double* ptd;
	int max;
	int number;
	int i = 0;
	puts("What is the maximum number of type double entries ? ");
	if (scanf("%d", &max) != 1)
	{
		puts("Number not correctly entered -- bye.");
		exit(EXIT_FAILURE);
	}
	ptd = (double*)malloc(max * sizeof(double));
	if (ptd == NULL)
	{
		puts("Memory allocation failed. Goodbye.");
		exit(EXIT_FAILURE);
	}
	/* ptd 现在指向有max个元素的数组 */
	puts("Enter the values (q to quit):");
	while (i < max && scanf("%lf", &ptd[i]) == 1)
		++i;
	printf("Here are your %d entries:\n", number = i);
	for (i = 0; i < number; i++)
	{
		printf("%7.2f ", ptd[i]);
		if (i % 7 == 6) // 7个元素一行
			putchar('\n');
	}
	if (i % 7 != 0)
		putchar('\n');
	puts("Done.");
	free(ptd);
	return 0;
}
```

---
### 3.3 free 的重要性

- 静态内存的数量在编译时是固定的，在程序运行期间也不会改变。
  
- 自动变量使用的内存数量在程序执行期间自动增加或减少。但是动态分配的内存数量只会增加，除非用 free() 进行释放

- 若未使用 free 释放 malloc 申请的内存, 且 malloc 返回的指针丢失或被释放, 该区域内存也不会被自动回收, 由于指针丢失, 导致这块区域也无法访问且无法重复利用

- 无节制申请内存但不释放的情况下, 会导致大量的内存被耗尽, 程序未结束之前就已经耗尽所有的内存, 这类问题称为内存泄露 (memory leak)

- 因此在使用申请的内存之后不再使用, 需要使用 free 释放掉多余的内存

---
### 3.4 calloc 

* 分配内存可以使用 calloc() :: calloc(unsigned int count, unsigned int size);
  - count 表示所需的存储单元的数目
  - size 表示存储单元的大小(字节为单位)

- calloc 函数在创建内存的时候, 同时会将块中的所有位都设置为 0 

- 使用 free 函数释放 calloc 申请的内存

```c
    long * newmem;
    newmem = (long *)calloc(100, sizeof (long));
```

---
### 3.5 动态内存分配和变长数组

- 使用变长数组或 malloc 创建数组的行为很相似, 但变长数组是自动存储类型, 该内存空间会自动释放, 而 malloc 需要使用 free 释放不用的空间

- 变长数组仅能在该定义的块中使用, malloc 创建的数组可以在多个函数中调用

- free 使用的指针变量可以与 malloc 的指针变量不同, 但要求两个指针的地址值相同, 不能释放同一块内存两次

> 多维数组

```c
    int n = 5;
    int m = 6;

    int arr[n][m];  // n x m de 变长数组
    int(*p1)[6];    // C99 之前写法
    int(*p2)[m];    // 需要编译器支持变长数组

    p1 = (int(*)[6])malloc(n*6*sizeof(int));    // n x 6 数组
    p2 = (int(*)[m])malloc(n*m*sizeof(int));    // n x m 数组, 需要支持变长数组
```

---
### 3.6 存储类别与动态内存分配

* 假设一个理想化模型: 程序把它可用的内存分为
  - 一部分供具有外部链接、内部链接和无链接的静态变量使用
  - 一部分供自动变量使用
  - 一部分供动态内存分配

- 静态类型所用的内存数量在编译时确定, 与程序的生命周期共存, 程序结束时销毁

- 自动类型在程序进入定义块时创建, 离开块时销毁, 这部分内存通常以栈方式处理, 新创建的变量按顺序加入内存, 以相反的顺序销毁

- 动态分配的内存在调用 malloc 或相关函数时存在, 在调用 free 时释放, 未使用的内存块分散在已使用的内存块之间, 使用动态内存通常比栈内存慢(动态分配的区域一般称为内存堆或自由内存)

---
## 4. 类型限定符

- 一般地, 我们使用类型和存储类别来描述一个变量, C90 新增了变量的恒常性(constancy)和易变性(volatility)

```c
    // C90
    const       恒常性
    volatile    易变性
    // C99
    restrict    约束
    // C11
    _Atomic     以支持并发程序设计(可选)
```

---
### 4.1 const

- 以 const 关键字声明的对象，其值不能通过赋值或递增、递减来修改

```c
    const int nochange = 1;         // 只读
    const char str[10] = "Hello";   // 只读数组
    
    // const 指针声明
    const char* ptr1;        // const 限定 ptr1 指向的值, 指针本身可修改
    char* const ptr2;        // const 限定 ptr2 指针本身, 指针指向的值可修改
    const char* const ptr;    // 限定指针本身与其指向的值

    // 形参指针
    void display(const char str[]);     // 限定 str 只读
    void display(const char* str)
```

> 对全局变量使用 const

* 全局变量声明 const 限定, 可以保护数据不被外部更改数据, 但文件中共享 const 数据要注意
  - 可以一个文件中使用定义式声明, 其他文件使用引用式声明(extern)
  - 另一种可以把 const 变量放在一个头文件中, 在其他文件中包含该头文件, 必须在头文件中用关键字 static 声明全局 const 变量(未 static 修饰 const 全局, 将多个文件都有相同标识符的定义式声明)

---
### 4.2 volatile

- volatile 限定告知计算机, 代理(不是变量所在的程序)可以修改该变量的值, 一般用于硬件地址以及在其他程序或同时运行的线程中共享数据

> volatile 涉及编译器的优化:

```c
    val1 = x;
    //do...不使用 x 的代码
    val2 = x;
```

- 一些编译器会将 x 的值保存在寄存器, 当 val2 使用 x 时, 并不会从原始内存位置的读取 x 的值, 会从寄存器上读取 x, 目的是为了程序优化(此过程称为高速缓存 caching)

- 但如果其他的代理在 val1 与 val2 改变了 x 的值, 编译器并不知道这类事发生, 安全起见, 使用 valotile 限定的变量不会采用高速缓存的方式读取 x 的值

> const volatile 变量

- 可以同时用 const 和 volatile 限定一个值, 通常用 const 把硬件时钟设置为程序不能更改的变量，但是可以通过代理改变，这时用 volatile

```c
    volatile const int loc;         // 等价
    const volatile int * ploc;
```

---
### 4.3 restrict

- restrict 关键字允许编译器优化某部分代码以更好地支持计算, 只能用于指针, 表明该指针是访问数据对象的唯一且初始的方式

```c
    int * restrict restar = (int *) malloc(10 * sizeof(int));
    // 指针 restar 是访问由 malloc() 所分配内存的唯一且初始的方式

    restar[0] += 5;
    restar[0] += 3;
    // 由于 restar 唯一指定访问方式, 编译器处于优化考虑, 会采用 restar[0] += 8 进行替换

    int ar[10];
    int * par = ar;

    par[0] += 5;
    ar[0] *= 2;
    par[0] += 3;    // par 未使用 restirct 限定, 编译器就必须假设最坏的方式(其他标识符可能已经改变该地址的值), par[0] += 8 不能进行替换
```

- 如果用了 restrict 关键字，编译器就可以选择捷径优化计算

- restrict 限定符还可用于函数形参中的指针, 意味着编译器可以假定在函数体内其他标识符不会修改该指针指向的数据，而且编译器可以尝试对其优化

> C 库有两个函数用于把一个位置上的字节拷贝到另一个位置

```c
    void * memcpy(void * restrict s1, const void * restrict s2,size_t n); 
    void * memmove(void * s1, const void * s2, size_t n);
```

- 表示从位置 s2 把 n 字节拷贝到 s1, 其中 memcpy 要求两个位置不重叠, memmove 不要求

- memcpy 说明两个指针都是访问相应数据的唯一方式, 要求不能访问同一块数据

---
### 4.4 _Atomic 

- 并发程序设计把程序执行分成可以同时执行的多个线程, 因此如何管理访问相同数据的不同线程

- C11 通过包含可选的头文件 stdatomic.h 和 threads.h，提供了一些可选的（不是必须实现的）管理方法

- 要通过各种宏函数来访问原子类型。当一个线程对一个原子类型的对象执行原子操作时，其他线程不能访问该对象

```c
    int num;        // 普通声明
    num = 12;       // 普通赋值

    _Atomic int num;            // 原子类型 num
    atomic_store(&num,12);      // 使用 stdatomic.h 宏对 num 赋值, 该原子过程中, 其他线程无法访问 num
```

---
### 4.5 旧关键字的新位置 (C99)

> const restrict

```c
    void method(int * const a1, int * restrict a2, int n);      // 常规旧风格
    //等价于 (新等价语法)
    void method(int a1[const], int a2[restrict], int n);    
        // 指针表示法和数组表示法都可以使用这两个限定符
```

> static 新增如何使用 static 形式参数

```c
    double stick(double ar[static 20]);
```

- static 的这种用法表明，函数调用中的实际参数应该是一个指向数组首元素的指针，且该数组至少有 20 个元素

---