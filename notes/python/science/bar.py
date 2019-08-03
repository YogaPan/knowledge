import numpy as np
import matplotlib.pyplot as plt

def main():
    width = 0.5

    plt.title('Sort speed')
    plt.ylabel('time')

    y = np.array([10, 32, 44, 1])

    ind = np.arange(len(y))
    plt.bar(ind, y, width=width, align='center', color=['r', 'g', 'y', 'c'])
    #  plt.bar(ind, y, width=width, label='sort', color='r')
    plt.xticks(ind + width - 1 / 2, ('Quick Sort', 'Heap Sort'))
    plt.grid(True)
    plt.savefig('bar.png')


if __name__ == '__main__':
    main()
