# Unsigned

无符号大正整数的四则运算实现，有了这个妈妈再也不怕我的学习。

十进制的哦~

## 实现思路

Unsigned 类内部使用一个 string 对象来保存数据，实现四则运算，最佳的做法就是先实现 Unsigned 实例的大小比较，再实现 Unsigned 对象实例的加法运行，再实现减法运行，接着就是乘法和除法，其中除法运行是实现最难，即使是模仿手算除法，也很难理清思路。或许我比较笨吧。

现提供相关算法思路

### 比较运算符

最主要讲解 ```==``` ， ```>``` ，这两个运算符，其中 ```<``` 可以使用 ```>``` 的运算结果再取反。

另，这里假设 Unsigned 对象中的 ```m_data``` 字段（也就是 string 对象）内部的数据是经过验证的。

#### 等号运算符

直接比较 Unsigned 对象中的```m_data``` 字段是否相等就行。

#### 小于运算符

这里讲一讲 Unsigned 对象中的```m_data``` 字段怎么存数字吧~

```

"1235892"

// 第一位即为数字的最高位

```
 
所以比较的时候可以从如下两个方面进行

1. ```m_data ``` 字段的长度。
2. ```m_data ``` 字段的长度相等的情况下，从最高位开始，对每一位进行比较。

### 四则运算

2015/6/18 : 今天发布了项目，但是还未解决除法运算。

#### 加法运算

加法运算模拟了手算加法，从个位开始，每一位进行相加，大于 9 时，使用进位 1 记录下来，在下一位加法时，把进位加上。

#### 减法运算

减法运算模拟了手算减法，从个位开始，每一位相减，相减小于 0 时，向高位借数 1 ，且高一位先减一，如此循环。

返回值是绝对值。

#### 乘法运算

乘法运算分为两大步，首先将数分为大小数，然后把大数乘以小数的每一位，得到的结果，在其后补上适当个数的零

```

    14251
   *  111
   ------

```

分解为 : 

```

    14251
   *    1
   ------
    14251

    14251
   *   1
   ------
    14251 补 1 个 0 

    14251
   *  1
   ------
    14251 补 2 个 0 

```

再使用前面完成的加法运算将每一步的结果相加。

#### 除法运算

现在还未能解决，项目中的代码是无法完成预定功能的。
