#include "client.h"

int		ret_error(char *message)
{
	dprintf(STDERR_FILENO, "./client: %s\n", message);
	return (-1);
}

void	usage(char *prog_name)
{
	printf("usage: %s: addr port\n", prog_name);
	exit(1);
}

int		get_inet_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
		return (INADDR_ANY);
	else return (inet_addr(addr));
}

int		create_client(char *addr, int port)
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

int		main(int argc, char **argv)
{
	int					port;
	int					client_sock;
	int					ret;

	if (argc != 3)
		usage(argv[0]);
	port = ft_atoi(argv[2]);
	if ((client_sock = create_client(argv[1], port)) == -1)
		return (1);
	ret = write(client_sock, "bonjour\n", 8);
	if (ret == -1)
		return (ret_error("write: error"));
	close(client_sock);
	return (0);
}
