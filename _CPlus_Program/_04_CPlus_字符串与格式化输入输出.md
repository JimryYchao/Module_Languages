# C Plus 字符串与字符串格式化输入/输出

---
- [C Plus 字符串与字符串格式化输入/输出](#c-plus-字符串与字符串格式化输入输出)
  - [1. 前导案例](#1-前导案例)
  - [2. 字符串](#2-字符串)
    - [2.1 char 类型数组和 null 字符](#21-char-类型数组和-null-字符)
    - [2.2 字符串的使用](#22-字符串的使用)
    - [2.3 strlen()函数](#23-strlen函数)
  - [3. 常量与C预处理指令](#3-常量与c预处理指令)
    - [3.1 define 声明常量表达式](#31-define-声明常量表达式)
    - [3.2 const 限定符(C90)](#32-const-限定符c90)
    - [3.3 明示常量](#33-明示常量)
  - [4. 输入与输出](#4-输入与输出)
    - [4.1 printf()](#41-printf)
    - [4.2 printf() 转换说明修饰符](#42-printf-转换说明修饰符)
    - [4.3 转换说明的意义](#43-转换说明的意义)
    - [4.4 scanf()](#44-scanf)
    - [4.5 printf 和 scanf 的区别](#45-printf-和-scanf-的区别)
    - [4.6 scanf() 转换说明修饰符](#46-scanf-转换说明修饰符)
    - [4.7 printf 和 scanf 的*修饰符](#47-printf-和-scanf-的修饰符)
  - [5. getchar() 与 putchar()](#5-getchar-与-putchar)

---
## 1. 前导案例

```C
#include <stdio.h>
#include <string.h>  // 提供strlen()函数的原型
#define DENSITY 62.4 // 人体密度（单位：磅/立方英尺）
int main()
{
    float weight, volume;
    int size, letters;
    char name[40]; // name是一个可容纳 40 个字符的数组

    printf("Hi! What's your first name?\n");
    scanf("%s", name);
    printf("%s, what's your weight in pounds?\n", name);
    scanf("%f", &weight);

    size = sizeof name;
    letters = strlen(name);
    volume = weight / DENSITY;

    printf("Well, %s, your volume is %2.2f cubic feet.\n", name, volume);
    printf("Also, your first name has %d letters,\n", letters);
    printf("and we have %d bytes to store it.\n", size);

    return 0;
}
/*
    array name[40]      存储用户输入的字符值
    %s      转换说明处理字符串的输入和输出
    #define DENSITY 62.4    用C预处理器把字符常量DENSITY定义为62.4
    strlen()    获取字符串的长度
*/
```

---
## 2. 字符串

- 字符串（character string）是一个或多个字符的序列。

---
### 2.1 char 类型数组和 null 字符

- C 语言中字符串都被存储在 char 类型的数组中，该数组由连续的存储单元组成。每个单元储存一个字符

```
    str = "hello world"
    __________________________    
    |h|e|l|l|o| |w|o|r|l|d|\0|
```

- 数组末尾位置的字符 \0 表示空字符 null，用于标记字符串的结束。C 字符串一定以 \0 结束。
- 因此 40 单元的字符数组储存字符串时只能储存 39 个字符。

---
### 2.2 字符串的使用

```c
#include <stdio.h>
#define PRAISE "You are an extraordinary being."
int main(void)
{
    char name[40];
    printf("What's your name? ");
    scanf("%s", name);
    printf("Hello, %s.%s\n", name, PRAISE);
    return 0;
}
```

- %s 表示标识转换字符串类型，两种类型的字符串分别保存在 name 数组和 PRAISE 中

- scanf() 只会读取用户输入的字符串的一个单词，当遇到第一个空白时(空格,制表符或换行符)就停止了。

> "X" 与 'X' 的区别

- 字符串常量 "X" 表示 char arr[2]{'X','\0'}
- 字符常量 'X' 表示 char 'X'

---
### 2.3 strlen()函数

- sizeof 运算符表示以字节为单位给出对象的大小，在计算字符串长度时会将空字符计入在内。
- strlen() 函数给出字符串中的字符长度，不会将结尾的空字符计入在内
- string.h 头文件提供 strlen() 和其他一些与字符串相关的函数

```C
    #define STR "Hello World"

    printf("The STR occupies %zd memory cells\n",sizeof STR);   //12
    printf("The STR Length: %zd", strlen(STR));    //11
    //如果编译器不识别%zd，尝试换成%u或%lu
```

---
## 3. 常量与C预处理指令

### 3.1 define 声明常量表达式

```c
    #define NAME value

    #define PI 3.141592f  //-----> constexpr
    #define Name "Ychao"
    #define NUM_MAX 9999
    #define NUM_MIN 0
    #define CHAR_A 'A'
```

---
### 3.2 const 限定符(C90)

- const 只读限定，const int num = 1 
- const TYPE NAME = value

---
### 3.3 明示常量

- C 头文件 limits.h 和 float.h 提供的数值类型大小限制相关的信息。定义数据类型的最大最小值等常量。

```
    CHAR_BIT    char类型的位数
    SCHAR_MAX   signed char 类型最大值
    UCHAR_MAN   unsigned char 类型最大值

    FLT_DIG     float 有效数字位数
    DBL_DIG     double 有效数字位数

    FLG_MANT_DIG    float 尾数位数
```

> 使用 limit.h 与 float.h 头文件中的明示常量

```c
#include <stdio.h>
#include <limits.h> // 整型限制
#include <float.h> // 浮点型限制
int main(void)
{
	printf("Some number limits for this system:\n");

	printf("Biggest int: %d\n", INT_MAX);
	printf("Smallest long long: %lld\n", LLONG_MIN);
	printf("One byte = %d bits on this system.\n", CHAR_BIT);
	printf("Largest double: %e\n", DBL_MAX);
	printf("Smallest normal float: %e\n", FLT_MIN);
	printf("float precision = %d digits\n", FLT_DIG);
	printf("float epsilon = %e\n", FLT_EPSILON);

	return 0;
}
/*
    Some number limits for this system:
    Biggest int: 2147483647
    Smallest long long: -9223372036854775808
    One byte = 8 bits on this system.
    Largest double: 1.797693e+308
    Smallest normal float: 1.175494e-38
    float precision = 6 digits
    float epsilon = 1.192093e-07
*/
```

---
## 4. 输入与输出

### 4.1 printf()

- 请求printf()函数打印数据的指令要与待打印数据的类型相匹配。
- printf() 函数的返回值为字符数组字符数量，为负值时表示输出错误。计算针对所有字符数，包括空格和不可见的换行符（\n）

> 转换说明及其打印的输出结果

```
    %a，%A      浮点数、十六进制数和p，P计数法（C99，C11）
    %c          单个字符
    %d          有符号十进制数
    %e，%E      浮点数，e计数法
    %f          浮点数，十进制
    %g，%G      自动选择%f 或 %e
    %i          有符号十进制整数
    %o          无符号八进制整数
    %p          指针
    %s          字符串
    %u          无符号十进制整数
    %x，%X      无符号十六进制整数，使用十六进制数 0f，0F
    %%          打印一个百分数符号 %
```

> 说明：

- 格式字符串中的转换说明一定要与后面的每个项相匹配，若忘记这个基本要求会导致严重的后果。

- 如果只打印短语或句子，就不需要使用任何转换说明。
- 打印百分数符号：%%

---
### 4.2 printf() 转换说明修饰符

- 在%和转换字符之间插入修饰符可修饰基本的转换说明。
  
```
    标记        -、+、空格、#、0，可以不使用标记或使用多个标记
    数字        表示最小字段宽度
    .数字       精度：%e、%E、%f转换表示小数位位数 
                     %g、%G转换表示有效数字的最大位数
                     %s转换表示待打印字符的最大数量
                     整型转换，表示待打印数字的最小位数
                     只使用 . 表示其后紧随一个0, %.f 等同于 %.0f;
    h           与整型转换说明一起使用，表示 (unsigned) short int
    hh          与整型转换说明一起使用，表示 signed char 或 unsigned char
    j           与整型，表示 intmax_t 和 uintmax_t 类型
    l           与整型，表示 (unsigned) long int
    ll          与整型，表式 (unsigned) long long int
    L           与浮点型，表示 long double
    t           与整型，表示 ptrdiff_t (两个指针差值)
    z           与整型，表示 size_t 类型，为 sizeof 返回类型
```

- %zd  返回的类型规定为无符号整数，不同系统中，可能使用 %u，%ul，%ull

- printf中的标记

```
    -       待打印项左对齐
    +       显示数值符号，符号为正显示+，符号为负显示-
    空格    有符号值若为正，在值前面显示前导空格；负则显示减号；+覆盖标记空格
    #       把结果转换为另一种形式：%o格式，结果以0开始
                                  %xX，结果以0x 0X开始
                                  %gG，防止结果后面的0被删除
                                  %#无数字，打印一个小数点字符
    0       数值类型，用前导0代替空格填充字段宽度；
            整数，出现 - 标记或者指定精度，则忽略 0 
```

> 字段宽度

```c
#include <stdio.h>
#define PAGES 959
int main(void)
{
    printf("*%d*\n", PAGES);     
    printf("*%2d*\n", PAGES);
    printf("*%10d*\n", PAGES);
    printf("*%-10d*\n", PAGES);
    
    return 0;
}
/*
    *959*
    *959*
    *       959*
    *959       *
*/
```

> 一些浮点型修饰符的组合

```c
#include <stdio.h>
int main(void)
{
    const double RENT = 3852.99; // const变量
    printf("*%f*\n", RENT);
    printf("*%e*\n", RENT);
    printf("*%4.2f*\n", RENT);
    printf("*%3.1f*\n", RENT);
    printf("*%10.3f*\n", RENT);
    printf("*%10.3E*\n", RENT);
    printf("*%+4.2f*\n", RENT);
    printf("*%010.2f*\n", RENT);
    return 0;
}
/*
    *3852.990000*
    *3.852990e+03*
    *3852.99*
    *3853.0*
    *  3852.990*
    * 3.853E+03*
    *+3852.99*
    *0003852.99*
 */ 
```

> 一些格式标记

```c
#include <stdio.h>
int main(void)
{
    printf("%x %X %#x\n", 31, 31, 31);
    printf("**%d**% d**% d**%+d**\n", 42, 42, -42, 42);
    printf("**%5d**%5.3d**%05d**%05.3d**\n", 6, 6, 6, 6);
    return 0;
}
/*
    1f 1F 0x1f
    **42** 42**-42**+42**
    **    6**  006**00006**  006**
*/
```

> 字符串格式

```c
#include <stdio.h>
#define BLURB "Authentic imitation!"
int main(void)
{
    printf("[%2s]\n", BLURB);
    printf("[%24s]\n", BLURB);
    printf("[%24.5s]\n", BLURB);
    printf("[%-24.5s]\n", BLURB);
    return 0;
}
/*
    [Authentic imitation!]
    [    Authentic imitation!]
    [                   Authe]
    [Authe                   ]
*/
```

---
### 4.3 转换说明的意义

- 实际上，转换说明的操作本质上是将原始值翻译成特定类型文本并打印出来。

> 注意

- 转换说明应该与待打印值的类型相匹配。

```c
#include <stdio.h>
int main(void)
{
	float n1 = 3.0;
	double n2 = 3.0;
	long n3 = 2000000000;
	long n4 = 1234567890;
	printf("%.1e %.1e %.1e %.1e\n", n1, n2, n3, n4);
	printf("%ld %ld\n", n3, n4);
	printf("%ld %ld %ld %ld\n", n1, n2, n3, n4);
	return 0;
}
/*
	3.0e+00 3.0e+00 3.1e+46 1.4e-305
	2000000000 1234567890
	0 1074266112 0 1074266112
*/
```

- 第1行，%e 未将 long 整数转换成浮点数
- 第3行，printf 语句中由其他不匹配的地方，即使后面用对了转换说明也会产生虚假的结果。

> 参数传递机制

- 参数传递机制因实现而异
- 就 printf("%ld %ld %ld %ld\n", n1, n2, n3, n4)，对于 n1，n2，系统仍会将 float(4bits) 转换成 double(8bits) 储存在 stack 中，n3,n4 long(4bits) 紧随压入栈中，
- %ld 转换说明，取参数读取栈中数据应读取 4 字节的 long 类型，但将 n1 的前半部分作为第一个参数，后半部分作为第二个参数。因此出现 printf 读错了字节导致转换说明出错。

---
### 4.4 scanf()

- scanf() 将输入的字符串转换成整数、浮点数、字符或字符串，同样和 printf 类似使用格式字符串和参数列表。
- scanf 中的格式字符串表明字符输入流的目标数据类型。
- 如果用scanf()读取基本变量类型的值，在变量名前加上一个&；
- 如果用scanf()把字符串读入字符数组中，不要使用&。
- scanf()函数使用空白（换行符、制表符和空格）把输入分成多个字段。但使用 %c 转换说明，scanf 会读取每个字符，包括空白

- scanf() 函数返回成功读取的项数，0 表示未读取任何项。

```c
#include <stdio.h>
int main(void)
{
	int age; // 变量
	float assets; // 变量
	char pet[30]; // 字符数组，用于储存字符串
	printf("Enter your age, assets, and favorite pet.\n");
	scanf("%d %f", &age, &assets); // 这里要使用& 
	scanf("%s",pet); // 字符数组不使用&
								  
	printf("%d $%.2f %s\n", age, assets, pet); 
	return 0;
}
```

---
### 4.5 printf 和 scanf 的区别

- scanf()函数所用的转换说明与printf()函数几乎相同。
- 主要的区别是，对于float类型和double类型，printf()都使用%f、%e、%E、%g和%G转换说明。
- scanf()只把它们用于float类型，对于 double 类型时要使用 l 修饰符。

---
### 4.6 scanf() 转换说明修饰符

```
    %c              字符
    %d,i            有符号十进制整数
    %e,f,g,a        浮点数
    %E,F,G,A        浮点数
    %o              有符号八进制整数
    %p              指针
    %s              字符串,从第一个非空白到下一个空白之前
    %u              无符号十进制整数
    %x,X            十六进制整数
```

> 修饰符

```
    *               抑制赋值
    数字            最大字段宽度,到最大字段或空白处停止
    hh              把整数作为 signed/unsigned char 读取
    ll              把整数作为 (unsigned) long long 读取

    h,l             %hd,hi      short int
                    %ho,hx,hu   unsigned shot int
                    %ld,li      long
                    %lo,lx,lu   unsigned long 
                    %le,lf,lg   double
    L               %Le,Lf,Lg   long double

    j               修饰整型    intmax_t 或 uintmax_t 类型
    z               sizeof 类型
    t               修饰整型    指针差值类型
```

> 注意

- scanf()函数允许把普通字符放在格式字符串中。除空格字符外的普通字符必须与输入字符串严格匹配

```
假设在两个转换说明中添加一个逗号：
    
    scanf("%d,%d", &n, &m);
    
scanf()函数将其解释成：用户将输入一个数字、一个逗号，然后再输入一个数字。也
就是说，用户必须像下面这样进行输入两个整数：
    
    88,121
```

- 除了 %c，其他转换说明都会自动跳过待输入值前面所有的空白。scanf("%d%d", &n, &m)与scanf("%d %d", &n, &m)的行为相同
- 对于 %c，scanf("%c", &ch)从输入中的第1个字符开始读取，而scanf(" %c", &ch)则从第1个非空白字符开始读取。

---
### 4.7 printf 和 scanf 的*修饰符

- printf 中的 * 表示用 * 代替预先字段宽度，%*d 表示可以通过传入的参数用户控制浮点值指定精度和字段宽度。( \* 预先占位符)

```c
#include <stdio.h>
int main(void)
{
	unsigned width, precision;
	int number = 256;
	double weight = 242.5;

	printf("Enter a field width:\n");
	scanf("%d", &width);    // 6
	printf("The number is :%*d:\n", width, number);  // 256

	printf("Now enter a width and a precision:\n");
	scanf("%d %d", &width, &precision);    // 8 3
	printf("Weight = %*.*f\n", width, precision, weight); // 242.500

	printf("Done!\n");
	return 0;
}
```

- Scanf：把*放在%和转换字符之间时，会使得scanf()跳过相应的输出项。
- scanf("%\*d %\*d %d", &n);  scanf 会跳过前两个整数，把第三个整数赋值给 n

---
## 5. getchar() 与 putchar()

- getchar()函数不带任何参数，它从输入队列中返回下一个字符。
- putchar()函数打印它的参数

```c
    char ch;
    ch = getchar();  //等价于 scanf("%c",&ch);
    putchar(ch);     //等价于 printf("%c",ch);   
```

- 此类函数只处理字符, 因此效率上比通用的 printf 与 scanf 更快更简洁

---