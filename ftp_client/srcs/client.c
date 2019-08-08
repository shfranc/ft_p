#include "client.h"

static int		get_inet_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
		return (INADDR_ANY);
	else return (inet_addr(addr));
}

int				create_client(char *addr, int port)
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
	if (connect(client_sock, (const struct sockaddr *)&client_sin, sizeof(client_sin)))
		return (ret_error("connect: error"));
	return (client_sock);
}
