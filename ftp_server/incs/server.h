#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <limits.h>

# define NB_CONNECT		42
# define BUF_SIZE		1024

extern int				g_server_sock;

int						create_server(uint16_t port);
uint16_t				get_port(char *port_str);
int						close_server(t_ex_ret ret);
t_ex_ret				handle_clients(int server_sock);
int						get_client_commands(int client_sock);
void					handle_sigint(int sig);
void					handle_child_signals(void);
int						ret_error(char *message);

#endif
