# Hard Disk

## swap

Create a 500 MB swapfile:
```sh
sudo dd if=/dev/zero of=/swapfile bs=1024 count=524288
sudo mkswap /swapfile
sudo swapon /swapfile
```

Check out all swap and memory status
```sh
sudo swapon -s
free -m
```

This will add swapfile every time you restart computer.
In **/etc/fstab** add:
```
/swapfile none swap sw 0 0
```

## df
```sh
# Display all file systems and their disk usage
df

# Human readable
df -h
```

## du
```sh
# Get a sum of the total size of a file/folder
du -sh file/directory

# Get recursively, individual file/folder sizes
du -ah directory
```

## dd
```sh
dd if=/dev/random of=/dev/sda
dd if=/dev/zero of=file_1GB bs=1024 count=1000000
mkfs.ext3 /dev/sda
```

## lsblk
```sh
lsblk
```

https://magiclen.org/extundelete/
