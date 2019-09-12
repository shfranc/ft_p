#include "server.h"

uint16_t			get_port(char *port_str)
{
	uint32_t	port;

	if (!ft_isnumber(port_str))
	{
		dprintf(STDERR_FILENO, "Unknown port: %s\n", port_str);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port < 1024 || port > USHRT_MAX)
	{
		dprintf(STDERR_FILENO, "Port range not valid: %s\n", port_str);
		return (0);
	}
	return ((uint16_t)port);
}

int				create_socket(int family)
{
	int						server_sock;
	struct protoent			*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (family == IP_V4)
	{
		if (!(server_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
			return (ret_error("socket inet: error"));
		return (server_sock);
	}
	else if (family == IP_V6)
	{
		if (!(server_sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)))
			return (ret_error("socket inet6: error"));
		return (server_sock);
	}
	return (0);
}

int				bind_server(int server_sock, uint16_t port)
{
	struct sockaddr_in		server_sin;
	struct sockaddr_in6		server_sin6;

	if (g_server.family == IP_V4)
	{
		server_sin.sin_family = AF_INET;
		server_sin.sin_port = htons(port);
		server_sin.sin_addr.s_addr = INADDR_ANY;
		if (bind(server_sock, (const struct sockaddr *)&server_sin,
			sizeof(server_sin)) != 0)
			return (ret_error("bind: error"));
	}
	else if (g_server.family == IP_V6)
	{
		server_sin6.sin6_family = AF_INET6;
		server_sin6.sin6_port = htons(port);
		server_sin6.sin6_addr = in6addr_any;
		if (bind(server_sock, (const struct sockaddr *)&server_sin6,
			sizeof(server_sin6)) != 0)
			return (ret_error("bind: error"));
	}
	return (0);
}

int				create_server(uint16_t port)
{
	int						server_sock;

	if (!(server_sock = create_socket(g_server.family)))
		return (-1);
	if (bind_server(server_sock, port) != 0)
		return (-1);
	listen(server_sock, NB_CONNECT);
	return (server_sock);
}

int					close_server(t_ex_ret ret)
{
	printf("Exiting...\n");
	if (g_server.server_sock == -1)
		exit(ret);
	if (close(g_server.server_sock) == -1)
		return (FAILURE);
	return (ret);
}
