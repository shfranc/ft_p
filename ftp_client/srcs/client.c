#include "client.h"

static int		get_inet_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
		return (INADDR_ANY);
	else return (inet_addr(addr));
}

int				connect_to_server(char *addr, int port)
{
	int						client_sock;
	struct protoent			*proto;
	struct sockaddr_in		client_sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(client_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	client_sin.sin_family = AF_INET;
	client_sin.sin_port = htons(port);
	client_sin.sin_addr.s_addr = get_inet_addr(addr);
	if (connect(client_sock, (const struct sockaddr *)&client_sin,
		sizeof(client_sin)))
		return (ret_error("Connection refused"));
	return (client_sock);
}

int				close_ctrl_sock()
{
	if (g_client.ctrl_sock != -1 && close(g_client.ctrl_sock) != -1)
		return (SUCCESS);
	return (FAILURE);
}

int				close_data_sock()
{
	int		ret;

	ret = -1;
	if (g_client.data_sock != -1)
		ret = close(g_client.data_sock);
	g_client.data_sock = -1;
	return (ret == -1 ? FAILURE : SUCCESS);
}
