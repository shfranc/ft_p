#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>
# include <time.h>
# include <limits.h>
# include <netinet/in.h>

# define IP_V4			AF_INET
# define IP_V6			AF_INET6

# define BUF_SIZE		1024
# define NB_COMMAND		8

# define INVALID_CMD	"?Invalid command."
# define LOG_ERROR		"\033[1;31m[ERROR]\033[0m"
# define LOG_INFO		"\033[1;37m[INFO]\033[0m"
# define LOG_CTRL		"\033[1;36m[CTRL]\033[0m"
# define LOG_DATA		"\033[1;35m[DATA]\033[0m"

# define RESP_220		"220 Server is ready"
# define END_OF_MESG	"\r\n"

typedef enum			e_reply
{
	RESP_SUCCESS,
	RESP_FAILURE,
	RESP_ERROR
}						t_reply;

typedef enum			e_pass
{
	AUTO,
	ON,
	OFF
}						t_pass;

typedef struct 			s_client
{
	t_bool				handcheck;
	uint8_t				family;
	char				*addr;
	uint16_t			port;
	uint16_t			data_port;
	t_pass				pass;
	int					ctrl_sock;
	int					server_dtp_sock;
	int					data_sock;
	char				*cwd;
	char				*resp;
}						t_client;

typedef void (f_command)(char *);

typedef struct			s_command
{
	char				*name;
	f_command			*run;
	char				*desc;
}						t_command;

t_client				g_client;
extern t_command		g_commands[NB_COMMAND];

/*
** CLIENT
*/
int						connect_to_server_sock(int data_sock, char *addr, uint16_t port);
int						connect_to_server(char *addr, uint16_t port);
int						close_ctrl_sock();

void					get_user_input(void);
void					send_to_server_ctrl(char *message);
void					get_server_response(void);
t_reply					parse_response(char *response);

/*
** DATA CHANNEL
*/
t_ex_ret				open_data_channel();
int						close_data_sock();
int						close_server_dtp_sock();
void					cmd_epsv();
void					cmd_pasv();
void					cmd_port();
uint16_t				get_random_port(void);
int						create_socket(int family);
int						bind_server(int server_sock, uint16_t port);

/*
** READER
*/
void					read_data_bin();

/*
** CMD
*/
void					cmd_ls(char *cmd);
void					cmd_cd(char *cmd);
void					cmd_get(char *cmd);
void					cmd_help(char *cmd);
void					cmd_pass(char *cmd);
void					cmd_put(char *cmd);
void					cmd_pwd(char *cmd);
void					cmd_quit(char *cmd);

/*
** LOGS
*/
void					log_info(char *message);
void					log_info_msg(char *desc, char *message);
void					log_info_nb(char *desc, int nb);
void					log_error(char *message);
void					log_client_command(char *cmd);
void					log_server_response(char *cmd);

/*
** TOOLS
*/
void					handle_sigint(int sig);
int						ret_error(char *message);

#endif
