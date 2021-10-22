# C Plus 文件的输入与输出

- 函数：fopen()、getc()、putc()、exit()、fclose()、fprintf()、fscanf()、fgets()、fputs()
- rewind()、fseek()、ftell()、fflush()、fgetpos()、fsetpos()、feof()、ferror()、ungetc()、setvbuf()、fread()、fwrite()
- 使用 C 标准 I/O 系列的函数处理文件
- 文件模式和二进制模式、文本和二进制格式、缓冲和无缓冲 I/O

---
- [C Plus 文件的输入与输出](#c-plus-文件的输入与输出)
	- [1. 与文件进行通信](#1-与文件进行通信)
		- [1.1 文件](#11-文件)
		- [1.2 文本模式与二进制模式](#12-文本模式与二进制模式)
		- [1.3 I/O 的级别](#13-io-的级别)
		- [1.4 标准文件](#14-标准文件)
	- [2. 标准 I/O](#2-标准-io)
		- [2.1 检查命令行参数](#21-检查命令行参数)
		- [2.2 fopen 函数](#22-fopen-函数)
		- [2.3 getc 与 putc 函数](#23-getc-与-putc-函数)
		- [2.4 文件结尾](#24-文件结尾)
		- [2.5 fclose 函数](#25-fclose-函数)
		- [2.6 指向标准文件的指针](#26-指向标准文件的指针)
	- [3. 一个简单的文件压缩过程](#3-一个简单的文件压缩过程)
	- [4. 文件 I/O 函数](#4-文件-io-函数)
		- [4.1 fprintf 和 fscanf, rewind 函数](#41-fprintf-和-fscanf-rewind-函数)
		- [4.2 fgets 和 fputs 函数](#42-fgets-和-fputs-函数)
	- [5. 随机访问: fseek 和 ftell 函数](#5-随机访问-fseek-和-ftell-函数)
		- [5.1 fseek 与ftell 的工作原理](#51-fseek-与ftell-的工作原理)
		- [5.2 二进制模式和文本模式](#52-二进制模式和文本模式)
		- [5.3 可移植性](#53-可移植性)
		- [5.4 fgetpos 与 fsetpos 函数](#54-fgetpos-与-fsetpos-函数)
	- [6. 标准 I/O 的机理](#6-标准-io-的机理)
	- [7. 其他标准 I/O 函数](#7-其他标准-io-函数)
		- [7.1 ungetc](#71-ungetc)
		- [7.2 fflush](#72-fflush)
		- [7.3 setvbuf](#73-setvbuf)
		- [7.4 二进制 I/O fread 与 fwrite](#74-二进制-io-fread-与-fwrite)
		- [7.5 feof 与 ferror](#75-feof-与-ferror)
		- [7.6 用二进制 I/O 进行随机访问](#76-用二进制-io-进行随机访问)

---
## 1. 与文件进行通信

- 程序从文件中读取信息或把信息写入文件，此交互的形式为文件重定向

---
### 1.1 文件

- 文件（file）通常是在磁盘或固态硬盘上的一段已命名的存储区，stdio.h 就是一个文件的名称

- 操作系统对于大型文件，会将它们分开储存，或包含一些额外的数据以方便确定文件的种类

- C 中把文件看作一串连续的字节，每个字节都可以被单独读取，C 提供两种文件模式，文本模式和二进制模式

---
### 1.2 文本模式与二进制模式

- 所有文件的内容都以二进制形式（0 或 1）储存。文件采用二进制编码的字符（ASCII 或 Unicode）表示文本即为文本文件；文件中的二进制代码表示机器语言代码或数值数据（使用相同的内部表示）或图片或音乐编码，该文件是二进制文件

- 在二进制模式中，程序可以访问文件的每个字节。

- 在文本模式中，程序所见的内容和文件的实际内容不同。程序以文本模式读取文件时，把本地环境表示的行末尾或文件结尾映射为 C 模式(表示以 \\n 表示换行)

- 不同系统读取文件时，C 模式与 UNIX 以换行符表示新的一行，早期的 OS X Macintosh 文件用回车符表示新的一行，而 MS-DOS 文件以 \\r\\n 表示新的一行
  
> 一个旧式 MS-DOS 文本文件, 以二进制模式读写文本时, 不会发生映射

```
                        二进制模式打开时, C 程序看到的内容
    First line\r\n      >>>>>>> First line\r\n  
    Second line\r\n             Second line\r\n           First line\n  
    Third line\r\n              Third line\r\n            Second line\n 
    ^Z                          ^Z                        Third line\n
                      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>      ^Z
    MS-DOS 文本文件         文本模式下, C 读取的内容
```

- 对于旧式 Mac 格式、MS-DOS 格式或 UNIX/Linux 格式的文件模式程序, 应使用二进制模式, C 程序才能确定实际文件的内容并执行相应的动作

---
### 1.3 I/O 的级别

* I/O 的两个级别（即处理文件访问的两个级别）
  - 底层 I/O（low-level I/O）使用操作系统提供的基本 I/O 服务
  - 标准高级 I/O（standard high-level I/O）使用 C 库的标准包和 stdio.h 头文件定义

- 由于不同的操作系统可能使用不同的底层 I/O 模式, 因此 C 标准只支持标准 I/O 包

---
### 1.4 标准文件

* C 程序会自动打开 3 个文件，它们被称为标准输入（standard input ） 、标准输出（ standard output ） 和标准错误输出（standard error output）。
  - 在默认情况下，标准输入是系统的普通输入设备，通常为键盘；
  - 标准输出和标准错误输出是系统的普通输出设备，通常为显示屏。

- 标准输入为程序提供输入，它是 getchar() 和 scanf() 使用的文件。程序通常输出到标准输出， 它是 putchar() 、puts() 和 printf() 使用的文件。标准错误输出提供了一个逻辑上不同的地方来发送错误消息。

- 重定向把其他文件视为标准输入或标准输出，重定向错误消息发送到文件，标准错误仍然会被发送到屏幕上

---
## 2. 标准 I/O

* 标准 I/O 包除了可移植以外还有两个好处。
  - 标准 I/O 有许多专门的函数简化了处理不同 I/O 的问题, printf 的转换说明
  - 输入和输出都是缓冲的，一次转移的是一大块信息而不是一字节信息

- 程序在读取文件时，一块数据被拷贝到缓冲区，利用缓冲可以极大地提高数据传输速率，程序检查缓冲区中的字节，而缓冲在后台处理

> 用标准 I/O 读取文件和统计文件中的字符数

```c
#include <stdio.h>
#include <stdlib.h> // 提供 exit()的原型
int main(int argc, char* argv[])
{
	int ch;		// 读取文件时，储存每个字符的地方
	FILE* fp;	// 文件指针
	unsigned long count = 0;
	// 1. 校验命令行参数数目
	if (argc != 2)	
	{
		printf("Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// 2. 尝试打开文件流
	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	// 3. 读取缓冲区的内容直至文件末尾, 并记录字符数目
	while ((ch = getc(fp)) != EOF)
	{
		putc(ch, stdout); // 与 putchar(ch); 相同
		count++;
	}
	fclose(fp);  // 关闭文件流 
	printf("File %s has %lu characters\n", argv[1], count);
	return 0;
}
```

---
### 2.1 检查命令行参数

- 程序检查 argc 的值，查看是否有命令行参数，字符串 argv\[0] 是该程序的名称。

- exit() 函数关闭所有打开的文件并结束程序，exit() 的参数被传递给一些操作系统，包括 UNIX、Linux、Windows 和 MS-DOS，以供其他程序使用（正常结束的程序传递 0，异常结束的程序传递非零值）。标准要求 0 或宏 EXIT_SUCCESS 用于表明成功结束程序，宏 EXIT_FAILURE 用于表明结束程序失败

- C 规定，在最初调用 main 中(非递归程序中调用 main)使用 return 与调用 exit(0) 效果相同

---
### 2.2 fopen 函数

- 程序使用 fopen() 函数打开文件, 打开成功后返回文件指针, 其他 I/O 函数可以使用这个指针指定该文件, 该指针并不指向实际的文件, 指向一个包含文件信息的数据对象, 包括操作文件的 I/O 函数所用的缓冲区信息

```
    fopen(char const* _FileName, char const* _Mode);
     >> FileName 打开的文件名称, 包括文件所在路径
     >> Mode 待打开文件的模式
----------------------------------------------------
    "r"         以读模式打开文件
    "w"         以写模式, 现有文件的长度截为 0, 文件不存在则创建新文件
    "a"         以写模式, 在现有文件末尾添加内容, 文件不存在则创建
    "r+"        以更新模式打开文件, 可读可写
    "w+"        可读可写, 现有文件的长度截为 0, 不存在时创建
    "a+"        可读可写, 在现有文件末尾添加内容, 文件不存在时创建, 只能从末尾添加内容
    
    以上模式添加'b'后缀         表示以二进制模式而不是文本模式打开文件
    wx,wbx,w+x,wb+x,w+bx      (C11)如果文件已存在或以独占模式打开文件, 则打开文件失败
```

- UNIX 和 Linux 这样只有一种文件类型的系统，带 b 字母的模式和不带 b 字母的模式相同

* C11 新增的 x 写模式, 与传统的 w 或 wb 写模式新增了一些特性:
  - 以传统的一种写模式打开一个现有文件，fopen() 会把该文件的长度截为 0，这样就丢失了该文件的内容。但是使用带 x 字母的写模式，即使 fopen() 操作失败，原文件的内容也不会被删除。
  - 如果环境允许，x 模式的独占特性使得其他程序或线程无法访问正在被打开的文件


---
### 2.3 getc 与 putc 函数

- getc() 和 putc() 函数与 getchar() 和 putchar() 函数类似, 但是需要指定函数使用的是哪一个文件

```c
    getc(File* _Stream);
    putc(int charactor, File* _Stream);
    // File* 参数 stdin 表示从标准输入读取, stdout 表示输出到标准输出
```

---
### 2.4 文件结尾

- 从文件中读取数据的程序要在读到文件结尾时停止, 定义在 stdio 的宏 EOF 表示程序读取到了文件的结尾

- 可以用入口条件循环验证文件输入, getc(fp) != EOF 验证是否读取到文件末尾, 以防止程序读到空文件

```c
int ch;
FILE * fp;
fp = fopen("file.txt", "r");
while (( ch = getc(fp)) != EOF)
{
    putchar(ch); //处理输入
}
```

---
### 2.5 fclose 函数

- fclose(fp) 函数关闭 fp 指定的文件，必要时刷新缓冲区，关闭成功返回 0，否则返回 EOF。

- 若磁盘已满、移动硬盘或移除或出现 I/O 错误，都会导致调用 fclose 函数失败

---
### 2.6 指向标准文件的指针

- stdio.h 头文件把 3 个文件指针与 3 个标准文件相关联，C 程序会自动打开这 3 个标准文件

```
    标准输入 >>> stdio >>> 通常为键盘等
    标准输出 >>> stdout >>> 显示器
    标准错误 >>> stderr >>> 显示器
```

---
## 3. 一个简单的文件压缩过程

- 示例把一个 r 模式文件中选定的数据拷贝到另一个 w 模式文件中

- 该程序以保留每 3 个字符中的第 1 个字符的方式压缩第 1 个文件的内容。最后，把压缩后的文本存入第 2 个文件

```c
#include <stdio.h>
#include <stdlib.h> // 提供 exit()的原型
#include <string.h> // 提供 strcpy()、strcat()的原型
#define LEN 40
int main(int argc, char* argv[])
{
	FILE* in, * out; // 声明两个指向 FILE 的指针
	int ch;
	char name[LEN]; // 储存输出文件名
	int count = 0;
	// 1. 检查命令行参数
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// 2. 设置输入
	if ((in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "I couldn't open the file \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	// 3. 设置输出
	strncpy(name, argv[1], LEN - 5); // 拷贝文件名
	name[LEN - 5] = '\0';
	strcat(name, ".red");			 // 在文件名后添加.red
	// 4. 以写模式打开文件
	if ((out = fopen(name, "w")) == NULL)
	{	
		fprintf(stderr, "Can't create output file.\n");
		exit(3);
	}
	// 5. 拷贝数据
	while ((ch = getc(in)) != EOF)
		if (count++ % 3 == 0)
			putc(ch, out);			// 打印 3 个字符中的第 1 个字符
	// 6. 收尾工作
	if (fclose(in) != 0 || fclose(out) != 0)
		fprintf(stderr, "Error in closing files\n");
	return 0;
}
```

---
## 4. 文件 I/O 函数

### 4.1 fprintf 和 fscanf, rewind 函数

- 文件 I/O 函数要用 FILE 指针指定待处理的文件

```c
    printf(char const* const _Format, ...);
    fprintf(FILE* _Stream, char const* const _Format, ...);
    // _Stream 需要指定待处理的文件

    scanf(char const* const _Format, ...);
    fscanf(FILE* const _Stream, char const* const _Format, ...);
    // _Stream 需要指定待处理的文件
```

> rewind 函数

- rewind 函数让程序回到文件开始处, 该文件必须开启可读模式

> 演示了这两个文件 I/O 函数和 rewind 函数的用法

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41
int main(void)
{
	FILE* fp;
	char words[MAX];
    // 1. 打开文件或创建
	if ((fp = fopen("wordy", "a+")) == NULL)
	{
		fprintf(stdout, "Can't open \"wordy\" file.\n");
		exit(EXIT_FAILURE);
	}
	puts("Enter words to add to the file; press the #");
	puts("key at the beginning of a line to terminate.");
    // 2. 标准输入字符串 # 行退出
	while((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))
		fprintf(fp, "%s\n", words);     // 将输入写入文件缓冲流
	puts("File contents:");
	rewind(fp);		                    /* 返回到文件开始处 */ 
	// 3. 读取文件中的内容
    while (fscanf(fp, "%s", words) == 1)    
		puts(words);
	puts("Done!");
    // 4. 关闭文件流
	if (fclose(fp) != 0)
		fprintf(stderr, "Error closing file\n");
	return 0;
}
```

---
### 4.2 fgets 和 fputs 函数

- fgets 保留了换行符, fputs 输出时不会再添加换行符

```c
    gets(char* _Buffer);
    gets_s(char* _Buffer, rsize_t _Size);
    fgets(char* _Buffer, int _MaxCount, FILE* _Stream);
    // _Buffer 表示储存输入位置的地址
    // _MaxCount 表示待输入字符串的大小
    // _Stream  文件指针，指定待读取的文件
    puts(char* _Buffer);
    fputs(char* _Buffer, FILE* _Stream);
```

---
## 5. 随机访问: fseek 和 ftell 函数

- fseek() 函数，把文件看作是数组，在 fopen() 打开的文件中直接移动到任意字节处。
  
- fseek() 有 3 个参数，返回 int 类型的值；ftell() 函数返回一个 long 类型的值，表示文件中的当前位置。

> 输出一个文件中的内容(倒序)

```c
#include <stdio.h>
#include <stdlib.h>
#define CNTL_Z '\032' /* DOS文本文件中的文件结尾标记 */
#define SLEN 81
int main(void)
{
    char file[SLEN];
    char ch;
    FILE *fp;
    long count, last;

    puts("Enter the name of the file to be processed:");
    scanf("%80s", file);
    if ((fp = fopen(file, "rb")) == NULL)   /* 只读模式 */
    { 
        printf("reverse can't open %s\n", file);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END);                /* 定位到文件末尾 */
    last = ftell(fp);
    for (count = 1L; count <= last; count++)
    {
        fseek(fp, -count, SEEK_END);        /* 回退 */
        ch = getc(fp);
        if (ch != CNTL_Z && ch != '\r')     /* MS-DOS 文件 */
            putchar(ch);
    }
    putchar('\n');
    fclose(fp);
    return 0;
}
```

- 之后讨论 fseek() 和 ftell() 函数的工作原理、如何使用二进制流、如何让程序可移植

---
### 5.1 fseek 与ftell 的工作原理

> fseek

```
    int fseek(FILE* _Stream, long _Offset, int _Origin);

    1. _Stream 指向待查找的文件，fopen() 应该已打开该文件
    2. _Offset 偏移量表示从起始点开始要移动的距离, 正数前移, 负数后移, 0 不动
    3. _Origin 起始模式, 该参数确定起始点
         SEEK_SET(== 0L) 表示文件开始处 
         SEEK_CUR(== 1L) 表示当前位置
         SEEK_END(== 2L) 表示文件末尾 

    # 演示
    fseek(fp, 0L, SEEK_SET);    // 定位至文件开始处
    fseek(fp, 10L, SEEK_SET);   // 定位至文件中的第10个字节
    fseek(fp, 2L, SEEK_CUR);    // 从文件当前位置前移2个字节
    fseek(fp, 0L, SEEK_END);    // 定位至文件结尾
    fseek(fp, -10L, SEEK_END);  // 从文件结尾处回退10个字节
```

- 如果一切正常，fseek() 的返回值为 0；如果出现错误（如试图移动的距离超出文件的范围），其返回值为 -1

> ftell

- ftell() 函数的返回类型是 long，它返回的是当前的位置, 第 N 个字节到开始处的字节数确定文件的位置 (该定义适用于以二进制模式打开的文件)

---
### 5.2 二进制模式和文本模式

- 随机访问的案例在 UNIX 和 MS-DOS 环境下均可运行

- UNIX 仅有一种文件格式, 不需要特殊转换

- MS-DOS 使用 Ctrl+Z 标记文本文件的结尾, C 以文本模式打开时能够识别到该文件末尾; 但当以二进制模式打开时, C 将 Ctrl+Z 当作文件中的一个字符, 实际的文件结尾符在其之后(可能是空字符填充, 在 DOS 环境中不会打印空字符)

* 二进制模式和文本模式的不同之处: 
  - MS-DOS 用 \\r\\n 组合表示文本文件换行。以文本模式打开相同的文件时，C 程序把 \\r\\n 看成 \\n
  - 二进制模式下, C 程序可以看到 \\r\\n, 随机访问的案例中包含了不打印 \\r 与 Ctrl_Z 字符的代码

- ftell 函数在文本模式与二进制模式中的工作方式不同, 对于文本模式，ftell() 返回的值可以作为 fseek() 的第 2 个参数

- 对于 MS-DOS，ftell() 返回的值把 \\r\\n 当作一个字节计数。

---
### 5.3 可移植性

- fseek() 和 ftell() 应该符合 UNIX 模型, 在二进制模式中，实现不必支持 SEEK_END 模式

- 在文本模式中，只有以下调用能保证其相应的行为

```
    fseek(fp, 0L, SEEK_SET);    // 定位至文件开始处
    fseek(fp, 0L, SEEK_CUR);    // 保持在当前位置不懂
    fseek(fp, 0L, SEEK_END);    // 定位至文件结尾
    fseek(fp, ftell-pos, SEEK_SET);   
    // 到距文件开始处 ftell-pos 的位置, ftell-pos 是 ftell() 的返回值
```

---
### 5.4 fgetpos 与 fsetpos 函数

- fseek()和 ftell()潜在的问题是，它们都把文件大小限制在 long 类型能表示的范围内。但不满足大型文件的需求

- ANSI C 新增了两个处理较大文件的新定位函数：fgetpos() 和 fsetpos()。不使用 long 类型的值表示位置, 采用类型为 fpos_t (file position type, 文件定位类型) 
  
- fpos_t 类型的变量或数据对象可以在文件中指定一个位置，它不能是数组类型, 除此之外，没有其他限制

- 实现可以提供一个满足特殊平台要求的类型，例如，fpos_t可以实现为结构。

```c
    int fgetpos(FILE * restrict stream, fpos_t * restrict pos);
    >>> 把 fpos_t 类型的值放在 pos 指向的位置上，该值描述了文件中的一个位置。
    >>> 如果成功，fgetpos() 函数返回 0；如果失败，返回非 0

    int fsetpos(FILE *stream, const fpos_t *pos);
    >>> 使用 pos 指向位置上的 fpos_t 类型值来设置文件指针指向该值指定的位置。
    >>> 如果成功，fsetpos() 函数返回 0；如果失败，则返回非 0
```

---
## 6. 标准 I/O 的机理

> 第一步  fopen

- 调用 fopen 函数打开文件, C 程序会自动打开三种标准文件, fopen 不仅打开一个文件同时会创建一个缓冲区 (在读写模式下会创建两个缓冲区) 以及一个包含文件和缓冲区数据的结构

- fopen 会返回一个指向该结构的指针 (fopen 函数打开一个流, 文本流或二进制流), 这个结构通常包含一个指定流中当前位置的文件位置指示器, 还包含错误和文件结尾的指示器、一个指向缓冲区开始处的指针、一个文件标识符和一个计数（统计实际拷贝进缓冲区的字节数）。

> 第二步  fp 指向

- 调用定义在 stdio.h 的输入函数 (如 fscanf, getc, fgets), 调用这些函数时, 文件中的数据块就被拷贝到缓冲区, 缓冲区的大小一般是 512 字节或是它的倍数

- 最初调用输入函数时, 一般需要设置 fp 指针所指的结构中的值 (设置流中的当前位置和拷贝进缓冲区的字节数, 一般从字节 0 开始)

> 第三步 输入函数

- 输入函数按要求从缓冲区读取数据, 文件位置指示器被设置为指向刚读取字符的下位字符, 所有的输入函数都是用相同的缓冲区, 任意一个输入函数被调用都将从上一个函数停止调用的位置开始

- 缓冲区读取结束时, 函数会请求把下一块缓冲大小的数据块从文件拷贝到缓冲区, 循环该行为直至输入函数可以读取到文件的所有内容, 直至文件末尾, 返回 EOF

> 第四步 输出函数

- 输出函数以类似输入读取文件的方式把数据写入缓冲区, 缓冲区填满时将数据拷贝到文件

> 第五步 fclose

- 调用 fclose 关闭缓冲区与文件, 释放流占用的资源

---
## 7. 其他标准 I/O 函数

### 7.1 ungetc

- ungetc() 函数把 c 指定的字符放回输入流中, 下一次输入函数读入的字符定位到最后放回的字符位置

```c
	int ungetc(int c, FILE *fp);
	>>>  c		将 c 指定的字符放回输入流中
	
	ch = getc(fp);
	ungetc(ch,fp);
```

> 读取内容但不包括 >>冒号<<

```c
int main(void)
{
	char ch;
	while ((ch = getchar()) != 0 && ch != EOF)
	{
		if (ch == ':')
		{
			ungetc(':',stdout);
			ch = getchar();		// 下次循环时跳过 : 字符, 此时 ch = ':'
			continue;
		}
		putc(ch,stdout);
	}
}
```

---
### 7.2 fflush 

- 调用 fflush() 函数引起输出缓冲区中所有的未写入数据被发送到 fp 指定的输出文件, 在输出操作时调用, 此过程为刷新缓冲区

- fp 为空指针时, 所有缓冲区都被刷新

- 在输入流中使用 fflush 函数效果是未定义的, 只要最近一次操作不是输入操作, 就可以调用 fflush 更新流

```c
	int fflush(FILE *fp);
```

---
### 7.3 setvbuf

- setvbuf() 函数创建了一个供标准 I/O 函数替换使用的缓冲区, 在打开文件后且没有对流进行其他操作之前调用该函数

- setvbuf 主要用于指定缓冲区的地址与大小, 指针 fp 识别待处理的流，buf 指向待使用的存储区, 若 buf 的值非 NULL, 则必须创建一个缓冲区

```c
	int setvbuf(FILE * restrict fp, 	// 待处理的流
				char * restrict buf, 	// 待使用的缓冲区
				int mode,				// 缓冲模式
				size_t size)			// 数据类型数组的大小
	>>> buf
		可以传递 NULL, 函数会为自己分配一个缓冲区

	>>> mode
		_IOFBF		完全缓冲(在缓冲区满时刷新)
		_IOLBF		行缓冲(在缓冲区满时或写入一个换行符时)
		_IONBF		无缓冲

	>>> size
		缓冲区大小, 若每个数据对象的大小是 300 字节, 则它的大小应是该数据对象大小的倍数
```

---
### 7.4 二进制 I/O fread 与 fwrite

- 之前用到的标准 I/O 函数都是面向文本的, 在处理数值转换说明的时候, 存在大小空间的变动, 例如, fprintf 把数值转换成字符数据, 这种转换可能会改变值

- 为保证数值在储存前后一致，最精确的做法是使用与计算机相同的位组合来储存

- 保存数据时若以程序所用到的表示法把数据储存在文件中, 则会以二进制形式储存数据,不存在从数值形式到字符串的转换过程, 可以保护相关数据精度不被丢失

- fread 与 fwrite 用于以二进制形式处理数据, 实际上，所有的数据都是以二进制形式储存的，甚至连字符都以字符码的二进制表示来储存

```c
	// fwrite
	size_t fwrite(void const* _Buffer,		// 待处理的流
		   	size_t _ElementSize,			// 待写入数据块的大小
			size_t _ElementCount,			// 待写入数据块的数量
			FILE* restrict _Stream)			// 待写入的文件
		return	返回成功写入项的数目	
	>>> 要保存一个内含 10 个 double 类型值的数组
	double earnings[10];
	fwrite(earnings, sizeof(double), 10, fp);

	// fread
	size_t fread(void* restrict _Buffer,	// 待接收读取的数据的块的地址
			size_t _ElementSize,			// 待读取数据块的大小
			size_t _ElementCount,			// 待读取数据块的数量
			FILE* restrict _Stream)			// 待读取的文件
		return	返回实际读取到的数目
	>>> 把 10 个 double 大小的值拷贝进 earnings 数组中
	double earnings[10];
	fread(earnings, sizeof (double), 10, fp);
```

> 二进制输出和文本输出

```c

	int num = 12345;	
	>>> 以二进制数把 1234 储存在 num 中
		___00110000_00111001___
	// 1. 文本输出模式
	fprintf(fp,"%d",num);
	>>> 把 '1'、'2'、'3'、'4'、'5' 的二进制码写入文件
	    ___00110001_00110010_00110011_00110100_00110101___
	//--------------------------------------------------------
	// 2. 二进制输出
	fwrite(&num, sizeof(int), 1, fp);
	>>> 把值 12345 的二进制写入文件
		___00110000_00111001___
```

- 一般而言，用二进制模式在二进制格式文件中储存二进制数据

---
### 7.5 feof 与 ferror

- 如果标准输入函数返回 EOF，则通常表明函数已到达文件结尾。

- 然而，出现读取错误时，函数也会返回 EOF。feof() 和 ferror() 函数用于区分这两种情况

```c
	int feof(FILE *fp);		
	// 当上一次输入调用检测到文件结尾时, 返回一个非 0 值, 否则返回 0

	int ferror(FILE *fp);
	// 当读或写出现错误，ferror() 函数返回一个非零值，否则返回 0。
```

---
### 7.6 用二进制 I/O 进行随机访问

```c
#include <stdio.h>
#include <stdlib.h>
#define ARSIZE 1000
int main()
{
	double numbers[ARSIZE];
	double value;
	const char *file = "numbers.dat";
	int i;
	long pos;
	FILE *iofile;
	// 1. 创建一组 double 类型的值
	for (i = 0; i < ARSIZE; i++)
		numbers[i] = 100.0 * i + 1.0 / (i + 1);
	// 2. 尝试打开文件 (二进制写入模式)
	if ((iofile = fopen(file, "wb")) == NULL)
	{
		fprintf(stderr, "Could not open %s for output.\n", file);
		exit(EXIT_FAILURE);
	}
	// 3. 以二进制格式把数组写入文件
	fwrite(numbers, sizeof(double), ARSIZE, iofile);
	fclose(iofile);
	if ((iofile = fopen(file, "rb")) == NULL)	// 二进制只读模式
	{
		fprintf(stderr, "Could not open %s for random access.\n", file);
		exit(EXIT_FAILURE);
	}
	// 4. 从文件中读取选定的内容
	printf("Enter an index in the range 0-%d.\n", ARSIZE - 1);
	while (scanf("%d", &i) == 1 && i >= 0 && i < ARSIZE)
	{
		pos = (long)i * sizeof(double); // 计算偏移量
		fseek(iofile, pos, SEEK_SET);	// 定位到此处
		fread(&value, sizeof(double), 1, iofile);	// 二进制写入 value
		printf("The value there is %f.\n", value);
		printf("Next index (out of range to quit):\n");
	}
	// 5. 完成
	fclose(iofile);
	puts("Bye!");
	return 0;
}
```

---