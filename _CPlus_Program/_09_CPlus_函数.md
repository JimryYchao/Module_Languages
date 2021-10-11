# C Plus 函数

---
- [C Plus 函数](#c-plus-函数)
  - [1. C 语言函数结构](#1-c-语言函数结构)

---
## 1. C 语言函数结构

- 函数（function）是完成特定任务的独立程序代码单元

- 程序在 3 处使用定义函数的标识符
  - 函数原型(function prototype) 告诉编译器函数的类型
  - 函数调用(function call)告诉在此处执行函数
  - 函数定义(function definition)指定函数要做什么

- 函数和变量一样，有多种类型。因此在任何程序在使用函数之前都必须要声明该函数的原型, 需要在 main() 函数定义前面出现, 函数原型指明了函数的返回值类型和函数接受的参数类型

```c
    void FuncA(void);   // 函数原型

    int main(void){
        FuncA();        // 函数调用
    }

    void FuncA(void){
        printf("Function start");
    }
```


















