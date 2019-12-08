#include "client.h"

void					cmd_cd(char *cmd)
{
	char	**params;
	char	*message;

	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	params = ft_strsplit(cmd, ' ');
	if (ft_tablen(params) != 2)
		return (ft_putendl("usage: cd directory"));
	message = ft_strjoin("CWD ", params[1]);
	send_to_server_ctrl(message);
	get_server_response();
	if (parse_response(g_client.resp) == SUCCESS)
		cmd_pwd("pwd");
	free(message);
	ft_freetab(&params);
}
