#ifndef SERVER_H
# define SERVER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <limits.h>
# include <time.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define OPTIONS		"d"
# define LS_PATH		"/bin/ls"
# define LS_OPTIONS		"-l"
# define LS_SEP			"--"
# define LOG_ERROR		"\033[1;31m[ERROR]\033[0m"
# define LOG_INFO		"\033[1;37m[INFO]\033[0m"
# define LOG_CTRL		"\033[1;36m[CTRL]\033[0m"
# define LOG_DATA		"\033[1;35m[DATA]\033[0m"

# define BUF_SIZE		1024
# define NB_CONNECT		42
# define NB_COMMAND		8

# define ROOT_ERR		"Impossible to get root directory."
# define ROOT_ERR_1		"No espace char `\\' in the root directory name."
# define RESP_125		"125 Data channel already opened"
# define RESP_200		"200 Active data connection established"
# define RESP_200_1		"200 New type set"
# define RESP_220		"220 Server is ready"
# define RESP_226		"226 Transfer done, closing the data channel"
# define RESP_250		"250 Change working directory done"
# define RESP_257		"257 \""
# define RESP_425		"425 Error while openning the data channel"
# define RESP_426		"426 Data channel is closed"
# define RESP_451		"451 Service interrupted"
# define RESP_500		"500 No such command"
# define RESP_501		"501 Error in params"
# define RESP_550		"550 No such file or directory"
# define RESP_550_1		"550 Path unavailable"
# define END_OF_MESG	"\r\n"


typedef struct 			s_server
{
	uint16_t			port;
	int					server_sock;
	char				*root_dir;
	int					tree_lvl;
}						t_server;

typedef struct			s_user
{
	char				*cwd;
	int					control_sock;
	int					server_dtp_sock;
	int					data_sock;
	uint16_t			dtp_port;
	char				*addr;
}						t_user;

typedef void (f_command)(t_user *user, char **cmd);

typedef struct			s_command
{
	char				*name;
	f_command			*run;
}						t_command;

extern t_server			g_server;
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
void					handle_clients(int server_sock);
void					get_client_commands(t_user *user);
void					send_to_user_ctrl(t_user *user, char *message);
void					close_data_channel(t_user *user);

/*
** CMD
*/
void					cmd_cwd(t_user *user, char **cmd);
void					cmd_list(t_user *user, char **cmd);
void					cmd_pasv(t_user *user, char **cmd);
void					cmd_port(t_user *user, char **cmd);
void					cmd_pwd(t_user *user, char **cmd);
void					cmd_retr(t_user *user, char **cmd);
void					cmd_stor(t_user *user, char **cmd);
void					cmd_type(t_user *user, char **cmd);

/*
** FILESYSTEM
*/
char					*get_virtual_absolute_path(t_user *user, char *path);
char					*convert_path_real_to_virtual(char *path);
char					*convert_path_virtual_to_real(char *path);
t_bool					is_valid_path(char *path);
void					update_user_cwd(t_user *user);
void					going_back_to_root_dir(t_user *user);

/*
** LOGS
*/
void					log_error(char *message);
void					log_info(char *message);
void					log_info_nbr(char *message, int nb);
void					log_info_str(char *desc, char *message);
void					log_client_command(char *cmd);
void					log_server_response(char *cmd);
void					log_data(char *cmd);
void					log_data_str(char *desc, char *message);
void					log_data_nbr(char *desc, int nb);
void					log_data_progress(int progress);

/*
** TOOLS
*/
int						get_next_line_crlf(int fd, char **line);
void					handle_sigint(int sig);
void					handle_child_signals(void);
int						ret_error(char *message);
t_ex_ret				ret_failure(char *message);
char					*ft_strdup2(char *s1, char *s2);

#endif
