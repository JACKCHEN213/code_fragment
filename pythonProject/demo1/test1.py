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
    plt.savefig(fname='img/test1.png')
    plt.show()


if __name__ == '__main__':
    main()
