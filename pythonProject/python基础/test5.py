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
    plt.savefig('img/test5.png')
    plt.show()


if __name__ == '__main__':
    main()
