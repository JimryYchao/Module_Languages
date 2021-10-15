# C Plus 字符串与字符串函数

- 输入输出函数： gets() 、gets_s() 、fgets() 、puts() 、fputs() 
- 字符串函数：strcat() 、strncat() 、strcmp() 、strncmp() 、strcpy() 、strncpy()、sprintf()、strchr() 
- C 库中的字符和字符串函数
  
---
- [C Plus 字符串与字符串函数](#c-plus-字符串与字符串函数)
  - [1. 表示字符串和字符串 I/O](#1-表示字符串和字符串-io)
    - [1.1 puts() 字符串显示](#11-puts-字符串显示)
    - [1.2 字符串字面量(字符串常量)](#12-字符串字面量字符串常量)
    - [1.3 字符串数组](#13-字符串数组)
    - [1.3 指针与字符串](#13-指针与字符串)
  - [2. 字符串输入](#2-字符串输入)
    - [2.1 分配空间](#21-分配空间)
    - [2.2 gets() 与 puts()](#22-gets-与-puts)
    - [2.3 fgets() 与 fputs()](#23-fgets-与-fputs)
    - [2.4 gets_s()](#24-gets_s)
    - [2.5 自定义 s_gets()](#25-自定义-s_gets)
    - [2.6 scanf 函数](#26-scanf-函数)
  - [3. 字符串输出](#3-字符串输出)
    - [3.1 puts 函数](#31-puts-函数)
    - [3.2 fputs 函数](#32-fputs-函数)
    - [3.3 printf 函数](#33-printf-函数)
  - [4. 自定义输入与输出函数](#4-自定义输入与输出函数)
  - [5. 字符串函数](#5-字符串函数)
    - [5.1 strlen 统计字符串长度](#51-strlen-统计字符串长度)
    - [5.2 strcat 拼接字符串](#52-strcat-拼接字符串)
    - [5.3 strncat 拼接指定字符数目](#53-strncat-拼接指定字符数目)
    - [5.4 strcmp 比较字符串](#54-strcmp-比较字符串)
    - [5.5 strncmp](#55-strncmp)
    - [5.6 strcpy 和 strncpy](#56-strcpy-和-strncpy)
    - [5.7 sprintf](#57-sprintf)
    - [5.8 其他字符串函数](#58-其他字符串函数)
  - [6. 字符串排序](#6-字符串排序)

---
## 1. 表示字符串和字符串 I/O

- 字符串是以空字符（\0）结尾的 char 类型数组

---
### 1.1 puts() 字符串显示

- puts() 函数专门输出字符串, 并且自动在最后添加换行符

```c
#include<stdio.h>
#define MSG "This is a massage."
#define SIZE 99
int main(void){
    char words[SIZE] = "Hello World.";
    const char* str = "Pointer string.";

    puts(words);
    puts(MSG);
    puts(str);

    words[0] = 'h';
    puts(words);
    
    return 0;
} 
/*
    Hello World.
    This is a massage.
    Pointer string.
    hello World.
*/
```

---
### 1.2 字符串字面量(字符串常量)

- 用双引号括起来的内容称为字符串字面量（string literal），也叫作字符串常量（string constant）

> 字符串串联

- 从 ANSI C 标准起，如果字符串字面量之间没有间隔，或者用空白字符分隔，C 会将其视为串联起来的字符串字面量。

```c
    char greeting[50] = "Hello, and"" how are" "you"
" today!";
    //等价于
    char greeting[50] = "Hello, and how are you today!";
```

> 显示双引号

- 字符串内部使用双引号: \"

```c
   const char* str = "Hello,\"WORLD\"";  // Hello,"WORLD"
```

> 字符串概念

- 字符串常量属于静态存储类别（static storage class），该字符串只会被储存一次，在整个程序的生命期内存在，即使函数被调用多次

- 用双引号括起来的内容被视为指向该字符串储存位置的指针
  
- 字符串常量本质是一个 const 数据, 其首字符的地址对应 const char* ptr 指针

```c
#include <stdio.h>
int main(void)
{
    printf("%s, %p, %c\n", "We", "are", *"space farers");
    return 0;
}
/*
    We, 00FA7B40, s
*/
```

> 字符串数组和初始化

- 预先声明的 char 数组需要预先指定一定的容量来储存字符串, 总是要比字符串的长度至少大一个空字符的空间, 所有未使用的元素都被自动初始化为 0
  
- 声明字符串时，可以让编译器确认数组的大小：const char str[] = "aaaa"，因为处理字符串的函数通常都不知道数组的大小，这些函数通过查找字符串末尾的空字符确定字符串在何处结束。
  
- 因为处理字符串的函数通常都不知道数组的大小，这些函数通过查找字符串末尾的空字符确定字符串在何处结束。

> 初始化字符数组来储存字符串和初始化指针来指向字符串有何区别

```c
    char charArr[] = "Hello World";   // 数组名 charArr 是常量
    const char *pStr = "hello World"; // 指针名 pStr 是变量

    // 1. 两者都可以使用数组表示法
    for (int i = 0; i < 11; i++)
        putchar(charArr[i]);          // Hello World
    putchar('\n');
    for (int j = 0; j < 11; j++)    
        putchar(pStr[j]);             // hello World
    putchar('\n');

    // 2. 两者都能进行指针加法操作
    putchar(*(charArr + i));
    putchar(*(pStr + i));

    // 3. 只有指针表示法可以进行递增操作
    while (*(head) != '\0')     /* 在字符串末尾处停止*/
        putchar(*(pStr++));

    // 4. 指针可以指向数组, 但数组不可以指向指针
    pStr = charArr;
    charArr = pStr; // ERROR 赋值运算符的左侧必须是变量
```

---
### 1.3 字符串数组

- 声明字符串数组时有两种方式：char[][] 与 const char* ptr[]

```c
#include <stdio.h>

int main(void) {
	char Strs[3][20]{
		"First Line",
		"Second Line",
		"Third Line"
	};
	const char* pStrs[3]{
		"First Line",
		"Second Line",
		"Third Line"
	};

	printf("Char[] size: %zd\n", sizeof Strs);		
	printf("pStr[] size: %zd\n", sizeof pStrs);		
}
/*
	Char[] size: 60
	pStr[] size: 12
*/
```

> 数组声明与指针声明方式的区别

* 相似点: 
  - 两者的初始化方式也相同。
  - 都可以使用下标访问字符串字面量, 使用两个下标访问单个字符

- 区别:
  - 数组需要指定大小, 同时数组储存着字符串字面量的副本，所以每个字符串都被储存了两次
  - 指针数组指针指向初始化时所用的字符串字面量的位置，这些字符串字面量被储存在静态内存中, 仅保存字符串地址
  - 因此, 字符串指针数组一般比数组声明方式占用的空间要小, 同时访问的效率要比数组方式快
  - 但数组方式可以修改单个字符的值, 指针方式不可以修改 const char* 类型值
  - 指针数组指向的字符串不必储存在连续的内存中, 但数组声明时需要指定大小, 内存上存储也是连续的

---
### 1.3 指针与字符串

- 字符串的绝大多数操作都是通过指针完成的

```c
#include <stdio.h>
int main(void)
{
	const char* mesg = "Don't be a fool!";
	const char* copy;
	copy = mesg;
	printf("%s\n", copy);
	printf("mesg = %s; &mesg = %p; value = %p\n", mesg, &mesg, mesg); 
	printf("copy = %s; &copy = %p; value = %p\n", copy, &copy, copy);
	return 0;
}
/*
    Don't be a fool!
    mesg = Don't be a fool!; &mesg = 00F4F848; value = 00FD7B30
    copy = Don't be a fool!; &copy = 00F4F83C; value = 00FD7B30
    指针的地址不同, 存储的地址相同
*/
```

---
## 2. 字符串输入

### 2.1 分配空间

- 为字符串分配内存后，便可读入字符串。

```c
    // 常规方式是显式声明 char[] 并指明数组的大小
    char name[20];
    scanf("%s",name);

    /* 不可采用指针方式声明未定义的字符串, 系统在分配空间时
    并未指定位置存储输入的字符串, 因此在输入时可能会修改擦写
    掉程序中的数据或代码 */
    char* name;         //ERROR
    scanf("%s",name);
```

---
### 2.2 gets() 与 puts()

```c
/*-----------------------------------------------------------
    gets();      用于保存整行输入的字符串, 遇到 \n 停止并丢弃, 
                 保存读取到的字符添加 \0 末尾   
    puts();      用于显式字符串, 并在末尾添加 \n            */
//-----------------------------------------------------------
#include <stdio.h>
#define SIZE 99
int main(void)
{
    char words[SIZE];
    puts("Enter a string, please.");
    gets(words);                // 输入
    printf("Your string twice:\n");
    printf("%s\n", words);      // %s 输出  
    puts(words);                // puts 输出 
    puts("Done.");
    return 0;
}
/*
    Enter a string, please.
    HelloWorld
    Your string twice:
    HelloWorld
    HelloWorld
    Done.
*/
```

> gets() 方法的局限性

- gets() 唯一参数是 char[], 它无法检测数组是否装得下输入行, gets 函数只知道数组的开始处, 如果输入的字符串过长, 会导致缓冲区溢出 (buffer overflow),

- 溢出的字符超出了指定的目标空间, 如果仅是占用了尚未使用的内存, 不会立即出现问题, 但如果擦除了程序中的其他程序, 会导致程序异常中止

- 在 UNIX 系统中, 使用 gets() 函数 可能会提示 “Segmentation fault” 分段错误, 说明程序试图访问未分配的内存

- gets() 函数存在一定的安全隐患, 恶意写入可能会导致系统安全破坏, 在 C11 标准之后被废除, 但一些编译器仍能继续支持 gets() 函数

---
### 2.3 fgets() 与 fputs() 

- fgets() 函数通过第 2 个参数限制读入的字符数来解决 gets() 溢出的问题。该函数专门设计用于处理文件输入

- fputs() 与 fgets() 配对使用, 用于将字符串输出写入到文件

- fgets 函数可以正常读取换行符, 

```c
/*
	fgets(char[], sizeLimit, File)	表示输入字符串
		char[]			用于接收字符串
		sizeLimit		指明了读入字符的最大数量
		File			指明要读入的文件, 读入键盘输入以 stdin 
                        (标准输入) 作为参数

	fputs(string, File)		表示输出字符串
		string			输出的字符串
		File			指明要写入的文件, 显示在终端, 使用 stdout 
                        (标准输出) 作为参数
*/
#include <stdio.h>
#define STLEN 14
int main(void)
{
	char words[STLEN];
	puts("Enter a string, please.");

	fgets(words, STLEN, stdin);
	printf("Your string twice (puts(), then fputs()) :\n");
	puts(words);			// puts 输出
	fputs(words, stdout);	// fputs 输出

	puts("Enter another string, please.");
	fgets(words, STLEN, stdin);
	printf("Your string twice (puts(), then fputs()) :\n");
	puts(words);			// puts 输出
	fputs(words, stdout);	// fputs 输出
	puts("Done.");
	return 0;
}
/*
	Enter a string, please.
	apple pie
	Your string twice (puts(), then fputs()):
	apple pie
	apple pie
	Enter another string, please.
	strawberry shortcake
	Your string twice (puts(), then fputs()):
	strawberry sh
	strawberry shDone.      // fputs 不会末尾自动添加 '\n'
*/
```

> 常见情况

- 输入的字符串超过 fgets(size) 的限制时, fgets() 会读入 size-1 个字符, 或者读取到第一个换行符为止, 并且将换行符储存在字符串中

- fputs 会将 fgets 的内容输出, 不会像 puts 函数那样在字符串的末尾添加换行符

> 循环读取文件并输出

- fputs 函数返回指向 char 的指针, 当函数读取到文件末尾时, 会返回一个空指针 (null pointer), C 语言中用 NULL 来代替

```c
#include <stdio.h>
#define STLEN 10
int main(void)
{
	char words[STLEN];
	puts("Enter strings (empty line to quit):");

	while (fgets(words, STLEN, stdin) != NULL && words[0] != '\n')
		fputs(words, stdout);
	puts("Done.");
	return 0;
}
/*
	Enter strings (empty line to quit):
	aaaaaaaaaaaaaabbbbbbbbbbbbccccccccccc ccccccc
	aaaaaaaaaaaaaabbbbbbbbbbbbccccccccccc ccccccc
	Done.
*/
```

- 虽然限制每次读取字符串时的最大限制是 10 个字节, 但不影响完整文件的读取

- 若要使该程序读取输入行，删除储存在字符串中的换行符，如果没有换行符，则丢弃数组装不下的字符，可以使用 getchar() 检查字符串读取是否到换行符 (检测是否读取到空行, 防止漏行未读到文件的末尾) 

- 案例：fgets 获取输入的字符串，丢弃输入行的超出字符

```c
#include <stdio.h>
#define STLEN 10
int main(void)
{
	char words[STLEN];
	int i;
	puts("Enter strings (empty line to quit):");
	while (fgets(words, STLEN, stdin) != NULL && words[0] != '\n') {
		i = 0;
		// 逐字符检查数组内是否有 '\n' 换行符, 且不包含空字符
		while (words[i] != '\n' && words[i] != '\0')    
			i++;
		// 替换掉换行符
		if (words[i] == '\n')
			words[i] = '\0';	
		// 如果 word[i] == '\0'则执行这部分代码
		else   
		{
			while (getchar() != '\n')
				continue;
		}
		puts(words);
	}
	puts("done");
	return 0;
}
```


> 空字符与空指针

- '\0' 整型: 数值为 0, 占 1 个字节
- NULL 指针类型: 数值用 0 表示, 占 4 个字节

---
### 2.4 gets_s() 

- C 库可选拓展方法

* gets_s (char* _Buffer, rsize_t _Size)
  - _Buffer     储存读取到的字符串缓冲
  - _Size       单次读取输入缓冲区字符数目的大小限制

- gets_s 只从标准输入中读取数据, 读取到换行符时, 会将其丢弃不会像 fgets 储存它

* gets_s 读取到最大字符数时都没读到换行符时
  - 首先，把目标数组中的首字符设置为空字符，读取并丢弃随后的输入直至读到换行符或文件结尾，然后返回空指针
  - 接着，调用依赖实现的“处理函数”（或你选择的其他函数），可能会中止或退出程序

```c
int main(void) {
	char arr[50];
	gets_s(arr, 20);
	puts(arr);
}
// 输入的字符串溢出 size 时会, 引发程序错误
```

---
### 2.5 自定义 s_gets()

- 读取整行输入并用空字符代替换行符，或者读取一部分输入，并丢弃其余部分
- 组合使用 fgets 与 getchar 

```c
/// <summary>
/// 读取字符串行
/// </summary>
/// <param name="st">传入字符串</param>
/// <param name="n">读取限制</param>
/// <returns>返回读取片段</returns>
char* s_gets(char* st, int n)
{
	char* ret_val;
	int i = 0;
	ret_val = fgets(st, n, stdin);
	if (ret_val)		// 即，ret_val != NULL
	{
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	} return ret_val;
}
```

---
### 2.6 scanf 函数

* scanf() 和gets() 或 fgets() 的区别在于它们如何确定字符串的末尾：
  - scanf() 更像是 “获取单词” 函数，而不是 “获取字符串” 函数
  - gets() 和 fgets() 会读取第 1 个换行符之前所有的字符

```c
#include <stdio.h>
int main(void)
{
	char name1[11], name2[11];
	int count;
	printf("Please enter 2 names.\n");
	count = scanf("%5s %10s", name1, name2);
	printf("I read the %d names %s and %s.\n",
		count, name1, name2); return 0;
}
/*
    Please enter 2 names.
  >> Jesse Jukes
    I read the 2 names Jesse and Jukes.
    
    Please enter 2 names.
  >> Liza Applebottham
    I read the 2 names Liza and Applebotth.
    
    Please enter 2 names.
  >> Portensia Callowit
    I read the 2 names Porte and nsia.
*/
```

> scanf, gets, fgets

- 根据输入数据的性质，用 fgets() 读取从键盘输入的数据更合适

- scanf() 的典型用法是读取并转换混合数据类型为某种标准形式

- scanf()和gets()类似, 存在输入行内容溢出的情况，%s 转换时使用字段宽度可防止溢出

---
## 3. 字符串输出

- C 有 3 个标准库函数用于打印字符串：put()、fputs() 和 printf()。

---
### 3.1 puts 函数

* puts(char const* _Buffer)   输出 char 指针类型
  - puts() 在显示字符串时会自动在其末尾添加一个换行符
  - puts 函数在遇到空字符时就停止输出，所以必须确保有空字符
  
- 应避免使用 puts 函数读取非字符串格式的 char[]，因为该 char[] 并未有一个空字符标记字符串的结束，因此 puts 读取内存时会一直打印后面的内容，直到遇到空字符

---
### 3.2 fputs 函数

- fputs() 函数是 puts() 针对文件定制的版本

* 主要与 puts 的区别是
  - fputs() 函数的第 2 个参数指明要写入数据的文件。如果要打印在显示器上，可以用定义在 stdio.h 中的 stdout（标准输出）作为该参数。
  - 与puts()不同，fputs()不会在输出的末尾添加换行符

- gets 丢弃输入中的换行符，puts 在输出中添加换行符；fgets 保留输入中的换行符，fputs 不在输出中添加换行符

> 循环读写举例

```c
char line[81];
while (fgets(line, 81, stdin))
    fputs(line, stdout);
// fgets 读取到空指针时(即文件末尾), 便可结束循环
```

---
### 3.3 printf 函数

- 与 puts() 不同的是，printf() 不会自动在每个字符串末尾加上一个换行符

- printf("%s\n", string) 与 puts(string) 效果相同, 
  
- printf 的形式多种多样, 但它的执行时间要长一些

- 一般使用 printf 打印自定义组合字符串

---
## 4. 自定义输入与输出函数

- 我们可以在 getchar 与 putchar 的基础上自定义所需的函数

> 打印字符串, 不添加换行符

```c
    void m_put_1(const char* str){
        while(*str)
            putchar(*str++)
    }
```

> 打印一个字符串，并统计打印的字符数 (输出自动换行)

```c
size_t m_put_2(const char* str) {
    size_t count = 0;
    while (*str) {
        count++;
        putchar(*str++);
    }
    putchar('\n');
    return count;
}
```

---
## 5. 字符串函数

- string.h 中常用的函数有 strlen()、strcat()、strcmp()、strncmp()、strcpy() 和 strncpy()

- stdio.h 中有 sprintf()

### 5.1 strlen 统计字符串长度

- strlen 用于统计字符串的长度，可以使用这个特点缩短字符串的长度（需要传入的字符串没有 const 修饰）

```c
void fit(char* str, unsigned size){
    if(strlen(str)>size)
        str[size] = '\0';
}
```

---
### 5.2 strcat 拼接字符串

- strcat()（用于拼接字符串）函数接受两个字符串作为参数。该函数把第 2 个字符串的备份附加在第 1 个字符串末尾，并把拼接后形成的新字符串作为第 1 个字符串，第 2 个字符串不变

- strcat() 函数返回第 1 个参数，即拼接第 2 个字符串后的第 1 个字符串的地址，拼接后的字符串不应超过第 1 个参数的最大容量（防止缓冲区溢出）

- strcat() 函数无法检查第 1 个数组是否能容纳第 2 个字符串，超过的字符溢出到相邻存储单元时就会出问题。

```c
/*
    strcat(char* str1, char* str2)   
            将 str2 拼接到 str1， 受 str1 大小限制
*/
#include<stdio.h>
#include<string.h>
int main(void) {
    char Str[20] = "hello";
    char str[] = " world";
   
    printf("Str address: %p\n"
        "Str value: %s\n"
        ">> use strcat(Str,str) <<\n", Str, Str);
    
    strcat(Str, str);
    printf("new Str address: %p\n"
        "Str value: %s", Str, Str);
}
/*
    Str address: 0136F808
    Str value: hello
    >> use strcat(Str,str) <<
    new Str address: 0136F808
    Str value: hello world
*/
```

---
### 5.3 strncat 拼接指定字符数目

- strcat() 函数无法检查第 1 个数组是否能容纳第 2 个字符串

- 用strncat()，该函数的第 3 个参数指定了最大添加字符数。

```c
/*
    strncat(char* str1,char* str2,size) 
        将 str2 拼接到 str1，在加到第 size 个字符或遇到空字符时停止
*/
    char str[20] = "First";
    strncat(str, " ADD STRING", 4);  
        // >>  "First ADD"
```

---
### 5.4 strcmp 比较字符串

* strcmp(str1,str2) 比较储存在不同大小数组中的字符串是否相同：
  - 0 表示字符串字面量相等
  - 假设字符串 str1[n] 之前的字符都相同，如果 str1[n] > str2[n]，函数返回 1，str1[n] < str2[n] 返回 -1

- strcmp() 函数比较字符串中的字符，直到发现不同的字符为止，这一过程可能会持续到字符串的末尾

```c
    strcmp("abc","abc") = 0;
    strcmp("abb","abc") = -1;
    strcmp("abc","abb") = 1;
```

---
### 5.5 strncmp 

- strncmp() 函数在比较两个字符串时，可以比较到字符不同的地方，也可以只比较第 3 个参数指定的字符数

```c
    strncmp("aaaaa","aaa",3) = 0;
```

---
### 5.6 strcpy 和 strncpy

- strcpy 与 strncpy 表示拷贝整个字符串
- 指针相等只是将字符串的地址复制, 不会产生字符串的副本

```c
    char words[20];
    strcpy(words,"HelloWorld");     // 注意字符串可接受大小
    strcpy(words,"HelloWorld",5);   // 限定复制字符的数量
```

- strcpy 可以用于字符串赋值, 返回类型是字符串首元素的地址

```c
    char target[20];
    int x;
    x = 50; /* 数字赋值*/
    
    strcpy(target, "Hi ho!");   /* 字符串赋值*/
    target = "So long";         /* 语法错误 */

    char str[] = "Hello World";
    char* P = strcpy(str+6,"WORLD");
    puts(P);
    puts(str)
```

- 可以指定从字符串的第 N 个元素开始拷贝, 从该位置开始复制第二个字符串

```c
    char str[] = "Hello world";
    char *P = strcpy(&str[6], "W"); //自 str[6] 字符开始拷贝 "W"
    printf("%p\n", P);        // 返回第一个参数首元素的地址
    printf("%p\n", &str[6]);      
    puts(str);

/*  0061FF16
    0061FF16
    Hello W
*/
```

- strncpy() 该函数的第 3 个参数指明可拷贝的最大字符数。

---
### 5.7 sprintf 

- sprintf  函数和 printf() 类似，但是它是把数据写入字符串

- sprintf()的第 1 个参数是目标字符串的地址。其余参数和 printf() 相同，即格式字符串和待写入项的列表

- sprintf() 的用法和 printf() 相同，只不过 sprintf() 把组合后的字符串储存在数组

- 该函数仍然存在数组缓冲溢出的可能, 所以要保证写入数组的字符串要比分配的空间小

---
### 5.8 其他字符串函数

```
1. char* strcpy(char* restrict s1, const char* restrict s2);
        >>> 把 s2 指向的字符串（包括空字符）拷贝至 s1 指向的位置，返回值 s1。

2. char* strncpy(char* restrict s1, const char* restrict s2, size_t n);
        >>> 把 s2 指向的字符串拷贝至 s1 指向的位置，拷贝的字符数不超过 n，其返回值是 s1

3. char* strcat(char* restrict s1, const char* restrict s2);
        >>> 把 s2 指向的字符串拷贝至 s1 指向的字符串末尾。s2 字符串
的第 1 个字符将覆盖 s1 字符串末尾的空字符。该函数返回 s1。

4. char* strncat(char* restrict s1, const char* restrict s2, size_t n);
        >>> 把 s2 字符串中的 n(或 s2 长度小于 n)个字符拷贝至 s1 字符串末尾。

5. int strcmp(const char* s1, const char* s2);
        >>> 如果两个字符串相等，则返回 0，不等时根据相对先后位置返回 1 或 -1

6. int strncmp(const char* s1, const char* s2, size_t n);
        >>> 在比较 n 个字符后或遇到第 1 个空字符时停止比较

7. char* strchr(const char* s, int c);
        >>> 如果 s 字符串中包含 c 字符，该函数返回指向 s 字符串首位置的指针，未找到返回空指针

8. char* strpbrk(const char* s1, const char* s2);
        >>> 若 s1 中包含 s2 中任意字符，返回 s1，否则返回空指针

9. char* strrchr(const char* s, int c);
        >>> 该函数返回 s 字符串中 c 字符的最后一次出现的位置，否则返回空指针

10. char* strstr(const char* s1, const char* s2);
        >>> 该函数返回指向 s1 字符串中 s2 字符串出现的首位置, 否则返回空

11. size_t strlen(const char* s);
        >>> 返回s字符串中的字符数，不包括末尾的空字符。
```

- 那些使用 const 关键字的函数原型表明，函数不会更改字符串

---
## 6. 字符串排序

