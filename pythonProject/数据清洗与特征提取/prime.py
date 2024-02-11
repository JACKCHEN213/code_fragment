# -*- coding: utf8 -*-
"""
求素数
"""
import math
from time import time

import numpy as np

p_list_5 = []


def method_1(a, b):
    """
    直接计算
    :param a:
    :param b:
    :return:
    """
    t = time()
    p = [p for p in range(a, b) if is_prime(p)]
    print('method_1: {:.2f}s'.format(time() - t))
    print(p)


def is_prime(x):
    return 0 not in [x % i for i in range(2, int(math.sqrt(x)) + 1)]


def method_2(a, b):
    """
    使用过滤器
    :param a:
    :param b:
    :return:
    """
    t = time()
    p = list(filter(is_prime, range(a, b)))
    print('method_2: {:.2f}s'.format(time() - t))
    print(p)


def method_3(a, b):
    """
    使用lambda
    :param a:
    :param b:
    :return:
    """
    t = time()
    is_prime2 = (lambda x: 0 not in [x % i for i in range(2, int(math.sqrt(x)) + 1)])
    p = list(filter(is_prime2, list(range(a, b))))
    print('method_3: {:.2f}s'.format(time() - t))
    print(p)


def method_4(a, b):
    """
    标记合数去素数
    :param a:
    :param b:
    :return:
    """
    t = time()
    p_list = []
    for i in range(a, b):
        flag = True
        for p in p_list:
            if p > math.sqrt(i):
                break
            if i % p == 0:
                flag = False
                break
        if flag:
            p_list.append(i)
    print('method_4: {:.2f}s'.format(time() - t))
    print(p_list)


def is_prime3(x):
    flag = True
    for p in p_list_5:
        if p > math.sqrt(x):
            break
        if x % p == 0:
            flag = False
            break
    if flag:
        p_list_5.append(x)


def method_5(a, b):
    """
    filter+去除合数
    :param a:
    :param b:
    :return:
    """
    t = time()
    list(filter(is_prime3, list(range(a, b))))
    print('method_5: {:.2f}s'.format(time() - t))
    print(p_list_5)


def main():
    a = 2
    b = 1000000
    # method_1(a, b)
    # method_2(a, b)
    # method_3(a, b)
    # method_4(a, b)
    method_5(a, b)
    p = np.array(p_list_5)
    p = [p >= a]
    print(p)
    p_rate = float(len(p) / float(b - a + 1))
    print('素数的概率: {}'.format(p_rate), end='\t    ')
    print('公正赔率: {}'.format(1 / p_rate))
    print('合数的概率: {}'.format(1 - p_rate), end='\t    ')
    print('公正赔率: {}'.format(1 / (1 - p_rate)))


if __name__ == '__main__':
    main()
