import re

def main():
    test_string = 'yoga'
    pattern = re.match('^(y){1,2}o(g)', test_string)

    if pattern:
        print(pattern.group())
        print(pattern.groups())
        print('yes')
    else:
        print('no')

if __name__ == '__main__':
    main()
