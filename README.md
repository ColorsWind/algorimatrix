# AlgoriMatrix

矩阵计算器，支持矩阵计算和一些`element-wise`运算。

https://github.com/ColorsWind/algorimatrix/



## 用户指南

软件包含两种模式：用户界面模式和命令行模式，对于用户界面模式，只需要直接打开程序。对于命令行模式，请使用参数`nogui`启动程序，如：

```shell
algorimatrix nogui
```

用户界面模式和命令行模式的语法规则是一致的，下面以用户界面模式为例：

### 界面介绍

![main-window.png](https://www.colors-wind.net/usr/uploads/2020/09/4100636080.png)

特别地，命令行模式可以使用`vars`查看变量表。·



### 语法

```shell
[VARIABLE = ]EXPRESSION
```

其中`VARIABLE`为变量名，用于存储右边`EXPRESSION`的结果，且变量名可省略，默认将结果存储到`ans`变量中。



### 表达式

表达式可以包括矩阵定义、函数调用和四则运算。

**矩阵定义**格式为`[NUMBER1, NUMBER2...;...]`即使用`,`分隔同一行的元素，用`;`分割不同的行。其中`NUMBER`可以替换成矩阵，只需要满足分块矩阵构造的规则。

**函数调用**格式为`FUNCTION(PARAMETER1, PARAMETER2,...)`，其中`PARAMETER`可以是一个表达式，若函数无参，可省略`(...)`。

**四则运算**格式同一般数学表达式的格式，如`A * (B + C)`，`[1, 2] * [2; 1]`。



### 函数

软件内置了一些函数，函数的输入和输出均为矩阵。

| 函数名      | 参数                  | 描述                                       |
| ----------- | --------------------- | ------------------------------------------ |
| sin         | Matrix                | 求矩阵所有元素的正弦                       |
| cos         | Matrix                | 求矩阵所有元素的余弦                       |
| tan         | Matrix                | 求矩阵所有元素的正切                       |
| cot         | Matrix                | 求矩阵所有元素的余切                       |
| sec         | Matrix                | 求矩阵所有元素的正割                       |
| csc         | Matrix                | 求矩阵所有元素的余割                       |
| arcsin      | Matrix                | 求矩阵所有元素的反正弦                     |
| arccos      | Matrix                | 求矩阵所有元素的反余弦                     |
| arctan      | Matrix                | 求矩阵所有元素的正切                       |
| ln          | Matrix                | 求矩阵所有元素的自然对数                   |
| log         | (Matrix,Matrix)       | 以矩阵1作为真数，矩阵2作为底数求对数       |
| exp         | Matrix                | 求矩阵所有元素的自然指数                   |
| pow         | (Matrix,Matrix)       | 以矩阵1作为底数，矩阵2作为指数求指数       |
| **triu**    | Matrix                | 将矩阵化为上三角矩阵                       |
| **det**     | Matrix                | 求矩阵行列式                               |
| **inv**     | Matrix                | 求矩阵的逆矩阵                             |
| swap        | (Matrix, i, j)        | 初等变换，交换矩阵两行                     |
| add         | (Matrix, i, j, k=1.0) | 初等变换，将第`j`行`k`倍加到第`i`行        |
| multiply    | (Matrix, i, k)        | 初等变换，将第`i`行乘以`k`                 |
| sub         | (Matrix, Matrix)      | 取指定行列的子矩阵                         |
| zeros       | (m, n=m)              | 生成`mxn`零矩阵                            |
| ident       | (n, k=1)              | 生成`n`阶主对角线元素为`k`的数量矩阵       |
| **adjoint** | Matrix                | 求伴随矩阵                                 |
| cofactor    | (Matrix, i, j)        | 求`Matrix(i, j)`的余子式                   |
| size        | Matrix                | 求矩阵的大小                               |
| row         | Matrix                | 求矩阵的行数                               |
| col         | Matrix                | 求矩阵的列数                               |
| **rank**    | Matrix                | 求矩阵的秩                                 |
| reshape     | (Matrix, m, n)        | 不改变矩阵的元素顺序，将矩阵转为`mxn`矩阵  |
| trans       | Matrix                | 矩阵转置                                   |
| sleep       | t                     | 线程休眠 `t` ms (仅仅用于测试模拟耗时任务) |

### 

## 开发者指南

### 如何构建

需要安装`git`，`cmake(VERSION >=3.16)`，`qt5`，开发环境为windows系统，使用编译器`msvc2017`。由于没有使用任何windows API，理论可兼容其他系统。

```shell
git clone https://github.com/ColorsWind/algorimatrix.git
cd algorimatrix
cmake --build  ./target --target algorimatrix
cd target
windeployqt algorimatrix
```



### 许可证

[Apache-2.0 License](https://github.com/ColorsWind/algorimatrix/blob/master/LICENSE)



### 实现

软件可分为三个模块：矩阵计算器、表达式解析器、用户界面

**矩阵计算器：**矩阵计算算法参考《线性代数与解析几何》

**表达式解析器：**包含三部分，词法分析器，变量表，语法分析器。其中语法分析器采用自上而下的分析方法。采用扩充巴科斯范式描述文法，产生式规则如下：

```
S -> VARIABLE=E[;]
E -> T{(+|-)T}
T -> U{(*|/)U}
U -> -F | +F | F
F -> (E) | FUNCTION[(L)] | VARIABLE | [M] | NUMBER
L -> E{,E} | ε 
M -> L{;L} | ε
```

各符号的含义

```
S: start, 文法开始符号
E: expression, 表达式
T: term, 表达式项
U: unary, 一元式
F: factor, 表达式项的因子
L: expression list，表达式列表
M: matrix, 矩阵
ε：空字
```

**用户界面：**用户界面采用Qt框架实现，为防止执行耗时任务用户界面卡死，矩阵计算任务在异步完成，采用信号槽机制与界面线程通信。为方便用户输入，输入栏还可保存输入的历史记录。



### 下载

https://github.com/ColorsWind/algorimatrix/releases/

https://www.colors-wind.net/archives/algorimatrix.html
