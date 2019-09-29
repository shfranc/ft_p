#include "client.h"

t_command		g_commands[NB_COMMAND] =
{
	{"cd", &cmd_cd, "change directory"},
	{"get", &cmd_get, "get a file"},
	{"help", &cmd_help, "display help"},
	{"ls", &cmd_ls, "list directroy"},
	{"pass", &cmd_pass, "switch passive/active mode"},
	{"put", &cmd_put, "put a file"},
	{"pwd", &cmd_pwd, "get current working directory"},
	{"quit", &cmd_quit, "exit the server"}
};

static void			promt(void)
{
	ft_putstr("ftp_client > ");
}

static void			loop_commands(char *cmd)
{
	int 				i;

	i = 0;
	while (i < NB_COMMAND && cmd)
	{
		if (ft_strncmp(cmd, g_commands[i].name,
			ft_strlen(g_commands[i].name)) == 0)
		{
			g_commands[i].run(cmd);
			return ;
		}
		i++;
	}
	printf("%s\n", INVALID_CMD);
}

void				get_user_input(void)
{
	int					ret_read;
	char				cmd[BUF_SIZE];

	while (1)
	{
		promt();
		ft_bzero(&cmd, BUF_SIZE);
		ret_read = read(STDIN_FILENO, &cmd, BUF_SIZE - 1);
		if (ret_read == -1)
			return (log_error("Failed to read from stdin"));
		cmd[ret_read - 1] = '\0';
		if (ft_strcmp(cmd, "exit") == 0
			|| ft_strcmp(cmd, "quit") == 0)
			return (cmd_quit(cmd));
		loop_commands(cmd);
	}
}
