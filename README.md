# AlgoriMatrix



## 产生式

```
S -> [VARIABLE=]E[;]
E -> T{(+|-)T}
T -> U{(*|/)U}
U -> -F | +F | F
F -> (E) | FUNCTION[(L)] | VARIABLE | \[M\] | NUMBER
L -> E{,E}
M -> L{;L}
```

各符合的含义

```
S: start, 文法开始符号
E: expression, 表达式
T: term, 表达式项
U: unary, 一元式
F: factor, 表达式项的因子
L: expression list，表达式列表
M: matrix, 矩阵
```

