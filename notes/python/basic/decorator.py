def logger(func):
    def wrapper(*args, **kwargs):
        print('start')
        func(*args, **kwargs)
        print('stop')
    return wrapper

@logger
def say(word):
    print(word)

def main():
    say('fuck')

if __name__ == '__main__':
    main()
