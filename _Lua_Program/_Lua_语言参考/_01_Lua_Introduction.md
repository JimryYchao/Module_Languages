# Lua Introduction(Lua 5.3)

---

- [Lua Introduction(Lua 5.4)](#lua-introductionlua-54)
  - [第1章 Lua 语言简介](#第1章-lua-语言简介)
    - [1.1 Lua 特性](#11-lua-特性)
    - [1.2 Lua 应用场景](#12-lua-应用场景)
    - [1.3 Lua 错误处理](#13-lua-错误处理)
      - [1.3.1 捕获错误](#131-捕获错误)
  - [第2章 Lua 基本概念](#第2章-lua-基本概念)
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
    - [4.2 索引](#42-索引)
    - [4.3 循环语句 —— while](#43-循环语句--while)
    - [4.4 循环语句 —— repeat](#44-循环语句--repeat)
    - [4.5 循环语句 —— for](#45-循环语句--for)
    - [4.6 条件语句 —— IF](#46-条件语句--if)
    - [4.6 函数 function](#46-函数-function)
    - [4.7 函数 —— 可变参数(...)](#47-函数--可变参数)
    - [4.8 函数 —— 闭包原则](#48-函数--闭包原则)
  - [5. 运算符](#5-运算符)
    - [5.1 算数运算符](#51-算数运算符)
    - [5.2 关系运算符](#52-关系运算符)
    - [5.3 逻辑运算符](#53-逻辑运算符)
    - [5.4 其他运算符](#54-其他运算符)
    - [5.5 三目运算实现](#55-三目运算实现)
  - [5.6 运算符优先级](#56-运算符优先级)

---
## 第1章 Lua 语言简介
### 1.1 Lua 特性

- Lua是一种功能强大、高效、轻量级、可嵌入的脚本语言。 它支持过程式编程、面向对象编程、函数式编程、数据驱动编程和数据描述。
- Lua结合了简单的过程语法和基于关联数组和可扩展语义的强大数据描述结构。
- Lua是动态类型的，通过使用基于寄存器的虚拟机解释字节码来运行，并具有自动内存管理和分代垃圾收集功能，这使它成为配置、脚本编制和快速原型的理想选择。
- Lua 采用标准C语言编写，是标准C和c++的共同子集。 Lua发行版包括一个名为Lua的主机程序，它使用Lua库提供一个完整的、独立的Lua解释器，供交互或批处理使用。
- Lua 的可拓展性保证它可以嵌入到主机客户机中。宿主程序可以调用函数来执行一段Lua代码，可以写入和读取Lua变量，可以注册要被Lua代码调用的C函数。 通过使用C函数，Lua可以被扩充以适应广泛的不同领域，从而创建共享语法框架的定制编程语言。

---
### 1.2 Lua 应用场景

- 游戏开发，独立应用脚本，Web 应用脚本
- 扩展和数据库插件如：MySQL Proxy 和 MySQL WorkBench
- 安全系统，如入侵检测系统

---
### 1.3 Lua 错误处理

- Lua 中的一些操作可能会引发错误。错误中断程序的正常流程，程序可以通过捕获错误继续运行。
- Lua 代码可以通过调用 error 函数显式地抛出错误。(这个函数永远不会返回。)

---
#### 1.3.1 捕获错误

- 要在 Lua 中捕获错误，可以使用 pcall(或 xpcall)执行受保护调用。函数pcall在保护模式下调用给定函数。运行函数时出现的任何错误都将停止其执行，并且控制将立即返回给 pcall, pcall 将返回一个状态代码(boolean，与错误信息)。

```lua
    func = function(...)
        local a1 = select(1, ...)
        local a2 = select(2, ...)
        print(a1 + a2)
    end

    a,b = pcall(func,100,"str")

    print(a,b)    ----- false //attempt to add a 'number' with a 'string'
```

---
## 第2章 Lua 基本概念

- Lua 是动态类型语言，变量不需要类型定义，只需要为变量赋值。 值可以存储在变量中，作为参数传递或结果返回。 

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
- 一般约定，以下划线开头连接一串大写字母的名字（比如 _VERSION）被保留用于 Lua 内部全局变量。

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

- Lua 是一种动态类型语言，因此 Lua 的变量没有类型之分，声明的变量仅有值的区别，所有的值都可以存储在变量中，作为参数传递给其他函数。
- 表、函数、线程和 (完整的)userdata 值都是对象:变量实际上并不包含这些值，只是对它们的引用。赋值、传递参数和函数返回总是操作对这些值的引用;这些操作并不意味着任何类型的复制。

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

- nil 表示"**值为空**"，任何未显式初始化的变量，默认值均为 nil。
- 给全局变量或者 table 表里的变量赋一个 nil 值，等同于把它们删掉。
- nil 不同于其他值，在 table 中代表一个缺席的键。

```lua
    tab1 = { key1 = "val1", key2 = "val2", "val3" }
    for k, v in pairs(tab1) do
        print(k .. " - " .. v)  
        --[[
            1    - val3
            key1 - val1
            key2 - val2
        --]]
    end
----------------------------------
    tab1.key1 = nil
    for k, v in pairs(tab1) do
        print(k .. " - " .. v)  
        --[[
            1    - val3
            key2 - val2
            //key1对被删除
        --]]
    end
```

---
### 3.3 【boolean】布尔类型

- 在Lua中，boolean 类型存在 true 与 false 两种值
- 在条件判断中，nil 判定为 false，非 nil 类型返回 true 

```lua
    print(type(true))   -- boolean
    print(type(false))  -- boolean
    print(type(nil))    -- nil
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

- Lua 中整型与浮点型整合为同一类型 number(Double64 与 Int64)
- 操作数运算时溢出时会进行环绕操作。
- Lua 数的两种子类型之间存在自动转换，

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

- 类型 string 表示不可变的字节序列。字符串由一对双引号或单引号来表示。
- [[ ]] 来表示多行字符串

```lua
    string1 = "this is string1"
    string2 = 'this is string2'
    string3 = [[    多行字符串
                声明      ]]
```

> 对一个数字字符串上进行算数操作时，Lua 会尝试将这个数字字符串转成一个数字
  
```lua
    print("2" + 6)      -- 8
    print("2" + "6")    -- 8
    print("2 + 6")      -- 2 + 6
    print("-2" * "6")   -- -12
    print("error" + 1)  -- error：转换 error 为 number 失败
```

> 字符串拼接 .. 与字符串长度 #

```lua
    print('1'..'2')     --- 12
    print(#'hello')     --- 5
```

---
### 3.6 【table】表结构

- 类型表实现了关联数组，即不仅可以有数字作为索引，还可以有除 nil 和 NaN 以外的任何 Lua 值作为索引的数组。
- 在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。也可以在表里添加一些数据，直接初始化表。
- Lua 数组索引是从 1 开始排序的，因此，使用pairs遍历打印输出时，会先打印 table 的数组部分，然后打印键值对部分。
- 表可以是异构的；也就是说，它们可以包含所有类型的值( nil 除外)。任何与值 nil 相关联的键都不被认为是表的一部分。相反，任何不属于表的键都有一个关联的值 nil，因此可以使用 nil 赋值 table 中的 key，将其关联的 value 失效。
- table 是 Lua 中唯一的数据结构机制；它们可以用来表示普通数组、列表、符号表、集合、记录、图表、树等。为了表示记录，Lua 使用字段名作为索引。语言通过提供 table.name 作为 \["name"]的语法糖来支持这种表示。
- 表字段的值可以是任何类型。特别是，由于函数是一级值，所以表字段可以包含函数。因此，表也可以携带方法。

> 整数与浮点值作为 table 键的二义性

- 表的索引遵循语言中原始相等的定义。表达式 a\[i] 和 a\[j] 表示相同的表元素，当且仅当 i 和 j 是 raw 相等(即在没有元方法的情况下相等)。特别地，具有整型值的浮点数与它们各自的整数相等 (例如1.0 == 1)。
- 为了避免二义性，任何用作键的浮点数如果与整数相等，都会被转换为该整数。例如，如果写入\[2.0]= true，则实际插入到表中的键将是整数 2。


```lua
-- 创建一个空的 table
    local tbl1 = {}
 
-- 直接初始表
    local tbl2 = {"apple", "pear", "orange", "grape"}
```

> Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字或者是字符串。

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

> 不同于其他语言的数组把 0 作为数组的初始索引，在 Lua 里表的默认初始索引一般以 1 开始。

```lua
local tbl = {"apple", "pear", "orange", "grape"}
for key, val in pairs(tbl) do
    print("Key", key)--1，2，3，4
end
```

> table 无固定长度大小，有新数据添加时 table 长度会自动增长，没初始化的 table 都是 nil。

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
            return n * factorial1(n - 1)    --5*4*3*2*1//递归算法
        end
    end
    print(factorial1(5))    --120

    factorial2 = factorial1
    print(factorial2(5))    --120
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
- Lua线程与操作系统线程无关。Lua在所有系统上都支持协程，即使是那些不支持线程的系统。

---
### 3.9 【userdata】自定义类型

- userdata 是一种用户自定义数据，用于表示一种由应用程序或 C/C++ 语言库所创建的类型，可以将任意 C/C++ 的任意数据类型的数据（通常是 struct 和 指针）存储到 Lua 变量中调用。
- userdata类型允许在Lua变量中存储任意的C数据。userdata 值表示一个原始内存块。有两种类型的 userdata: 完整 userdata，它是一个由 Lua 管理的内存块对象，以及轻量级 userdata，它只是一个 C 指针值。Userdata 在 Lua 中没有预定义的操作，除了赋值和标识测试。通过使用元表，程序员可以为完整的 userdata 值定义操作。Userdata 值不能在 Lua 中创建或修改，只能通过 C API。这保证了主程序和 C 库拥有数据的完整性。

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

> ***注意：如果要对多个变量赋值必须依次对每个变量赋值。***

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

### 4.2 索引

- \[ ]  ：对于表和字符串可以使用[] 进行元素访问。

- table 还可以点出元素。

```lua
t[i]
t.i                 -- 当索引为字符串类型时的一种简化写法
gettable_event(t,i) -- 采用索引访问本质上是一个类似这样的函数调用
```

---
### 4.3 循环语句 —— while

- while 循环(满足既定条件后循环)

```lua
    while (condition) do
        statement<循环体语句>
    end
-----------------------------------
    a=10
    while( a < 20 )
    do
       print("a 的值为:", a)
       a = a + 1
    end
```

---
### 4.4 循环语句 —— repeat

- repeat ... until(直至满足条件后跳出循环)
    
```lua
    repeat
        statements<循环体语句>
    until (condition)
-----------------------------------
    a = 10
    repeat
       print("a的值为:", a)
       a = a + 1
    until( a > 15 )
```

---
### 4.5 循环语句 —— for

- 数值 FOR 循环

```lua
    for var = exp1 , exp2 [,exp3] do  
        <循环体>  
    end  
    --[[
        【exp1】 起始值
        【exp2】 最终值
        【exp3】 步长数  -- 默认为 1，参数可选
         表达式 exp 开始时仅运行一次
    --]]

    for i=10,1,-1 do   --递减1，循环范围 10 ~ 1
        print(i)
    end
```

- 泛型 FOR 循环

  - 泛型 for 循环通过一个迭代器函数来遍历所有值，类似C#中的 foreach 语句。
  
  - Lua 编程语言中泛型 for 循环语法格式：

```lua
    a = {"one", "two", "three"}
    for i, v in ipairs(a) do 
    --i是数组索引值，v是对应索引的数组元素值。ipairs是Lua提供的一个迭代器函 数，用来迭代数组。
        print(i, v)
    end 
---------------------------------------------------
    days = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"}  
    for i,v in ipairs(days) do  
        print(v) 
    end           --按照数组的索引依次遍历，从1开始
```

---
### 4.6 条件语句 —— IF

- 控制结构的条件表达式结果可以是任何值，**Lua认为false和nil为假，true和非nil为真。**

```lua
    if <condition> then
        <执行体>
    elseif <condition> then
        <执行体>
    else
        <执行体>
    end
```

---
### 4.6 函数 function

- 在Lua中，函数是对语句和表达式进行抽象的主要方法。既可以用来处理一些特殊的工作，也可以用来计算一些值。

- Lua 提供了许多的内置函数，你可以很方便的在程序中调用它们，如**print()**函数可以将传入的参数打印在控制台上。

- Lua 函数主要有两种用途：
  1.完成指定的任务，这种情况下函数作为调用语句使用；
  2.计算并返回值，这种情况下函数作为赋值语句的表达式使用。

```lua
    -- 声明方式一
    [local] function name(arg1,arg2,...)
        <方法体>
        [return] result
    end

    -- 声明方式二
    [local] name = function(arg1,arg2,...)
        <方法体>
        [return] result
    end

--------------------------------------------------
    -- exam
    local func = function(x,y)
        local z = x*2 + y-2
        return z
    end

    print(func(2,3))  ----5
```

---

- 函数可以作为参数传入另一个函数中。

```lua
    myprint = function(param)
    print("这是打印函数 -   ##",param,"##")
    end
    function add(num1,num2,functionPrint)
    result = num1 + num2
    -- 调用传递的函数参数
    functionPrint(result)
    end
    myprint(10)
    -- myprint 函数作为参数传递
    add(2,5,myprint)
```

- 函数多返回值: lua 可以 return 多个值

```lua
    function Func()
        return 1,2,3
    end

    a,b,c = Func()

    print(a,b,c)    --- 1  2  3
```

---
### 4.7 函数 —— 可变参数(...)

- Lua 函数可以接受可变数目的参数，和 C 语言类似，在函数参数列表中使用 ... 表示函数有可变的参数。
- 向函数传递可变参数时, 需要内部声明表结构接收参数
- 有时候我们可能需要几个固定参数加上可变参数，固定参数必须放在变长参数之前

```lua
    function add(...)  
        local s = 0  
        table = {...}
        for i, v in ipairs(table) do   
        --> {...} 表示一个由所有变长参数构成的表结构  
        s = s + v  
        end  
        return s  
    end  
    print(add(3,4,5,6,7))  --->25
```

> 使用 select 函数遍历可变参数列表

```lua
    select('#', ...)   --返回可变参数的长度
    select(n, ...)     --返回位于第 n 位的参数, n 不能超过最大长度
---------------------------------------------------------
    function foo(...)  
        for i = 1, select('#', ...) do  -->获取参数总数
            --select获取到传入的可变参数的数目
            local arg = select(i, ...); -->读取参数
            --选择出位于第i个位置之后的可变参数
            print("arg", arg);  
        end  
    end  
 
    foo(1, 2, 3, 4);  
```   

---
### 4.8 函数 —— 闭包原则

- 闭包原则：**闭包就是能够读取其他函数内部变量的函数**。例如在javascript中，只有函数内部的子函数才能读取**局部变量**，所以闭包可以理解成“**定义在一函数内部的函数**“。在本质上，**闭包是将函数内部和函数外部连接起来的桥梁**。

```lua
------------------------
    function F8()
      return function()
      print(123)
      end
    end
    F = F8()
    F()--123
------------------------
    --Lua的闭包
    function F9(x)
      --改变函数的生命周期
      return function(y)
      return x+y
      end
    end
    F10 = F9(15)
    --[[
    返回的函数类型会把F函数的临时变量存储起来，
    从而改变了传入的15的生命周期。
    ]]

    print(F10(5))-- 15+5 = 20
------------------------
```

---
## 5. 运算符

### 5.1 算数运算符

```lua
    c = a + b ---- 加法

    c = a - b ---- 减法
    
    c = a * b ---- 乘法
    
    c = a / b ---- 除法
   
    c = a % b ---- 取余

    c = a ^ b ---- 幂运算

    c = -a   ----- 符号运算
```

---
### 5.2 关系运算符

```lua
    a > b ----- 大于

    a < b ----- 小于

    a >= b ---- 大于等于

    a <= b ---- 小于等于

    a == b ---- 等于

    a ~= b ---- 不等于
```

---
### 5.3 逻辑运算符

```lua
    a and b ---- 逻辑与
    a or b ----- 逻辑或
    not true --- 逻辑非
```

> 在Lua中的逻辑运算符也支持短路原则，左操作数不满足,则右操作数不执行。

```lua
    -- and(&&) or(||) not(!)
    print(true and false)   --false
    print(false or true)    --true
    print(not true)         --false

    ---- Lua的逻辑运算支持短路,左操作数不满足,则右操作数不执行

    print(false and print("123"))   
                --<false>//print("123被短路")，并不执行
    print(true and print("123"))
                --false ;返回 123  nil//(print()方法的返回  值是nil）
```

---
### 5.4 其他运算符

```lua
    --   # : 数组的长度
    print(#{1,2,3,4,5,6}) --- 6

    --   .. : 字符串拼接符
    print('1'..2)  ---12
        -- 拼接符第一位仅能为 字符类型
```

---
### 5.5 三目运算实现

```lua
    a = exp and exp1 or exp2
    -- exp 为 true  返回 exp1 的值
    -- exp 为 false 返回 exp2 的值
```

---
## 5.6 运算符优先级

- (^) > (not) > (负号) > (*，/，%) > (+，-) > ( . . 拼接符) > (关系运算符) > ( and ) > ( or )

---