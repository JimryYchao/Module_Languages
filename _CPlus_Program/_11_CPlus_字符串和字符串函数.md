# C Plus 字符串与字符串函数

- 函数： gets() 、gets_s() 、fgets() 、puts() 、fputs() 、strcat() 、strncat() 、strcmp() 、strncmp() 、strcpy() 、strncpy()、sprintf()、strchr() 创建并使用字符串
- C 库中的字符和字符串函数
  
---
- [C Plus 字符串与字符串函数](#c-plus-字符串与字符串函数)
  - [1. 表示字符串和字符串 I/O](#1-表示字符串和字符串-io)
    - [1.1 puts() 字符串显示](#11-puts-字符串显示)
    - [1.2 字符串字面值(字符串常量)](#12-字符串字面值字符串常量)

---
## 1. 表示字符串和字符串 I/O

- 字符串是以空字符（\0）结尾的char类型数组

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
### 1.2 字符串字面值(字符串常量)

