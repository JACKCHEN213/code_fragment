# -*- coding: utf8 -*-
import numpy as np
import pandas as pd


def main():
    d = np.random.rand(3, 4)
    print(d)
    data = pd.DataFrame(data=d, columns=['a', 'b', 'c', 'd'])
    print(data)
    print(data[['a', 'b']])
    data.to_csv('data/test3.csv', index=False, header=True)


if __name__ == '__main__':
    main()
