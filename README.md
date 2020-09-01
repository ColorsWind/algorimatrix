# AlgoriMatrix



## 产生式

```
E -> T{(+|-)T}
T -> U{(*|/)U}
U -> -F | +F | F
F -> (E) | FUNCTION(L) | VARIABLE | [L] | NUMBER
L -> E{,E}
```

