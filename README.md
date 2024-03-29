# FT_P
Implementing a server and a client in C, for file transfers over network with TCP/IP.
Both the client and the server are following the [RFC959](https://tools.ietf.org/html/rfc959) and [RFC2428](https://tools.ietf.org/html/rfc2428) (IPv6 extension).

![FTP schema](misc/ftp.png)

## Server

### Usage
```bash
cd ftp_server
make
./server 4242
```

### Commands
**Command** | **Description** | **Usage**
:---: | --- | ---
CWD | Change directory | `CWD <somewhere>`
LIST | List content of the directory, send the result in the data channel | `LIST <something>`
PASV | Passive mode, create a data channel and send IP + port to the client | `PASV`
EPSV | Extended passive mode, passive mode with ipv6 protocol | `EPSV`
PORT | Active mode, connect to the data channel the client already openned | `PORT <addr1>,<addr2>,<addr3>,<addr4>,<port1>,<port2>`
EPRT | Extended active mode, active mode with ipv6 protocol | `EPRT \|<protocol>\|<addr>\|<port>\|`
PWD | Send the path of the current working directory | `PWD`
RETR | Get and send a file to the client through the data channel | `RETR <file>`
STOR | Get and store a file the client has sent through the data channel | `STOR <file>`
TYPE | Set type for the tranfer (ascii or binary) | `TYPE <A\|I>`

### Options
```bash
usage: ./server [-46dv] port
	4	force protocol IPV4
	6	force protocol IPV6
	d	debug mode
	v	verbose mode
```

## Client

### Requirements
- rlwrap

### Usage
```bash
cd ftp_client
make
rlwrap ./client 127.0.0.1 4242
```

### Commands
#### User commands
**Command** | **Description** | **Usage**
:---: | --- | ---
ascii | switch to ascii mode | `ascii`
bin | switch to binary mode | `bin`
cd | change directory | `cd <somewhere>`
get | get a file | `get <file>`
help | display help | `help`
ls | list directroy | `ls <something>`
pass | switch passive/active mode | `pass [on\|off\|auto]`
put | put a file | `put <file>`
pwd | get current working directory | `pwd`
quit | exit the server | `quit`

#### Client commands
**Command** | **Description**
:---: | ---
PASS | Passive mode, connect to the data channel createdby the server
EPSV | Extended passive mode, passive mode with ipv6 protocol
PORT | Active mode, open the data channel so the server can connect
EPRT | Extended active mode, active mode with ipv6 protocol
