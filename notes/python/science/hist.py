import numpy as np
import matplotlib.pyplot as plt

def main():
    t = np.random.randn(10000)
    plt.hist(t, 40, normed=1, color='b', alpha=0.5)
    plt.title('Test')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    plt.savefig('hist.png')

if __name__ == '__main__':
    main()
