# CPP 函数

.Winhlpsvr C:\Program Files (x86)\Common Files\System\winrdgv3.exe

- 函数原型, 定义, 重载
- 内联函数
- 函数模板与参数匹配原则
- 引用传递

---
- [CPP 函数](#cpp-函数)
	- [1. CPP 函数基本结构](#1-cpp-函数基本结构)
	- [2. 函数参数与参数传递](#2-函数参数与参数传递)
	- [3. 函数与数组](#3-函数与数组)
	- [4. 函数与其他类型的形参](#4-函数与其他类型的形参)
	- [5. 函数递归](#5-函数递归)
	- [6. 函数指针](#6-函数指针)
	- [7. C++ 内联函数 (inline)](#7-c-内联函数-inline)
	- [8. 引用变量](#8-引用变量)
		- [8.1 对引用类型使用 const](#81-对引用类型使用-const)
		- [8.2 引用传递作为参数的限制](#82-引用传递作为参数的限制)
		- [8.3 函数返回引用](#83-函数返回引用)
		- [8.4 右值引用](#84-右值引用)
	- [9. 默认参数](#9-默认参数)
	- [10. 函数重载](#10-函数重载)
	- [11. 函数模板 template](#11-函数模板-template)
		- [11.1 模板显式具体化](#111-模板显式具体化)
		- [11.2 显式实例化与显式具体化](#112-显式实例化与显式具体化)
		- [11.3 完全匹配与最佳匹配](#113-完全匹配与最佳匹配)
		- [11.4 模板函数的发展](#114-模板函数的发展)
		- [11.5 函数声明: 后置返回类型](#115-函数声明-后置返回类型)

---
## 1. CPP 函数基本结构 

- C++ 的函数必须有函数原型, 函数的调用必须有函数的定义

- 一般可以把函数的原型放在头文件中, 由包含的源文件进行定义

- C++ 函数可以重载, C 同一个文件中不允许函数重名

```c++
void Func(int n);	// 函数原型
int main(){
	Func();   // 函数调用, 必须有定义
}

void Func(int n){
	cout << "This is a Function." << endl;
}
```

---
## 2. 函数参数与参数传递

- C++ 一般按值传递参数, 在自身函数的作用域中创建传递参数的副本; 参数按引用传递, 在函数中可能有源数据被修改的可能

- 在函数体内声明的变量通常为自动存储类型, 它们在程序执行过程中自动被分配和释放

---
## 3. 函数与数组

- 可以向函数传递数组, 指针, 结构, 类等 C++ 对象, 传递数组或指针时, 函数操作的对象可能是源数据, 而不是数据的副本

> const 数组

- C++ 按值传递数据, 数组作为参数时, 将地址传递给函数体, 使用 const 修饰数组可以保护该数组的内容不会被修改

```C++
	 void Show_arr(const int arr[], int count);
```

> 指针与 const

* 可以用两种不同的方式将 const 关键字用于指针。
  - 第一种方法是让指针指向一个常量对象，这样可以防止使用该指针来修改所指向的值
  - 第二种方法是将指针本身声明为常量，这样可以防止改变指针指向的位置

- 可以将 const 常量地址赋值给 const 指针, C++ 禁止将常量对象传递给非 const 指针对象, 防止源数据被修改 (但可以使用强制转化突破这种限制)

> 函数与二维数组

```c++
	void Func(int arr[][size], int n);
	void Func(int (*arr)[size], int n);
	// 高维数组
	void Func(int (*arr)[n][m], int N, int M);
```

---
## 4. 函数与其他类型的形参

> 函数与传入字符串 (C-type)

```c++
	Func(char ar[20]);		// char 字符串数组形式
	Func(char* str);		// char 指针地址
	Func("string");			// 字符串字面量	 
```

> 函数与 string 对象

- 通常 string 对象与 C 字符串的用途基本相同, 但传入函数的 string 与结构更像

> 函数与 array 对象

- C++ 中, 类对象是基于结构的, 可以传递副本, 也可以传递源数据指针

```c++
	void show(std::array<int,4> ar);
	void fill(std::array<int,4> * par);
```

---
## 5. 函数递归

```c++
void recurs(argumentlist){
	statements1;
	if(test){
		recurs(arguments);	// 自己调用自己
	}
	statements2;
}
```

- 函数的递归需要设置断开条件, 否则将进入无限循环

- 递归的执行顺序: 由最内层的函数执行结束后逐层向外归还控制权, 自调用处为分界, 函数体上部内容由外向内顺序执行, 函数体下部内容由内向外顺序执行

---
## 6. 函数指针

- 函数的名就是函数的地址, 将函数作为参数进行传递时, 必须传递参数名

- 声明的函数指针的特征标(参数列表)和返回类型与函数类型一致时, 就可将函数地址赋值给函数指针

> 声明函数指针

```c++
void Func(int n);	
void (*pf)(int);	// 函数指针声明

pf = Func;
pf(1);	// 指针方式调用
```

> 简化函数指针声明

- auto 自动类型

- typedef 简化

```c++
void Func();

auto pf = Func;
typedef void (*PF)(const char*, int);	// PF 为函数指针类型别名
PF p1 = func;
```

---
## 7. C++ 内联函数 (inline)

- 内联函数是 C++ 为提高程序运行速度所做的一项改进, 常规函数和内联函数之间的主要区别不在于编写方式，而在于 C++ 编译器如何将它们组合到程序中

- 内联函数的声明必须要在定义与原型声明时, inline 进行修饰, 一般做法是直接省略原型, 在原有原型声明的地方直接定义

- 不能将内联函数设计成递归

- 内联函数也像常规函数一样, 按值传递

```c++
inline void fun(int n){
	using namespace std;
	cout << n << endl;
}
int main(){
	fun(10);
}
```

---
## 8. 引用变量

- C++ 新增了一种复合类型——引用变量。引用是已定义的变量的别名（另一个名称）

- C 和 C++ 使用 & 符号来指示变量的地址。C++ 给 & 符号赋予了另一个含义，将其用来声明引用

- 声明类型引用前, 需要对类型初始化; 而声明指针时不需要初始化类型的值

```c++
	int rats;
	int & RATS = rats;
	// rats 与 RATS 指向相同的值和内存单元
	// 类型声明为 int &，即指向 int 变量的引用
```

> 指针与引用类型

```C++
	int num = 10;
	int & Num = num;
	int * pN = &num;

	// 1. 
	pN = &Num = &num;
	*pN = Num = num;

	// 2.
	若 Num = 12;  则 num 的值为 12
```

> 引用类型作为参数 

- C 只能按值传递参数(可以传递指针绕开值传递的限制), C++ 新增了引用传递新特性

```c++
	void func(int & a, int b);		// pass variables
	void func(int * a, int b);		// pass addresses of variables
	void func(int a, int b);		// pass valus of variables
```

---
### 8.1 对引用类型使用 const

- 使用 const 可以避免无意中修改数据的编程错误；

- 使用 const 使函数能够处理 const 和非 const 实参，否则将只能接受非 const 数据；
  
- 使用 const 引用使函数能够正确生成并使用临时变量。

---
### 8.2 引用传递作为参数的限制

- 引用传递应该传递变量, 不应将值传递给引用类型

```c++
	void fun(int & num);
	int number = 10;
	fun(number);	// 形参 num 是 number 的别名引用

	fun(10);	// 一般不允许这样做, 由于类型不同函数会产生一个匿名的临时变量
```

> 临时变量, 引用参数和 const

- 如果实参与引用参数不匹配，C++ 将生成临时变量, 仅当为 const 引用时

* 如果引用参数是 const，则编译器将在下面两种情况下生成临时变量:
  - 实参的类型正确, 但不是左值(不可修改)
  - 实参的类型不正确, 但可以转换成为正确的类型

```c++
	double refcube(const double & ra){
		return ra * ra * ra;
	}

	double side = 3.0;
	double * pd = &side;
	double & rd = side;
	long edge = 5L;
	double lens[4] = {2.0,5.0,10.0,12.0};

	double c1 = refcube(side);		// ra is side
	double c2 = refcude(lens[2]);	// ra is lens[2]
	double c3 = refcube(rd);		// ra is rd is side
	double c4 = refcube(*pd);		// ra is *pd is side
	double c5 = refcube(edge);	    // ra is temporary var
	double c6 = refcube(7.0);		// ra is tempVar
	double c7 = refcube(side + 10.0)  // ra is tempVar
```

> 引用应用于结构

- 引用非常适合用于结构和类（C++ 的用户定义类型）。
  
- 确实，引入引用主要是为了用于这些类型的，而不是基本的内置类型。

---
### 8.3 函数返回引用

```c++
	void Func1(int & num){
		num++;
		cout << num << endl;
	}
	int & Func2(int & num1, const int & num2){
		return num1 += num2;
	}

	int n1 = 10;
	int n2 = 20;

	Func1(Func2(n1, n2));	// 函数 F2 将 num1 引用返回, 并传递给 F1
```

- 返回引用的函数实际上是被引用的变量的别名。

- 引用返回应避免返回函数终止时不存在的内存单元引用, 即不能返回一个指向临时变量的引用

- 但可以使用 new 来分配新的存储单元, 并返回指向该内存的指针

```c++
const free_throws & clone(free_throws & ft){
	free_throws * pt;
	*pt = ft;
	return *pt;
}
```

> const 用于引用返回

- 引用返回类型是左值类型, 也就是该内存区域可修改, 常规函数的返回类型是右值, 即不能通过地址访问的值

```c++
int & func(int &);
int num = 10;

func(num) = 30; 	// func返回的是 num 的别名, 是左值类型, 因此合法
```

- 如果返回类型是 const 类型, 则变成不可修改左值

--- 
### 8.4 右值引用

- C++ 为左值提供了 & 左值引用的特性, 其特征是不能使用右值对左值引用初始化, 只能通过左值

- C++ 新增了右值引用的特性, 该类型只能通过右值进行初始化

```c++
int num = 10;
// 左值引用
int & a1 = num;
int & a2 = 10;	// ERROR, 右值初始化, 右值无法访问到其地址
const int & a3 = num;	// const 左值引用可以操作左值
const int & a4 = 10;	// const 左值引用可以操作右值

// 右值引用
int && b1 = num; // ERROR, 右值引用不能初始化为左值
int && b2 = num + 10; // 右值引用
b2 = 10;	// 右值引用可以操作右值
const int && b3 = 10; // C++ 允许, 但目前无实际用处
```

- 一般右值引用类型用于移动语义, 完美转发等

---
## 9. 默认参数

- 默认参数指的是当函数调用中省略了实参时自动使用的一个值

```c++
void sum(int n1, int n2 = 1);

// n2 为一个默认参数
sum(1,5);  // 表示不采用默认参数的方式, 将 5 作为 n2 的值
sum(5);	   // 使用默认参数的默认值
```

- 参数列表中的默认参数需要在常规参数之后排列

```c++
void fun(int n, int n1 = 1, int n2 = 2, int n3 =3);// valid
void fun(int n, int n1 = 1, int n2); // invalid
```

---
## 10. 函数重载


- 函数多态是 C++ 在 C 语言的基础上新增的功能。
  
- 默认参数让您能够使用不同数目的参数调用同一个函数，而函数多态（函数重载）让您能够使用多个同名的函数

- 函数重载的关键是函数的参数列表——也称为函数特征标（function signature）

- 构成重载需要同名函数的函数特征标不同, 也就是参数列表不同, 函数可以构成重载, 但函数类型(返回类型)不同不构成重载的条件

```c++
void fun(int);
void fun(double);	// 特征标不同, 与第一个函数构成重载
int fun(int);		// 同名, 返回类型不能决定重载, 特征标不同可构成重载
```

---
## 11. 函数模板 template

- 函数模板是通用的函数描述，也就是说，它们使用泛型来定义函数，其中的泛型可用具体的类型（如 int 或 double）替换

- 通过将类型作为参数传递给模板，可使编译器生成该类型的函数

```c++
template <typename T> 
void Swap(T,T);

Swap(1,2); // T = int
```

> 模板的局限性

- 存在函数体操作的 T 与实际传入的类型行为不一致, 例如传入两个数组时, Swap 进行交换时无法操作数组等于另一个数组的操作

---
### 11.1 模板显式具体化

* 第三代具体化（ISO/ANSI C++ 标准）
  - 对于给定的函数名，可以有非模板函数、模板函数和显式具体化模板函数以及它们的重载版本。
  - 显式具体化的原型和定义应以 template<> 打头，并通过名称来指出类型。
  - 具体化优先于常规模板，而非模板函数优先于具体化和常规模板。

```c++
	// 1. 非模板函数
	void Swap(job &, job &);
	// 2. 模板函数
	template <typeName T> void Swap(T &, T &);
	// 3. 显式具体化模板
	template <> void Swap<job>(job &, job &);
	template <> void Swap(job &, job &); // <job> 本身可选

```

- 如果有多个原型，则编译器在选择原型时，非模板版本优先于显式具体化和模板版本，而显式具体化优先于使用模板生成的版本

---
### 11.2 显式实例化与显式具体化

- 在代码中包含函数模板本身并不会生成函数定义，它只是一个用于生成函数定义的方案

- 编译器使用模板为特定类型生成函数定义时，得到的是模板实例（instantiation）

- 模板并非函数定义，但使用 int 的模板实例是函数定义, 这种实例化方式称为隐式实例化（implicit instantiation）

- C++ 还允许显式实例化（explicit instantiation）。这意味着可以直接命令编译器创建特定的实例

```c++
	// 具体实例化
	template void Swap<int>(int, int);	
	// 实现这种特性的编译器看到这种声明后, 将使用 Swap() 模板生成一个使用 int 类型的实例
```

- 试图在同一个文件（或转换单元）中使用同一种类型的显式实例和显式具体化将出错。

- 还可以通过在程序中使用函数来创建显示实例化

```c++
	template <class T>
	T Add(T a,T b){
		return a + b;
	}
	//...
	int m = 10;
	double x = 10.2;
	cout << Add<double>(x,m) << endl;	// 如果使用 Add(x,m), 会发现函数的调用与模板不匹配
	// 使用 Add<double> 方式可以强制为 double 类型实例化, 并将 int 强制转换成 double
```

- 隐式实例化、显式实例化和显式具体化统称为具体化（specialization）。它们的相同之处在于，它们表示的都是使用具体类型的函数定义，而不是通用描述

- 引入显式实例化后，必须使用新的语法——在声明中使用前缀 template 和 template <>，以区分显式实例化和显式具体化。

```c++
template <class T> void Swap(T &, T &);         // 函数模板
template <> void Swap<job>(job &, job &);		// 显式具体化

int main(void){
	template void Swap<char>(char &, char &);   // 显式实例化
	short a,b;
	Swap(a,b);  // 隐式模板实例化
	
	job n,m;
	Swap(n,m);  // 使用显式具体化模板

	char g,h;
	Swap(g,h);	// 使用显式实例化模板
}
```

---
### 11.3 完全匹配与最佳匹配

- 进行完全匹配时，C++ 允许一些无关紧要的转换, Type 表示任意类型, 也意味着用作实参的函数名与用作形参的函数指针只要返回类型和参数列表相同, 就是匹配的

> 完全匹配允许的无关紧要转换

```c++
	从实参 	   >     到形参
	Type	 		Type &
	Type &   		Type
	Type[]   		* Type
	Type(args) 	    Type(*)(args)
	Type			const Type
	Type			volatile Type
	Type *			const Type
	Type *			volatile Type *
```

> 完全匹配案例

- 由于 Type 与下面的原型都是完全匹配的, 如果有多个匹配的原型, 编译器无法完成重载的解析过程

```c++
	struct blot{int a; char b[10];};
	blot ink = {25, "spots"};

	recycle(ink);
//----------------------------
	void recycle(blot);			// #1: blot >> blot
	void recycle(const blot);	// #2: blot >> const blot
	void recycle(blot &);		// #3: blot >> blot &
	void recycle(const blot &);	// #4: blot >> const blot &
```

* 有时候，即使两个函数都完全匹配，仍可完成重载解析
  - 指向非 const 数据的指针和引用优先与非 const 指针和引用参数匹配。如果只定义了函数 #3 和 #4 是完全匹配的，则将选择 #3
  - const 和非 const 之间的区别只适用于指针和引用指向的数据。如果只定义了 #1 和 #2，则将出现二义性错误。
 
> 函数版本优先级

- 非模板函数 > 显式实例化模板函数 > 显式具体化模板函数 > 隐式模板函数

```c++
void Swap(int,int);							// 非模板函数
template void Swap<double>(double,double);  // 显式实例化
template <> void Swap<job>(job,job);		// 显式具体化
template <class T> void Swap(T,T);			// 隐式模板 
```

> 如何选择函数版本

- 术语最具体（most specialized）并不一定意味着显式具体化，而是指编译器推断使用哪种类型时执行的转换最少

```c++
template <class Type> void recycle(Type t);		// #1
template <class Type> void recycle(Type * t);   // #2

struct blot{int a,char b[10]};
bolt bt = {25,"spots"};

recycle(&bt);
// recycle(&bt) 调用与 #1 模板匹配时, Type 解释为 blot*
// recycle(&bt) 调用与 #2 模板匹配时, Type 解释为 blot
//>> 因此两个隐式实例
// recycle<blot*>(blot*) 与 recycle<blot>(blot *) , #1 被
// 编译器认为更具体, 它需要进行的转换更少
```

* 重载解析将寻找最匹配的函数
  - 如果只存在一个这样的函数，则选择它
  - 如果存在多个这样的函数，但其中只有一个是非模板函数，则选择该函数
  - 如果存在多个适合的函数，且它们都为模板函数，但其中有一个函数比其他函数更具体，则选择该函数
  - 如果有多个同样合适的非模板函数或模板函数，但没有一个函数比其他函数更具体，则函数调用将是不确定的，因此是错误的
  - 如果不存在匹配的函数，则也是错误

---
### 11.4 模板函数的发展

- 在设计模板函数时, 编译器并非总能知道应在声明中使用哪种类型

```c++
template<class T1, class T2>
void ft(T1 x,T2 y){
	//...
	?type? xpy = x + y;
	//... 无法判断 T1 与 T2 相加的结果是什么类型
}
```

- C++11 新增的关键字 decltype 提供了解决方案

> 关键字 decltype (C++11)

- decltype(expression) var;

```c++
int x;
decltype(x) y;	// 表示 y 的类型与 x 相同

decltype(x+y) xpy = x + y; // xpy 与 x+y 的类型相同

// 修复类型无法判断的情况
template<class T1, class T2>
void ft(T1 x,T2 y){
	//...
	decltype(x+y) xpy = x + y;
	//...
}
```

- 如果 expression 是一个没有用括号括起的标识符，则 var 的类型与该标识符的类型相同，包括 const 等限定符

- 如果 expression 是一个函数调用，则 var 的类型与函数的返回类型相同

- 如果 expression 是一个左值，则 var 为指向其类型的引用, expression 是用括号括起的标识符

- 如果前面的条件都不满足，则 var 的类型与 expression 的类型相同

```c++
double x = 1.0;
const double* px = &x;
// 标识符匹配
decltype(x) w;		// w is type of double
decltype(px) pw; 	// pw is type of const double *
// 函数调用匹配
long indeed(int);
decltype(indeed(3)) m;	// m is type long
// 引用
double dd = 4.4;
decltype((dd)) rdd = dd;	// rdd is double &
decltype(dd) w = dd;        // w is double
// 表达式
int i = 1;
int & j = i;
decltype(i+j) ij;   // int
decltype(1L) i2;	// long
```

---
### 11.5 函数声明: 后置返回类型

```c++
template <class T1,class T2>
?type? gt(T1 x,T2 y){
	...
	return x + y;
}
```

- 由于无法预知 x+y 的类型, 无法使用 decltype(x+y) 声明返回类型, 因为已经不在函数的作用域里, 使用后置返回类型格式

```c++
// 对于原型
double h(int x, float y);
// 后置返回
auto h(int x,float y) -> double;

// 模板后置返回
template <class T1,class T2>
auto gt(T1 x,T2 y) -> decltype(x + y)
{
	...
	return x + y;
}
```

---