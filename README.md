# bbr-preload
A Linux-based experimental LD_PRELOAD library to enable TCP BBR for a specific process.

## Build Instructions
`make`

## Usage
`LD_PRELOAD=./libbbr.so curl www.google.com`

## Debug
`LD_PRELOAD=./libbbr.so strace -e trace=network curl -I www.google.com`

```
[root@foo bbr-preload]# LD_PRELOAD=./libbbr.so strace -e trace=network curl -I www.google.com
socket(AF_INET6, SOCK_DGRAM, IPPROTO_IP) = 3
socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) = 3
setsockopt(3, SOL_TCP, TCP_CONGESTION, [7496290], 4) = 0
setsockopt(3, SOL_TCP, TCP_NODELAY, [1], 4) = 0
setsockopt(3, SOL_SOCKET, SO_KEEPALIVE, [1], 4) = 0
setsockopt(3, SOL_TCP, TCP_KEEPIDLE, [60], 4) = 0
setsockopt(3, SOL_TCP, TCP_KEEPINTVL, [60], 4) = 0
connect(3, {sa_family=AF_INET, sin_port=htons(80), sin_addr=inet_addr("142.250.188.228")}, 16) = -1 EINPROGRESS (Operation now in progress)
getsockopt(3, SOL_SOCKET, SO_ERROR, [0], [4]) = 0
getpeername(3, {sa_family=AF_INET, sin_port=htons(80), sin_addr=inet_addr("142.250.188.228")}, [128 => 16]) = 0
getsockname(3, {sa_family=AF_INET, sin_port=htons(47818), sin_addr=inet_addr("10.0.0.14")}, [128 => 16]) = 0
sendto(3, "HEAD / HTTP/1.1\r\nHost: www.googl"..., 79, MSG_NOSIGNAL, NULL, 0) = 79
recvfrom(3, "HTTP/1.1 200 OK\r\nContent-Type: t"..., 102400, 0, NULL, NULL) = 1125
HTTP/1.1 200 OK
```
