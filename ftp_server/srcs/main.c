#include "server.h"

int		ret_error(char *message)
{
	dprintf(STDERR_FILENO, "./server: %s\n", message);
	return (-1);
}

void	usage(char *prog_name)
{
	printf("%s: port\n", prog_name);
	exit(1);
}

int		create_server(int port)
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

int		main(int argc, char **argv)
{
	int					port;
	int					server_sock;
	int					client_sock;
	struct sockaddr_in	client_sin;
	unsigned int		client_sin_len;
	int					ret;
	char				buf[BUF_SIZE];
	int					pid;

	if (argc != 2)
		usage(argv[0]);
	port = ft_atoi(argv[1]);
	server_sock = create_server(port);
	while (1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_sin_len);
		if ((pid = fork()) == 0)
		{
			// child process
			while((ret = read(client_sock, &buf, BUF_SIZE - 1)) > 0)
			{
				buf[ret] = '\0';
				printf("socket: %d - pid: %d - recieved %d bytes: [%s]\n", client_sock, pid, ret, buf);
			}
			close(client_sock);
		}
		else
		{
			close(client_sock);
			// parent process
		}

	}

	close(server_sock);
	return (0);
}
