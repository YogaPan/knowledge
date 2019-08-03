# Networking

## IP
```sh
ifconfig

# Check IP address
ifconfig | grep inet
ip addr
```
## Check open port

```sh
netstat
sudo netstat -p
sudo netstat -lptu | grep :http
sudo netstat -lptun | grep :80

sudo netstat -lntp
sudo netstat -luntp

sudo netstat -an | grep EST    # Check who connected to you

netstat -rn

sudo lsof -i :80
```

# iptables
```sh
sudo iptables -I INPUT -p tcp --dport 80 -j ACCEPT
sudo iptables -A INPUT -j REJECT

sudo iptables -I INPUT -i lo -j ACCEPT
sudo iptables -I INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

sudo iptables -I INPUT -p tcp -s 10.10.188.233 --dport 80 -j ACCEPT


sudo vim /etc/sysctl.conf # Set net.ipv4.ip_forward = 1
sysctl -p
sysctl -a | grep ip_forward
sudo iptables -t nat -A POSTROUTING -s 10.10.177.0/24 -j SNAT --to 10.10.188.232
sudo iptables -t nat -nL
netstat -rn
sduo route add -net 10.10.188.0/24 gw 10.10.177.232 dev eth0

sudo iptables -t nat -A INPUT PREROUTING -d 10.10.188.232 -p tcp --dport 80 -j DNAT
--to 10.10.177.233:80

sudo iptables -I INPUT -p tcp --syn --dport 80 -m connlimit --connlimit-above
100 -j REJECT

sudo iptables -A INPUT -p icmp -m limit --limit 1/m --limit-burst 10 -j ACCEPT
sudo iptables -A INPUT -p icmp -j DROP

# Enable apt-get
sudo iptables -F OUTPUT  # remove your existing OUTPUT rule which becomes redundant
sudo iptables -A OUTPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp --dport 80 -m state --state NEW -j ACCEPT
sudo iptables -A OUTPUT -p tcp --dport 53 -m state --state NEW -j ACCEPT
sudo iptables -A OUTPUT -p udp --dport 53 -m state --state NEW -j ACCEPT
```

## nmap
```sh
sudo nmap -sS -p 1-10000 localhost
```

## ab
```
ab -n 10000 -c 140 http://localhost:8080/
```

## Ping
```sh
ping host
ping -c count host
ping -i seconds host
ping -n host   # Ping host without trying to lookup symbolic names for addresses.
```

## ssh and scp
```sh
ssh username@192.168.0.1   # And then enter your password

scp local_file username@192.168.0.1:/path/to/dir
scp -r local_dir username@192.168.0.1:/path/to/dir

scp username@192.168.0.1:/path/to/file /path/to/local
scp -r username@192.168.0.1:/path/to/dir /path/to/local

```

## Login without password
```sh
ssh-keygen -t rsa
scp ~/.ssh/*.pub remote:~/.ssh/
ssh remote
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
exit
eval `ssh-agent -s`
ssh-add
```
http://blog.faq-book.com/?p=1375

## Telnet
- quit
- CTRL + ]
```sh
telnet ip_address port
```

## netcat
```sh
# Is port open?
nc -v -w1 www.google.com 80

# Port Scanning
nc -vnz -w1 192.168.233.208 1-1000 2000-3000

# Simple server
while true; do sudo nc -l 80 < index.html; done

# Simple client
echo -ne "GET / HTTP/1.0\r\n\r\n" | nc www.google.com 80

# Copy file
nc -l 5000 > my.jpg          # Server
nc hostB.com 5000 < my.jpg   # Client

# Copy directory
nc -l 5000 | tar xvf -                      # Server
tar cvf - /path/to/dir | nc hostB.com 5000  # Client
```
http://blogger.gtwang.org/2014/02/linux-utility-netcat-examples.html

## nslookup
```sh
nslookup host
```

## route
```sh
traceroute host
```

## wget
```sh
wget www.example.com
```

## curl
```sh
curl www.example.com -o filename
```

## httpie
```sh
http www.examle.com
http -d www.example.com
```

## Apache2

All your web page in /var/www/html
```sh
sudo service apache2 status
sudo service apache2 start
sudo service apache2 stop
sudo service apache2 restart
```

## Nginx

All your web page in /usr/share/nginx/html  
/etc/nginx/nginx.conf
```sh
sudo service nginx status
sudo service nginx start
sudo service nginx stop
sudo service nginx restart
```

https://www.linode.com/docs/websites/nginx/how-to-configure-nginx

## FTP

/etc/vsftpd.conf
```conf
pasv_min_port=50000
pasv_max_port=60000
```
```sh

$ sudo restart vsftpd

$ ftp localhost 21
> ls
> get
> put
> mget *

$ wget -r ftp://user:pass@server.com/

```
