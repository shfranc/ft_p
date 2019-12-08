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

static void			prompt(void)
{
	printf("ftp_client:%s %s > ", g_client.cwd,
		parse_response(g_client.resp) == SUCCESS ? "✓" : "✗");
	fflush(stdout);
}

static void			loop_commands(char *input)
{
	const char			*separator = " \t\0";
	int 				i;

	i = 0;
	while (i < NB_COMMAND && input)
	{
		if (ft_strncmp(input, g_commands[i].name,
			ft_strlen(g_commands[i].name)) == 0
			&& ft_strchr(separator, input[ft_strlen(g_commands[i].name)]))
			return (g_commands[i].run(input));
		i++;
	}
	printf("%s\n", INVALID_CMD);
	g_client.resp = ft_strdup(RESP_500);
}

void				get_user_input(void)
{
	int					ret_read;
	char				input[BUF_SIZE];

	while (1)
	{
		prompt();
		ft_bzero(&input, BUF_SIZE);
		ret_read = read(STDIN_FILENO, &input, BUF_SIZE - 1);
		if (ret_read == -1)
			return (log_error("Failed to read from stdin"));
		input[ret_read - 1] = '\0';
		if (ft_strcmp(input, "exit") == 0
			|| ft_strcmp(input, "quit") == 0)
			return (cmd_quit(input));
		loop_commands(input);
	}
}
