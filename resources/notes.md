# FT_P

## Channels
-> Envoie
<- Reçoit

1. Control / Command
2. Data

## Open session:
Mode Anonyme:
1. Connected to 127.0.0.1.
2. 220 server ready
3. input command, lors de cette command
	a. EPSV -> on est en anonyme
	b. PASV activation du mode passif
	c. si echec, PORT + envoie du port ?
	d. LIST

Mode login:
1. Connected to 127.0.0.1.
2. 220 server ready
3. client request user + send USER user
331 Username ok, send password. dans tous les cas

## CMD
- EPSV: extended passive mode, mode anonyme ?
- PASV: passive mode
- PORT: data channel port
	PORT h1,h2,h3,h4,p1,p2 -> 8 bits séparés par des virgules
1er envoi: PASV ou PORT en actif
- LIST: ls -l

### LIST:
client:
```
ftp> ls
---> EPSV
530 Log in with USER and PASS first.
disabling epsv4 for this connection
---> PASV
530 Log in with USER and PASS first.
---> PORT 127,0,0,1,194,151
530 Log in with USER and PASS first.
---> LIST
530 Log in with USER and PASS first.
ftp>
```

server:
```
DEBUG:pyftpdlib:127.0.0.1:49800-[] <- EPSV
DEBUG:pyftpdlib:127.0.0.1:49800-[] -> 530 Log in with USER and PASS first.
DEBUG:pyftpdlib:127.0.0.1:49800-[] <- PASV
DEBUG:pyftpdlib:127.0.0.1:49800-[] -> 530 Log in with USER and PASS first.
DEBUG:pyftpdlib:127.0.0.1:49800-[] <- PORT 127,0,0,1,194,151
DEBUG:pyftpdlib:127.0.0.1:49800-[] -> 530 Log in with USER and PASS first.
DEBUG:pyftpdlib:127.0.0.1:49800-[] <- LIST
DEBUG:pyftpdlib:127.0.0.1:49800-[] -> 530 Log in with USER and PASS first.
```
