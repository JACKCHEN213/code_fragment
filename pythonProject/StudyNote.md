# 学习笔记

## 初识python

### matplotlib

#### 线条颜色

```python
b: 蓝色
g: 绿色
r: 红色
c: 青色
m: 品红
y: 黄色
k: 黑色
w: 白色
```

#### 线条样式

```python
- 实线
-- 破折线，也称为虚线
-. 点划线
: 细小点线
. 点标记
, 像素标记（很小的点）
o 圆圈标记
v 下三角标记
^ 上三角标记
< 左三角标记
> 右三角标记
1 下三叉戟标记
2 上三叉戟标记
3 左三叉戟标记
4 右三叉戟标记
s 正方形标记
p 五边形标记
* 星号标记
h 六边形标记1
H 六边形标记2
+ 加号标记
x 乘号标记
D 菱形标记
d 细小菱形标记
| 垂直线标记
_ 水平线标记
```

### 绘制一个空心圆

```python
# -*- coding: utf8 -*-
import numpy as np
import matplotlib.pyplot as plt


def main():
    print('Hello World')
    x = 2 * np.random.rand(10000, 2) - 4
    # print(x)
    # print(x[1])
    # print(x[:, 1])
    lx = x[:, 0]
    ly = x[:, 1]
    # 小于比较
    idx = lx ** 2 + ly ** 2 < 1
    hole = lx ** 2 + ly ** 2 <= 0.25
    idx = np.logical_and(idx, ~hole)  # [True false ... True True]
    """
    # 数据清洗
    lx[lx < 0.5] = 0.5
    """
    # print(idx)
    plt.plot(lx[idx], ly[idx], 'go', markersize=1)
    plt.savefig(fname='test1.png')
    plt.show()


if __name__ == '__main__':
    main()

```
![img/demo1.png](demo1/img/test1.png)

### 均匀分区迭代后是高斯分布（正态分布）

> 验证中心极限定理

```python
# -*- coding: utf8 -*-
import numpy as np
import matplotlib.pyplot as plt


def main():
    p = np.random.rand(10000)
    # bins: 等分为20份
    # color: 填充的颜色
    # edgecolor: 边界线的颜色【b: 蓝色 g: 绿色 r: 红色 c: 青色 m: 品红 y: 黄色k: 黑色 w: 白色】
    plt.hist(p, bins=20, color='g', edgecolor='k')
    plt.savefig(fname='test2_1.png')
    plt.show()

    # ignore pep8
    N = 10000
    times = 100
    z = np.zeros(N)
    for i in range(times):
        z += np.random.randn(N)

    z /= times
    plt.hist(z, bins=20, color='m', edgecolor='k')
    plt.savefig(fname='test2_2.png')
    plt.show()


if __name__ == '__main__':
    main()

```

1. 均匀分布

![](demo1/img/test2_1.png)

2. 高斯分布

![](demo1/img/test2_2.png)

### np与pd的转换

```python
# -*- coding: utf8 -*-
import numpy as np
import pandas as pd


def main():
    d = np.random.rand(3, 4)
    print(d)
    data = pd.DataFrame(data=d, columns=['a', 'b', 'c', 'd'])
    print(data)
    print(data[['a', 'b']])
    data.to_csv('test3.csv', index=False, header=True)


if __name__ == '__main__':
    main()

```

#### y = x^x绘制

```python
# -*- coding: utf8 -*-
import numpy as np
import matplotlib.pyplot as plt


def main():
    x = np.arange(0, 10, .1)
    y = x ** x
    plt.plot(x, y, 'r-', lw=3)
    plt.savefig('test4.png')
    plt.show()


if __name__ == '__main__':
    main()

```

![](demo1/img/test4.png)


### 随机森林预测正确的概率

```python
# -*- coding: utf8 -*-
from scipy.special import comb
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl


def get_bagging(n, p):
    """
    获取正确的概率
    :param n:
    :param p:
    :return:
    """
    s = 0
    for i in range(n // 2 + 1, n + 1):
        s += comb(n, i) * p ** i * (1 - p) ** (n - i)
    return s


def main():
    p = 0.6
    n = 100
    x = np.arange(1, n, 2)
    y = np.empty_like(x, dtype='double')
    for i, t in enumerate(x):
        bagging = get_bagging(t, p)
        if t % 10 == 9:
            print(f'{t}: {bagging}')
        y[i] = bagging
    mpl.rcParams['font.sans-serif'] = 'simHei'
    mpl.rcParams['axes.unicode_minus'] = False
    plt.figure(facecolor='w')
    plt.plot(x, y, 'ro-', lw=2, mec='k')
    plt.xlim(0, n)
    plt.ylim(0.6, 1)
    plt.xlabel('分类器个数', fontsize=16)
    plt.ylabel('正确率', fontsize=16)
    plt.title('随机森林正确率', fontsize=20)
    plt.grid(visible=True, ls=':', color='#606060')
    plt.savefig('test5.png')
    plt.show()


if __name__ == '__main__':
    main()

```

![](demo1/img/test5.png)
