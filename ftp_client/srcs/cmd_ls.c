#include "client.h"

void					cmd_ls(char *cmd)
{
	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));	
	printf("%s\n", cmd);
}
