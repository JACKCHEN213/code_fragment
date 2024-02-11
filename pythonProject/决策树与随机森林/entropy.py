# -*- coding: utf8 -*-
"""
两点分布的熵
H(x) = -p*lnp - (1-p)*ln(1-p)
熵: 随机事件，不确定的物理量
信息熵
"""
import numpy as np
import matplotlib.pyplot as plt


def main():
    eps = 1e-4
    p = np.linspace(eps, 1 - eps, 100)
    h = -(1 - p) * np.log2(1 - p) - p * np.log2(p)
    gini = 2 * (1 - p) * p
    plt.plot(p, gini, 'r-', lw=3)
    plt.plot(p, h / 2, 'g-', lw=3)
    plt.title('Gini/Entropy', fontsize=16)
    plt.show()


if __name__ == '__main__':
    main()
