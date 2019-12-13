#include "client.h"

void		get_file(char *filename)
{
	int			fd;
	struct stat buf_stat;
	int			ret;

	ret = 0;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0 || fstat(fd, &buf_stat) < 0)
		return(log_error("Failed to create a file"));
	log_info_msg("Receiving", filename);
	if (g_client.data_type == ASCII)
		ret = read_data_ascii(fd);
	else if (g_client.data_type == BIN)
		ret = read_data_bin(fd);
	if (ret >= 0)
		printf("%d bytes received\n", ret);
}

void					cmd_get(char *cmd)
{
	char	**params;
	char	*message;
	char	*filename;

	if (g_client.ctrl_sock == -1)
		return (ft_putendl("Not connected."));
	params = ft_strsplit(cmd, ' ');
	if (ft_tablen(params) < 2 || ft_tablen(params) > 3)
	{
		ft_freetab(&params);
		return (ft_putendl("usage: get source [dest]"));
	}
	if (open_data_channel() == FAILURE)
	{
		ft_freetab(&params);
		return (log_error("get command aborted"));
	}
	message = ft_strjoin("RETR ", params[1]);
	send_to_server_ctrl(message);
	get_server_response();
	filename = params[2] ? params[2] : params[1];
	get_file(filename);
	get_server_response();
	parse_response(g_client.resp);
	free(message);
	ft_freetab(&params);
	close_data_sock();
	close_server_dtp_sock();
}
