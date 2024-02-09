# -*- coding: utf8 -*-
"""
Nagel-Schreckenberg交通流模型
路面上有N辆车，以不同的速度向前行驶，模拟堵车问题。有以下假设:
1. 假设某辆车的当前速度是v
2. 若前方可见范围内没车，则它在下一秒的车速提高到v+1，直到达到规定的最高限速
3. 若前方有车，前车的距离为d，且d<v，则它下一秒的车速降低到d - 1
4. 每辆车会以概率p随机减速v-1
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl


def main():
    path = 500  # 距离
    n = 100  # 车辆数
    v_max = 5  # 最大速度
    p = 0.3  # 减速概率
    times = 300
    np.random.seed(0)
    x = np.sort(np.random.rand(n) * path)  # 车辆的初始位置
    v = np.ones(n) * v_max  # 所有车辆的初始速度设置为最大速度

    # 记录车辆位置的矩阵，用于后续的可视化
    X = np.zeros((times, n))

    for t in range(times):
        for i in range(n):
            # 计算前车的距离
            if i == n - 1:  # 处理环形道路的最后一辆车
                d = x[0] - x[i] + path
            else:
                d = x[i + 1] - x[i]

            # 规则1: 加速
            if v[i] < v_max:
                v[i] += 1

            # 规则2: 减速避免碰撞
            if d <= v[i]:
                v[i] = d - 1

            # 规则3: 随机减速
            if np.random.rand() < p:
                v[i] = max(v[i] - 1, 0)

        # 更新车辆位置
        x = (x + v) % path

        # 记录位置
        X[t] = x

        # 观察车辆位置
        plt.scatter(x, [t] * n, s=1, c='k', alpha=0.05)

    mpl.rcParams['font.sans-serif'] = ['SimHei']
    mpl.rcParams['axes.unicode_minus'] = False
    # plt.figure(figsize=(8, 6), facecolor='w')
    plt.xlim(0, path)
    plt.ylim(0, times)
    plt.xlabel(u'车辆位置', fontsize=16)
    plt.ylabel(u'模拟时间', fontsize=16)
    plt.title(u'环形公路车辆堵车模拟', fontsize=20)
    # plt.tight_layout(pad=2)
    plt.savefig('img/test2.png')
    plt.show()


if __name__ == '__main__':
    main()
