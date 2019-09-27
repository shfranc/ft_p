#include "client.h"

void					cmd_pwd(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") != 0)
		ft_putendl("usage: pwd");
	send_to_server_ctrl("PWD");
	get_server_response();
	// ft_putendl(g_client.resp);
}
