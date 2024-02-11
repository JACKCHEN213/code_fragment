# -*- coding: utf8 -*-
"""
激活函数 - sigmoid函数
"""


import numpy as np
import matplotlib.pyplot as plt


def main():
    np.set_printoptions(suppress=True)
    x = np.linspace(-7, 7, 101)
    y = 1 / (1 + np.exp(-x))
    plt.plot(x, y, 'r-', lw=5)
    plt.show()
    # print(x)


if __name__ == '__main__':
    main()
