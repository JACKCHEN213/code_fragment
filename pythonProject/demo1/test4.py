# -*- coding: utf8 -*-
import numpy as np
import matplotlib.pyplot as plt


def main():
    x = np.arange(0, 10, .1)
    y = x ** x
    plt.plot(x, y, 'r-', lw=3)
    plt.savefig('img/test4.png')
    plt.show()


if __name__ == '__main__':
    main()
