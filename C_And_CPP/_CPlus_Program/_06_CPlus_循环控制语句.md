# 循环控制语句

- 关键字：for、while、do while
- 使用关系运算符构建控制循环的表达式
- 循环与循环辅助

---
- [循环控制语句](#循环控制语句)
  - [1. 关系表达符](#1-关系表达符)
    - [1.1 真假值](#11-真假值)
    - [1.2 _Bool 类型](#12-_bool-类型)
    - [1.3 关系运算符优先级](#13-关系运算符优先级)
  - [2. 入口条件循环 while](#2-入口条件循环-while)
  - [3. 入口条件循环 for](#3-入口条件循环-for)
  - [4. 出口条件循环 do while](#4-出口条件循环-do-while)
  - [5. 循环辅助 continue 与 break](#5-循环辅助-continue-与-break)
  - [6. 使用循环的注意事项](#6-使用循环的注意事项)

---
## 1. 关系表达符

```
    <   小于
    <=  小于等于
    >   大于
    >=  大于等于
    ==  相等
    !=  不等
```

- 关系运算符用于构建控制语句中的条件判断表达式(关系表达式)

- 关系表达式不能用于比较字符串的大小

- 由于浮点数精度的问题, 比较浮点数的大小尽量使用 < 和 > , 使用 fabs() 函数返回浮点值的绝对值。

- 关系表达式的返回值：1 表示 true，0 表示 false

---
### 1.1 真假值

- 在测试表达式中，整数 0 表示为 false 值，非 0 值均为 true

```c
    int num = 10;
    while(num--){
        printf("Num: %d",num);
    }
```

---
### 1.2 _Bool 类型

- _Bool 类型变量只能存储 0(假) 或 1(真), 其他非 0 值赋值给 _Bool 会被设置为 1

```c
    int num;
    _Bool isOpen = 1;
    while(isOpen){
        isOpen = (scanf("%u",&num) == 1);
        printf("NUM: %d",num);
    }
```

- C99 提供 stdbool.h 使得 bool 成为 _Bool 的别名, 用 true 和 false 分别定义为 1 和 0 的符号常量

---
### 1.3 关系运算符优先级

- 高优先级: <, <=, >, >=

- 低优先级: ==, !=

---
## 2. 入口条件循环 while 

- while 循环是使用入口条件的有条件循环

```c
    while(expression){
        statement
    }
```

- expression 使用关系表达式

- statement 为循环体语句, while 语句直至不满足关系表达式时, 跳出循环

- 可以使用 if 与 break 控制提前跳出循环

```c
#include <stdio.h>
int main(void)
{
	int num = 0;
	while (++num < 100) {
		printf("NUM: %d\n", num);
		if (num == 50)
			break;
	}
	printf("BREAK SUCCESS: %d", num);
}
/*
    ......
	NUM: 49
	NUM: 50
	BREAK SUCCESS: 50
*/
```

---
## 3. 入口条件循环 for

```
    for(初始化表达式 ; 测试表达式 ; 更新表达式) -- 控制表达式
    {
        循环体语句块
    }
```

- 对于for, 使用 ( , ) 用于分隔多个子表达式组合成初始化或更新表达式

```c
#include <stdio.h>
int main(void)
{
	int a, b;
	for (a = 1, b = 10; a < b; a++, b--) {
		printf("mul: %d\n", a * b);
	}
}
/*
	mul: 10
	mul: 18
	mul: 24
	mul: 28
	mul: 30
*/
```

---
## 4. 出口条件循环 do while

```c
    do{
        statement
    }while ( expression );
```

- 至少循环一次, 再进入条件判断

---
## 5. 循环辅助 continue 与 break

- continue 终止当前循环体语句跳转到测试表达式

- break 会终止包含它的最近循环, 并执行下一阶段
  
---
## 6. 使用循环的注意事项

- 注意循环的测试条件要能使循环结束；

- 确保循环测试中的值在首次使用之前已初始化；

- 确保循环在每次迭代都更新测试的值。

---