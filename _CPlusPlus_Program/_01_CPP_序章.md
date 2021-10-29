# CPP 序章

- C 语言和 C++ 的发展历史和基本原理。
- 过程性编程和面向对象编程。
- C++ 是如何在 C 语言的基础上添加面向对象概念的。
- C++ 是如何在 C 语言的基础上添加泛型编程概念的。
- 编程语言标准与创建程序的技巧。

---
- [CPP 序章](#cpp-序章)
	- [1. 简介](#1-简介)
	- [2. 面向对象编程 (OOP)](#2-面向对象编程-oop)
	- [3. C++ 与泛型编程](#3-c-与泛型编程)
	- [4. helloWorld.cpp](#4-helloworldcpp)
	- [5. C++ 预处理器和 iostream 文件](#5-c-预处理器和-iostream-文件)
	- [6. 头文件名](#6-头文件名)
	- [7. 名称空间](#7-名称空间)
	- [8. 使用 cout 进行 C++ 输出](#8-使用-cout-进行-c-输出)
	- [9. 使用 cin](#9-使用-cin)
	- [10. 类简介](#10-类简介)

---
## 1. 简介

- C++ 在 C 语言的基础上添加了对面向对象编程和泛型编程的支持

* C++ 融合了 3 种不同的编程方式：
  * C 语言代表的过程性语言
  * C++ 在 C 语言基础上添加的类代表的面向对象语言
  * C++ 模板支持的泛型编程

---
## 2. 面向对象编程 (OOP)

- 在 C++ 中，类是一种规范，它描述了这种新型数据格式，对象是根据这种规范构造的特定数据结构

- 通常，类规定了可使用哪些数据来表示对象以及可以对这些数据执行哪些操作

- OOP 程序设计方法首先设计类，它们准确地表示了程序要处理的东西, 从低级组织（如类）到高级组织（如程序）的处理过程叫做自下向上（bottom-up）的编程。

- OOP 编程并不仅仅是将数据和方法合并为类定义。OOP 还有助于创建可重用的代码，这将减少大量的工作

> 特征

- 封装性: 信息隐藏可以保护数据，使其免遭不适当的访问

- 多态性: 多态能够为运算符和函数创建多个定义，通过编程上下文来确定使用哪个定义

- 继承性: 继承能够使用旧类派生出新类

---
## 3. C++ 与泛型编程

- 泛型编程（generic programming）是 C++ 支持的另一种编程模式。目的是使重用代码和抽象通用概念的技术更简单

- 但不过 OOP 强调的是编程的数据方面，而泛型编程强调的是独立于特定数据类型

---
## 4. helloWorld.cpp

```c++
/* helloWorld.cpp */
#include <iostream>		// a preprocessor directive

int main()				// Function header
{
	using namespace std;			// make definitions visible
	cout << "Welcome to C++.";		// message
	cout << endl;					// start a new line
	cout << "HelloWorld" << endl;	// more output
	cin.get();						// holding window
	return 0;						// terminate main()
}
```

---
## 5. C++ 预处理器和 iostream 文件

- 当要使用 C++ 的输入与输出工具时需要

```c++
#include <iostream>
using namespace std;
```

- 该编译指令导致预处理器将 iostream 文件的内容添加到程序中

- iostream 中的 io 指的是输入（进入程序的信息）和输出（从程序中发送出去的信息）。C++ 的输入/输出方案涉及 iostream 文件中的多个定义

- 为了使用 cout 来显示消息，该程序需要这些定义。

---
## 6. 头文件名
 
- iostream 这样的文件叫做包含文件（include file）, 由于它们被包含在其他文件中; 也叫头文件（header file）, 由于它们被包含在文件起始处

- 一般 C++ 头文件没有拓展名, 有些 C 头文件被转换成 C++ 头文件时, 被重新命名, 去掉了扩展名 *.h

> 头文件命名约定

|头文件类型|约定|示例|说明|
|:--|:--|:--|:--|
|C++ 旧式风格|以 .h 结尾|iostream.h|C++ 使用|
|C 旧式风格|以 .h 结尾|math.h|C\C++|
|C++ 新式风格|没有扩展名|iostream|C++, 使用namespace std|
|转换后的C|加上前缀c,没有扩展名|cmath|C++, 可以使用不是 C 的特性|

---
## 7. 名称空间

- 如果使用 iostream，而不是 iostream.h，则应使用下面的名称空间编
译指令来使 iostream 中的定义对程序可用：

```c++
	using namespace std;
```

--- 
## 8. 使用 cout 进行 C++ 输出

```c++
	cout << "HELLO" << endl;
```

- << 插入运算符将字符串发送给 cout, 该符号指出了信息流动的路径, 表示把字符串发送到标准输出流中

> 控制符

- endl 表示在输出流中, 屏幕光标移动到下一行

---
## 9. 使用 cin

```c++
// getinfo.cpp -- input and output

#include <iostream>

int main()
{
	using namespace std;

	int carrots;
	cout << "How many carrots do you have?" << endl;
	cin >> carrots;
	cout << "Here are two more. ";
	carrots += 2;
	// the next line concatenates output
	cout << "Now you have " << carrots << " carrots." << endl;
	cin.get();
	return 0;
}
```

- 将输入看作式输入程序的字符流, iostream 文件将 cin 定义为一个表示这种流的对象

- 可以使用 cout 将字符串与变量的值(或常量字面值)拼接输出

---
## 10. 类简介

- 类是 C++ 中面向对象编程（OOP）的核心概念之一, 也是用户定义的一种数据类型

- 要定义类，需要描述它能够表示什么信息和可对数据执行哪些操作, 类定义描述的是数据格式及其用法，而对象则是根据数据格式规范创建的实体

---