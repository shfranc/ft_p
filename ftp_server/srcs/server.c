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

int				create_server(uint16_t port)
{
	int						server_sock;
	struct protoent			*proto;
	struct sockaddr_in		server_sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (ret_error("getprotobyname: error"));
	if (!(server_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)))
		return (ret_error("socket: error"));
	server_sin.sin_family = AF_INET;
	server_sin.sin_port = htons(port);
	server_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server_sock, (const struct sockaddr *)&server_sin, sizeof(server_sin)))
		return (ret_error("bind: error"));
	listen(server_sock, NB_CONNECT);
	return (server_sock);
}

int					close_server(t_ex_ret ret)
{
	printf("Exiting...\n");
	if (g_server_sock == -1)
		exit(ret);
	if (close(g_server_sock) == -1)
		return (FAILURE);
	return (ret);
}
