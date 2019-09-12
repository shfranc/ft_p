# FT_P
Implementing a server and a client in C, for file transfers over network with TCP/IP.

## Server

### Usage
```bash
cd ftp_server
make
./server 4242
```

### Commands
- CWD: change directory
- LIST: list content of the directory, send the result in the data channel
- PASV: Passive mode, create a data channel and send IP + port to the client
- EPSV: Extended passive mode, passive mode with ipv6 protocol
- PORT: Active mode, connect to the data channel the client already openned
- EPRT: Extended active mode, active mode with ipv6 protocol
- PWD: send the path of the current working directory
- RETR: get and send a file to the client through the data channel
- STOR: get and store a file the client has sent through the data channel
- TYPE: set type for the tranfer (ascii or binary)

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
