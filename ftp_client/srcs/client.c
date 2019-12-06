#include "client.h"

int				connect_to_server_sock(int data_sock, char *addr, uint16_t port)
{
	struct sockaddr_in		client_sin;
	struct sockaddr_in6		client_sin6;

	if (g_client.family == IP_V4)
	{
		client_sin.sin_family = AF_INET;
		client_sin.sin_port = htons(port);
		client_sin.sin_addr.s_addr = inet_addr(addr);
		if (connect(data_sock, (const struct sockaddr *)&client_sin,
			sizeof(client_sin)))
			return (ret_error("connect: error"));
	}
	else if (g_client.family == IP_V6)
	{
		client_sin6.sin6_family = AF_INET6;
		client_sin6.sin6_port = htons(port);
		if (inet_pton(AF_INET6, addr, &client_sin6.sin6_addr) == 0)
			return (ret_error("inet_pton: error"));
		if (connect(data_sock, (const struct sockaddr *)&client_sin6,
			sizeof(client_sin6)) == -1)
			return (ret_error("connect: error"));
	}
	return (0);
}

int			connect_to_server(char *addr, uint16_t port)
{
	int						sock;

	if (!(sock = create_socket(g_client.family)))
		return (-1);
	if (connect_to_server_sock(sock, addr, port) != 0)
		return (-1);
	return (sock);
}

int					close_ctrl_sock()
{
	if (g_client.ctrl_sock != -1 && close(g_client.ctrl_sock) != -1)
		return (SUCCESS);
	return (FAILURE);
}

int					close_data_sock()
{
	int		ret;

	ret = -1;
	if (g_client.data_sock != -1)
		ret = close(g_client.data_sock);
	g_client.data_sock = -1;
	return (ret == -1 ? FAILURE : SUCCESS);
}

int					close_server_dtp_sock()
{
	int		ret;

	ret = -1;
	if (g_client.server_dtp_sock != -1)
		ret = close(g_client.server_dtp_sock);
	g_client.server_dtp_sock = -1;
	return (ret == -1 ? FAILURE : SUCCESS);
}
