import requests
import sys

def main():
    url = sys.argv[1]
    t = requests.get(url)
    print(t.content)

if __name__ == '__main__':
    main()
