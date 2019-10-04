#include "client.h"

void					cmd_put(char *cmd)
{
	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));	
	printf("%s\n", cmd);
}
