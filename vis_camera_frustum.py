import matplotlib.pyplot as plt
import math
import numpy as np


def calculate(fx, fy, h, alpha, beta):
    fx = fx / 180 * np.pi
    fy = fy / 180 * np.pi
    alpha = alpha / 180 * np.pi
    beta = beta / 180 * np.pi
    d1 = h * np.tan(alpha - fx / 2)
    d2 = h * np.tan(alpha + fx / 2)
    if d2 < 0:
        d2 = 1000
    p1 = [-d1 / np.cos(fy / 2) * np.cos(np.pi - beta - fy / 2), d1 / np.cos(fy / 2) * np.sin(np.pi - beta - fy / 2)]
    p2 = [d1 / np.cos(fy / 2) * np.cos(beta - fy / 2), d1 / np.cos(fy / 2) * np.sin(beta - fy / 2)]
    p3 = [-d2 / np.cos(fy / 2) * np.cos(np.pi - beta - fy / 2), d2 / np.cos(fy / 2) * np.sin(np.pi - beta - fy / 2)]
    p4 = [d2 / np.cos(fy / 2) * np.cos(beta - fy / 2), d2 / np.cos(fy / 2) * np.sin(beta - fy / 2)]
    return p1, p2, p3, p4


def add_camera(flength, h, alpha, beta, color):
    fov = {28: 75, 35: 63, 50: 46, 85: 28}
    fx = fov[flength]
    fy = fx
    beta = 180 - beta

    p1, p2, p3, p4 = calculate(fx, fy, h, alpha, beta)

    x1, y1 = p1
    x2, y2 = p2
    x3, y3 = p4
    x4, y4 = p3

    x_min, x_max = -85, 115
    y_min, y_max = 0, 38.8

    x = [x1, x2, x3, x4]
    y = [y1, y2, y3, y4]
    print(np.array(x))
    print(np.array(y))
    print()

    plt.fill(x, y, color=color, alpha=0.5)

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)


plt.figure()

# boundary
x = [-85, 115, 115, -85]
y = [0, 0, 38.8, 38.8]
plt.fill(x, y, color='white')

# focal length, camera height, elevation, azimuth
# flength, h, alpha, beta
add_camera(35, 13, 50, 10, 'red')
add_camera(35, 13, 50, 50, 'black')
add_camera(35, 13, 50, 90, 'yellow')
add_camera(50, 13, 62, 120, 'blue')
add_camera(50, 13, 62, 150, 'gray')
add_camera(50, 13, 62, 160, 'orange')
add_camera(50, 13, 70, 170, 'skyblue')
add_camera(50, 13, 74, 173, 'snow')

plt.show()
