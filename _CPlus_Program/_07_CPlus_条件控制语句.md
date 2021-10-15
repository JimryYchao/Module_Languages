# 条件控制语句

- 关键字： if 、else 、switch 、continue 、break 、case 、default、goto
- 逻辑运算符与条件运算符
- 条件分支语句与多重选择语句
- 标签跳转

---
- [条件控制语句](#条件控制语句)
  - [1. if 条件分支语句](#1-if-条件分支语句)
  - [2. 逻辑运算符](#2-逻辑运算符)
  - [3. 条件运算符 ?:](#3-条件运算符-)
  - [4. 多重选择 switch 和 break](#4-多重选择-switch-和-break)
  - [5. goto 语句](#5-goto-语句)

---
## 1. if 条件分支语句

```c
    if(exp1){
        //do....
    }else if(exp2){
        //do....
    }else{
        //do....
    }
```

> getchar 与 putchar

```c    
#define SPACE ' '
#include <stdio.h>
int main(void)
{
	char ch;
	ch = getchar(); // 读取一个字符
	while (ch != '\n') // 当一行未结束时
	{
		if (ch == SPACE) // 留下空格
			putchar(ch); // 该字符不变
		else
			putchar(ch + 1); // 改变其他字符
		ch = getchar(); // 获取下一个字符
	}
	putchar(ch); // 打印换行符
	return 0;
}
```

---
## 2. 逻辑运算符

```
    &&      与
    ||      或
    !       非
```

> 运算法则

```c
    true && true = true
    false && false/true = false
    true || false/true = true
    false || false = false
```

> 逻辑运算符备选拼写 iso646.h

```c
    include<iso646.h>

    and  等价于 &&
    or   等价于 ||
    not  等价于  !
```

> 优先级

- 非 ( ! ) > 与 ( && ) > 或 ( || )

> 短路原则

- 当 && 左侧不满足结果为 true 的条件时, 右侧表达式不会被计算

- 当 || 左侧满足结果为 true 时, 右侧表达式不会被计算

---
## 3. 条件运算符 ?:

- C 提供条件表达式（conditional expression）作为表达 if else 语句的一种便捷方式，该表达式使用?:条件运算符

```C
    x = (条件判断式) ? true_exp : false_exp

    //等价于
    x = (y<0) ? y : -y

    if(y<0){
        x = y;
    }else{
        x = -y;
    }
```

---
## 4. 多重选择 switch 和 break

```c
int main(void)
{
	char ch = getchar();
	switch (ch) {
	case 'A':
		printf("%c", ch);
	case 'B':
		printf("%c", ch+1);
		break;
	case 'C':
		printf("%c", ch);
    default:
        break;
	}
}
```

> switch 语句

```c
    switch(整数表达式){
        case 常量1: do... break;
        case 常量2: do... break;
        ...
        default: do...
    }
```

- case 语句没有 break 时, 允许 case 之间自上而下贯穿, 直至遇到 default 或语句块结束, 或遇到 break 语句;

- case 的类型必须能包含 switch(exp) 指定校验选择的数据类型(必须是整数类型), 至少要类型一致;

- break 语句会跳出 switch 语句块, default 分支表示当所有未满足 case 分支时的最终选择(可选分支)

- C 语言的 case 一般都指定一个常量值，不能使用一个范围

---
## 5. goto 语句

- goto 语句有两部分: goto 与 标签名

- 一般条件跳转 if ~ else 结构可以满足, goto 语句一般用于出现问题时从一组嵌套循环中跳出, 而 break 只能跳出当前循环

```c
int main(void)
{
    int funct,i,j;
    while(funct > 0){
        for (i = 0; i < 100; i++)
        {
            for ( j = 0 ;j < 50 ;j++)
            {
                //do.....
                if (condition)
                    goto out;
            }
            //do.....
        }
        //do.....
    }
    out:
        //do....
    return 0;
}
```

---