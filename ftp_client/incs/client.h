#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>

# define BUF_SIZE		1024

extern int				g_client_sock;

int						create_client(char *addr, int port);
int						send_commands_to_server(int client_sock);

void					handle_sigint(int sig);
int						ret_error(char *message);

#endif
