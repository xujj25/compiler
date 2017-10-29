# Compiler

《编译原理》课程project，实现编译器简单组件。

------

## 词法分析器

### Description

设一语言的关键词、运算符、分界符的个数与单词如下： 

```cpp
struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //关键词
struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="}; //运算符
struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ; //分界符
struct { int number; string str[100];} identifieres={0}; //标识符
struct { int number; string str[100];} Unsigned_integer={0}; //无符号整数
```

以上类号分别为1~5，序号从0开始；
标识符是字母开头的字母数字串；常量为无符号整数；
用C++设计一程序实现词法分析。

### Input

输入一程序，结束符用”#”；

### Output

输出单词数对：<类号，序号>。 输出标识符表，用空格分隔； 输出无符号整数表，用空格分隔；

### Sample Input
```plain
main()
{ int a=2,b=3;
  return 2*b+a;
}#
```

### Sample Output

```plain
<1,1><3,0><3,1><3,2><1,0><4,0><2,2><5,0><3,4><4,1><2,2><5,1><3,5><1,2><5,0><2,1>
<4,1><2,0><4,0><3,5><3,3>
identifieres:a b
Unsigned_integer:2 3
```

### 程序实现

已在[*simpleLexer*](./simpleLexer)目录中给出