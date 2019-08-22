#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <limits.h>
#include <time.h>
#include <stdlib.h>

# define OPTIONS		"d"
# define NB_CONNECT		42
# define BUF_SIZE		1024
# define NB_COMMAND		2
# define LS_PATH		"/bin/ls"
# define LS_OPTIONS		"-l"
# define LS_SEP			"--"

# define END_OF_MESG	"\r\n"
# define RESP_125		"125 Data channel already opened"
# define RESP_220		"220 Server is ready"
# define RESP_226		"226 Transfer done, closing the data channel"
# define RESP_425		"425 Error while openning the data channel"
# define RESP_500		"500 No such command"
# define RESP_550		"550 No such file or directory"

typedef struct			s_user
{
	int					control_sock;
	int					server_dtp_sock;
	int					data_sock;
	uint16_t			dtp_port;
}						t_user;

typedef void (f_command)(t_user *user, char **cmd);

typedef struct			s_command
{
	char				*name;
	f_command			*run;
}						t_command;

extern int				g_server_sock;
extern t_command		g_commands[NB_COMMAND];

/*
** SERVER
*/
int						create_server(uint16_t port);
uint16_t				get_port(char *port_str);
int						close_server(t_ex_ret ret);

/*
** CLIENT
*/
t_ex_ret				handle_clients(int server_sock);
int						get_client_commands(t_user *user);
void					send_to_user_ctrl(t_user *user, char *message);
void					close_data_channel(t_user *user);
/*
** CMD
*/
void					cmd_pasv(t_user *user, char **cmd);
void					cmd_list(t_user *user, char **cmd);

/*
** LOGS
*/
void					log_info(char *message);
void					log_client_command(char *cmd);
void					log_server_response(char *cmd);

/*
** TOOLS
*/
void					handle_sigint(int sig);
void					handle_child_signals(void);
int						ret_error(char *message);

#endif
