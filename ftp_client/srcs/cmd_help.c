#include "client.h"

void			cmd_help(char *cmd)
{
	int		i;

	if (ft_strcmp(cmd, "help") != 0)
		ft_putendl("usage: help");
	i = 0;
	while (i < NB_COMMAND)
	{
		printf("%-15s %s\n", g_commands[i].name, g_commands[i].desc);
		i++;
	}
}
