# Lua 数组与迭代器

---

- [Lua 数组与迭代器](#lua-数组与迭代器)
  - [1. Lua 数组的实现](#1-lua-数组的实现)
    - [1.1 数组的长度](#11-数组的长度)
  - [2. 数组的遍历(FOR迭代器)](#2-数组的遍历for迭代器)
  - [3. 无状态迭代器](#3-无状态迭代器)
  - [4. 多状态的迭代器](#4-多状态的迭代器)

---
## 1. Lua 数组的实现

- 数组，就是相同数据类型的元素按一定顺序排列的集合，可以是一维数组和多维数组。

- Lua 数组的索引键值可以使用整数表示，数组的大小不是固定的
- Lua 的数组索引从 1 开始, 高维数组通过表的嵌套结构实现

```lua
    ------- 一维数组
    arr = {}
    for i = 0,10 do
        arr[i] = i^2
    end
    
    for i = 0, #arr do
        print("Index:"..i..",Value:"..arr[i])
    end

    ------- 二维数组
    array = {}
    for i=1,3 do
       array[i] = {}
          for j=1,3 do
             array[i][j] = i*j
          end
    end
```

---
### 1.1 数组的长度

- 当数组中的索引是自定义索引时，计算长度时会忽略小于等于0的索引。

```lua
    #{[0]=0,[-1]=-1,1,2,3,4,5}  ----- 5
```

- 当显式索引跳跃声明时，当只跳一格时(不允许连续间隔跳跃)，索引不会断掉，长度受自定义最大值影响，当for遍历时，未定义索引的键值对将为 nil 返回。
  - 显式声明方式: \[1] = 'value';

```lua
    arr = {[1]=1,[2]=2,[4]=4,[5]=5,[7]=7,[9]=9}
    #arr  --- 5

    for i=1,#arr do
        print(arr[i])   ----- 1,2,nil,4,5  (中断)
    end 
----------------------------------------------------    
    Arr = {[1]=1,[2]=2,[4]=4,[5]=5,[7]=7,[8]=8}  
    #Arr --- 8

    for i=1,#Arr do
        print(Arr[i])   ----- 1,2,nil,4,5,nil,7,8  (跳跃)
    end
```

---
## 2. 数组的遍历(FOR迭代器)

- For 实现了两种迭代器, For..pairs 用于遍历 table 的所有键值对, For..ipairs 用于遍历 table 中的数组部分
- table 中值存在非 number,nil 与 string 类型时, 迭代遍历 table 将发生错误

```lua
    Arr = {1,2,3,4,5,a ="a",b ="b"}
    A = 'A'
    B = 'B'
    Arr[A] = 1
    Arr[B] = 2

    
    for key, value in pairs(Arr) do  --- 遍历键值对
        print('key'..key..',value'..value)
    end
    --[[
        key1,value1
        key2,value2
        key3,value3
        key4,value4
        key5,value5
        keya,valuea
        keyb,valueb
        keyA,value1
        keyB,value2     
    --]]

    for index, value in ipairs Arr do
        print('index'..index..',value'..value)
    end
    --[[
        index1,value1
        index2,value2
        index3,value3
        index4,value4
        index5,value5
    --]]
```

> 迭代器的执行过程

- 首先，初始化，计算 in 后面表达式的值，表达式应该返回泛型 for 需要的三个值：迭代函数、状态常量、控制变量；与多值赋值一样，如果表达式返回的结果个数不足三个会自动用 nil 补足，多出部分会被忽略。
- 第二，将状态常量和控制变量作为参数调用迭代函数（注意：对于 for 结构来说，状态常量没有用处，仅仅在初始化时获取他的值并传递给迭代函数）。
- 第三，将迭代函数返回的值赋给变量列表。
- 第四，如果返回的第一个值为nil循环结束，否则执行循环体。
- 第五，回到第二步再次调用迭代函数

---  
## 3. 无状态迭代器

- 无状态的迭代器是指不保留任何状态的迭代器，因此在循环中我们可以利用无状态迭代器避免创建闭包花费额外的代价。
- 每一次迭代，迭代函数都是用两个变量（状态常量和控制变量）的值作为参数被调用，一个无状态的迭代器只利用这两个值可以获取下一个元素。

```lua
    function func(maxCount,value) 
      if value < maxCount then
      value = value+1
      return value,value*2
      end
    end
    -----------------------
    for i,v in func,5,0 do
      print(i,v)
    end
    --[[
        当5，0传入函数时，会将返回的值依次赋给i，v，然后 i，v 进入循环体执行语句块, 后再次进入函数func，函数返回值赋值给 i,v，直到函数控制变量不满足条件, 跳出函数作用域，迭代或循环体结束。

        当函数一直处于无法 end 状态时, for 循环进入死循环 
    --]]
```

---
## 4. 多状态的迭代器

- 迭代器需要保存多个状态信息而不是简单的状态常量和控制变量，最简单的方法是使用闭包.
- 还有一种方法就是将所有的状态信息封装到 table 内，将 table 作为迭代器的状态常量，因为这种情况下可以将所有的信息存放在 table 内，所以迭代函数通常不需要第二个参数。

```lua
array = {1,2,3,4,5,6,7}
function elementIterator (collection)
   local index = 0
   local count = #collection
   -- 闭包函数
   return function ()
      index = index + 1
      if index <= count
      then
         --  返回迭代器的当前元素
         return collection[index]
      end
   end
end
for element in elementIterator(array)
do
   print(element)
end
```

- 在 elementIterator 函数内定义了另外一个匿名函数。此匿名函数中使用了一个外部变量 index (译注：此变量在匿名函数之外，elementIterator 函数内)。每次内部的匿名函数被调用时，都会将 index 的值增加 1，并统计数返回的每个元素。
- 利用函数的闭包原则内部嵌套函数存储临时变量，在for循环体持续更新，直至返回空nil时跳出循环。

---