# FT_P
Implementing a server and a client in C, for file transfers over network with TCP/IP.

## Server

### Usage
```bash
cd ftp_server
make
./server 4242
```

## Client

### Usage
```bash
cd ftp_client
make
./client 127.0.0.1 4242
```

### Commands
- ls
- cd
- get
- put
- pwd
- quit
