#include "server.h"

static void			log_client_command(int bytes, char *cmd)
{
	ft_putstr("recieved ");
	ft_putnbr(bytes);
	ft_putstr(" bytes: [");
	ft_putstr(cmd);
	ft_putendl("]");
}

int				exec_cmd(int client_sock, char *cmd)
{
	char	*argv[2];
	int		pid;

	if ((pid = fork()) < 0)
		return(ret_error("fork: error"));
	if (pid == 0)
	{
		// child process
		handle_child_signals();
		argv[0] = cmd;
		argv[1] = NULL;
		dup2(client_sock, STDOUT_FILENO);
		execv(cmd, argv);
		perror("execv");
		printf("execv: error");
		exit(FAILURE);
	}
	else
	{
		// parent process
	}
	return (0);
}

int					get_client_commands(int client_sock)
{
	int					ret;
	char				buf[BUF_SIZE];

	while ((ret = read(client_sock, &buf, BUF_SIZE - 1)) > 0)
	{
		buf[ret] = '\0';
		log_client_command(ret, buf);
		if (ft_strcmp(buf, "pwd\n") == 0)
			exec_cmd(client_sock, "pwd");
		if (write(client_sock, "OK\n", 3) == -1)
			return (ret_error("write: Failed to write to client"));
	}
	if (ret == -1)
	{
		close(client_sock);
		return (ret_error("read: Failed to read from client"));
	}
	close(client_sock);
	return (SUCCESS);
}
