# CPP 逻辑语句

- 循环语句与关系表达式
- 分支语句与逻辑运算符
- typedef

---
- [CPP 逻辑语句](#cpp-逻辑语句)
	- [1. 循环](#1-循环)
		- [1.1 for 循环](#11-for-循环)
		- [1.2 while 循环](#12-while-循环)
		- [1.3 do while 循环](#13-do-while-循环)
		- [1.4 基于范围的 for 循环](#14-基于范围的-for-循环)
	- [2. 分支](#2-分支)
		- [2.1 if-else](#21-if-else)
		- [2.2 字符函数库 cctype](#22-字符函数库-cctype)
		- [2.3 三元条件运算符](#23-三元条件运算符)
		- [2.4 switch 语句](#24-switch-语句)
	- [3. break 与 continue](#3-break-与-continue)
	- [4. 简单文件输入/输出](#4-简单文件输入输出)
		- [4.1 文本 I/O 和文本文件](#41-文本-io-和文本文件)
		- [4.2 写入到文本文件中](#42-写入到文本文件中)

---
## 1. 循环

### 1.1 for 循环

> for 循环组成部分

```c++
	for(initialization; test-expression; update-expression){
		// code
	}
```

> C-风格字符串的比较

- 由于数组名是数组的地址, 用引号括起的字符串常量也是其地址

```c++
	// 比较
	word == "mete";	// 不合法,  word 为字符串 char 数组
```

- 比较的是两者的地址是否相同, 即使两者包含相同的字符, 结果可能也是否定的(地址比较)

- 由于 C++ 将 C-风格字符串视为地址，因此如果使用关系运算符来比较它们，将无法得到满意的结果

- 应使用 C-风格字符串库中的 strcmp() 函数来比较, 如果两个字符串相同，该函数将返回零

> 比较 string 类字符串

- 可以使用关系运算符比较 string 类字符串是否相等

```c++
	string word = "meta";
	bool isEq = word != "mate";		// false
```

---
### 1.2 while 循环

> while 循环组成部分

```c++
	while(test-expression){
		// code
	}
```

> 在设计循环时

- 指定循环终止的条件。

- 在首次测试之前初始化条件。

- 在条件被再次测试之前更新条件。

> 延时循环

* ANSI C 和 C++ 库中有一个函数 clock(), 返回程序开始执行后所用的系统时间 
  - clock() 返回时间的单位不一定是秒
  - 其次，该函数的返回类型在某些系统上可能是 long，在另一些系统上可能是unsigned long 或其他类型。

- 头文件 ctime 中定义了一个符号常量 CLOCKS_PER_SEC, 该常量等于每秒钟包含的系统时间单位数, 将系统时间除以这个值，可以得到秒数

```c++
	clock_t start = clock();
	clock_t delay = 10 * CLOCKS_PER_SEC;
	while(clock() - start < delay)
		;
	cout << "Done!" << endl;
```

> 类型别名

```c++
	// 方式一	预处理指令
	#define BYTE char;

	// typedef 运算
	typedef typeName aliasName;
	typedef char byte;
```

---
### 1.3 do while 循环

> do while 循环组成部分

- 出口条件（exit condition）循环

```c++
	do{
		// code
	}while(test-expression)
```

---
### 1.4 基于范围的 for 循环

- C++11 新增了一种循环：基于范围（range-based）的 for 循环, 这简化了一种常见的循环任务：对数组（或容器类，如vector和array）的每个元素执行相同的操作

> 循环结构

```c++
	for(element:Arr{element}){
		// code
	}

	// ex
	for(int x:{1,2,3,4,5,6,7}){
		sum += x;
	}
```

> cin 输入

- 若 ch 是一个 char 变量

```c++
	// 1. 传入下一个字符给 ch
	cin >> ch;	// cin 将忽略空格, 换行符, 制表符

	// 2. 调用读取输入中的下一个字符
	bool _bl = cin.get(ch);	// 不管该字符是什么都会存储在 ch 中
		// 到达 EOP 时, 返回 false
	
	// 3. 获取下一个输入的字符
	ch = cin.get();		//  返回 EOF 表示到达文件尾部 
```

---
## 2. 分支

### 2.1 if-else

```c++
	if(test-expression){
		// code
	}else if(test-expression){
		// code
	}else{
		// code
	}
```

> 逻辑运算符

```c++
	&&  与	and
	||  或	or
	!   非  not
```

---
### 2.2 字符函数库 cctype

```c++
isalnum(ch) 	若字母数字，即字母或数字，该函数返回true
isalpha(ch) 	若字母，该函数返回true
iscntrl(ch) 	若控制字符，该函数返回true
isdigit(ch) 	若数字（0～9），该函数返回true
isgraph(ch)		若除空格之外的打印字符，该函数返回true
islower(ch)		若小写字母，该函数返回true
isprint(ch) 	若打印字符（包括空格），该函数返回true
ispunct(ch) 	若标点符号，该函数返回true
isspace(ch)		若标准空白字符，如空格、进纸、换行符、回车、水平制表符
					或者垂直制表符，该函数返回true
isupper(ch) 	若大写字母，该函数返回true
isxdigit(ch) 	若十六进制数字，即0～9、a～f或A～F，该函数返回true
tolower(ch) 	若大写字符，则返回其小写，否则返回该参数
toupper(ch) 	若小写字符，则返回其大写，否则返回该参数
```

---
### 2.3 三元条件运算符

```c++
	exp1 ? exp_yse : exp_no
	// 由 exp1 的判断情况决定返回 exp_yes 还是 exp_no
```

---
### 2.4 switch 语句

> 格式

```c++
	switch(integer-expression){
		case label1 : statement(s);
		case label2 : statement(s);
			break;
		case label3 : statement(s);
		default : statement(s);
	}
```

- 可以使用枚举量作为 switch 语句的 case 标签

---
## 3. break 与 continue

- break 和 continue 语句都使程序能够跳过部分代码。
  
- 可以在 switch 语句或任何循环中使用 break 语句，使程序跳到 switch 或循环后面的语句处执行。
  
- continue 语句用于循环中，让程序跳过循环体中余下的代码，并开始新一轮循环

---
## 4. 简单文件输入/输出

### 4.1 文本 I/O 和文本文件

- 使用 cin 进行输入时，程序将输入视为一系列的字节，其中每个字节都被解释为字符编码。输入一开始都是字符数据 (文本数据), cin 对象负责将文本转换为其他类型

```c++
	char ch
	cin >> ch;	// cin 会将输入的字符赋值给 ch, 这里并未发生转换

	int n;
	cin >> n;	// cin 会一直读取数字字符直至中断, 通过计算并转换

	double x
	cin >> x;	// cin 读取数字, 句点, 直至遇到第一个不属于浮点数的字符

	char word[20];
	cin >> word;	// 不断读取直至遇到空白字符

	char word[20];
	cin.getline(word, 20);	/* cin将不断读取，直到遇到换行符（示例输入行
	少于50个字符）。所有字符都将被存储到数组 word 中，并在末尾加上一个空字
	符。换行符被丢弃 */
```

---
### 4.2 写入到文本文件中

> 对于文件输入，C++ 使用类似于 cout 的东西

- 必须包含头文件 iostream。
- 头文件 iostream 定义了一个用处理输出的 ostream 类。
- 头文件 iostream 声明了一个名为 cout 的 ostream 变量（对象）。
- 必须指明名称空间 std；例如，为引用元素 cout 和 endl，必须使用编译指令 using 或前缀 std::。
- 可以结合使用 cout 和运算符 << 来显示各种类型的数据。

> 文件输出

- 必须包含头文件 fstream。
- 头文件 fstream 定义了一个用于处理输出的 ofstream 类。
- 需要声明一个或多个 ofstream 变量（对象），并以自己喜欢的方式对其进行命名，条件是遵守常用的命名规则。
- 必须指明名称空间 std；例如，为引用元素 ofstream，必须使用编译指令 using 或前缀 std::。
- 需要将 ofstream 对象与文件关联起来。为此，方法之一是使用 open() 方法。
- 使用完文件后，应使用方法 close() 将其关闭。
- 可结合使用 ofstream 对象和运算符 << 来输出各种类型的数据。

> 使用文件输出的主要步骤

1．包含头文件fstream。
2．创建一个ofstream对象。
3．将该ofstream对象同一个文件关联起来。
4．就像使用cout那样使用该ofstream对象。

> outfile.cpp

```c++
	
```

---