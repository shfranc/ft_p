#include "client.h"

void					cmd_cd(char *cmd)
{
	char	**params;
	char	*message;

	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	printf("%s\n", cmd);
	params = ft_strsplit(cmd, ' ');
	if (ft_tablen(params) > 2)
		return (ft_putendl("usage: cd [dir]"));
	message = ft_strjoin("CWD ", params[1]);
	printf("%s\n", message);
	send_to_server_ctrl(message);
	get_server_response();
	if (parse_response(g_client.resp) == RESP_SUCCESS)
		printf("%s\n", g_client.resp);
	free(message);
	ft_freetab(&params);
}