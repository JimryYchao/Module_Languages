# C Plus 数组和指针

- 数组与指针的运用
- 多维数组的延申
- 变长数组

---
- [C Plus 数组和指针](#c-plus-数组和指针)
	- [1. 数组](#1-数组)
		- [1.1 数组: 指定初始化器(C99)](#11-数组-指定初始化器c99)
		- [1.2 多维数组](#12-多维数组)
	- [2. 指针与数组](#2-指针与数组)
		- [2.1 指针与地址的关系](#21-指针与地址的关系)
	- [3. 函数、数组和指针](#3-函数数组和指针)
		- [3.1 指针表示法与数组表示法](#31-指针表示法与数组表示法)
	- [4 指针操作](#4-指针操作)
		- [4.1 指针的基本操作](#41-指针的基本操作)
		- [4.2 指针注意事项](#42-指针注意事项)
	- [5. 保护数组中的数据](#5-保护数组中的数据)
		- [5.1 对形参使用 const](#51-对形参使用-const)
	- [6. 指向多维数组的指针](#6-指向多维数组的指针)
		- [6.1 多维数组的指针表示法](#61-多维数组的指针表示法)
		- [6.2 指针的兼容性](#62-指针的兼容性)
		- [6.3 函数与多维数组](#63-函数与多维数组)
	- [6. 变长数组 (VLA)](#6-变长数组-vla)
	- [7. 复合字面值](#7-复合字面值)

---
## 1. 数组

- 数组有数据类型相同的一系列元素组成。

- 当初始化列表中的值少于数组元素个数时，编译器会把剩余的元素都初始化为 0;

- 初始化的数组元素个数不能超过数组长度

```c
    //1. 数组的声明包括数据类型与数组大小
    int IntArr[count];  
    int Arr[10]; // 内含 10 个 int 类型元素的数组

    //2. 初始化
    int Arr[10] = {0,1,2,3,4,5,6,7,8,9};
    char str[] = "HelloWorld";      // str 数组的大小在声明初始化时自动确定

    int Arr[10];
    Arr[0] = 0;
    Arr[1] = 1; //..........

    //3. const 只读数组
    const int Arr[3] = {};  //声明并初始化
    // 当初始化列表中的值少于数组元素个数时，编译器会把剩余的元素都初始化为 0
```

---
### 1.1 数组: 指定初始化器(C99)

```c
    int arr[5] = {0,1,2,3,4};   // 传统方式
    int Arr[5] = {[2] = 2};     // 将 Arr[2] = 2, 指定初始化器, 其余元素为默认值
```

---
### 1.2 多维数组

```c
    int Arr[length0][length1];
    int Arr[3][3][3][3];  //......多维数组

    int Array[4][4] = {
        {1,2,3,4},
        {10,20,30,40},
        {100,200,300,400},
        {0,0,0,0}
    }
```

---
## 2. 指针与数组

- 数组表示法其实是变相地使用指针。

- 数组名是数组首元素的地址。

* 如果 Array 是一个数组，下面的语句成立：
    - Array == &Array[0]; // 数组名是该数组首元素的地址

> 数组指针地址

```c
#include <stdio.h>
#define SIZE 4
int main(void)
{
	short dates[SIZE];
	short* pti;		// 对应 short 数组指针
	short index;	// 数组索引
	double bills[SIZE];
	double* ptf;	// 对应 double 数组指针
	pti = dates;		// 把数组地址赋给指针
	ptf = bills;		

	printf("%22s %11s\n", "short", "double");
	for (index = 0; index < SIZE; index++)
		printf("pointers + %d: %10p %10p\n", 
			index, pti + index, ptf + index); 
	return 0;
}
/*
	                 short      double
	pointers + 0:   004FF994   004FF954
	pointers + 1:   004FF996   004FF95C
	pointers + 2:   004FF998   004FF964
	pointers + 3:   004FF99A   004FF96C
*/
```

- 数组内相邻元素地址对应关系：&arr[n+1] = &arr[n]+1 

- 指针类型加 1 表示增加一个存储单元，对于组数表示下一个元素地址，而不是表示下一个字节地址，因此这就要求指针与指向对象类型相对应（例如，pti 的类型是 short 类型，pti + 1，其值每次递增 2 字节）

- 在数组中，定义 arr[n] 的含义是 *(arr + n)  //(其中 arr = &arr[0])

---
### 2.1 指针与地址的关系

- 指针的值是它所指向对象的地址。地址的表示方式依赖于计算机内部的硬件。

- 许多计算机（包括 PC 和 Mac）都是按字节编址，意思是内存中的每个字节都按顺序编号。

- 一个较大对象的地址（如 double 类型的变量）通常是该对象第一个字节的地址。

- 在指针前面使用 * 运算符可以得到该指针所指向对象的值。

- 指针加 1，指针的值递增它所指向类型的大小（以字节为单位）。

---
## 3. 函数、数组和指针

- 编写一个处理数组的函数，数组作为函数的参数时，如何定义函数的原型：由于数组名是该数组首元素的地址，实际传入的参数是一个储存数组首元素的地址（Arr = &Arr[0]）

```c
#include <stdio.h>
#define SIZE 4

void PrintStr(char* strArr);
int main(void)
{
	char str[] = "HELLO";
	PrintStr(str);
}
void PrintStr(char* strArr) {
	printf("%s", strArr);
}
```

> 案例: 数组元素求和问题

```c
#include <stdio.h>
#define SIZE 4

void Sum(int* Arr, int size);

int main(void)
{
	int Arr[SIZE] = { 1,2,3,4 };
	Sum(Arr, SIZE);
}

void Sum(int* Arr, int size) {
	int sum = 0;
	int* start = Arr;
	while (Arr < start + size){    // 设置边界
		sum += *Arr++;     // 等价 sum = sum + *(Arr++)
	}
	printf("%d", sum);
}
```

---
### 3.1 指针表示法与数组表示法

- 处理数组的函数实际上用指针作为参数，但是在编写这样的函数时，可以选择是使用数组表示法还是指针表示法。

- 对于 int Arr[Size] 数组，*(Arr+i) 与 Arr[i] 等价，但指针表示法（尤其与增量运算符一起使用时）更接近于机器语言，编译时能够生成效率更高的代码

---
## 4 指针操作

- 案例演示中将打印与指针类型相关的三种结果，该指针的值（该指针指向的地址）、指向地址的值、以及类型自己的地址。

- 编译器不支持 %p 转换说明时，可以使用 %u 或 %lu 代替 %p

- 编译器不支持 %td 转换说明打印地址的差值，可以用 %ld、%d 代替

```c
#include <stdio.h>
int main(void)
{
	int urn[5] = { 100, 200, 300, 400, 500 };
	int* ptr1, * ptr2, * ptr3;
	ptr1 = urn;				// 把一个地址赋给指针
	ptr2 = &urn[2];			// 把一个地址赋给指针
	printf("pointer value, dereferenced pointer, pointer address : \n");

	// 1. 解引用指针，以及获得指针的地址
	printf("ptr1 = %p, *ptr1 = %d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);
	printf("ptr2 = %p, *ptr2 = %d, &ptr2 = %p\n", ptr2, *ptr2, &ptr2);

	// 2. 指针加法
	ptr3 = ptr1 + 4;
	printf("\nadding an int to a pointer:\n");
	printf("ptr1 + 4 = %p, *(ptr1 + 4) = %d\n", ptr1 + 4, *(ptr1 + 4));

	// 3. 递增指针
	ptr1++;
	printf("\nvalues after ptr1++:\n");
	printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);

	// 4. 递减指针
	ptr2--;
	printf("\nvalues after ptr2--:\n");
	printf("ptr2 = %p, *ptr2 = %d, &ptr2 = %p\n", ptr2, *ptr2, &ptr2);

	--ptr1; // 恢复为初始值
	++ptr2; // 恢复为初始值
	printf("\nPointers reset to original values:\n");
	printf("ptr1 = %p, ptr2 = %p\n", ptr1, ptr2);

	// 5. 一个指针减去另一个指针
	printf("\nsubtracting one pointer from another:\n");
	printf("ptr2 = %p, ptr1 = %p, ptr2 - ptr1 = %td\n", ptr2, ptr1, ptr2 - ptr1);

	// 6. 一个指针减去一个整数
	printf("\nsubtracting an int from a pointer:\n");
	printf("ptr3 = %p, ptr3 - 2 = %p\n", ptr3, ptr3 - 2);
	
	return 0;
}
/*
	pointer value, dereferenced pointer, pointer address :
	ptr1 = 010FFC9C, *ptr1 = 100, &ptr1 = 010FFC90
	ptr2 = 010FFCA4, *ptr2 = 300, &ptr2 = 010FFC84
	
	adding an int to a pointer:
	ptr1 + 4 = 010FFCAC, *(ptr1 + 4) = 500
	
	values after ptr1++:
	ptr1 = 010FFCA0, *ptr1 =200, &ptr1 = 010FFC90
	
	values after ptr2--:
	ptr2 = 010FFCA0, *ptr2 = 200, &ptr2 = 010FFC84
	
	Pointers reset to original values:
	ptr1 = 010FFC9C, ptr2 = 010FFCA4
	
	subtracting one pointer from another:
	ptr2 = 010FFCA4, ptr1 = 010FFC9C, ptr2 - ptr1 = 2
	
	subtracting an int from a pointer:
	ptr3 = 010FFCAC, ptr3 - 2 = 010FFCA4
*/
```

---
### 4.1 指针的基本操作

1. 赋值：可以把地址赋值给指针（int* pInt = &A）

2. 解引用：* 运算符给出指针指向地址上储存的值（int a = *pInt）

3. 取址：指针也有自己的地址和值（int* pPtr = &pInt）

4. 指针与整数相加：可以使用 + 运算符把指针与整数相加，或整数与指针相加（整数都会和指针所指向类型的大小（以字节为单位）相乘，然后把结果与初始地址相加；ptr1 + 4 与 &Arr[4] 等价）

5. 指针减去一个整数：可以使用 - 运算符从一个指针中减去一个整数

6. 递增指针：递增指向数组元素的指针可以让该指针移动至数组的下一个元素

7. 递减指针：除了递增指针还可以递减指针。

8. 指针求差：可以计算两个指针的差值（求差的两个指针分别指向同一个数组的不同元素，通过计算求出两元素之间的距离。差值的单位与数组类型的单位相同）
   - ptr2 - ptr1 得 2，意思是这两个指针所指向的两个元素相隔两个 int
9. 比较：使用关系运算符可以比较两个指针的值，前提是两个指针都指向相同类型的对象。
  
---
### 4.2 指针注意事项

- **不可解引用未初始化的指针**！！！

```c
  int * pt;// 未初始化的指针
  *pt = 5; // 严重的错误
```

- 创建一个指针时，系统只分配了储存指针本身的内存，并未分配储存数据的内存。

- 在使用指针之前，必须先用已分配的地址初始化它。之后才可以进行解引用的操作

---
## 5. 保护数组中的数据

- 一般函数处理基本类型（int）时，选择传递 int 的值，通常是直接传递数值。若需要在函数改变该数值时，才会传递指针；对于数组只能传递指针，若函数按值传递数组，只能将数组的所有数据进行拷贝，但直接操作原数组则效率会更高

- 引用传递存在意外修改原始数据的可能，值传递通过传递原始数据的副本，可以有效的保护数据。

```c
int sum(int ar[], int n)  // 错误的代码
{
  int i;
  int total = 0;
  for( i = 0; i < n; i++)
  total += ar[i]++;       // 错误递增了每个元素的值, 导致数组中每个元素的值都加 1
  return total;
}
```

---
### 5.1 对形参使用 const

- 如果函数的意图不是修改数组中的数据内容，那么在函数原型和函数定义中声明形式参数时应使用关键字 const

```c
int sum(const int ar[], int n); /* 函数原型 */
int sum(const int ar[], int n) /* 函数定义 */
{
  int i;
  int total = 0;
  for( i = 0; i < n; i++)
  total += ar[i];
  return total;
}
// 函数不能修改 ar 指向的数组中的内容，
// const 表示该函数处理数组时将其视为常量
```

> 使用 const 保护数组

```c
#include <stdio.h>
#define MONTHS 12
int main(void) {
	const int days[MONTHS]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
	days[4] = 15;	// 不可修改

	double rates[] = { 1.0,2.0,3.0,4.0,5.0 }; 
	const double* pr = rates;   // pr 指向数组的首元素

	*pr = 10.0;		// 不可修改
	pr[2] = 66;		// 不可修改
	rates[0] = 1010;  // rates 数组未被 const 限定
}
```

> 关于 const 指针赋值和 const 需要注意一些规则

* **前缀 const 声明指针** >> const int* pr = Arr
   - 把 const 数据或非 const 数据的地址初始化为指向 const 的指针或为其赋值是合法的  
   - 只能把非 const 数据的地址赋给普通指针

-  **后缀 const 声明** >> int* const pr = Arr
   - 对指针值做 const 限定, 但可以修改指针指向地址的值
   - 仅能将可修改值的地址传递给指针

* **双限定** >> const int* const pr = Arr
   - 指针值与指向值均 const 限定

```C
int main(void) {
	const int  Arr[] = { 1,2,3,4 };
	int Arr2[] = { 4,3,2,1 };

	//const 后缀声明: 对指针值做 const 限定, 但可以修改指针指向地址的值
	int* const pInt1 = Arr;			//Error: const int[] 要求值不可修改
	int* const pInt1 = &Arr2[2];	//仅能将可修改值的地址传递给指针

	//const 前缀声明: 表明指针指向的值做 const 限定, 不可修改指针指向值, 但可以修改指针自身值
	const int* pInt2 = Arr;
	*pInt2 = 10;		//Error: 不可修改指针指向值
	pInt2 = Arr2;		//可以修改指针自身值

	//const 双限定: 指针值与指向值均 const 限定
	const int* const pInt3 = &Arr[2];
	pInt3 = Arr;	//Error: 仅能声明时初始化
}
```

---
## 6. 指向多维数组的指针

```c
int main(void) {
	int(Arr[2])[3] = {		// 二维数组
		{1,2,3},
		{2,3,4}
	};
	int Arr1[] = { 1,2,3,4 };

	int* pr[2] = { Arr1,&Arr1[1] };	// pr 是一个包含两个指针元素的数组
	int(*pr1)[3] = Arr;				// pr1 指向一个内含两个 int 类型值的数组

	for (size_t i = 0; i < 2; i++)
	{
		printf("%p\n", pr1[i]);
		printf("%p\n", Arr[i]);
	}
}
```

> 通过指针获取 二维数组 的信息

```c
#include <stdio.h>
int main(void)
{
	int zippo[4][2] = { { 2, 4 }, { 6, 8 },{ 1, 3 }, { 5, 7 } }; 
	int(*pz)[2];
	pz = zippo;

	printf(">> pz = %p, pz + 1 = %p\n",pz, pz + 1);
	printf("   pz[0] = %p, pz[0] + 1 = %p\n", pz[0], pz[0] + 1);
	printf("   *pz = %p, *pz + 1 =% p\n", *pz, *pz + 1);
	printf(">> pz[0][0] = %d\n", pz[0][0]);
	printf("   *pz[0] = %d\n", *pz[0]);
	printf("   **pz = %d\n", **pz);
	printf(">> pz[2][1] = %d\n", pz[2][1]);
	printf("   *(*(pz+2) + 1) = %d\n", *(*(pz + 2) + 1));
	return 0;
}
/*
	>> pz = 007AF710, pz + 1 = 007AF718
	   pz[0] = 007AF710, pz[0] + 1 = 007AF714
	   *pz = 007AF710, *pz + 1 =007AF714
	>> pz[0][0] = 2
	   *pz[0] = 2
	   **pz = 2
	>> pz[2][1] = 3
	   *(*(pz+2) + 1) = 3
*/
```

- 其中: 	
  
``` 
    int Arr[3][2];
    int(*pz)[2];
    pz = Arr;

    pz[0][0] == *(*(Arr)) == **pz
    pz[m][n] == *(*(Arr + m) + n)

    int Arr[] = {0,1,2,3}
    int* pr = Arr;
    pr[0] = *pr = 0;
```

---
### 6.1 多维数组的指针表示法

- 对于 Arr[n][m][i][l]... 数组

```c
  int Arr[a][b][c][d];
  int(*pr)[b][c][d] = Arr;

  Arr[0][0][0][0] = ****pr = pr[0][0][0][0];
```

---
### 6.2 指针的兼容性

- 指针之间的赋值比数值类型之间的赋值要严格

- 数值类型之间存在隐式或显式类型转换, 但是不同类型的指针不能这样做

- 严格遵守 const 指针赋值规则, C++ 不允许把 const 指针赋给非 const 指针, 虽然 C 允许这样做, 但是通过非 const 指针修改 const 指针指向的值, 其行为是未定义(非法)

---
### 6.3 函数与多维数组

> 输出班上每位学生的总分

```c
#include <stdio.h>
void ScoreSum(int score[][4]);
// 等价于 ScoreSum(int(*pr)[4]);
int main(void)
{
	int scores[4][4]{
		{88,99,66,44},
		{55,78,65,32},
		{77,85,98,48},
		{12,45,25,35}
	};
	ScoreSum(scores);
}
void ScoreSum(int score[][4]) {
  const	int(*pr)[4] = score;

	for (size_t i = 0; i < 4; i++)
	{
		int sum = 0;
		for (size_t j = 0; j < 4; j++)
		{
			sum += pr[i][j];
		}
		printf("%d\n", sum);
	}
}
```

- 一般而言，声明一个指向N维数组的指针时，只能省略最左边方括号中的值：

```c
  int sum4d(int ar[][12][20][30], int rows);
```

---
## 6. 变长数组 (VLA)

- 在声明函数时可以使用 C99 新增的变长数组(变长数组不能改变大小), 一般作为用于函数的形参声明

- 传入的数组不能使用 static 或 extern 存储类别说明符

- C11 把变长数组作为一个可选特性

- 格式:

```c
  // C 函数不存在函数重载
  void Func(int size, int Arr[size]);
  void Func(int row, int col, int Arr[row][col]);
  void Func(int size, int(*pr)[size]);

  void Function(int Arr[size],int size);  // 无效的顺序
  void Func(int, int, int Arr[*][*]);  //省略模式
```

- 变长数组名实际上是一个指针

- 带变长数组形参的函数实际上是在原始数组中处理数组，因此可以修改传入的数组

- C99/C11 标准允许在声明变长数组时使用 const 变量。要求该数组的定义必须是声明在块中的自动存储类别数组。

- 变长数组还允许动态内存分配，这说明可以在程序运行时指定数组的大小。

- 普通 C 数组都是静态内存分配，即在编译时确定数组的大小

---
## 7. 复合字面值

- C99 新增了复合字面量（compound literal）。字面量是除符号常量外的常量。

- 5 是 int 类型字面量，81.3 是 double 类型的字面量，'Y' 是 char 类型的字面量，"elephant" 是字符串字面量。

- 对于数组，复合字面量类似数组初始化列表，前面是用括号括起来的类型名

```c
  int arr[2] = {1,2};     // 常规数组声明
  (int[2]){1,2}   //复合字面量
  // (int[2])  即为数组复合字面量的类型名(匿名)
  // 也可省略数组大小     即 (int[]){1,2}
```

- 因为复合字面量是匿名的，所以不能先创建然后再使用它，必须在创建的同时使用它

- 也可使用指针记录地址  >> int* ptr = (int[2]){1,2}; 

- 多维复合字面量: (int[2][1]){{1},{2}};

```c
fun((int[2]) { 10,20 }, 3);

void fun(int* arr, int size) {
	for (size_t i = 0; i < size; i++)
	{
		printf("%d", arr[i]);
	}
}
```

- 复合字面量是提供只临时需要的值的一种手段。复合字面量具有块作用域（第12章将介绍相关内容），这意味着一旦离开定义复合字面量的块，程序将无法保证该字面量是否存在。
  
---