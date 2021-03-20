import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import curve_fit
import os
import glob


def gauss(x, H, A, x0, sigma):
    return H + A * np.exp(-(x - x0) ** 2 / (2 * sigma ** 2))


def gauss_fit(x, y):
    mean = sum(x * y) / sum(y)
    sigma = np.sqrt(sum(y * (x - mean) ** 2) / sum(y))
    popt, pcov = curve_fit(gauss, x, y, p0=[min(y), max(y), mean, 0])
    return popt


def main():

    # Get path to GATE output folder
    PATH = os.path.join(os.getcwd(), 'output')

    # Select only Dose files from DoseActor
    files = glob.glob(os.path.join(PATH, '*Dose.txt'))

    # Load xz and yz dose
    for dose_file in sorted(files):
        if os.path.isfile(dose_file) is True:
            if 'doseInX' in dose_file:
                print('Load: {}'.format(dose_file))
                xz = np.loadtxt(dose_file)
            if 'doseInY' in dose_file:
                print('Load: {}'.format(dose_file))
                yz = np.loadtxt(dose_file)

    # Data
    # lateral coordinates -> geometry of GATE
    xdata = np.linspace(-200, 200, xz.shape[0])
    # lateral coordinates -> geometry of GATE
    ydata = np.linspace(-200, 200, yz.shape[0])

    print('Processing x coordinates:')
    x = []
    for i, item in enumerate(xz):
        H, A, x0, sigma = gauss_fit(xdata, item)
        x.append(x0)

    print('Processing y coordinates:')
    y = []
    for i, item in enumerate(yz):
        H, A, x0, sigma = gauss_fit(ydata, item)
        y.append(x0)

    # Save output to npy file
    # np.save('MC_p1MeV_xz.npy', [x, np.linspace(0.1, 400, xz.shape[0])])

    # Plot deflection curve
    print('Plot: xz')
    plt.plot(np.linspace(0.1, 400, xz.shape[0]), x, 'red')
    plt.xlabel('z')
    plt.ylabel('x')
    plt.show()

    print('Plot: yz')
    plt.plot(np.linspace(0.1, 400, yz.shape[0]), y, 'blue')
    plt.xlabel('z')
    plt.ylabel('y')
    plt.show()

    # 3D Plot
    print('Plot: 3D')
    from mpl_toolkits import mplot3d
    plt.figure()
    ax = plt.axes(projection="3d")

    z_line = np.linspace(0.1, 400, xz.shape[0])
    x_line = x
    y_line = y
    ax.plot3D(x_line, y_line, z_line, 'green')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.show()


if __name__ == "__main__":
    main()
