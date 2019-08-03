# Basic command

## Install
```sh
sudo apt-get update
sudo apt-get upgrade

sudo apt-get install package-name
sudo apt-get remove package-name
sudo apt-get autoremove

apt-cache search package-name

dpkg --get-selections | grep -v deinstall
apt --installed list
```

## Shutdown
```sh
sudo shutdown -h now  # Halt now
sudo shutdown -r +5 "Server will reboot 5 minutes later"
sudo shutdown -c      # Cancel shutdown
```

## User
```sh
# All default settings in /etc/default/useradd
# All skelton in /etc/skel/
# All user in /etc/passwd
# All passwd and expiry in /etc/shadow
# All group in /etc/group

sudo adduser [-unqGmMd] username
# u: uid
# d: home directory
# m: need home directory
# M: no home directory

sudo adduser username groupname # Add group to user
sudo adduser yogapan sudo       # Add yogapan sudoer
sudo adduser yogapan admin      # Add yogapan administrator

# Change username
usermod -l newUsername oldUsername
usermod -d /home/newHomeDir -m newUsername

# Change uid
usermod -u 1020 username

# group
usermod -G root,yoga username

# Change expiration time
usermod -e 2020/12/31 username

sudo passwd username            # change your password
sudo passwd -l username         # lock user
sudo passwd -u username         # unlock user

sudo deluser username                # Delete user
sudo deluser username --remove-home  # Delete user and his home directory

# user imformation
id
groups

```

Sudo without password
```
$ sudo visudo

%admin  ALL=(ALL) ALL

# Change to
%admin  ALL=(ALL) NOPASSWD:ALL

$sudo adduser username admin
```

```passwd
# /etc/passwd
# 644
# user:passwd:uid:gid:comment:home:shell

root:x:0:0:root:/root:/bin/bash
sshd:x:104:65534::/var/run/sshd:/usr/sbin/nologin  # uid < 500 is used by system
yoga:x:1000:1000::/home/vagrant:/usr/bin/zsh       # comment is not required
```

```shadow
# /etc/shadow
# 400

root:$6$R/sHak3K$rt3WyOAz7NwvQZqx1dgyfuod6pgh763EoGnURnazWsQYtgHHHGQ9i1wPGXARsxflR30Dw9e4ecGXrElLPGiWH.:16855:0:99999:7:::
```
1. login name
2. encrypted password
3. date of last password change: count from 1/1/1970.
4. minimum password age: The minimum number of days required between password
   changes, default is 0, means don't care.
5. maxmum password age: The maximum number of days the password is valid.
   default is 99999, means this password is always valid.
6. password warning period: The number of days before password is to expire that
   user is warned that his/her password must be changed. default is 7.
7. password inactivity period: The number of days after password expires that
   account is disabled.
8. account expiration date: days since Jan 1, 1970 that account is disabled i.e.
   an absolute date specifying when the login may no longer be used.
9. reserved field

```sh
sudo chage username  # change user password expiry information
chage -l username    # list user password expiry information
```

### enable password shadow
```sh
pwconv    # This is default
pwunconv
```

- http://www.cyberciti.biz/faq/understanding-etcshadow-file/
- http://blogger.gtwang.org/2013/03/linux-etcshadow.html
- http://blog.xuite.net/rockmansyz/twblog/115535151-LINUX+%E4%BD%BF%E7%94%A8%E8%80%85%E5%B8%B3%E6%88%B6%E8%88%87%E7%BE%A4%E7%B5%84%E7%AE%A1%E7%90%86
- http://dywang.csie.cyut.edu.tw/dywang/linuxSystem/node58.html
## Hostname
```sh
hostname                   # Show hostname
sudo vim /etc/hostname     # Change hostname
sudo shutdown -r now       # Have to reboot to see result
```

## Cron
| command    | descrption       |
|------------|------------------|
| crontab -e | edit cron        |
| crontab -r | remove cron      |
| crontab -l | list cron        |
| crontab -u | change cron user |

minute | hour | day  | month | week | user | command
-------|------|------|-------|------|------|--------------
 0~59  | 0~23 | 1~31 | 1~12  | 0~6  | user | /usr/bin/xxxx

**Example**
```cron
*/5 * * * * root /usr/libexec/atrun      # Every 5 minutes
0 1 1-20 * * root /usr/libexec/atrun     # At day 1~20's one o'clock
*/5 8-16 * * * root /usr/libexec/atrun
@reboot root /usr/libexec/atrun
```

Cron command
```sh
$ sudo service cron status
$ sudo service cron start
$ sudo service cron stop
$ sudo service cron restart
```
## Update time
```sh
sudo ntpdate -s time.stdtime.gov.tw
```
