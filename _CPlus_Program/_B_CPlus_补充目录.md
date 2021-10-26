# 补充目录清单

---
- [补充目录清单](#补充目录清单)
	- [1. 新增的 C99 和 C11 的 ANSI C 库](#1-新增的-c99-和-c11-的-ansi-c-库)
		- [1.1 断言 assert.h](#11-断言-asserth)
		- [1.2 C11 静态断言 _Static_assert](#12-c11-静态断言-_static_assert)
		- [1.3 复数 complex.h](#13-复数-complexh)
		- [1.4 错误报告 errno.h](#14-错误报告-errnoh)
		- [1.5 浮点环境 fenv.h (C99)](#15-浮点环境-fenvh-c99)

---
## 1. 新增的 C99 和 C11 的 ANSI C 库

---
### 1.1 断言 assert.h

- assert.h 头文件中把 assert() 定义为一个宏。在包含 assert.h 头文件之前定义宏标识符 NDEBUG，可以禁用 assert() 宏。

- 通常用一个关系表达式或逻辑表达式作为 assert() 的参数，如果运行正常，那么程序在执行到该点时，作为参数的表达式应该为真

```c
	void assert(int exprs);
	// 如果 expts 为非 0(真), 宏无效,
	// 如果为 0(假), 则会显示该表达式所在的行号与文件名, 然后调用 abort()
```

---
### 1.2 C11 静态断言 _Static_assert

- 关键字声明: _Static_assert(常量表达式,字符串字面量), 提供一个编译时检查

- 如果对常量表达式求值为0，编译器会给出一条包含字符串字面量的错误消息；否则，没有任何效果。

---
### 1.3 复数 complex.h

- C99 提供支持复数计算, C11 进一步支持了这个功能

- _Imaginary 类型为可选类型, C99 的实现必须提供 _Complex 类型, C11 提供可选

> complex.h 提供的宏

```c
	complex 	展开为类型 _Complex
	_Complex_I  展开为 const float _Complex 类型的表达式, 其值的平方为 -1
	//如果支持虚数类型
	imaginary 		展开为 _Imaginary
	_Imaginary_I	展开为 const float _Imaginary 类型, 平方为 -1

	I 	展开为 _Complex_I 或 _Imaginary_I
```

> C 与 C++ 实现复数方面

- C 通过 complex.h 头文件支持，而 C++ 通过 complex 头文件支持。
  
- 而且，C++ 使用类来定义复数类型。

> 使用数学公式

- 可以使用 STDC CX_LIMITED_RANGE 编译指令来表明是使用普通的数学公式（设置为 on 时）, 还是要特别注意极值（设置为 off 时）

```c
	#include <complex.h>
	#pragma STDC CX_LIMITED_RANGE on
```

> 复数数学公式 

- 库函数分为 3 种：double、float、long double, float 和 long double 版本只需要在函数名后面分别加上 f 和 l。

```c
	// PS 角度的单位是弧度

	// 1. 反三角函数 (返回角度: 弧度)
	double complex cacos(double complex z);		// 返回 z 的复数反余弦
	double complex casin(double complex z);		// 返回 z 的复数反正弦
	double complex catan(double complex z);		// 返回 z 的复数反正切
	
	// 2. 三角函数
	double complex ccos(double complex z);		// 返回 z 的复数余弦
	double complex csin(double complex z);		// 返回 z 的复数正弦
	double complex ctan(double complex z);		// 返回 z 的复数正切

	// 3. 反双曲线
	double complex cacosh(double complex z);	// 返回 z 的复数反双曲余弦
	double complex casinh(double complex z);	// 返回 z 的复数反双曲正弦
	double complex catanh(double complex z);	// 返回 z 的复数反双曲正切

	// 4. 双曲线
	double complex ccosh(double complex z);		// 返回 z 的复数双曲余弦
	double complex csinh(double complex z);		// 返回 z 的复数双曲正弦
	double complex ctanh(double complex z);		// 返回 z 的复数双曲正切
	
	// 5. 指数与对数
	double complex cexp(double complex z);		// 返回 e 的 z 次幂复数值
	double complex clog(double complex z);		// 返回 z 的自然对数的复数值
	double cabs(double complex z);				// 返回 z 的绝对值或大小
	
	// 6. z 的 y 次幂
	double complex cpows(double complex z, double complex y);	

	// 7. 复数平方根
	double complex csqrt(double complex z);	

	// 8. 以弧度为单位返回 z 的相位角 (或幅角)
	double carg(double complex z);	

	// 9. 以实数返回 z 的虚部
	double cimag(double complex z);

	// 10. 返回 z 的共轭复数
	double complex conj(double complex z);
	
	// 11. 返回 z 在黎曼球面上的投影
	double complex cponj(double complex z);	
	
	// 12. 返回实部为 x, 虚部为 y 的复数
	double complex CMPLX(double x, double y);

	// 13. 以实数形式返回 z 的实部
	double creal(double complex z);	
```

---
### 1.4 错误报告 errno.h

- errno.h 头文件支持较老式的错误报告机制。该机制提供一个标识符（或有时称为宏） ERRNO 可访问的外部静态内存位置

> 标准提供了 3 个宏值表示特殊的错误

```c
	EDOM 	函数调用中的域错误 (参数越界)
	ERANGE	函数返回值的范围错误 (返回值越界)
	EILSEQ  宽字符转换错误
```

---
### 1.5 浮点环境 fenv.h (C99)

