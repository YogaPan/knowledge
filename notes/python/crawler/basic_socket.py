import socket

def main():
    hostname = socket.gethostname()
    print(hostname)

if __name__ == '__main__':
    main()
