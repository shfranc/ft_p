#include "server.h"

// int				exec_cmd(int client_sock, int client_data_sock, char *bin_path, char *options)
// {
// 	char	*argv[3];
// 	int		pid;
// 	int		waitstatus;
// 	int		ret;

// 	ft_putendl("exec cmd");
// 	if ((pid = fork()) < 0)
// 		return(ret_error("fork: error"));
// 	if (pid == 0)
// 	{
// 		// child process
// 		ft_putnbr_endl(client_data_sock);
// 		handle_child_signals();
// 		argv[0] = bin_path;
// 		argv[1] = options;
// 		argv[2] = NULL;
// 		if (dup2(client_data_sock, STDOUT_FILENO) == -1)
// 			ret_error("dup2: error");
// 		execv(bin_path, argv);
// 		perror("execv");
// 		ft_putendl("execv: error");
// 		exit(FAILURE);
// 	}
// 	else
// 	{
// 		// parent process
//         wait(&waitstatus);
//         ret = WEXITSTATUS(waitstatus);
// 		send(client_sock, "200 Command done\r\n", 19, 0);
// 	}
// 	return (ret);
// }

t_command		g_commands[NB_COMMAND] =
{
	{"PASV", &cmd_pasv}
};

void			loop_commands(t_user *user, char *cmd)
{
	int 				i;

	i = 0;
	while (i < NB_COMMAND)
	{
		if (ft_strcmp(cmd, g_commands[i].name) == 0)
		{
			log_info("command found");
			g_commands[i].run(user);
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
		loop_commands(user, buf);
	}
	if (ret == -1)
	{
		close(user->control_sock);
		return (ret_error("read: Failed to read from client"));
	}
	close(user->control_sock);
	return (SUCCESS);
}
