# Lua Introduction

//运算符 .. %
---

- [Lua Introduction](#lua-introduction)
  - [//运算符 .. %](#运算符--)
  - [第1章 Lua 语言简介](#第1章-lua-语言简介)
    - [1.1 Lua 特性](#11-lua-特性)
    - [1.2 Lua 应用场景](#12-lua-应用场景)
  - [第2章 Lua 概念](#第2章-lua-概念)
    - [2.1 注释规则](#21-注释规则)
    - [2.2 标识符原则](#22-标识符原则)
    - [2.3 全局变量与局部变量规则](#23-全局变量与局部变量规则)
    - [2.4 关键字](#24-关键字)
  - [第3章 Lua 数据类型](#第3章-lua-数据类型)
    - [3.1 type( ) 获取变量的类型](#31-type--获取变量的类型)
    - [3.2 【nil】空类型](#32-nil空类型)
    - [3.3 【boolean】布尔类型](#33-boolean布尔类型)
    - [3.4 【number】数值类型](#34-number数值类型)
    - [3.5 【string】字符串类型](#35-string字符串类型)
    - [3.6 【table】表结构](#36-table表结构)
    - [3.7 【function】函数](#37-function函数)
    - [3.8 【thread】线程类型](#38-thread线程类型)
    - [3.9 【userdata】自定义类型](#39-userdata自定义类型)
  - [第4章 Lua 语法结构](#第4章-lua-语法结构)
    - [4.1 赋值](#41-赋值)
    - [4.2](#42)

---
## 第1章 Lua 语言简介

- Lua是一种轻量小巧的脚本语言，用标准 C 语言编写并以源代码形式开放，其设计目的是为了嵌入应用程序中，从而为应用程序提供灵活的扩展和定制功能。
- *.lua 文本后缀

---
### 1.1 Lua 特性

- 轻量级：它用标准 C 语言编写并以源代码形式开放，编译后仅仅一百余 K，可以很方便的嵌入别的程序里。

- 可扩展：Lua提供了非常易于使用的扩展接口和机制：由宿主语言(通常是C或C++)提供这些功能，Lua可以使用它们，就像是本来就内置的功能一样。

- 其他特性：
  - 支持面向过程 (procedure-oriented) 编程和函数式编程 (functional programming) ；
  - 自动内存管理；只提供了一种通用类型的表（table），用它可以实现数组，哈希表，集合，对象；
  - 语言内置模式匹配；闭包 (closure) ；函数也可以看做一个值或参数；提供多线程（协同进程，并非操作系统所支持的线程）支持；
  - 通过闭包和 table 可以很方便地支持面向对象编程所需要的一些关键机制，比如数据抽象，虚函数，继承和重载等。

---
### 1.2 Lua 应用场景

- 游戏开发
- 独立应用脚本
- Web 应用脚本
- 扩展和数据库插件如：MySQL Proxy 和 MySQL WorkBench
- 安全系统，如入侵检测系统

---
## 第2章 Lua 概念

- Lua 是动态类型语言，变量不要类型定义，只需要为变量赋值。 值可以存储在变量中，作为参数传递或结果返回。 

---

### 2.1 注释规则

```lua
    --1. 单行注释内容 (--)

    --2. 多行注释内容 (--[[ ]]--)
        --[[ 
            首行
                次行
                     第三行  
        ]]--

    --PS: 支持多行注释格式还有 
        --[[ ... ]]     
        --[[ ... --]]
        --[=[ ... ]=]--

    --推荐的多行注释 (--[=[ ... ]=]--)
```

### 2.2 标识符原则

- 由 [A-Za-z0-9_] 组成, 不建议使用汉字和内置保留字, 数字不可开头, 区分大小写

```lua
    Anumber
    Bboolean
    Cstring
    D_Function1
    Function2
```

---
### 2.3 全局变量与局部变量规则

- 在 Lua 上下文中, 未 local 修饰的变量均为全局变量, 包括在函数体之内, 未初始化过的变量默认值为 nil

```lua
    print(b)--nil
    b = 10  --- 全局变量, 可在其他 lua 上下文中调取访问
    print(b)--10

    local c = 10 ---局部变量, 仅在该变量作用域范围内访问
```

---
### 2.4 关键字

```lua
    -- 【声明相关】
        
        local       --声明局部变量
      --function    --声明函数数据类型

    -- 【值相关】

        nil         --空
        true false  --boolean 两种值
        return      --返回类型关键字
        end         --结束作用域
        goto        --跳转
        and         --逻辑与
        or          --逻辑或
        not         --逻辑非
    
    -- 【循环语句相关】
    
        for/in/do/end     -- for 循环 
        repeat/until      -- repeat 循环
        while/do/end      -- while 循环  

    -- 【条件语句相关】
        
        if/then/else/elseif/    -- if 条件语句

```

---
## 第3章 Lua 数据类型

> Lua 中有 8 个基本类型分别为：nil、boolean、number、string、userdata、function、thread 和 table。

|类型|描述|
|:----|:----|
|nil|只有值nil属于该类，表示一个无效值（在条件表达式中相当于false）。|
|boolean|包含两个值：false和true。|
|number|表示双精度类型的实浮点数（有效数字15到16位）|
|string|字符串由一对双引号或单引号来表示|
|function|由 C 或 Lua 编写的函数|
|userdata|表示任意存储在变量中的C数据结构|
|thread|表示执行的独立线路，用于执行协同程序|
|table|Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字、字符串或表类型。在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。|
|||

---
### 3.1 type( ) 获取变量的类型


- type(变量) 返回该变量的变量类型的字符串。

```lua
    print(type("Hello world"))      --> string
    print(type(10.4*3))             --> number
    print(type(print))              --> function
    print(type(type))               --> function
    print(type(true))               --> boolean
    print(type(nil))                --> nil
    print(type(type(X)))            --> string
```

---
### 3.2 【nil】空类型

- nil 类型表示一种没有任何有效值，它只有一个值 nil，例如打印一个没有赋值的变量，便会输出一个 nil 值。
- 任何未显式初始化的变量， 默认值均为 nil
- 对于全局变量和 table，nil 还有一个"删除"作用，给全局变量或者 table 表里的变量赋一个 nil 值，等同于把它们删掉。

```lua
    tab1 = { key1 = "val1", key2 = "val2", "val3" }
    for k, v in pairs(tab1) do
        print(k .. " - " .. v)  --<1 - val3><key1 - val1><key2 - val2>
    end
----------------------------------
    tab1.key1 = nil
    for k, v in pairs(tab1) do
        print(k .. " - " .. v)  --<1 - val3><key2 - val2>//key1对被删除
    end
```

---
### 3.3 【boolean】布尔类型

- 在Lua中，boolean 类型存在 true 与 false 两种值
- 在条件判断中，nil 判定为 false，非 nil 类型返回 true 

```lua
    print(type(true))--boolean-
    print(type(false))--boolean
    print(type(nil))--nil
-----------------------------------------------
    if false or nil then
        print("至少有一个是 true")
    else
        print("false 和 nil 都为 false")
    end
        -- false 和 nil 都为 false
------------------------------------------------
    if 0 and "string" then
        print("数字 0 和 string 是 true")
    else
        print("数字 0 为 false")
    end
        -- 数字 0 和 string 是 true
```

---
### 3.4 【number】数值类型

- Lua 中整型与浮点型整合为同一类型 number

```lua
    print(type(2))
    print(type(2.2))
    print(type(0.2))
    print(type(2e+1))
    print(type(0.2e-1))
    print(type(7.8263692594256e-06))
```

---
### 3.5 【string】字符串类型

  - 字符串由一对双引号或单引号来表示。
  - [[ ]] 来表示多行字符串

```lua
    string1 = "this is string1"
    string2 = 'this is string2'
    string3 = [[    多行字符串
                声明      ]]
```

- 对一个数字字符串上进行算数操作时，Lua 会尝试将这个数字字符串转成一个数字
  
```lua
    print("2" + 6)--8
    print("2" + "6")--8
    print("2 + 6")--2 + 6
    print("-2e2" * "6")--   -1200
    print("error" + 1)--//error：转换error为number失败
```

---
### 3.6 【table】表结构

- 在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。也可以在表里添加一些数据，直接初始化表。

- Lua 数组索引是从 1 开始排序的，因此，使用pairs遍历打印输出时，会先打印 table 的数组部分，然后打印键值对部分。

```lua
-- 创建一个空的 table
    local tbl1 = {}
 
-- 直接初始表
    local tbl2 = {"apple", "pear", "orange", "grape"}
```

- Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字或者是字符串。

```lua
    tabl = {a =1,b = 2,[1]=666}
```

> 可以在表中像声明变量一样配置表的键值对，但是数字索引需要用中括号括起来。

```lua
    a = {}
    key = 10
    a[key] = 22
    a[key] = a[10] + 11

    print(a[10])  -- 33
    print(a[key]) --33
```

> table 外部声明成员

```lua
    a = {}
   -- a[number] = value   table 外部声明成员 

    a[key1] = 1
    a[key2] = 2
    a[key3] = a[key1] + a[key2]

    for k, v in pairs(a) do
        print(k .. " : " .. v)
    end

    --[[
            1 : 1
            str : 3
            999 : 2
    ]]
```

- 不同于其他语言的数组把 0 作为数组的初始索引，在 Lua 里表的默认初始索引一般以 1 开始。

```lua
local tbl = {"apple", "pear", "orange", "grape"}
for key, val in pairs(tbl) do
    print("Key", key)--1，2，3，4
end
```

- table 无固定长度大小，有新数据添加时 table 长度会自动增长，没初始化的 table 都是 nil。

```lua
a3 = {}
for i = 1, 10 do
    a3[i] = i
end
a3["key"] = "val"
print(a3["key"])--val
print(a3["none"])--nil
```

---
### 3.7 【function】函数

- 在 Lua 中，函数是被看作是"第一类值（First-Class Value）"，函数可以存在变量里。

```lua
    function factorial1(n)
        if n == 0 then
            return 1
        else
            return n * factorial1(n - 1)--5*4*3*2*1//递归算法
        end
    end
    print(factorial1(5))--120

    factorial2 = factorial1
    print(factorial2(5))--120
```

- 当函数作为变量名传入函数时，作为实参使用匿名写法，作为匿名函数传入

```lua
    function testFun(tab,fun)
            for k ,v in pairs(tab) do
                    print(fun(k,v));
            end
    end
    --------------------------------
    tab = {key1="val1",key2="val2"};

    testFun(tab,
            function(key,val)--匿名函数
                  return key.."="..val;
            end);
```

---
### 3.8 【thread】线程类型

- 在 Lua 里，最主要的线程是协同程序（coroutine）。它跟线程（thread）差不多，拥有自己独立的栈、局部变量和指令指针，可以跟其他协同程序共享全局变量和其他大部分东西。

- 线程跟协程的区别：线程可以同时多个运行，而协程任意时刻只能运行一个，并且处于运行状态的协程只有被挂起（suspend）时才会暂停。

---
### 3.9 【userdata】自定义类型

- userdata 是一种用户自定义数据，用于表示一种由应用程序或 C/C++ 语言库所创建的类型，可以将任意 C/C++ 的任意数据类型的数据（通常是 struct 和 指针）存储到 Lua 变量中调用。

---
## 第4章 Lua 语法结构

### 4.1 赋值

- 赋值是改变一个变量的值和改变表域的最基本的方法。

- Lua 可以对多个变量同时赋值，变量列表和值列表的各个元素用逗号分开，赋值语句右边的值会依次赋给左边的变量。

```lua
    a = "hello" .. "world"
   
    a, b = 10, 2*x    -->       a=10; b=2*x
```

- 交换数值：遇到赋值语句Lua会先计算右边所有的值然后再执行赋值操作，所以我们可以这样进行交换变量的值。

```lua
    x, y = y, x                     -- swap 'x' for 'y'
    
    a[i], a[j] = a[j], a[i]         -- swap 'a[i]' for 'a[j]'
```

- 当变量个数和值的个数不一致时，Lua会一直以变量个数为基础采取以下策略：
  - 当变量个数 > 值的个数，按变量个数补足nil。
  - 当变量个数 < 值的个数，多余的值会被忽略。

**注意：如果要对多个变量赋值必须依次对每个变量赋值。**

```lua
    a, b, c = 0, 1
    print(a,b,c)             --> 0   1   nil
    ------------------------------------------------------------
    a, b = a+1, b+1, b+2     -- value of b+2 is ignored
    print(a,b)               --> 1   2
    ------------------------------------------------------------
    a, b, c = 0
    print(a,b,c)             --> 0   nil   nil
```

- 多值赋值经常用来交换变量，或将函数调用返回给变量, lua 

```lua
a, b = f()
```

- 应该尽可能的使用局部变量，有两个好处：
  - 避免命名冲突。
  - 访问局部变量的速度比全局变量更快。

---




---
### 4.2 
