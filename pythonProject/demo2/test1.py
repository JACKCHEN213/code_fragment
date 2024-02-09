# -*- coding: utf8 -*-
"""
九点分布
计算N的阶乘首位数字出现的概率
方法:
1. N! = 10 ^(log 10 N!) = 10^(log10 N + log 10 (N-1) + ... + log 10 1)
2. 10^2.1 = 10 ^ 2 x 10^0.1 = 100 x 10^0.1
3. 100 x 10^0.1的数位数字为int(10^0.1)
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from time import time


def get_first_digital(num):
    num -= int(num)
    return int(10 ** num)


def main():
    """
    1. 计算log 10 N!
    2. 计算10^(log 10 N!)=int(10^(log10 N!(去除整数)))
    :return:
    """
    N = 5434500
    x = np.arange(1, N + 1, 1)
    frequency = [0] * 9

    t0 = time()
    # 1. 计算log10 N!
    y = np.cumsum(np.log10(x))
    # 2. 计算int(10 ^ (y -= int(y)))
    for s in y:
        frequency[get_first_digital(s) - 1] += 1
    t1 = time()

    print(f'计算耗时: {t1 - t0}s')

    # 渲染
    mpl.rcParams['font.sans-serif'] = 'simHei'
    mpl.rcParams['axes.unicode_minus'] = False
    plt.plot(np.arange(1, 10), frequency, np.arange(1, 10),
             frequency, 'go', lw=2, markersize=8)
    for x, y in enumerate(frequency):
        plt.text(x + 1.2, y, frequency[x], verticalalignment='top', fontsize=13)
    plt.title('{}!首位数字出现频率, 计算耗时: {:.2f}s'.format(N, t1 - t0), fontsize=18)
    plt.xlim(0.5, 9.5)
    plt.ylim(0, max(frequency)*1.03)
    plt.xlabel('首位数字', fontsize=16)
    plt.ylabel('频率', fontsize=16)
    plt.grid(visible=True, ls=':', color='#404040')
    plt.savefig('img/test1.png')
    plt.show()
    pass


if __name__ == '__main__':
    main()
