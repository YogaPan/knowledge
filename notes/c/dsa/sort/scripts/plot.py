import numpy as np
import matplotlib.pyplot as plt

def main():
    plt.title('Sort Speed Compare')
    plt.xlabel('Data')
    plt.ylabel('Time')
    plt.axis([0, 5000, 0, 0.04])

    # insertion sort
    data_list = []
    time_list = []
    with open('./insertion_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(temp[0])
            time_list.append(temp[2])

    plt.plot(data_list, time_list, 'r-', label='Insertion Sort')

    # selection sort
    data_list = []
    time_list = []
    with open('./selection_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'g-', label='Selection Sort')

    # bubble sort
    data_list = []
    time_list = []
    with open('./bubble_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'b-', label='Bubble Sort')

    # heap sort
    data_list = []
    time_list = []
    with open('./heap_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'c-', label='Heap Sort')

    # merge sort
    data_list = []
    time_list = []
    with open('./merge_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'y-', label='Merge Sort')

    # quick sort
    data_list = []
    time_list = []
    with open('./quick_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'k-', label='Quick Sort')

    # radix sort
    data_list = []
    time_list = []
    with open('./radix_sort.txt', 'r') as f:
        for line in f:
            temp = line.split()
            data_list.append(float(temp[0]))
            time_list.append(float(temp[2]))

    plt.plot(data_list, time_list, 'm-', label='radix Sort')

    plt.legend(loc=2,prop={'size': 12})
    plt.savefig('sort.png')

if __name__ == '__main__':
    main()
