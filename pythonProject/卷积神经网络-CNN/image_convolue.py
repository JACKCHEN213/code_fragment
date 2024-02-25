#!/usr/bin/python
#  -*- coding:utf-8 -*-

import numpy as np
import os
from PIL import Image
from matplotlib import pyplot as plt
import matplotlib

matplotlib.rcParams['font.sans-serif'] = ['SimHei']
matplotlib.rcParams['axes.unicode_minus'] = False


def convolve(image, weight):
    height, width = image.shape
    h, w = weight.shape
    height_new = height - h + 1
    width_new = width - w + 1
    image_new = np.empty((height_new, width_new), dtype=float)
    for i in range(height_new):
        for j in range(width_new):
            image_new[i, j] = np.sum(image[i:i + h, j:j + w] * weight)
    image_new = image_new.clip(0, 255)
    image_new = np.rint(image_new).astype('uint8')
    return image_new


def convolve_image(image, weight, title):
    r = convolve(image[:, :, 0], weight)
    g = convolve(image[:, :, 1], weight)
    b = convolve(image[:, :, 2], weight)
    img = np.stack((r, g, b), 2)
    # if weight not in ('avg3', 'avg5', 'avg20', 'gauss'):
    #     img = 255 - img
    plt.title(title)
    plt.imshow(Image.fromarray(img))
    plt.show()


def convolve_3x3(image):
    weight = np.ones((3, 3))
    weight /= weight.sum()
    convolve_image(image, weight, '3x3变换')


def convolve_5x5(image):
    weight = np.ones((5, 5))
    weight /= weight.sum()
    convolve_image(image, weight, '5x5变换')


def convolve_20x20(image):
    weight = np.ones((20, 20))
    weight /= weight.sum()
    convolve_image(image, weight, '20x20变换')


def convolve_gauss(image):
    gauss = np.array(([0.003, 0.013, 0.022, 0.013, 0.003],
                      [0.013, 0.059, 0.097, 0.059, 0.013],
                      [0.022, 0.097, 0.159, 0.097, 0.022],
                      [0.013, 0.059, 0.097, 0.059, 0.013],
                      [0.003, 0.013, 0.022, 0.013, 0.003]))
    convolve_image(image, gauss, '高斯变换')


def convolve_soble_x(image):
    soble_x = np.array(([-1, 0, 1],
                        [-2, 0, 2],
                        [-1, 0, 1]))
    convolve_image(image, soble_x, 'soble_x变换')


def convolve_soble_y(image):
    soble_y = np.array(([-1, -2, 1],
                        [0, 0, 0],
                        [1, 2, 1]))
    convolve_image(image, soble_y, 'soble_y变换')


def convolve_soble(image):
    soble = np.array(([-1, -1, 0],
                      [-1, 0, 1],
                      [0, 1, 1]))
    convolve_image(image, soble, 'soble变换')


def convolve_prewitt_x(image):
    prewitt_x = np.array(([-1, 0, 1],
                          [-1, 0, 1],
                          [-1, 0, 1]))
    convolve_image(image, prewitt_x, 'prewitt_x变换')


def convolve_prewitt_y(image):
    prewitt_y = np.array(([-1, -1, -1],
                          [0, 0, 0],
                          [1, 1, 1]))
    convolve_image(image, prewitt_y, 'prewitt_y变换')


def convolve_prewitt(image):
    prewitt = np.array(([-2, -1, 0],
                        [-1, 0, 1],
                        [0, 1, 2]))
    convolve_image(image, prewitt, 'prewitt变换')


def convolve_laplacian4(image):
    laplacian4 = np.array(([0, -1, 0],
                           [-1, 4, -1],
                           [0, -1, 0]))
    convolve_image(image, laplacian4, 'laplacian4变换')


def convolve_laplacian8(image):
    laplacian8 = np.array(([-1, -1, -1],
                           [-1, 8, -1],
                           [-1, -1, -1]))
    convolve_image(image, laplacian8, 'laplacian8变换')


# image_new = 255 * (image_new - image_new.min()) / (image_new.max() - image_new.min())


if __name__ == "__main__":
    A = Image.open("./src/girl.png", 'r')
    print(A)
    output_path = './ImageConvolve/'
    if not os.path.exists(output_path):
        os.mkdir(output_path)
    a = np.array(A)
    print(a.shape)
    convolve_3x3(a)
    convolve_5x5(a)
    convolve_20x20(a)
    convolve_soble_x(a)
    convolve_soble_y(a)
    convolve_soble(a)
    convolve_gauss(a)
    convolve_prewitt_x(a)
    convolve_prewitt_y(a)
    convolve_prewitt(a)
    convolve_laplacian4(a)
    convolve_laplacian8(a)
    exit()
    weight_list = (
        'avg3', 'avg5', 'avg20', 'gauss', 'soble_x', 'soble_y', 'soble', 'prewitt_x', 'prewitt_y', 'prewitt',
        'laplacian4',
        'laplacian8')
    print('梯度检测：')
    for weight in weight_list:
        print(weight, 'R', end=' ')
        R = convolve(a[:, :, 0], eval(weight))
        print('G', end=' ')
        G = convolve(a[:, :, 1], eval(weight))
        print('B')
        B = convolve(a[:, :, 2], eval(weight))
        I = np.stack((R, G, B), 2)
        if weight not in ('avg3', 'avg5', 'avg20', 'gauss'):
            I = 255 - I
        Image.fromarray(I).save(output_path + weight + '.png')
