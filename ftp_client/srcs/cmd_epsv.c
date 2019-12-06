#include "client.h"

static char		**parse_response_epsv(char *msg)
{
	char	**details;
	char	*start;
	char	*end;
	char	*tmp;

	start = ft_strchr(msg, '(');
	end = ft_strrchr(msg, ')');
	tmp = ft_strsub(msg, start - msg + 1, end - start -1);
	details = ft_strsplit(tmp, '|');
	free(tmp);
	return (details);
}

static int			connect_to_DTP_server(uint16_t port)
{
	int						data_sock;

	if (!(data_sock = create_socket(g_client.family)))
		return (-1);
	if (connect_to_server_sock(data_sock, g_client.addr, port) != 0)
		return (-1);
	return (data_sock);
}

void					cmd_epsv()
{
	char		**details;

	log_info("Extended passive mode");
	send_to_server_ctrl("EPSV");
	get_server_response();
	if (parse_response(g_client.resp) != RESP_SUCCESS)
		return (log_error("Failed to connect to the data channel."));
	details = parse_response_epsv(g_client.resp);
	ft_puttab(details);
	g_client.data_port = ft_atoi(details[0]);
	log_info_msg("addr", g_client.addr);
	log_info_nb("port", g_client.data_port);
	if ((g_client.data_sock = connect_to_DTP_server(g_client.data_port)) == -1)
		return (log_error("Failed to connect to the data channel."));
	ft_freetab(&details);
}
