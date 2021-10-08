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
    - [4.2 printf 转换说明修饰符](#42-printf-转换说明修饰符)

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
### 4.2 printf 转换说明修饰符

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