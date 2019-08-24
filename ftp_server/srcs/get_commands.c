#include "server.h"

t_command		g_commands[NB_COMMAND] =
{
	{"CWD", &cmd_cwd},
	{"LIST", &cmd_list},
	{"PASV", &cmd_pasv},
	{"PORT", &cmd_port},
	{"PWD", &cmd_pwd},
	{"RETR", &cmd_retr},
	{"TYPE", &cmd_type}
};

void			loop_commands(t_user *user, char **cmd)
{
	int 				i;

	i = 0;
	while (i < NB_COMMAND && cmd[0])
	{
		if (ft_strcmp(cmd[0], g_commands[i].name) == 0)
		{
			g_commands[i].run(user, cmd);
			return ;
		}
		i++;
	}
	send_to_user_ctrl(user, RESP_500);
}

int				get_client_commands(t_user *user)
{
	int					ret;
	char				buf[BUF_SIZE];
	int 				client_data_sock;
	char				**cmd;

	client_data_sock = -1;
	while ((ret = read(user->control_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		if (buf[ret - 2] == '\r')
			buf[ret - 2] = '\0';
		else if (buf[ret - 1] == '\n')
			buf[ret - 1] = '\0';
		else
			buf[ret] = '\0';
		log_client_command(buf);
		if (ft_strcmp(buf, "QUIT") == 0)
			break ;
		cmd = ft_strsplit(buf, ' ');
		loop_commands(user, cmd);
		ft_freetab(&cmd);
	}
	if (ret == -1)
	{
		close(user->control_sock);
		return (ret_error("read: Failed to read from client"));
	}
	close(user->control_sock);
	return (SUCCESS);
}
