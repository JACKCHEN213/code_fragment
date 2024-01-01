# -*- coding: utf8 -*-
import numpy as np
import matplotlib.pyplot as plt


def main():
    p = np.random.rand(10000)
    # bins: 等分为20份
    # color: 填充的颜色
    # edgecolor: 边界线的颜色【b: 蓝色 g: 绿色 r: 红色 c: 青色 m: 品红 y: 黄色k: 黑色 w: 白色】
    plt.hist(p, bins=20, color='g', edgecolor='k')
    plt.savefig(fname='img/test2_1.png')
    plt.show()

    # ignore pep8
    N = 10000
    times = 100
    z = np.zeros(N)
    for i in range(times):
        z += np.random.randn(N)

    z /= times
    plt.hist(z, bins=20, color='m', edgecolor='k')
    plt.savefig(fname='img/test2_2.png')
    plt.show()


if __name__ == '__main__':
    main()
