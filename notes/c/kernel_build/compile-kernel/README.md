# Challenge2

## How to do?
```sh
$ git clone https://github.com/torvalds/linux.git && cd linux
$
$ make localmodconfig   # All your settings will in .config
$ vim .config           # change CONFIG_LOCALVERSION_AUTO=y

$ make -jx              # x means how many cpus you have
$ make modules_install install
$
$ dmesg | head -n 2
$ uname -a
```

##
- [The Linux Kernel Module Programming Guide](http://www.tldp.org/LDP/lkmpg/2.6/html/lkmpg.html)
- [你知道 Linux 内核是如何构建的吗？](https://github.com/MintCN/linux-insides-zh/blob/master/Misc/how_linux_compile.md)
