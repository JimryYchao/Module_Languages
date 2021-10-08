# C 语言概述

---
- [C 语言概述](#c-语言概述)
  - [1. Hello World](#1-hello-world)
  - [2. 程序细节](#2-程序细节)
    - [2.1 #include指令和头文件](#21-include指令和头文件)
    - [2.2 main()函数](#22-main函数)
    - [2.3 注释](#23-注释)
  - [3. 调试程序](#3-调试程序)
    - [3.1 语法错误](#31-语法错误)
    - [3.2 语义错误](#32-语义错误)
    - [3.3 程序状态](#33-程序状态)
  - [4. 关键字与保留标识符](#4-关键字与保留标识符)

---
## 1. Hello World

```C
#include <stdio.h>      
    /* 预处理指令 --- 头文件 */
int main(void){         /* 程序入口 */
    int num;            /* 定义声明 */
    num = 1;            /* 变量赋值 */
    printf("Hello World");  /* 输出函数 printf() */
    return 0;
}
```

- stdio.h 是 C 编译器软件包的标准部分，它提供键盘输入和屏幕输出的支持。

---
## 2. 程序细节

### 2.1 #include指令和头文件

- #include\<stdio.h> 的作用相当于把stdio.h文件中的所有内容都输入该行所在的位置。
- 所有的C编译器软件包都提供stdio.h文件。该文件中包含了供编译器使用的输入和输出函数信息。该文件名的含义是标准输入/输出头文件。
- 通常，在C程序顶部的信息集合被称为头文件（header）。头文件帮助编译器把你的程序正确地组合在一起。

---
### 2.2 main()函数

- int main(void) C 程序一定从main()函数开始执行，该格式是标准形式，表示为C程序的主入口。

---
### 2.3 注释

- /* 简单的注释 */ 多行注释: 编译时忽略
- // 单行注释

---
## 3. 调试程序

### 3.1 语法错误

- 不遵循 C 语言的规则就会犯语法错误
- C语言的语法错误指的是，把有效的C符号放在错误的地方。

---
### 3.2 语义错误

- 语义错误是指意思上的错误
- 在C语言中，如果遵循了C规则，但是结果不正确，那就是犯了语义错误

---
### 3.3 程序状态

- 程序状态（program state）是在程序的执行过程中，某给定点上所有变量值的集合。它是计算机当前状态的一个快照。
- 通过逐步跟踪程序的执行步骤，并记录每个变量，便可监视程序的状态。

---
## 4. 关键字与保留标识符

```c
  // 标准 C 关键字
  auto    extern    short    while
  break   float     case     for
  sizeof  char      goto     static

  if    continue    switch   void
  int   default     typedef  do
  long  double      register unsigned
  else  restrict    return                                     ;
  struct                                                       ;
  union                                                        ;

  // C90 新增
  signed   const   volatile   enum                             ;

  // C99 新增
  inline                                                       

  // C11 新增的保留标识符
  _Alignas    _Alignof    _Atomic
  _Bool       _Complex    _Generic
  _Imaginary  _Noreturn   _Static_assert
  _Thread_local
```

---