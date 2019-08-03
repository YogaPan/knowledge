import numpy as np
import matplotlib.pyplot as plt

def main():
    t1 = np.linspace(0, 7, 10000)
    t2 = t1 * t1

    plt.title('test')
    plt.ylabel('Y')
    plt.xlabel('X')
    plt.axis([0, 10, 0, 40])
    plt.plot(t1, t2, 'g-', linewidth=2.0,
            label='n2')
    #  plt.grid(True)
    plt.legend()

    plt.savefig('line.png')

if __name__ == '__main__':
    main()
