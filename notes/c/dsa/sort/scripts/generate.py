import random

def main():
    random_number = None
    with open('./random.txt', 'w') as f:
        for x in range(5000):
            random_number = random.randint(1, 5000)
            f.write(str(random_number) + '\n')

if __name__ == '__main__':
    main()
