# CPP 数据类型与运算符

- CPP 基本数据类型与 const
- 算数运算符与类型之间的转换
- 复合类型

---
## 1. 简单变量

### 1.1 整型类型

- 整型有无符号与有符号两种区别

> 有符号类型

```c++
	short s = 1;	// 16bits(至少为)
	int	i = 2;		// 32bits(至少与short一样长)
	long l = 3L;		// 至少32位, 且至少与int一样长
	long long ll = 4LL; 		至少64位, 且至少与long一样长
```

> 无符号类型

```c++
	unsigned short us = 1u;
	unsigned int/unsigned ui = 2u;
	unsigned long ul = 3ul;
	unsigned long long ull = 4ull;
```

> sizeof 运算符

- 可以使用 sizeof 查看当前系统的整型类型对应的大小

```c++
	int num = 0;
	sizeof(int);
	sizeof num;
```

> climits 头文件

- 头文件 climit 定义了符号常量来表示类型的限制, 例如最大值与最小值常量值

> 初始化

```c++
	int a = 1;
	int b(2);
	int c = {3};
```

---
### 1.2 整数字面值与进制

- 整型字面值（常量）是显式地书写的常量, 有三种不同的方式来书写整数, 进制基数分别为 10, 8, 16

```c++
	int num_10 = 9876543210;
	int num_8 =  076543210;	// 八进制 0 前缀
	int num_16 = 0xFEDCBA9876543210;  // 十六进制 0x 前缀
	int num_2 =  0b10101010;	// 二进制 0b 前缀
```

> cout 输出指定进制的数字与进制控制符

- dec 用于指定 cout 以十进制格式显示数字, hex 为十六进制, oct 为八进制

```c++
	int number = 42;
	cout << dec;  // 默认行为
	cout << "decimal for 42 : " << number << endl;
	cout << hex;  // 修改 cout 输出的数字显示格式为十六进制
	cout << "hexadecimal for 42 : " << number << endl;
	cout << oct;  // 修改 cout 输出显示的数字格式为八进制
	cout << "octal for 42 : " << number << endl;
/*
	decimal for 42 : 42
	hexadecimal for 42 : 2a
	octal for 42 : 52
*/	
```

- 不能使用 std 空间中声明的指定标识符作为变量名

---
### 1.3 char 字符与小整数

- char 用来表示计算机系统中的所有基本符号 (0~127), 或表示一个很小的整数

> 输出字符

```c++
	cout << '$';  // 会输出 $ 字符的 ASCII 码
	cout.put('$');	// 输出字符 $
```

- 字符 '\n' 换行符在 cout 输出中可以替换 endl 控制符

> signed char 和 unsigned char

- char 在默认情况下既不是没有符号, 也不是有符号

- 如果需要 char 有某种特定的行为，则可以显式地将类型设置为 signed char 或 unsigned char

- 将 char 用作数值类型, unsigned char 表示 0 ~ 255, signed char 表示 -128 ~ 127

> wchar_t

- 程序需要处理的字符集可能无法用一个 8 位的字节表示, 对于大型字符集, 扩展宽字符类型 wchar_t, 至少 16 位字节

- cin 与 cout 将输入输出看作是 char 流, 对于处理 wchar_t 类型并不适用, iostream 提供 wcin 与 wcout 用于处理 wchar_t 流, L 前缀指示宽字符常量和宽字符串

```c++
	// 宽字符表示,
	wchar_t c_t = L'p';
	wcout << L"tall" << endl;
```

> 新增 char16_t 与 char32_t (C++11)

- C++11 使用 u 表示 char16_t 字符常量值, 使用 U 表示 char32_t 字符常量值

---
### 1.4 bool 类型

- C++ 中新增了 bool 类型 (不同于 C)

- 字面值 true 与 false 可以通过提升转换为 int 类型, true 被转换为 1, 而 false 被转换为 0

- 整数值也可以被隐式转换成为 bool 类型, 任何非 0 值转换成 true (隐式), 0 被转换成 false

```c++
	bool is_ready = true;

	int allowed = true;   // 1
	int is_stop = false;  // 0

	bool start = -100;	// true
	bool stop = 0;		// false
```

---
### 1.5 浮点数

- 计算机把浮点数分成两部分储存, 一部分表示值(基准值), 一部分是对该值放大或缩小(缩放因子, 移动小数点的位置)

```c++
	0.314159 	// 基准值
	10			// 缩放因子
```

> E 表示法

```c++
	3.999E100	>>	3.999 x 10^2
	6E10
```

> 浮点类型

```c++
	float f = 1.0f;		// 至少 32 位
	double d = 2.0;		// 至少 48 位且不少于 float
	long double ld = 3.0L;	// 至少和 double 一样多
```

> cfloat 浮点限制

- 标记限制各浮点类型的范围与常量值

> cout 输出浮点数

- 通常 cout 会删除浮点数结尾的 0, 将 1.230000 显示为 1.23

---
## 2. 算术运算符

- 操作数运算的结果类型一般以其中操作数最大的类型为基准

```c++
	// 二元
	+, -, *, /, %
```

---
### 2.1 类型转变

> 自动类型转换

- 将一种算术类型的值赋给另一种算术类型的变量时，C++ 将对值进行转换；

- 表达式中包含不同的类型时，C++ 将对值进行转换；

- 将参数传递给函数时，C++ 将对值进行转换。

- 整型与浮点型之间的转换存在潜在数据精度丢失或截断的问题
  
> 以 { } 方式初始化进行的转换

- C++11 将使用大括号的初始化称为列表初始化（listinitialization）, 这种初始化常用于给复杂的数据类型提供值列表

- 这种方式对类型转换的要求更严格, 列表初始化不允许缩窄 (narrowing)(即变量的类型可能无法表示赋值给它的值), 不允许浮点型转换为整型, 部分转换可能被允许

```c++
	const int code = 66;
	int x = 66;
	char c1 = {31325};			// narrowing, not allowed
	char c2 = {66};				// allowed, can hold 66
	char c3 {code};				// allowed, can hold code(const)
	char c4 = {x};				// not allowed, x is not constant
	x = 31325;
	char c5 = x;				// allowed 默认方式的初始化允许
```

> 表达式中的转换

1. 如果有一个操作数的类型是 long double，则将另一个操作数转换为 long double。
2. 否则，如果有一个操作数的类型是 double，则将另一个操作数转换为 double。
3. 否则，如果有一个操作数的类型是 float，则将另一个操作数转换为 float。
4. 否则，说明操作数都是整型，因此执行整型提升。
5. 在这种情况下，如果两个操作数都是有符号或无符号的，且其中一个操作数的级别比另一个低，则转换为级别高的类型。
6. 如果一个操作数为有符号的，另一个操作数为无符号的，且无符号操作数的级别比有符号操作数高，则将有符号操作数转换为无符号操作数所属的类型。
7. 否则，如果有符号类型可表示无符号类型的所有可能取值，则将无符号操作数转换为有符号操作数所属的类型。
8. 否则，将两个操作数都转换为有符号类型的无符号版本

> 传递参数时的转换

- 传递参数时的类型转换通常由 C++ 函数原型控制, 也可以取消原型对参数传递的控制

- C++ 将对 char 和 short 类型（signed 和 unsigned）应用整型提升, 将 float 参数提升为 double

> 强制类型转换

- 通过强制类型转换机制显式地进行类型转换(两种形式)

```c++
	(long)number;	// 1
	long(number);	// 2
```

- C++ 引入了 4 个强制转换运算符, 例如 static_cast\<type>(val)

---
### 2.2 auto 声明

- auto 声明的变量会自动推断其类型 (不同于 C)

```c++
	auto n = 100;   // n is int
	auto x = 1.5;	// x is double
	auto y = 1.3e12L;  // y is long double
```

---
## 3. 复合类型

### 3.1 数组

- 数组（array）是一种数据格式，能够存储多个同类型的值

```c++
	typeName arrayName[arraySize];
```

> 初始化

```c++
	// 1. 声明规则
	int cards[4] = {1,2,3,4};
	int hand[4];
	hand[4] = {5,6,7,8}; // ERROR, hand[4] 超出索引, 且只能代表单个元素
	hand = cards;		// ERROR, hand 为数组的地址, 为不可修改对象

	// 2. 初始化
	int arr1[5] = {1,2};	// 其他会初始化为 0(default value)
	int arr2[500] = {0};	// 将全部元素初始化为 0 
	int arr2[] = {};		// 将初始化为 0
	int arr3[] = {1,2,3,4,5,6};	// 大小自动计算 
	int arr4[]{1,2,3,4,5,6,7};	// 可省略等号 (C++11)

	// 3. 数组的长度
	int count = sizeof(arr1)/sizeof(int);
```

---
### 3.2 字符串

- 字符串是存储在内存的连续字节中的一系列字符, C++ 保留了 C 风格的字符串, 同时也扩容了一种基于 string 类库的方法

```c++
	char str[] = {'H','e','l','l','o','\0'};	// C 风格 
	char str2[] = "World";
```

> 字符串的拼接

```c++
	"Hello" " world""!"   "大拇指"	// 之间可以是 0 ~ 多个空格
```

> 字符串输入

```c++
	char name[81];
	using namespace std;
	cin >> name;	
	cout << "Your Name is " << name << endl;
```

> 每次读取一行字符串输入

- istream 中的类（如 cin）提供了一些面向行的类成员函数

- 面向行的输入: getline() 将丢弃换行符

```c++
	cin.getline(char[],count);
	// char[]  >> 数组 Name, 
	// count   >> 读取的字符数目
```

- 面向行的输入: get() 将换行符保留在输入序列

```c++
	cin.get(name,ArSize);		
	cin.get(name2,ArSize);		// a problem
	// 首次调用后, 换行符被保留在输入队列, 二次调用首字符就是换行符

	cin.get(); 	// 读取下一个字符, 可以用来跳过换行符

	// 演示 1
	cin.get(name,ArSize);		// read first line
	cin.get();					// read newline
	cin.get(name2,ArSize);		// read second line

	// 演示 2
	cin.get(name,ArSize).get();	// 类函数拼接
```

> 空行和其他问题

- 当 get() 读取空行时, 将设置失效位（failbit）, 接下来的输入将被阻断, 可以使用 cin.clear() 恢复输入

- 若输入行包含的字符数比指定的多时, getline() 与 get() 将余下的字符留在队列中, 且 getline 会设置失效位, 并关闭后面的输入

> 混合输入字符串和数字

```c++
#include <iostream>
int main(){
	using namespace std;
	cout << "What year was your house built?\n";
	int year;
	cin >> year;
	cout << "What is its street address?\n";
	char address[80];
	cin.getline(address,80);
	cout << "Year built: " << year << endl;
	cout << "Address: " << address << endl;
	cout << "Done!\n";
	return 0;
}
// 问题: 当cin读取年份，将回车键生成的换行符留在了输入队列中
// 后面的cin.getline( )看到换行符后，将认为是一个空行，并将一个空字符串赋给address数组。
// 解决: 可以通过 (cin >> year).get(); 跳过换行符 
```

---
### 3.3 string 类简介

- ISO/ANSI C++98 标准通过添加 string 类扩展了 C++ 库，因此现在可以 string 类型的变量, 而不是字符数组来存储字符串。

```c++
#include <iostream>
#include <string>

int main()
{
	using namespace std;
	char arr1[20];
	char arr2[20] = "CHAR Arr2";
	string str1;
	string str2 = "STRING Str2";

	cout << "Input a line: ";
	cin >> arr1;
	cout << "Input another line: ";
	cin >> str1;
	cout << "Then here are some lines: \n";
	cout << arr1 << " " << arr2 << " "
		 << str1 << " " << str2 << endl;
	cout << "The third letter in " << arr2 << " is " << arr2[2] << endl;
	cout << "The third letter in " << str2 << " is " << str2[2] << endl;

	return 0;
}
```

> 字符串的拼接与附加

- string 类可以使用运算符 + 将两个 string 对象合并起来

```c++
	string str3;
	str3 = str1+ str2;
	str3 += "this is a string"
```

> string 对象的长度

- 使用 size() 获取字符串的长度

```c++
	int size = str1.size();
```

> string 类 I/O

- 比对 C 风格字符串与 C++ string 类, 两者在输入输出上句法略有不同

```c++
// strtype.cpp -- line input
#include <iostream>
#include <string>     // make string class available
#include <cstring>    // C-style string library
int main()
{
    using namespace std;
    char charr[20] = {}; 
    string str;

    cout << "Length of string in charr before input: " 
         << strlen(charr) << endl;
    cout << "Length of string in str before input: "
         << str.size() << endl;
    cout << "Enter a line of text:\n";
	// 1. C-type 输入
    cin.getline(charr, 20);     // indicate maximum length
    cout << "You entered: " << charr << endl;
    cout << "Enter another line of text:\n";
    // 2. C++ 输入
	getline(cin, str);          // cin now an argument; no length specifier
    cout << "You entered: " << str << endl;
    cout << "Length of string in charr after input: " 
         << strlen(charr) << endl;
    cout << "Length of string in str after input: "
         << str.size() << endl;
    // cin.get();
    return 0; 
}
/*
	Length of string in charr before input: 0
	Length of string in str before input: 0
	Enter a line of text:
	Hello
	You entered: Hello
	Enter another line of text:
	World
	You entered: World
	Length of string in charr after input: 5
	Length of string in str after input: 5
*/
```

> 原始 (raw) 字符串

- 在原始字符串中，字符表示的就是自己, 序列 \n 不表示换行符, 

- 原始字符串将 "(和)" 用作定界符，并使用前缀 R 来标识原始字符串

- 原始字符串中的引号与其他转义字符可以显示原义

```c++
	cout << R"(This "Line" uses "\n" instead of endl.)" << '\n';
	// This "Line" uses "\n" instead of endl.
```

- 在 R 与 ( ) 之间可以自定义定界符, 要求在字符串的开头与结尾都要包含相同的字符

```c++
	cout << R"++("this is a new line.")++" << endl;
```

- R 可以与其他字符串结合, 以标识 wchar_t 等类型的原始字符串 (Ru, UR等)

---
### 3.4 结构

- 结构是用户定义的类型，而结构声明定义了这种类型的数据属性

```c++
struct m_st{
	char name[20];
	float volume;
	double price;
};

// C-type 
struct m_st book = {"Hi!", 1.5, 99};
// C++
m_st book2 {"new book", 15, 22};
```

> 位字段

- C++ 也允许指定占用特定位数的结构成员，这使得创建与某个硬件设备上的寄存器对应的数据结构非常方便

- 字段的类型应为整型或枚举

```c++
struct torget{
	unsigned int SN : 4;  // 4 bits for SN
	unsigned int : 4;	// 4 bits unused
	bool goodin : 1;   // valid input (1 bit)
	bool goodTorgle : 1; // successful
} tg ={14, true, false};
```

---
### 3.5 共用体

- 共用体（union）是一种数据格式，它能够存储不同的数据类型，但只能同时存储其中的一种类型 (实际的大小以包含的最大类型为准)

```c++
	union one4all{
		int int_val;
		long long_val;
		double double_val;
	} val = {long_val = 15L};

	cout << one4all.long_val;
	// 调用其他成员时可能会出现意向不到的结果, 本质上各类型使用的内存区域是同一个
```

- 共用体的用途之一是，当数据项使用两种或更多种格式（但不会同时使用）时，可节省空间。

- 默认初始化时以第一个成员为标准

- 共用体常用于操作系统数据结构或硬件数据结构

---
### 3.6 枚举

- C++ 的 enum 工具提供了另一种创建符号常量的方式，这种方式可以代替 const

- 可以为枚举项设定初始值, 默认从 0 顺次赋值

- 由于枚举项是常量, 对于枚举变量可以用枚举项赋值给变量, 但不允许使用整型常量值直接赋值

```c++
	enum Color{
		red,blue,green,white = 10
	};
	Color mC = red;  // valid
	mC = 1500;	      // invalid
```

- C++ 的枚举并没有定义算数运算

```c++
	mC = blue;
	mC++;	// invalid
	mC = red + black;  // invalid
```

> 枚举与整型

- 枚举量是整型, 可被提升为 int 类型, 但 int 类型不能自动转换成枚举类型

- 整型需要强制转换, 可以赋给枚举变量

> 枚举的取值范围

- 最初对于枚举来说，只有声明中指出的那些值是有效的, 但 C++ 现在通过强制类型转换，增加了可赋给枚举变量的合法值

- 每个枚举都有取值范围（range），通过强制类型转换，可以将取值范围中的任何整数值赋给枚举变量，即使这个值不是枚举值

```c++
	enum bits{
		one = 1,
		two = 2,
		four = 4,
		eight = 8,
	};

	mgflag = bits(6);	// valid, 6 在 bits 的范围内
```

* 取值范围的定义: 
  - 要找出上限，需要知道枚举量的最大值
  - 找到大于这个最大值的、最小的 2 的幂，将它减去 1，得到的便是取值范围的上限
  - 如一个枚举的最大枚举量是 101, 则它的上限是 128-1 = 127
  - 当最小值不小于 0, 下限为 0; 若小于 0, 为最小枚举量负方向的最近 2 的幂, 并加上 1
  - 如一个枚举的最小枚举量为 -6, 则它的下限是 -8+1 = -7;

- C++11 扩展了枚举，增加了作用域内枚举（scoped enumeration）

---
### 3.7 指针和自由存储空间

* 计算机程序在存储数据时必须跟踪的三种基本属性
  - 信息存储在何处
  - 存储的值为多少
  - 存储的信息是什么类型

- 以指针为基础, 指针是一个变量, 其存储的是值的地址, 通过地址可以找到常规变量的值

```c++
	int number = 100;
	int *pN = &number;		// number 的地址
	cout << *pN << " " << pN << endl;
```

- 使用常规变量时, 值是指定的值, 而地址为派生量

> C++ 内存管理编程理念核心 (指针与 C++ 基本原理)

- 面向对象编程与传统的过程性编程的区别在于，OOP 强调的是在运行阶段（而不是编译阶段）进行决策。运行阶段指的是程序正在运行时，编译阶段指的是编译器将程序组合起来时。
  
- 运行阶段决策就好比度假时，选择参观哪些景点取决于天气和当时的心情；而编译阶段决策更像不管在什么条件下，都坚持预先设定的日程安排。

- 运行阶段决策提供了灵活性，可以根据当时的情况进行调整; 编译阶段决策坚持编译前的设定, 例如声明数组时, 数组的长度就已经设定好了, 运行时不能进行修改

- 使用 OPP 时, 可能在运行阶段确定数组的长度, 因此可以在程序运行时创建数组, C++ 采用 new 请求正确数量的内存以及使用指针来跟踪新分配的内存的位置

> 指针的危险

- 在 C++ 中创建指针时，计算机将分配用来存储地址的内存，但不会分配用来存储指针所指向的数据的内存 (使用未初始化的指针是危险的行为), 使用之前需要将指针指向一个确定的, 适当的地址

> new 分配内存

- 变量是在编译时分配的有名称的内存，而指针只是为可以通过名称直接访问的内存提供了一个别名

- C 中可以使用 malloc() 来分配内存, C++ 可以使用 new 运算符, 当创建变量时, new 会为该数据类型分配一块未使用的正确的内存, 并返回该内存地址

```c++
	typeName* pointer_name = new typeName;
	int* ptr = new int;
```

- new int 表示需要适合存储 int 的内存

- 对于指针，需要指出的另一点是，new 分配的内存块通常与常规变量声明分配的内存块不同。变量的值都存储在被称为栈（stack）的内存区域中，而 new 从被称为堆（heap）或自由存储区（freestore）的内存区域分配内存

> delete 释放内存

- 当需要内存时，可以使用 new 来请求; delete 运算符，它使得在使用完内存后，能够将其归还给内存池

```c++
	int* ptr = new int;
	//... use ptr
	delete ptr;
```

- delete 用于释放 ptr 指向的内存, 但不会删除该指针本身; 不能使用 delete释放声明变量所获取的内存

```C++
	int num = 15;
	int* ptr = &num;
	delete ptr;			// not allowed
```

- new 与 delete 要配对使用, 防止发生内存泄露, 被分配的内存没有被释放将无法在使用

> new 创建动态数组

- 在编译时给数组分配内存被称为静态联编（static binding），意味着数组是在编译时加入到程序中的。

- 使用 new 时，如果在运行阶段需要数组，则创建它；如果不需要，则不创建。还可以在程序运行时选择数组的长度。这被称为动态联编（dynamic binding）

- 数组是在程序运行时创建的。这种数组叫作动态数组（dynamic array）

```c++
	int* pArr = new int[10];
	// ... use Arr
	delete [] pArr;
	// 表示释放整个数组
```

> new 与 delete 注意事项

- 不要使用 delete 来释放不是 new 分配的内存。
- 不要使用 delete 释放同一个内存块两次。
- 如果使用 new [ ] 为数组分配内存，则应使用 delete [ ] 来释放。
- 如果使用 new [ ] 为一个实体分配内存，则应使用 delete（没有方括号）来释放。
- 对空指针应用 delete 是安全的。

---
### 3.8 指针, 数组和算数指针

- 指针和数组基本等价的原因在于指针算术（pointer arithmetic）和 C++ 内部处理数组的方式

```c++
	int Arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int* pArr = Arr;

	int counter = -1;
	// 1. 数组模式访问元素
	while(++counter < 10){
		cout << "ARR: " << Arr[counter] << endl;
		cout << "pARR: " << *(pArr + counter) << endl;
	}
```

- 可以使用数组模式或者指针模式访问数组元素, 指针递增 1 表示, 地址值递增自身代表类型的字节大小

- 数组名为该数组首元素的地址

> 指针算术

- C++ 允许将指针和整数相加。加1的结果等于原来的地址值加上指向的对象占用的总字节数

- 可以将一个指针减去另一个指针，获得两个指针的差, 即得到两个元素的间隔。

> 自动存储、静态存储和动态存储

- 根据用于分配内存的方法，C++ 有 3 种管理数据内存的方式

* 自动存储: 在函数内部定义的常规变量使用自动存储空间，被称为自动变量（automatic variable），这意味着它们在所属的函数被调用时自动产生，在该函数结束时消亡
  - 自动变量通常存储在栈中。这意味着执行代码块时，其中的变量将依次加入到栈中，而在离开代码块时，将按相反的顺序释放这些变量，这被称为后进先出（LIFO）

* 静态存储: 静态存储是整个程序执行期间都存在的存储方式。使变量成为静态的方式有两种：一种是在函数外面定义它；另一种是在声明变量时使用关键字 static：
  - 静态变量可能存在于程序的整个生命周期

* 动态存储: new 和 delete 运算符提供了一种比自动变量和静态变量更灵活的方
法。它们管理了一个内存池，这在 C++ 中被称为自由存储空间（free store）或堆（heap）
  - 但 new 和 delete 的相互影响可能导致占用的自由存储区不连续，这使得跟踪新分配内存的位置更困难

> 栈、堆和内存泄漏

- 使用 new 运算符在自由存储空间（或堆）上创建变量后，没有调用 delete, 则即使包含指针的内存由于作用域规则和对象生命周期的原因而被释放，在自由存储空间上动态分配的变量或结构也将继续存在

- 这将导致内存泄漏。被泄漏的内存将在程序的整个生命周期内都不可使用；这些内存被分配出去，但无法收回

- 这种泄漏还会给一些操作系统或在相同的内存空间中运行的应用程序带来负面影响，导致它们崩溃

---
### 3.9 数组的替代品: vector 与 array

> 模板类 vector

- 模板类 vector 类似于 string 类，也是一种动态数组, 基本上，它是使用 new 创建动态数组的替代品。实际上，vector 类确实使用 new 和 delete 来管理内存，但这种工作是自动完成的。

```c++
	vector<typeName> vt(n_elem);

#include <vector>
using namespace std;
int main(){
	vector<int> vi;			// create a zero-size array
	int n;
	cin >> n;
	vector<double> vd(n);	// create am array of n doubles
}
```

> 模板类 array (C++11)

- 与数组一样，array 对象的长度也是固定的，也使用栈（静态内存分配），而不是自由存储区，因此其效率与数组相同

```c++
	array<typeName, n_elem> arr; // n_elem 不能是变量

#include <array>
int main(){
	using namespace std;
	array<int,5> ai;
}
```

> 数组, vector 与 array 的区别

- 都是用标准数组法来访问各个元素

- array 和数组存储在栈中, vector 存储在堆或自由存储区中

- array 对象可以赋给 array, 但数组只能逐元素复制数据

- array 与 vector 可以使用 at() 成员函数访问元素, 并在运行期间获取非法索引(数组在超出边界的索引并不检查, 但 at() 的额外检查能够降低以外超界错误的概率, 但额外检查带来的运行时间会更长)

---