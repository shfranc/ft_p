#include "client.h"

void					cmd_ls(char *cmd)
{
	char	**params;
	char	*message;

	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	params = ft_strsplit(cmd, ' ');
	if (ft_tablen(params) > 2)
	{
		ft_freetab(&params);
		return (ft_putendl("usage: ls [directory]"));
	}
	if (open_data_channel() == FAILURE)
	{
		ft_freetab(&params);
		return (log_error("ls command aborted"));
	}
	message = params[1] ? ft_strjoin("LIST ", params[1]) : ft_strdup("LIST");
	send_to_server_ctrl(message);
	get_server_response();
	read_data_bin(STDOUT_FILENO);
	get_server_response();
	parse_response(g_client.resp);
	free(message);
	ft_freetab(&params);
	close_data_sock();
	close_server_dtp_sock();
}
