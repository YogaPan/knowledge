## Challenge1

## Prepare
```sh
sudo apt-get install linux-headers-`uname -r`
```

# See your result
```sh
$ make

$ insmod hello.ko
$ lsmod
$ rmmod hello.ko
$
$ dmesg | tail -n -3
```

## LINK
- http://elinux.org/Debugging_by_printing
- http://smilejay.com/2011/12/linux_loglevel/
