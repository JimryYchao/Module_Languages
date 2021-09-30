# Lua 字符串

---

- [Lua 字符串](#lua-字符串)
  - [1. Lua 字符串](#1-lua-字符串)
  - [2. Lua 转义字符](#2-lua-转义字符)
  - [3. 字符串 API](#3-字符串-api)

---
## 1. Lua 字符串

```lua
    str1 = "string"     
    str2 = 'string'
    str3 = [[string1
    string2]]               --- 多行字符串
```

---
## 2. Lua 转义字符

|转义字符|意义|ASCII码值（十进制）|
|:----|:----|:----|
|\a|响铃(BEL)|007|
|\b|退格(BS) ，将当前位置移到前一列|008|
|\f|换页(FF)，将当前位置移到下页开头|012|
|\n|换行(LF) ，将当前位置移到下一行开头|010|
|\r|回车(CR) ，将当前位置移到本行开头|013|
|\t|水平制表(HT) （跳到下一个TAB位置）|009|
|\v|垂直制表(VT)|011|
|\\\\ |代表一个反斜线字符 \\ |092|
|\\'|代表一个单引号（撇号）字符|039|
|\\"|代表一个双引号字符|034|
|\0|空字符(NULL)|000|
|\ddd|1到3位八进制数所代表的任意字符|三位八进制|
|\xhh|1到2位十六进制所代表的任意字符|二位十六进制|
|\\[|左方括号|091
|\\]|右方括号|093

---
## 3. 字符串 API

- 大小写转换 : string.upper (str) 与 string.lower (str)
- 替换字符串 : string.gsub (mainString, findString, replaceString [, num])
- 字符串反转 : string.reverse (arg)
- 字符串拼接 : string.format(...) 返回格式化字符串
- 字符串截取 : string.sub (str，i [，j = -1])
- 长度获取 : string.len (str)
- 整型转换字符 : string.char (arg \[,arg1,arg2, ...]) 
- 字符转换整型 : string.byte (str \[, index])
- 字符串查找 : string.find (str, substr, [index [, endIndex]])
- 字符串重复 : string.rep (str, n)
- 字符串匹配 : string.match (str, pattern, index)
- 






